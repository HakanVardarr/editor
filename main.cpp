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
            if (input.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT && input.Event.KeyEvent.bKeyDown)
            {
                if (currentCursorPosition.X + 1 < terminalSize.X)
                {
                    currentCursorPosition.X += 1;
                }
            }
            else if (input.Event.KeyEvent.wVirtualKeyCode == VK_LEFT && input.Event.KeyEvent.bKeyDown)
            {
                if (currentCursorPosition.X - 1 > 0)
                {
                    currentCursorPosition.X -= 1;
                }
            }

            else if (input.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE && input.Event.KeyEvent.bKeyDown)
            {
                terminal.Exit();
            }
        }

        terminal.MoveCursor(currentCursorPosition);
        terminal.UpdateCursor(currentCursorPosition);
    }

    return 0;
}