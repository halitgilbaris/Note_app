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
#include <atomic>
#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#endif

#include "note.h"
#include "folder.h"

std::atomic<bool> s_running(true);  
extern int g_note_counter;
int g_note_counter = 0;

extern ImFont* normalFont;
extern ImFont* bigFont;

int number = 1;

std::string titleStr = "";
std::string contentStr = "";






void note_class::add_note(std::vector<Note> &notes, bool* pencereDurumu) {


    ImGuiWindowFlags alt_flags = ImGuiWindowFlags_NoTitleBar | 
                                 ImGuiWindowFlags_NoResize | 
                                 ImGuiWindowFlags_NoMove | 
                                 ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoBackground; 


    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);

    if (ImGui::Begin("Add new note", pencereDurumu, alt_flags)) 
    {
        ImGui::Text("Note title:");
        ImGui::InputText("##title_input", &titleStr);

        ImGui::Spacing();

        ImGui::Text("Note content:");
        ImGui::InputTextMultiline("##content_input", &contentStr, ImVec2(-FLT_MIN, 300.0f));

        ImGui::Separator();

        if (ImGui::Button("Save note", ImVec2(150.0, 45.0))) {
            if (!titleStr.empty()) {
                Note newNote;
                newNote.id = g_note_counter;
                newNote.title = titleStr;
                newNote.content = contentStr;

                auto nowtime = std::chrono::system_clock::now();
                std::time_t time_t = std::chrono::system_clock::to_time_t(nowtime);
                std::string timeStr = std::ctime(&time_t);
                if (!timeStr.empty() && timeStr.back() == '\n') { timeStr.pop_back(); }
                newNote.createdAt = timeStr;

                notes.push_back(newNote);
                g_note_counter++;

                titleStr.clear();
                contentStr.clear();

                if (pencereDurumu) *pencereDurumu = false;
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(100.0, 45.0))) {
            titleStr.clear();
            contentStr.clear();
            if (pencereDurumu) *pencereDurumu = false;
        }

        ImGui::End();
    } 
}












void note_class::view_note(const std::vector<Note> &notes, bool* pencereDurumu){


    ImGuiWindowFlags alt_flags = ImGuiWindowFlags_NoTitleBar | 
                                 ImGuiWindowFlags_NoResize | 
                                 ImGuiWindowFlags_NoMove | 
                                 ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoBackground; 


    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);

    if(ImGui::Begin("View note", pencereDurumu, alt_flags)){

        for(const auto& x : notes){
            ImGui::PushFont(bigFont);
            ImGui::Text("Note %d", number);
            ImGui::PopFont();

            ImGui::Text("ID: %d", x.id);
            ImGui::Spacing();
            ImGui::Text("Title: %s", x.title.c_str());
            ImGui::Spacing();
            ImGui::Text("Content: %s", x.content.c_str());
            ImGui::Spacing();
            ImGui::Text("Created at: %s", x.createdAt.c_str());
            ImGui::Spacing();
            ImGui::Separator();
        }
        if(ImGui::Button("Back",ImVec2(100.0, 45.0))){
            if(pencereDurumu) *pencereDurumu = false;
        }


    }

    ImGui::End();
}













void note_class::delete_note(std::vector<Note> &notes, bool* pencereDurumu){

    static int deleteNoteID;
    static bool invaildID = false;
    static bool succesID = false;


    ImGuiWindowFlags alt_flags = ImGuiWindowFlags_NoTitleBar | 
                                 ImGuiWindowFlags_NoResize | 
                                 ImGuiWindowFlags_NoMove | 
                                 ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoBackground; 

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);

    if(ImGui::Begin("View note", pencereDurumu, alt_flags)){

        ImGui::PushFont(bigFont);
        ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "Please enter the ID of the note to be deleted!");
        ImGui::PopFont();

        ImGui::SetNextItemWidth(200.0f); 
        ImGui::InputInt("##enter_id", &deleteNoteID, 0, 0, ImGuiInputTextFlags_CharsDecimal);

        ImGui::SameLine();
        if(ImGui::Button("DELETE", ImVec2())){
            invaildID = false;
            succesID = false;

            int delIndeks = -1;

            for(size_t i = 0; i < notes.size(); i++){
                if(notes[i].id == deleteNoteID){
                    delIndeks = i;
                    break;
                }
            }

            if(delIndeks != -1){
                notes.erase(notes.begin() + delIndeks);
                succesID = true;
            }
            else{
                invaildID = true;
            }
        }

        if(invaildID) {
            ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "Invalid ID number, please check!");
        }
        if(succesID) {
            ImGui::TextColored(ImVec4(0.0, 1.0, 0.0, 1.0), "Note successfully deleted!");
        }

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20.0f); 
        if(ImGui::Button("Back to Menu", ImVec2(150.0f, 40.0f))) {
            *pencereDurumu = false;
            invaildID = false;      
            succesID = false;
        }
        ImGui::End();
    }
}



















