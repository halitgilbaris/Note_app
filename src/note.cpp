#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <cstdlib>
#include <filesystem>

#ifdef _WIN32
#include <conio.h>
#endif

#include "note.h"
#include "folder.h"




void add_note(std::vector<std::string> &notes){
    std::string note;

    std::cout << "Please enter note!\n";

    std::getline(std::cin, note);

    notes.push_back(std::move(note));
    std::cout << "Note saved!\n";

}







void view_note(const std::vector<std::string> &notes){

    if(notes.empty()){
        std::cout << "No notes found!\n\n";
        return;
    }


    int number = 1;

    for(const auto& note : notes){
        std::cout << number << ")\n";
        std::cout << note << "\n";
        number++;
    }
    
    
}




void delete_note(std::vector<std::string> &notes){

    if(notes.empty()){
        std::cout << "No notes available to delete!\n";
        return;
    }

    int deletenote;

    std::cout << "Please select note for delete (1-" << notes.size() << "): ";
    
    if(!(std::cin >> deletenote)){
        std::cout << "Please enter a valid number!\n";
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return;
    }




    if(deletenote >= 1 && deletenote <= notes.size()){
        notes.erase(notes.begin() + (deletenote - 1));
        std::cout << "Note deleted successfully!\n\n";
    }else{
        std::cout << "Invaild note number!\n";
    }


}




void edit_note(std::vector<std::string> &notes){

    if(notes.empty()){
        std::cout << "No notes avaiable to edit!\n";
        return;
    }
    
    int editnote;

    std::cout << "Please select note for edit (1-" << notes.size() << "): ";
    std::cin >> editnote;
    std::cin.ignore();


    if(editnote >= 1 && editnote <= notes.size()){
        
        std::string oldNote = notes[editnote - 1];

        std::cout << oldNote;

        std::string newNote = oldNote;
        char ch;

        //13 = Enter
        #ifdef _WIN32
        while ((ch = _getch()) != 13){

            //Backspace
            if(ch == 8){
                if(!newNote.empty()){
                    newNote.pop_back();

                    std::cout << "\b \b"; 
                }
            }else if (ch >= 32 && ch <= 126) { 
                newNote.push_back(ch); 
                std::cout << ch;           
            }
        }
        #endif
        

        std::cout << std::endl; 
        notes[editnote - 1] = std::move(newNote);
        std::cout << "Note updated successfully!\n";


    }else{
        std::cout << "Invalid note number!\n";
    }


}




void create_txt(const std::vector<std::string> &notes){

    static int i = 1;
    int createnot;
    
    std::cout << "Please select note for edit (1-" << notes.size() << "): ";
        std::cin >> createnot;
        std::cin.ignore();

    if(createnot >= 1 && createnot <= notes.size()){

        const char* userProfile = std::getenv("USERPROFILE");
        if (!userProfile) {
            std::cout << "Error: Could not find user profile!\n";
            return;
        }

        std::string desktopPath = std::string(userProfile) + "\\Desktop\\" + std::to_string(i) +" not.txt";

        std::ofstream file(desktopPath);

        if(file.is_open()){
            file << notes[createnot - 1] << "\n";

            file.close();
            std::cout << "Notes saved to Desktop successfully!\n";
            i++;
        }else{
            std::cout << "Error: Could not create the file on Desktop!\n";
        }
    }
}


