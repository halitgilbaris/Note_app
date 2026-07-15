#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <limits>

#include "note.h"

using namespace std;



vector<string> notes;


void header(){

    //INFO ABOUT APPLICATION

    cout << "===============================================\n"
         << "Note_app v0.3.5 - Telif Hakkı (c) 2026\n"
         << "Licensed under MIT / GPLv3 / Apache 2.0\n"
         << "===============================================\n\n";
    
    this_thread::sleep_for(chrono::seconds(3));

    cout << "====================\n"
         << "      Note_App      \n"
         << "       v0.3.5       \n"
         << "===================\n\n";

}






int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    notes.reserve(100);

    header();

    cout << "Initializing";
    cout.flush();
    for(int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << ".";
        cout.flush();
    }

    cout << "\n";

    
    this_thread::sleep_for(chrono::seconds(1));


    cout << "Loading";
    cout.flush();
    for(int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << ".";
        cout.flush();
    }

    cout << "\n\n";
    
    
    cout << "\nWELCOME!\n\n";

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


        switch (choice) {
            case 1:
                add_note(notes); // note.h içinde add_note(std::vector<std::string>& n) şeklinde referans olmalı
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
                std::cout << "Invalid choice!\n";
                break;
        }
    }
    cout << "Exiting... Goodbye!\n";
    return 0;
}
