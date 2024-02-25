use super::{errors::EditorError, log, map_error};
use crossterm::{
    cursor,
    event::{read, Event, KeyCode, KeyEventKind},
    execute, queue, style, terminal,
};
use std::{
    fmt::Display,
    fs::{File, OpenOptions},
    io::{stdout, Stdout, Write},
};

enum Action {
    MoveRight,
    MoveLeft,
    MoveDown,
    MoveUp,
    Exit,
    Resize(u16, u16),
}

enum Mode {
    Normal,
    Insert,
}

impl Display for Mode {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            &Mode::Insert => write!(f, "Insert"),
            &Mode::Normal => write!(f, "Normal"),
        }
    }
}

pub struct Editor {
    log_file: File,
    stdout: Stdout,
    size: (u16, u16),
    cursor_pos: (u16, u16),
    halt: bool,
}

impl Editor {
    pub fn new() -> Result<Self, EditorError> {
        std::panic::set_hook(Box::new(|_panic_info| {
            _ = execute!(stdout(), terminal::LeaveAlternateScreen);
            _ = terminal::disable_raw_mode();
        }));

        let mut stdout = stdout();
        let log_file = OpenOptions::new()
            .read(true)
            .write(true)
            .create(true)
            .truncate(true)
            .open("editor.log")
            .unwrap();

        map_error!(terminal::enable_raw_mode(), EditorError::SetupError)?;
        map_error!(
            execute!(stdout, terminal::EnterAlternateScreen),
            EditorError::SetupError
        )?;
        map_error!(
            execute!(stdout, terminal::Clear(terminal::ClearType::All)),
            EditorError::SetupError
        )?;

        let size = map_error!(terminal::size(), EditorError::SetupError)?;

        Ok(Self {
            log_file,
            stdout,
            size,
            cursor_pos: (0, 0),
            halt: false,
        })
    }

    pub fn run(&mut self) -> Result<(), EditorError> {
        while !self.halt {
            if let Some(action) = self.match_event(map_error!(read(), EditorError::ReadError)?) {
                self.match_action(action)?;
            }

            map_error!(
                queue!(
                    self.stdout,
                    cursor::MoveTo(0, self.size.1 - 2),
                    style::Print(Mode::Normal)
                ),
                EditorError::CursorMoveError
            )?;

            map_error!(
                queue!(
                    self.stdout,
                    cursor::MoveTo(self.cursor_pos.0, self.cursor_pos.1)
                ),
                EditorError::CursorMoveError
            )?;

            self.stdout.flush().unwrap();
        }

        Ok(())
    }

    fn match_action(&mut self, action: Action) -> Result<(), EditorError> {
        match action {
            Action::Exit => {
                self.halt = true;
            }
            Action::MoveLeft => {
                self.cursor_pos.0 = self.cursor_pos.0.saturating_sub(1);
            }
            Action::MoveRight => {
                log!(self.log_file, "{} {}", self.cursor_pos.0, self.size.0);
                if self.cursor_pos.0 < self.size.0 {
                    self.cursor_pos.0 += 1;
                }
            }
            Action::MoveDown => {
                if self.cursor_pos.1 < self.size.1 - 2 {
                    self.cursor_pos.1 += 1;
                }
            }
            Action::MoveUp => {
                self.cursor_pos.1 = self.cursor_pos.1.saturating_sub(1);
            }
            Action::Resize(width, height) => {
                self.size = (width, height);
                map_error!(
                    queue!(
                        self.stdout,
                        cursor::MoveTo(0, 0),
                        terminal::Clear(terminal::ClearType::All)
                    ),
                    EditorError::SetupError
                )?;
            }
        }
        Ok(())
    }

    fn match_event(&self, event: Event) -> Option<Action> {
        match event {
            Event::Key(event) => {
                if event.kind == KeyEventKind::Press {
                    match event.code {
                        KeyCode::Char('q') => Some(Action::Exit),
                        KeyCode::Right | KeyCode::Char('l') => Some(Action::MoveRight),
                        KeyCode::Left | KeyCode::Char('h') => Some(Action::MoveLeft),
                        KeyCode::Up | KeyCode::Char('j') => Some(Action::MoveUp),
                        KeyCode::Down | KeyCode::Char('k') => Some(Action::MoveDown),
                        _ => None,
                    }
                } else {
                    None
                }
            }
            Event::Resize(width, height) => Some(Action::Resize(width, height)),
            _ => None,
        }
    }
}

impl Drop for Editor {
    fn drop(&mut self) {
        _ = execute!(self.stdout, terminal::LeaveAlternateScreen);
        _ = terminal::disable_raw_mode();
    }
}
