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

















void note_class::search_note_ID(const std::vector<Note> &notes, bool *pencereDurumu, bool* searchIDopen, bool* searchTITLEopen, bool* searchCONTENTopen){

    static int searchID = -1;
    static bool searchIDSucces = false;
    static bool searchIDHasRun = false;
    static std::vector<Note> searchIDResults;

    ImGuiWindowFlags alt_flags = ImGuiWindowFlags_NoTitleBar | 
                                 ImGuiWindowFlags_NoResize | 
                                 ImGuiWindowFlags_NoMove | 
                                 ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoBackground; 

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);

    if(ImGui::Begin("Search ID", pencereDurumu, alt_flags)){

        ImGui::PushFont(bigFont);
        ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "Please enter the ID of the note you wish to search for!");
        ImGui::PopFont();

        ImGui::Spacing();

        ImGui::InputInt("##Search_ID", &searchID, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::SameLine();

        if(ImGui::Button("Search", ImVec2())){
            searchIDSucces = false;
            searchIDHasRun = true;
            searchIDResults.clear();

            for(const auto& ID : notes){
                if(searchID == ID.id){
                    searchIDSucces = true;
                    searchIDResults.push_back(ID);
                }
            }
        }

        if(searchIDHasRun){
            if(!searchIDSucces){
                ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "Notes not found!");
            }
            else{
                for(const auto& result : searchIDResults){
                    ImGui::Separator();
                    ImGui::Text("ID: %d", result.id);
                    ImGui::Spacing();
                    ImGui::Text("Title: %s", result.title.c_str());
                    ImGui::Spacing();
                    ImGui::Text("Content: %s", result.content.c_str());
                    ImGui::Spacing();
                    ImGui::Text("Created at: %s", result.createdAt.c_str());
                    ImGui::Separator();
                }
            }
        }

        if(ImGui::Button("Back to menu", ImVec2(300.0, 75.0))){
                if(searchIDopen) *searchIDopen = false;
                if(searchTITLEopen) *searchTITLEopen = false;
                if(searchCONTENTopen) *searchCONTENTopen = false;
                searchIDHasRun = false;
                searchIDResults.clear();
                if(pencereDurumu) *pencereDurumu = false;
            }

        ImGui::End();
    }
}












void note_class::search_note_title(const std::vector<Note> &notes, bool *pencereDurumu, bool* searchIDopen, bool* searchTITLEopen, bool* searchCONTENTopen){

    static std::string searchTITLE = "";
    static bool searchTITLESucces = false;
    static bool searchTitleHasRun = false;
    static std::vector<Note> searchTitleResults;


    ImGuiWindowFlags alt_flags = ImGuiWindowFlags_NoTitleBar | 
                                 ImGuiWindowFlags_NoResize | 
                                 ImGuiWindowFlags_NoMove | 
                                 ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoBackground; 

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);

    if(ImGui::Begin("Search Title", pencereDurumu, alt_flags)){

        ImGui::PushFont(bigFont);
        ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "Please enter the title of the note you wish to search for!");
        ImGui::PopFont();

        ImGui::Spacing();

        ImGui::InputText("##Search_Title", &searchTITLE);
        ImGui::SameLine();

        if(ImGui::Button("Search", ImVec2())){
            searchTITLESucces = false;
            searchTitleHasRun = true;
            searchTitleResults.clear();

            for(const auto& TITLE : notes){
                if(searchTITLE == TITLE.title){
                    searchTITLESucces = true;
                    searchTitleResults.push_back(TITLE);
                }
            }
        }

        if(searchTitleHasRun){
            if(!searchTITLESucces){
                ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "Notes not found!");
            }
            else{
                for(const auto& result : searchTitleResults){
                    ImGui::Separator();
                    ImGui::Text("ID: %d", result.id);
                    ImGui::Spacing();
                    ImGui::Text("Title: %s", result.title.c_str());
                    ImGui::Spacing();
                    ImGui::Text("Content: %s", result.content.c_str());
                    ImGui::Spacing();
                    ImGui::Text("Created at: %s", result.createdAt.c_str());
                    ImGui::Separator();
                }
            }
        }

        if(ImGui::Button("Back to menu", ImVec2(300.0, 75.0))){
                if(searchIDopen) *searchIDopen = false;
                if(searchTITLEopen) *searchTITLEopen = false;
                if(searchCONTENTopen) *searchCONTENTopen = false;
                searchTitleHasRun = false;
                searchTitleResults.clear();
                if(pencereDurumu) *pencereDurumu = false;
            }

        ImGui::End();
    }
}


















