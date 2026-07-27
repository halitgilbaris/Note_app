#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <vector>
#include <thread>
#include <atomic>
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
int g_note_counter = 0;



void file_save(const std::vector<Note> &notes){
    const char* userProfile = std::getenv("USERPROFILE");
    if(!userProfile) return;

    std::string folderPath = std::string(userProfile) + "\\Note_app";

    #ifdef _WIN32
    _mkdir(folderPath.c_str());
    #endif

    std::string saveSystem = folderPath + "\\saves.txt";
    std::ofstream savefile(saveSystem);

    if(savefile.is_open()){
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

    const char* userProfile = getenv("USERPROFILE");
    if(!userProfile){
        g_save_finished = true;
        return;
    }

    std::string saveSystem = std::string(userProfile) + "\\Note_app\\saves.txt";
    std::ifstream loadFile(saveSystem);

    if(!loadFile.is_open()){
        g_save_finished = true;
        return;
    }

    std::string line;
    notes.clear();



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
        
    }
    loadFile.close();
    g_save_finished = true;
}
