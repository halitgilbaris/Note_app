#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <limits>

#include "note.h"

using namespace std;



vector<string> notes;

int main(){
    
    //INFO ABOUT APPLICATION    
    cout << "===============================================\n";
    cout << "Uygulama Adı v1.0.0 - Telif Hakkı (c) 2026\n";
    cout << "Licensed under MIT / GPLv3 / Apache 2.0\n";
    cout << "===============================================\n\n";
    
    this_thread::sleep_for(chrono::seconds(3));

    cout << "====================\n";
    cout << "      Note_App      \n";
    cout << "       v0.3.4       \n";
    cout << "===================\n\n";


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
        cout << "\n-----MENU-----\n";
        cout << "1-Add Note\n";
        cout << "2-View Notes\n";
        cout << "3-Delete Note\n";
        cout << "4-Edit Note\n";
        cout << "5-Exit\n";
        cout << "Your choice: ";
        
        if (!(cin >> choice)) {
            cout << "Please only number!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if(choice == 1){
            add_note(notes);
        }else if(choice == 2){
            view_note(notes);
        }else if(choice == 3){
            delete_note(notes);
        }else if(choice == 4){
            edit_note(notes);
        }else if(choice == 5){
            isRunning = false;
        }else{
            cout << "Inviald choice\n";
        }
    }
    return 0;
}
