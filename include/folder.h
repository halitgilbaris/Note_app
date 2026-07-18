#pragma once

#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

extern volatile bool g_running;
extern volatile bool g_save_finished;

void file_save(const std::vector<std::string> &notes);
#ifdef _WIN32
BOOL WINAPI ConsoleHandler(DWORD signal);
#endif
void load_file(std::vector<std::string> &notes);