void note_class::search_note_content(const std::vector<Note> &notes, bool *pencereDurumu, bool* searchIDopen, bool* searchTITLEopen, bool* searchCONTENTopen){

    static std::string searchCONTENT = "";
    static bool searchCONTENTSucces = false;
    static bool searchContentHasRun = false;
    static std::vector<Note> searchContentResults;


    ImGuiWindowFlags alt_flags = ImGuiWindowFlags_NoTitleBar | 
                                 ImGuiWindowFlags_NoResize | 
                                 ImGuiWindowFlags_NoMove | 
                                 ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoBackground; 

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);

    if(ImGui::Begin("Search Content", pencereDurumu, alt_flags)){

        ImGui::PushFont(bigFont);
        ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "Please enter the content of the note you wish to search for!");
        ImGui::PopFont();

        ImGui::Spacing();

        ImGui::InputText("##Search_Content", &searchCONTENT);
        ImGui::SameLine();

        if(ImGui::Button("Search", ImVec2())){
            searchCONTENTSucces = false;
            searchContentHasRun = true;
            searchContentResults.clear();

            for(const auto& CONTENT : notes){
                if(searchCONTENT == CONTENT.content){
                    searchCONTENTSucces = true;
                    searchContentResults.push_back(CONTENT);
                }
            }
        }

        if(searchContentHasRun){
            if(!searchCONTENTSucces){
                ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "Notes not found!");
            }
            else{
                for(const auto& result : searchContentResults){
                    ImGui::Separator();
                    ImGui::Text("ID: %d", result.id);
                    ImGui::Spacing();
                    ImGui::Text("Title: %s", result.title.c_str());
                    ImGui::Spacing();
                    ImGui::Text("Content: %s", result.content.c_str());
                    ImGui::Spacing();
                    ImGui::Text("Created at: %s", result.createdAt.c_str());
                    ImGui::Separator();
                }
            }
        }

        if(ImGui::Button("Back to menu", ImVec2(300.0, 75.0))){
                if(searchIDopen) *searchIDopen = false;
                if(searchTITLEopen) *searchTITLEopen = false;
                if(searchCONTENTopen) *searchCONTENTopen = false;
                searchContentHasRun = false;
                searchContentResults.clear();
                if(pencereDurumu) *pencereDurumu = false;
            }

        ImGui::End();
    }
}












void note_class::search_menu(const std::vector<Note> &notes, bool* pencereDurumu, bool* searchIDopen, bool* searchTITLEopen, bool* searchCONTENTopen){
    



    ImGuiWindowFlags alt_flags = ImGuiWindowFlags_NoTitleBar | 
                                 ImGuiWindowFlags_NoResize | 
                                 ImGuiWindowFlags_NoMove | 
                                 ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoBackground; 

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);
    

    if(!*searchIDopen && !*searchTITLEopen && !*searchCONTENTopen){

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0, 0.0));

        ImGui::Begin("AnaEkran", NULL, alt_flags);{
            ImGui::PushFont(bigFont);
            ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "Please select your search type!");
            ImGui::PopFont();


            if(ImGui::Button("Search ID", ImVec2(300.0, 75.0))){
                *searchIDopen = true;
                *searchTITLEopen = false;
                *searchCONTENTopen = false;
            }


            if(ImGui::Button("Search title", ImVec2(300.0, 75.0))){
                *searchTITLEopen = true;
                *searchIDopen = false;
                *searchCONTENTopen = false;
            }


            if(ImGui::Button("Search content", ImVec2(300.0, 75.0))){
                *searchCONTENTopen = true;
                *searchIDopen = false;
                *searchTITLEopen = false;
            }


            if(ImGui::Button("Back to menu", ImVec2(300.0, 75.0))){
                if(pencereDurumu) *pencereDurumu = false;
            }

            ImGui::End();
        }

        ImGui::PopStyleVar();

    }
    else{
        if(*searchIDopen){
            search_note_ID(notes, pencereDurumu, searchIDopen, searchTITLEopen, searchCONTENTopen);
        }
        else if(*searchTITLEopen){
            search_note_title(notes, pencereDurumu, searchIDopen, searchTITLEopen, searchCONTENTopen);
        }
        else if(*searchCONTENTopen){
            search_note_content(notes, pencereDurumu, searchIDopen, searchTITLEopen, searchCONTENTopen);
        }
    }
    
}
