#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <chrono>
#include <thread>
#include <ctime>

#ifdef _WIN32
#include <conio.h>
#endif

#include "note.h"
#include "folder.h"


std::atomic<bool> s_running(true);  


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


void note_class::search_note_title(const std::vector<Note> &notes){

    std::string search_title;

    std::cout << "Please enter the title you wish to search for: ";
    getline(std::cin, search_title);

    for(const auto& titles : notes){
        if(titles.title == search_title){
            std::cout << "Note found!\n\n";
            std::cout << "---------------------------------------------------\n";
            std::cout << "ID: " << titles.id << "\n";
            std::cout << "Title: " << titles.title << "\n";
            std::cout << "Content: " << titles.content << "\n";
            std::cout << "Created at: " << titles.createdAt << "\n";
            std::cout << "---------------------------------------------------\n";
        }
        else{
            std::cout << "Note not found!\n";
        }
    }
}




void note_class::search_note_content(const std::vector<Note> &notes){

    std::string search_content;

    std::cout << "Please enter the content you wish to search for: ";
    getline(std::cin, search_content);

    for(const auto& contents : notes){
        if(contents.title == search_content){
            std::cout << "Note found!\n\n";
            std::cout << "---------------------------------------------------\n";
            std::cout << "ID: " << contents.id << "\n";
            std::cout << "Title: " << contents.title << "\n";
            std::cout << "Content: " << contents.content << "\n";
            std::cout << "Created at: " << contents.createdAt << "\n";
            std::cout << "---------------------------------------------------\n";
        }
        else{
            std::cout << "Note not found!\n";
        }
    }
}





void note_class::search_note_createdAt(const std::vector<Note> &notes){

    std::string search_createdAt;

    std::cout << "Please enter your secret information when creating the note: ";
    getline(std::cin, search_createdAt);

    for(const auto& createdAts : notes){
        if(createdAts.title == search_createdAt){
            std::cout << "Note found!\n\n";
            std::cout << "---------------------------------------------------\n";
            std::cout << "ID: " << createdAts.id << "\n";
            std::cout << "Title: " << createdAts.title << "\n";
            std::cout << "Content: " << createdAts.content << "\n";
            std::cout << "Created at: " << createdAts.createdAt << "\n";
            std::cout << "---------------------------------------------------\n";
        }
        else{
            std::cout << "Note not found!\n";
        }
    }
}




void note_class::search_menu(const std::vector<Note> &notes){

    int choice_search_menu;
    s_running = true;

    while(s_running){

        #ifdef _WIN32
            std::system("cls");
        #else
            std::system("clear");
        #endif

        std::cout << "1-Search title\n"
              << "2-Search content\n"
              << "3-Search created at\n"
              << "4-Return menu\n"
              << "Your choice: ";

        // HATA DÜZELTİLDİ: if içindeki cin kontrolü parantezi düzeltildi
        if(!(std::cin >> choice_search_menu)){
            std::cout << "Please only number!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        switch (choice_search_menu)
        {
        case 1:
            search_note_title(notes);
            std::cout << "\nPress Enter to return to menu...";
            std::cin.get(); 
            break;
        case 2:
            search_note_content(notes);
            std::cout << "\nPress Enter to return to menu...";
            std::cin.get(); 
            break;
        case 3:
            search_note_createdAt(notes);
            std::cout << "\nPress Enter to return to menu...";
            std::cin.get(); 
            break;
        case 4:
            s_running = false;
            break;
        default:
            std::cout << "Invalid choice!\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }
    }
}
