#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <limits>
#include <atomic>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#include "note.h"
#include "folder.h"

std::vector<Note> notes;
std::atomic<bool> g_running(true);       
std::atomic<bool> g_save_finished(false);

std::string note;

#ifdef _WIN32
BOOL WINAPI ConsoleHandler(DWORD signal);
#endif

void header(){
    std::cout << "===============================================\n"
        << "Note_app v0.7.4-beta - Telif Hakki (c) 2026\n"
        << "Licensed under MIT / GPLv3 / Apache 2.0\n"
        << "===============================================\n\n";
    
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "====================\n"
        << "      Note_App      \n"
        << "     v0.7.4-beta       \n"
        << "===================\n\n";
}

int main(){
    #ifdef _WIN32
    if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE)) {
        std::cout << "Kapatma dinleyicisi baslatilamadi!\n";
        return 1;
    }
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    notes.reserve(100);
    header();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::thread yukleme_thread(load_file, std::ref(notes));
    yukleme_thread.detach();

    std::cout << "Loading";
    for(int i = 0; i < 3; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << ".";
        std::cout << std::flush;
    }
    std::cout << "\n\n";
    
    std::cout << "WELCOME!\n";
    note_class noteClass;
    int choice;

    while (g_running){

        #ifdef _WIN32
            std::system("cls");
        #else
            std::system("clear");
        #endif

        std::cout << "\n-----MENU-----\n"
            << "1-Add Note\n"
            << "2-View Notes\n"
            << "3-Delete Note\n"
            << "4-Edit Note\n" 
            << "5-Create txt\n" 
            << "6-Search menu\n"  
            << "7-Exit\n"
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
                noteClass.add_note(notes);
                break;
            case 2:
                noteClass.view_note(notes);
                std::cout << "\nPress Enter to return to menu...";
                std::cin.get(); 
                break;
            case 3:
                noteClass.delete_note(notes);
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            case 4:
                noteClass.edit_note(notes);
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            case 5:
                noteClass.create_txt(notes);
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            case 6:
                noteClass.search_menu(notes);
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            case 7:
                g_running = false;
                break;
            default:
                std::cout << "Invalid choice!\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
        }
    }

    file_save(notes);
    std::cout << "Exiting... Goodbye!\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(800)); 
    return 0;
}
