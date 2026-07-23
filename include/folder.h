#pragma once
#include <vector>
#include <atomic>
#include "note.h" 


extern std::atomic<bool> g_running;
extern std::atomic<bool> g_save_finished;

void file_save(const std::vector<Note> &notes, int current_i);
void load_file(std::vector<Note> &notes, int &current_i);
