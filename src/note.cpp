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
