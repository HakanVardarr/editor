#include "Terminal.h"

int main()
{

    Terminal terminal;

    if (!terminal.Run())
        return 1;

    while (terminal.Run())
    {
        if (!terminal.Clear())
            return 1;

        terminal.Exit();
    }

    // INPUT_RECORD irInBuf;
    // DWORD dwNumRead;

    // COORD cPos = {0, 0};

    // while (true)
    // {
    //     CONSOLE_SCREEN_BUFFER_INFO csbi;
    //     if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
    //         ErrorExit("GetConsoleScreenBufferInfo");

    //     DWORD written = 0;
    //     PCWSTR sequence = L"\x1b[2J";
    //     if (!WriteConsoleW(hStdout, sequence, (DWORD)wcslen(sequence), &written, NULL))
    //     {
    //         SetConsoleMode(hStdout, fdwSaveOldMode);
    //         ErrorExit("WriteConsoleW");
    //     }

    //     if (!SetConsoleCursorPosition(hStdout, cPos))
    //     {
    //         SetConsoleMode(hStdout, fdwSaveOldMode);
    //         ErrorExit("SetConsoleCursorPosition");
    //     }

    //     if (!ReadConsoleInput(hStdin, &irInBuf, 1, &dwNumRead))
    //     {
    //         SetConsoleMode(hStdout, fdwSaveOldMode);
    //         ErrorExit("ReadConsoleInput");
    //     }

    //     if (dwNumRead != 1)
    //         continue;

    //     if (irInBuf.EventType == KEY_EVENT)
    //     {
    //         if (irInBuf.Event.KeyEvent.bKeyDown)
    //         {
    //             if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
    //                 break;

    //             if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT)
    //             {
    //                 if (cPos.X + 1 < csbi.dwSize.X)
    //                 {
    //                     cPos.X += 1;
    //                 }
    //             }
    //         }
    //     }
    // }

    // SetConsoleMode(hStdout, fdwSaveOldMode);

    return 0;
}