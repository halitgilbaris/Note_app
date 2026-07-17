#pragma once

#include <vector>
#include <string>
#include <windows.h>

extern volatile bool g_running;
extern volatile bool g_save_finished;

void file_save(const std::vector<std::string> &notes);
BOOL WINAPI ConsoleHandler(DWORD signal);
void load_file(std::vector<std::string> &notes);
