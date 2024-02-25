use editor::Editor;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut editor = Editor::new()?;
    editor.run()?;

    Ok(())
}
