#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <vector>
#include <thread>
#include <atomic>
#include <algorithm>
#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#ifdef _WIN32
#include <windows.h>
#include <direct.h> 
#endif

#include "folder.h"
#include "note.h"





std::vector<Note> notes;
std::atomic<bool> g_running(true);
std::atomic<bool> g_save_finished(false);
int g_note_counter = 1;

namespace {
std::string get_notes_folder_path() {
    const char* userProfile = std::getenv("USERPROFILE");
    const char* homeDir = std::getenv("HOME");
    std::string base = userProfile ? userProfile : (homeDir ? homeDir : ".");

#ifdef _WIN32
    return base + "\\Note_app";
#else
    return base + "/Note_app";
#endif
}
}

void file_save(const std::vector<Note> &notes){
    std::string folderPath = get_notes_folder_path();
    std::filesystem::create_directories(folderPath);

#ifdef _WIN32
    std::string saveSystem = folderPath + "\\saves.txt";
#else
    std::string saveSystem = folderPath + "/saves.txt";
#endif

    std::ofstream savefile(saveSystem);

    if(savefile.is_open()){
        savefile << "__next_id__=" << g_note_counter << "\n";
        for(const auto& x : notes){
            savefile << x.id << "|||" 
                    << x.title << "|||" 
                    << x.content << "|||" 
                    << x.createdAt << "\n";
        }
        savefile.close();
    }
}





void load_file(std::vector<Note> &notes){
    g_save_finished = false;

    std::string folderPath = get_notes_folder_path();
#ifdef _WIN32
    std::string saveSystem = folderPath + "\\saves.txt";
#else
    std::string saveSystem = folderPath + "/saves.txt";
#endif

    std::ifstream loadFile(saveSystem);
    if(!loadFile.is_open()){
        g_note_counter = 1;
        g_save_finished = true;
        return;
    }

    std::string line;
    notes.clear();
    int loaded_next_id = 1;
    int highest_id = 0;

    while(std::getline(loadFile, line)){
        if(line.rfind("__next_id__=", 0) == 0){
            loaded_next_id = std::stoi(line.substr(std::string("__next_id__=").size()));
            continue;
        }

        std::vector<std::string> tokens;
        size_t pos = 0;
        std::string token;
        std::string delimiter = "|||";

        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + delimiter.length());
        }
        tokens.push_back(line);

        if(tokens.size() == 4){
            Note loadedNote;
            loadedNote.id = std::stoi(tokens[0]);
            loadedNote.title = tokens[1];
            loadedNote.content = tokens[2];
            loadedNote.createdAt = tokens[3];
            notes.push_back(loadedNote);
            highest_id = std::max(highest_id, loadedNote.id);
        }
    }

    if(notes.empty()){
        g_note_counter = 1;
    } else {
        g_note_counter = std::max(loaded_next_id, highest_id + 1);
    }

    loadFile.close();
    g_save_finished = true;
}
