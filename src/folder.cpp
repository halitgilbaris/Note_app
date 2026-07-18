#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <vector>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#include <direct.h> 
#endif

#include "folder.h"
#include "note.h"



extern std::vector<std::string> notes;
extern volatile bool g_running;
extern volatile bool g_save_finished; 


void file_save(const std::vector<std::string> &notes){

    const char* userProfile = std::getenv("USERPROFILE");
    if(!userProfile) return;

    std::string folderPath = std::string(userProfile) + "\\Note_app";

    #ifdef _WIN32
    _mkdir(folderPath.c_str());
    #endif


    std::string saveSystem = folderPath + "\\saves.txt";
    std::ofstream savefile(saveSystem);

    int i = 1;

    if(savefile.is_open()){
        for(auto& x : notes){
            savefile << i << ") " << x << "\n";
            i++;
        }
    savefile.close();
    }else{
        return;
    }

}

#ifdef _WIN32
BOOL WINAPI ConsoleHandler(DWORD signal){
    if (signal == CTRL_CLOSE_EVENT) { 
        g_running = false; 
        file_save(notes);
        ExitProcess(0);   
        return TRUE; 
    }
    return FALSE;
}
#endif




void load_file(std::vector<std::string> &notes){

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
        g_save_finished = true;
        return;
    }


    if(loadFile.is_open()){
        std::string line;
        notes.clear();

        while(std::getline(loadFile, line)){

            size_t pos = line.find(") ");

            if(pos != std::string::npos){
                std::string pure_note = line.substr(pos + 2);

                if(!pure_note.empty()){
                    notes.push_back(pure_note);
                }
            }

        }
        if(loadFile.bad()){
            std::cerr << "Error: An error occurred while reading the save file!\n";
        }
        loadFile.close();
    }
    g_save_finished = true;


}
