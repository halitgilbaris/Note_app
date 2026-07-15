#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <limits>

#include "note.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

vector<string> notes;

void header(){
    cout << "===============================================\n"
         << "Note_app v0.3.6 - Telif Hakki (c) 2026\n"
         << "Licensed under MIT / GPLv3 / Apache 2.0\n"
         << "===============================================\n\n";
    
    this_thread::sleep_for(chrono::seconds(3));

    cout << "====================\n"
         << "      Note_App      \n"
         << "       v0.3.6       \n"
         << "===================\n\n";
}

int main(){
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    notes.reserve(100);

    header();

    cout << "Initializing";
    for(int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << ".";
        cout << flush;
    }
    cout << "\n";

    this_thread::sleep_for(chrono::seconds(1));

    cout << "Loading";
    for(int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << ".";
        cout << flush;
    }
    cout << "\n\n";
    
    cout << "WELCOME!\n";

    bool isRunning = true;
    int choice;

    while (isRunning){
        cout << "\n-----MENU-----\n"
             << "1-Add Note\n"
             << "2-View Notes\n"
             << "3-Delete Note\n"
             << "4-Edit Note\n"    
             << "5-Exit\n"
             << "Your choice: ";
        
        if (!(cin >> choice)) {
            cout << "Please only number!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
                isRunning = false;
                break;
            default:
                cout << "Invalid choice!\n";
                break;
        }
    }
    cout << "Exiting... Goodbye!\n";
    return 0;
}
