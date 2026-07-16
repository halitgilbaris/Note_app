#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <limits>

#include "note.h"

#ifdef _WIN32
#include <windows.h>
#endif



std::vector<std::string> notes;

void header(){
    std::cout << "===============================================\n"
         << "Note_app v0.4.6 - Telif Hakki (c) 2026\n"
         << "Licensed under MIT / GPLv3 / Apache 2.0\n"
         << "===============================================\n\n";
    
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "====================\n"
         << "      Note_App      \n"
         << "       v0.4.6       \n"
         << "===================\n\n";
}

int main(){
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    notes.reserve(100);

    header();

    std::cout << "Initializing";
    for(int i = 0; i < 3; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << ".";
        std::cout << std::flush;
    }
    std::cout << "\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Loading";
    for(int i = 0; i < 3; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << ".";
        std::cout << std::flush;
    }
    std::cout << "\n\n";
    
    std::cout << "WELCOME!\n";

    bool isRunning = true;
    int choice;

    while (isRunning){
        std::cout << "\n-----MENU-----\n"
             << "1-Add Note\n"
             << "2-View Notes\n"
             << "3-Delete Note\n"
             << "4-Edit Note\n" 
             << "5-Create txt\n"   
             << "6-Exit\n"
             << "Your choice: ";
        
        if (!(std::cin >> choice)) {
            std::cout << "Please only number!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                add_note(notes); 
                break;
            case 2:
                view_note(notes);
                break;
            case 3:
                delete_note(notes);
                break;
            case 4:
                edit_note(notes);
                break;
            case 5:
                create_txt(notes);
                break;
            case 6:
                isRunning = false;
                break;
            default:
                std::cout << "Invalid choice!\n";
                break;
        }
    }
    std::cout << "Exiting... Goodbye!\n";
    return 0;
}
