#include <iostream>
#include <string>

#include "note.h"

using namespace std;



void add_note(vector<string> &notes){
    string note;

    cout << "Please enter note!\n";

    cin.ignore();
    getline(cin, note);

    notes.push_back(note);
    cout << "Note saved!\n";

}







void view_note(const vector<string> &notes){

    if(notes.empty()){
        cout << "No notes found!\n\n";
        return;
    }


    int number = 1;

    for(auto& note : notes){
        cout << number << ")\n";
        cout << note << "\n";
        number++;
    }
    
    
}