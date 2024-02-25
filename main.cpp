#include "Terminal.h"

int main()
{

    Terminal terminal;

    if (!terminal.Run())
        return 1;

    if (!terminal.Clear())
        return 1;

    while (terminal.Run())
    {
        COORD currentCursorPosition = terminal.CursorPosition();
        COORD terminalSize = terminal.TerminalSize();

        INPUT_RECORD input = terminal.ReadInput();

        if (input.EventType == KEY_EVENT)
        {

            if (input.Event.KeyEvent.uChar.AsciiChar == 'q' && input.Event.KeyEvent.bKeyDown)
            {
                terminal.Exit();
            }
        }

        terminal.MoveCursor(currentCursorPosition);
        terminal.UpdateCursor(currentCursorPosition);
    }

    return 0;
}