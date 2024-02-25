#ifndef TERMINAL_H
#define TERMINAL_H

#ifdef _WIN32

#include "Windows.h"
#include <string>
#include <iostream>

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

    BOOL Clear();
    BOOL Run();

private:
    HANDLE hStdin, hStdout;
    DWORD dwOldMode, dwMode;
    BOOL bRun = true;
    COORD cPos = {0, 0}, cSize;

    VOID Cleanup(std::string sMessage);
};

#else
#error ONLY SUPPORTS WINDOWS FOR NOW
#endif

#endif