void note_class::edit_note(std::vector<Note> &notes, bool* pencereDurumu){

    static bool editContent = false;
    static bool editTitle = false;

    static std::string editTitleStr = "";
    static std::string editContentStr = "";

    static int editTitleID = -1;
    static int editContentID = -1;

    ImGuiWindowFlags alt_flags = ImGuiWindowFlags_NoTitleBar | 
                                 ImGuiWindowFlags_NoResize | 
                                 ImGuiWindowFlags_NoMove | 
                                 ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoBackground; 

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);

    if(ImGui::Begin("Edit note", pencereDurumu, alt_flags)){

        for(auto& x : notes){ 

            std::string titleButtonID = "Edit Title##" + std::to_string(x.id);
            std::string contentButtonID = "Edit Content##" + std::to_string(x.id);

            std::string saveTitle = "Save##Title" + std::to_string(x.id);
            std::string saveContent = "Save##Content" + std::to_string(x.id);

            ImGui::PushFont(bigFont);
            ImGui::Text("Note %d", number);
            ImGui::PopFont();

            ImGui::Text("ID: %d", x.id);
            ImGui::Spacing();


            //if click to button button and text delete for edit title
            if(editTitleID != x.id){
                ImGui::Text("Title: %s", x.title.c_str());
                ImGui::SameLine();

                if(ImGui::Button(titleButtonID.c_str(), ImVec2())){
                    editTitleID = x.id;
                    editTitleStr = x.title;
                }
            }
            else{
                std::string secretTitleID = "##" + titleButtonID;

                ImGui::InputText(secretTitleID.c_str(), &editTitleStr);
                ImGui::SameLine();

                if(ImGui::Button(saveTitle.c_str())){
                    x.title = editTitleStr;
                    editTitleID = -1;
                }
            }


            //if click to button button and text delete for edit content
            ImGui::Spacing();

            if(editContentID != x.id){
                ImGui::Text("Content: %s", x.content.c_str());
                ImGui::SameLine();

                if(ImGui::Button(contentButtonID.c_str(), ImVec2())){
                    editContentID = x.id;
                    editContentStr = x.content;
                }
            }
            else{
                std::string secretContentID = "##" + contentButtonID;

                ImGui::InputTextMultiline(secretContentID.c_str(), &editContentStr, ImVec2(-FLT_MIN, 300.0f));

                if(ImGui::Button(saveContent.c_str())){
                    x.content = editContentStr;
                    editContentID = -1;
                }
            }



            ImGui::Spacing();

            ImGui::Text("Created at: %s", x.createdAt.c_str());
            ImGui::Spacing();
            ImGui::Separator();
        }

        ImGui::Spacing();
        if(ImGui::Button("Back to Menu", ImVec2(150.0, 40.0))) {
            if(pencereDurumu) *pencereDurumu = false;
        }
        ImGui::End();
    }
}













void note_class::create_txt(const std::vector<Note> &notes, bool* pencereDurumu) {

    static int file_counter = 1;
    static int txtID = 0;
    
    static bool succesTXT = false;
    static bool failTXT = false;

    static bool allsuccesTXT = false;
    static bool allfailTXT = false;

    ImGuiWindowFlags alt_flags = ImGuiWindowFlags_NoTitleBar | 
                                 ImGuiWindowFlags_NoResize | 
                                 ImGuiWindowFlags_NoMove | 
                                 ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoBackground; 

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);

    if(ImGui::Begin("Edit note", pencereDurumu, alt_flags)){

        ImGui::PushFont(bigFont);
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Please enter the ID of the note you wish to save!");
        ImGui::PopFont();

        ImGui::InputInt("##InputID", &txtID, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::SameLine();

        if(ImGui::Button("Create txt", ImVec2())){
            succesTXT = false;
            failTXT = false;
            allsuccesTXT = false;
            allfailTXT = false;

            const char* userProfile = std::getenv("USERPROFILE");
            bool notBulundu = false;

            if(userProfile){
                for(const auto& x : notes){
                    if(txtID == x.id){
                        std::string desktopPath = std::string(userProfile) + "\\Desktop\\" + std::to_string(file_counter) + "_note.txt";
                        std::ofstream file(desktopPath);

                        if (file.is_open()) {
                            file << "ID: " << x.id << "\n"
                                 << "Title: " << x.title << "\n"
                                 << "Content: " << x.content << "\n"
                                 << "Created At: " << x.createdAt << "\n";
                            file.close();
                            file_counter++;
                            succesTXT = true;
                        }
                        notBulundu = true;
                        break;
                    }
                }
            }
            
            if(!notBulundu || !succesTXT){
                failTXT = true;
            }
        }
        
        ImGui::SameLine();

        if(ImGui::Button("Create all txt", ImVec2())){
            succesTXT = false;
            failTXT = false;
            allsuccesTXT = false;
            allfailTXT = false;

            const char* userProfile = std::getenv("USERPROFILE");

            if(userProfile && !notes.empty()){
                std::string desktopPath = std::string(userProfile) + "\\Desktop\\All_notes_" + std::to_string(file_counter) + ".txt";
                std::ofstream file(desktopPath);

                if (file.is_open()) {
                    for(const auto& e : notes){
                        file << "========================================\n"
                             << "ID: " << e.id << "\n"
                             << "Title: " << e.title << "\n"
                             << "Content: " << e.content << "\n"
                             << "Created At: " << e.createdAt << "\n";
                    }
                    file << "========================================\n";
                    file.close();
                    file_counter++;
                    allsuccesTXT = true;
                } else {
                    allfailTXT = true;
                }
            } else {
                allfailTXT = true;
            }
        }

        ImGui::Spacing();
        
        if(succesTXT){
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Selected note exported successfully!");
        }
        else if(failTXT){
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Transaction failed, please check the ID!");
        }

        if(allsuccesTXT){
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "All notes combined and exported to a single file successfully!");
        }
        else if(allfailTXT){
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Export all failed! The list might be empty.");
        }

        ImGui::Spacing();
        if(ImGui::Button("Back to menu", ImVec2(150.0f, 40.0f))){
            if(pencereDurumu) *pencereDurumu = false;
        }

        ImGui::End();
    }
}













