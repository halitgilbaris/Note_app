#pragma once
#include <vector>
#include <atomic>
#include "note.h" 


extern std::vector<Note> notes;
extern std::atomic<bool> g_running;
extern std::atomic<bool> g_save_finished;
extern int g_note_counter; 

void file_save(const std::vector<Note> &notes);
void load_file(std::vector<Note> &notes);
