use thiserror::Error;

#[derive(Error, Debug)]
pub enum EditorError {
    #[error(
        "\x1b[31m\x1b[1merror: \x1b[0m\x1b[1mError ocured when setting up the Editor.\x1b[22m"
    )]
    SetupError,
    #[error("\x1b[31m\x1b[1merror: \x1b[0m\x1b[1mCannot move cursor.\x1b[22m")]
    CursorMoveError,
    #[error("\x1b[31m\x1b[1merror: \x1b[0m\x1b[1mCannot read events.\x1b[22m")]
    ReadError,
}
