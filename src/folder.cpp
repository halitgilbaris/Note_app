#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <vector>
#include <thread>
#include <atomic>

#ifdef _WIN32
#include <windows.h>
#include <direct.h> 
#endif

#include "folder.h"
#include "note.h"


extern std::vector<Note> notes;
extern std::atomic<bool> g_running;
extern std::atomic<bool> g_save_finished; 
extern int g_note_counter; 

void file_save(const std::vector<Note> &notes, int current_i){
    const char* userProfile = std::getenv("USERPROFILE");
    if(!userProfile) return;

    std::string folderPath = std::string(userProfile) + "\\Note_app";

    #ifdef _WIN32
    _mkdir(folderPath.c_str());
    #endif

    std::string saveSystem = folderPath + "\\saves.txt";
    std::ofstream savefile(saveSystem);

    if(savefile.is_open()){

        savefile << current_i << "\n";

        for(const auto& x : notes){
            savefile << x.id << "|||" 
                    << x.title << "|||" 
                    << x.content << "|||" 
                    << x.createdAt << "\n";
        }
        savefile.close();
    }
}


#ifdef _WIN32
BOOL WINAPI ConsoleHandler(DWORD signal){
    if (signal == CTRL_CLOSE_EVENT || signal == CTRL_C_EVENT) { 
        g_running = false; 

        file_save(notes, g_note_counter); 
        ExitProcess(0);   
        return TRUE; 
    }
    return FALSE;
}
#endif

void load_file(std::vector<Note> &notes, int &current_i){
    g_save_finished = false;

    const char* userProfile = getenv("USERPROFILE");
    if(!userProfile){
        g_save_finished = true;
        return;
    }

    std::string saveSystem = std::string(userProfile) + "\\Note_app\\saves.txt";
    std::ifstream loadFile(saveSystem);

    if(!loadFile.is_open()){
        std::cerr << "Error: Could not open the save file!\n";
        current_i = 0; 
        g_save_finished = true;
        return;
    }

    std::string line;
    notes.clear();

    if(std::getline(loadFile, line)){
        try {
            current_i = std::stoi(line);
        } catch (...) {
            current_i = 0; 
        }
    }


    while(std::getline(loadFile, line)){
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
        }
    }
    
    if(loadFile.bad()){
        std::cerr << "Error: An error occurred while reading the save file!\n";
    }
    loadFile.close();
    g_save_finished = true;
}
