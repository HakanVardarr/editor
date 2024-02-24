#include <iostream>
#include <Windows.h>

void ErrorExit(LPCSTR errorMessage)
{
    std::cerr << errorMessage << std::endl;
    exit(EXIT_FAILURE);
}

class Terminal
{
public:
    Terminal()
    {
        hStdin = GetStdHandle(STD_INPUT_HANDLE);
        if (hStdin == INVALID_HANDLE_VALUE)
        {
                }
    }

private:
    HANDLE hStdin, hStdout;
};

int main()
{
    DWORD fdwSaveOldMode, fdwMode;
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle");

    if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
        ErrorExit("GetConsoleMode");

    fdwMode = ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode))
        ErrorExit("SetConsoleMode");

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle");

    INPUT_RECORD irInBuf;
    DWORD dwNumRead;

    COORD cPos = {0, 0};

    while (true)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
            ErrorExit("GetConsoleScreenBufferInfo");

        DWORD written = 0;
        PCWSTR sequence = L"\x1b[2J";
        if (!WriteConsoleW(hStdout, sequence, (DWORD)wcslen(sequence), &written, NULL))
        {
            SetConsoleMode(hStdout, fdwSaveOldMode);
            ErrorExit("WriteConsoleW");
        }

        if (!SetConsoleCursorPosition(hStdout, cPos))
        {
            SetConsoleMode(hStdout, fdwSaveOldMode);
            ErrorExit("SetConsoleCursorPosition");
        }

        if (!ReadConsoleInput(hStdin, &irInBuf, 1, &dwNumRead))
        {
            SetConsoleMode(hStdout, fdwSaveOldMode);
            ErrorExit("ReadConsoleInput");
        }

        if (dwNumRead != 1)
            continue;

        if (irInBuf.EventType == KEY_EVENT)
        {
            if (irInBuf.Event.KeyEvent.bKeyDown)
            {
                if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                    break;

                if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT)
                {
                    if (cPos.X + 1 < csbi.dwSize.X)
                    {
                        cPos.X += 1;
                    }
                }
            }
        }
    }

    SetConsoleMode(hStdout, fdwSaveOldMode);

    return 0;
}