#ifndef TERMINAL_H
#define TERMINAL_H

#ifdef _WIN32

#include "Windows.h"
#include <string>

#define CLEANUP_AND_RETURN(message) \
    Cleanup(message);               \
    bRun = false;                   \
    return;

#define CLEANUP_AND_RETURN_FALSE(message) \
    Cleanup(message);                     \
    return false;

class Terminal
{
public:
    Terminal();
    Terminal(const Terminal &) = delete;
    Terminal &operator=(const Terminal &) = delete;
    Terminal(Terminal &&) = delete;
    Terminal &operator=(Terminal &&) = delete;
    ~Terminal();

    VOID Exit();
    VOID UpdateCursor(COORD pos);

    BOOL Clear();
    BOOL Run();
    BOOL MoveCursor(COORD pos);
    BOOL Write(std::string content, DWORD *written);

    COORD CursorPosition();
    COORD TerminalSize();

    INPUT_RECORD ReadInput();

private:
    HANDLE hStdin, hStdout;
    DWORD dwOldMode, dwMode;
    BOOL bRun = true;
    COORD cPos = {0, 0}, cSize;

    VOID Cleanup(std::string sMessage);
    HANDLE CreateConsoleBuffer();
};

#else
#error ONLY SUPPORTS WINDOWS FOR NOW
#endif

#endif