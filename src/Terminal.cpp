#include "Terminal.h"
#include <iostream>

#ifdef _WIN32
Terminal::Terminal()
{
}

Terminal::~Terminal()
{
}

#else
#error ONLY SUPPORTS WINDOWS FOR NOW
#endif