//TODO: YAPILACAK


//void note_class::search_note_title(const std::vector<Note> &notes){
//    std::string search_title;
//    std::cout << "Please enter the title you wish to search for: ";
//    getline(std::cin, search_title);
//
//    bool found = false;
//    for(const auto& titles : notes){
//        if(titles.title == search_title){
//            std::cout << "---------------------------------------------------\n";
//            std::cout << "ID: " << titles.id << "\n";
//            std::cout << "Title: " << titles.title << "\n";
//            std::cout << "Content: " << titles.content << "\n";
//            std::cout << "Created at: " << titles.createdAt << "\n";
//            std::cout << "---------------------------------------------------\n";
//            found = true;
//        }
//    }
//    if(!found) {
//        std::cout << "Note not found!\n";
//    }
//}
//
//
//
//
//
//
//
//
//
//
//
//
//void note_class::search_note_content(const std::vector<Note> &notes){
//    std::string search_content;
//    std::cout << "Please enter the content you wish to search for: ";
//    getline(std::cin, search_content);
//
//    bool found = false;
//    for(const auto& contents : notes){
//        if(contents.content == search_content){ 
//            std::cout << "---------------------------------------------------\n";
//            std::cout << "ID: " << contents.id << "\n";
//            std::cout << "Title: " << contents.title << "\n";
//            std::cout << "Content: " << contents.content << "\n";
//            std::cout << "Created at: " << contents.createdAt << "\n";
//            std::cout << "---------------------------------------------------\n";
//            found = true;
//        }
//    }
//    if(!found) {
//        std::cout << "Note not found!\n";
//    }
//}
//
//
//
//
//
//
//
//void note_class::search_note_createdAt(const std::vector<Note> &notes){
//    std::string search_createdAt;
//    std::cout << "Please enter creation time you wish to search for: ";
//    getline(std::cin, search_createdAt);
//
//    bool found = false;
//    for(const auto& createdAts : notes){
//        if(createdAts.createdAt == search_createdAt){ 
//            std::cout << "---------------------------------------------------\n";
//            std::cout << "ID: " << createdAts.id << "\n";
//            std::cout << "Title: " << createdAts.title << "\n";
//            std::cout << "Content: " << createdAts.content << "\n";
//            std::cout << "Created at: " << createdAts.createdAt << "\n";
//            std::cout << "---------------------------------------------------\n";
//            found = true;
//        }
//    }
//    if(!found) {
//        std::cout << "Note not found!\n";
//    }
//}
//
//
//
//
//
//
//void note_class::search_menu(const std::vector<Note> &notes, bool* pencereDurumu){
//    int choice_search_menu;
//    s_running = true;
//
//    while(s_running){
//        #ifdef _WIN32
//            std::system("cls");
//        #else
//            std::system("clear");
//        #endif
//
//        std::cout << "1-Search title\n"
//              << "2-Search content\n"
//              << "3-Search created at\n"
//              << "4-Return menu\n"
//              << "Your choice: ";
//
//        if(!(std::cin >> choice_search_menu)){
//            std::cout << "Please only number!\n";
//            std::clearerr(stdin);
//            std::cin.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//            std::this_thread::sleep_for(std::chrono::seconds(2));
//            continue;
//        }
//
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//        switch (choice_search_menu)
//        {
//        case 1:
//            search_note_title(notes);
//            std::cout << "\nPress Enter to return...";
//            std::cin.get(); 
//            break;
//        case 2:
//            search_note_content(notes);
//            std::cout << "\nPress Enter to return...";
//            std::cin.get();
//            break;
//        case 3:
//            search_note_createdAt(notes);
//            std::cout << "\nPress Enter to return...";
//            std::cin.get();
//            break;
//        case 4:
//            s_running = false;
//            break;
//        default:
//            std::cout << "Invalid choice!\n";
//            std::this_thread::sleep_for(std::chrono::seconds(2));
//            break;
//        }
//    }
//}
