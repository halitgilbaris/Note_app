#pragma once

#include <vector>
#include <string>
#include <windows.h>

extern volatile bool g_running;

void file_save(const std::vector<std::string> &notes);
BOOL WINAPI ConsoleHandler(DWORD signal);
