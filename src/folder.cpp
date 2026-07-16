#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <vector>
#include <windows.h>
#include <direct.h> 

#include "folder.h"
#include "note.h"

#ifdef _WIN32
#endif

extern std::vector<std::string> notes;
extern volatile bool g_running;
extern volatile bool g_save_finished; 


void file_save(const std::vector<std::string> &notes){

    const char* userProfile = std::getenv("USERPROFILE");
    if(!userProfile) return;

    std::string folderPath = std::string(userProfile) + "\\Note_app";

    #ifdef _WIN32
    _mkdir(folderPath.c_str()); // Klasör varsa hiçbir şey yapmaz, yoksa hata vermeden açar
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

BOOL WINAPI ConsoleHandler(DWORD signal){
    if (signal == CTRL_CLOSE_EVENT) { 
        g_running = false; 
        file_save(notes);
        ExitProcess(0);   
        return TRUE; 
    }
    return FALSE;
}