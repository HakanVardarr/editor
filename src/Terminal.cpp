#include "Terminal.h"

#ifdef _WIN32
Terminal::Terminal()
{
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
    {
        CLEANUP_AND_RETURN("Failed to get stdin handle.");
    }

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE)
    {
        CLEANUP_AND_RETURN("Failed to get stdout handle.");
    }

    if (!GetConsoleMode(hStdin, &dwOldMode))
    {
        CLEANUP_AND_RETURN("Failed to get console mode.");
    }

    dwMode = dwOldMode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT);
    if (!SetConsoleMode(hStdin, dwMode))
    {
        CLEANUP_AND_RETURN("Failed to set console mode.");
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
    {
        CLEANUP_AND_RETURN("Failed to get console screen info");
    }

    cSize = csbi.dwSize;
}

Terminal::~Terminal()
{
    SetConsoleMode(hStdin, dwOldMode);
}

VOID Terminal::Exit()
{
    bRun = false;
}

VOID Terminal::UpdateCursor(COORD pos)
{
    cPos = pos;
}

BOOL Terminal::Clear()
{
    if (!SetConsoleCursorPosition(hStdout, {0, 0}))
    {
        CLEANUP_AND_RETURN_FALSE("Cannot set cursor position");
    }

    DWORD written = 0;
    PCWSTR sequence = L"\x1b[2J";
    if (!WriteConsoleW(hStdout, sequence, (DWORD)wcslen(sequence), &written, NULL))
    {
        CLEANUP_AND_RETURN_FALSE("Cannot write to console.");
    }

    return true;
}

BOOL Terminal::Run()
{
    return bRun;
}

BOOL Terminal::MoveCursor(COORD pos)
{
    if (!SetConsoleCursorPosition(hStdout, pos))
    {
        CLEANUP_AND_RETURN_FALSE("Cannot set cursor position");
    }
}

COORD Terminal::CursorPosition() const
{
    return cPos;
}

COORD Terminal::TerminalSize() const
{
    return cSize;
}

INPUT_RECORD Terminal::ReadInput()
{
    DWORD cNumRead;
    INPUT_RECORD irInBuf[1];
    if (!ReadConsoleInput(
            hStdin,
            irInBuf,
            1,
            &cNumRead))
    {
    }

    return irInBuf[0];
}

VOID Terminal::Cleanup(std::string sMessage)
{
    std::cerr << sMessage << std::endl;
    SetConsoleMode(hStdin, dwOldMode);
}

#else
#error ONLY SUPPORTS WINDOWS FOR NOW
#endif