#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <vector>

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




void delete_note(vector<string> &notes){

    if(notes.empty()){
        cout << "No notes available to delete!\n";
        return;
    }

    int deletenote;

    cout << "Please select note for delete (1-" << notes.size() << "): ";
    cin >> deletenote;

    if(deletenote >= 1 && deletenote <= notes.size()){
        notes.erase(notes.begin() + (deletenote - 1));
    }else{
        cout << "Invaild note number!\n";
    }


}





void edit_note(vector<string> &notes){

    if(notes.empty()){
        cout << "No notes avaiable to edit!\n";
        return;
    }
    
    int editnote;

    cout << "Please select note for edit (1-" << notes.size() << "): ";
    cin >> editnote;
    cin.ignore();


    if(editnote >= 1 && editnote <= notes.size()){
        
        string oldNote = notes[editnote - 1];

        cout << oldNote;

        string newNote = oldNote;
        char ch;

        while ((ch = _getch()) != 13){

            if(ch == 8){
                if(!newNote.empty()){
                    newNote.pop_back();

                    cout << "\b \b"; 
                }
            }else if (ch >= 32 && ch <= 126) { 
                newNote.push_back(ch); 
                cout << ch;           
            }
        }
        

        cout << endl; 
        notes[editnote - 1] = newNote;
        cout << "Note updated successfully!\n";


    }else{
        cout << "Invalid note number!\n";
    }


}