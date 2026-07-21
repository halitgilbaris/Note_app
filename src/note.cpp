#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <chrono>
#include <ctime>

#ifdef _WIN32
#include <conio.h>
#endif

#include "note.h"
#include "folder.h"

// class note_class{ bloğu komple kaldırıldı, sadece fonksiyonlar üye olarak yazıldı:

void note_class::add_note(std::vector<Note> &notes){
    Note newNote;
    newNote.id = i;
    std::cout << "Please enter title of note: ";
    std::getline(std::cin, newNote.title);
    std::cout << "Please enter content of notes: ";
    std::getline(std::cin, newNote.content);

    auto nowtime = std::chrono::system_clock::now();
    std::time_t time_t = std::chrono::system_clock::to_time_t(nowtime);
    std::string timeStr = std::ctime(&time_t);

    if (!timeStr.empty() && timeStr.back() == '\n') {
        timeStr.pop_back();
    }
    
    newNote.createdAt = timeStr;
    notes.push_back(newNote);
    i++;
}






void note_class::view_note(const std::vector<Note> &notes){
    if(notes.empty()){
        std::cout << "No notes found!\n\n";
        return;
    }
    int number = 1;
    for(const auto& note : notes){
        std::cout << number << ")\n"
                << "ID: " << note.id << "\n"
                << "Title: " << note.title << "\n"
                << "Content: " << note.content << "\n"
                << "Created at: " << note.createdAt << "\n"
                << "--------------------------------------------\n";
        number++;
    }
}










void note_class::delete_note(std::vector<Note> &notes){
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
    if(deletenote >= 1 && deletenote <= static_cast<int>(notes.size())){
        notes.erase(notes.begin() + (deletenote - 1));
        std::cout << "Note deleted successfully!\n\n";
    }else{
        std::cout << "Invalid note number!\n";
    }
}










void note_class::edit_note(std::vector<Note> &notes){
    if(notes.empty()){
        std::cout << "No notes available to edit!\n";
        return;
    }
    int editnote;
    std::cout << "Please select note for edit (1-" << notes.size() << "): ";
    std::cin >> editnote;
    std::cin.ignore();

    if(editnote >= 1 && editnote <= static_cast<int>(notes.size())){
        std::string oldContent = notes[editnote - 1].content;
        std::cout << "Old Content: " << oldContent << "\nNew Content: ";
        std::string newNote = "";

        #ifdef _WIN32
        char ch;
        while ((ch = _getch()) != 13){
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
        std::cout << std::endl; 
        #else
        std::getline(std::cin, newNote);
        #endif

        notes[editnote - 1].content = std::move(newNote);
        std::cout << "Note updated successfully!\n";
    }else{
        std::cout << "Invalid note number!\n";
    }
}









void note_class::create_txt(const std::vector<Note> &notes) {
    static int file_counter = 1;
    if (notes.empty()) {
        std::cout << "No notes available to export!\n";
        return;
    }
    int createnot;
    std::cout << "Please select note for export (1-" << notes.size() << "): ";
    std::cin >> createnot;
    std::cin.ignore();
    
    if (createnot >= 1 && createnot <= static_cast<int>(notes.size())) {
        const char* userProfile = std::getenv("USERPROFILE");
        if (!userProfile) return;
        
        std::string desktopPath = std::string(userProfile) + "\\Desktop\\" + std::to_string(file_counter) + "_not.txt";
        std::ofstream file(desktopPath);
        
        if (file.is_open()) {
            const auto& note = notes[createnot - 1];
            file << "ID: " << note.id << "\n"
                << "Title: " << note.title << "\n"
                << "Content: " << note.content << "\n"
                << "Created At: " << note.createdAt << "\n";
            file.close();
            std::cout << "Note saved to Desktop successfully!\n";
            file_counter++;
        }
    }
}
