#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "note.h"

using namespace std;

vector<string> notes;

int main(){

    //INFO ABOUT APPLICATION    

    cout << "====================\n";
    cout << "     Note_App     \n";
    cout << "      v0.1.0      \n";
    cout << "===================\n\n";

    cout << "Initializing...\n";
    this_thread::sleep_for(chrono::seconds(2));

    cout << "Loading...\n";
    this_thread::sleep_for(chrono::seconds(2));

    cout << "WELCOME!\n\n";




    bool isRunning = true;
    int choice;

    while (isRunning){

        cout << "\n-----MENU-----\n";
        cout << "1-Add Note\n";
        cout << "2-Views note\n";
        cout << "3-Exit\n";

        cin >> choice;
    
        if(choice == 1){
            add_note(notes);
        }else if(choice == 2){
            view_note(notes);
        }else if(choice == 3){
            isRunning = false;
        }else{
            cout << "Gecersiz secim\n";
        }


    }


    return 0;

}