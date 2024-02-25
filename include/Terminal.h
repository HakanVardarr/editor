#ifndef TERMINAL_H
#define TERMINAL_H

#ifdef _WIN32

#include "Windows.h"
#include <string>

class Terminal
{
public:
    Terminal();
    Terminal(const Terminal &) = delete;
    Terminal &operator=(const Terminal &) = delete;
    Terminal(Terminal &&) = delete;
    Terminal &operator=(Terminal &&) = delete;
    ~Terminal();

private:
};

#else
#error ONLY SUPPORTS WINDOWS FOR NOW
#endif

#endif