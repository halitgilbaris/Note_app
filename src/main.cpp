#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "imgui_stdlib.h" 
#include <iostream> 

#include <note.h>
#include <folder.h>

// 💾 UYGULAMA KAPANDIĞINDA ÇALIŞACAK FONKSİYON
void NotlariKaydet() {
    // Uygulama çarpıdan kapatıldığı an bu fonksiyon tetiklenir.
    // Dosyaya yazma kodlarını buraya ekleyebilirsin.
    std::cout << "Uygulama kapatiliyor, notlar kaydediliyor..." << std::endl;
}


ImFont* normalFont = nullptr;
ImFont* bigFont = nullptr;



int main() {
    // --- 1. ARKA PLAN VE PENCERE HAZIRLIKLARI ---
    if (!glfwInit()) return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); // Tam ekran başlatma

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Note app", NULL, NULL);
    if (!window) { glfwTerminate(); return 1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);






    // --- create note_class and prepare
    note_class note_Class;
    
    std::vector<Note> notes;

    static bool eklemeAcik = false;
    bool listelemeAcik = false;
    static bool silmeAcik = false;
    static bool duzenlemeAcik = false;
    static bool txtAcik = false;
    static bool aramaAcik = false;
    static bool noNoteWarning = false;
    static bool noDelNOte = false;
    static bool noNoteEdit = false;
    static bool noNoteTXT = false;
    static bool txtBasarili = false;





    
    // --- 2. IMGUI VE TÜRKÇE FONT ENTEGRASYONU ---
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();

    static const ImWchar turkce_araligi[] = {
        0x0020, 0x00FF, // Standart Latin Karakterleri
        0x0100, 0x017F, // Türkçe Karakterleri Barındıran Genişletilmiş Latin (Latin Extended-A)
        0
    };


    #ifdef _WIN32
        // Windows için standart Arial fontu (Hem normal hem büyük yüklüyoruz)
        normalFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 18.0f, NULL, turkce_araligi);
        bigFont  = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 28.0f, NULL, turkce_araligi);
    #else
        // Ubuntu / Linux için standart DejaVu fontu (Hem normal hem büyük yüklüyoruz)
        normalFont = io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 18.0f, NULL, turkce_araligi);
        bigFont  = io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 28.0f, NULL, turkce_araligi);
    #endif

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");





    


    // --- 3. ANA UYGULAMA DÖNGÜSÜ ---
    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // =========================================================
        // 🎯 SENİN OYUN ALANIN: TASARIMINI SADECE BURAYA YAZACAKSIN
        // =========================================================
        
        // Ekranı tamamen kaplayan görünmez pencere flagleri
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | 
                                 ImGuiWindowFlags_NoResize | 
                                 ImGuiWindowFlags_NoMove | 
                                 ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoBackground;

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(io.DisplaySize);






        //button position and buttons
    
        if (!eklemeAcik && !listelemeAcik && !silmeAcik && !duzenlemeAcik &&!txtAcik && !aramaAcik){
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0, 0.0));
            ImGui::Begin("AnaEkran", NULL, flags);




            ImGui::SetCursorPosX(0.0);
            if(ImGui::Button("Add note", ImVec2(300.0, 75.0))){
                eklemeAcik = true; 
                noNoteWarning = false;
            }






            ImGui::SetCursorPosX(0.0);
            if(ImGui::Button("View notes", ImVec2(300.0, 75.0))){
                if(notes.empty()){
                    listelemeAcik = false;
                    noNoteWarning = true;
                    
                }
                else{
                    listelemeAcik = true;
                    noNoteWarning = false;
                }
            }
            if(noNoteWarning){
                ImVec2 eskiImlecKonumu = ImGui::GetCursorPos(); 

                ImGui::SetCursorPos(ImVec2(330.0, 100.0));
                ImGui::PushFont(bigFont);
                ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "NO NOTES!");
                ImGui::PopFont();

                ImGui::SetCursorPos(eskiImlecKonumu); 
            }








            ImGui::SetCursorPosX(0.0);
            if(ImGui::Button("Delete note", ImVec2(300.0, 75.0))){
                if(notes.empty()){
                    silmeAcik = false;
                    noDelNOte = true;
                    
                }
                else{
                    silmeAcik = true;
                    noDelNOte = false;
                }
            }
            if(noDelNOte){
                ImVec2 past = ImGui::GetCursorPos(); 

                ImGui::SetCursorPos(ImVec2(330.0, 180.0));
                ImGui::PushFont(bigFont);
                ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "NO NOTES FOR DELETE!");
                ImGui::PopFont();

                ImGui::SetCursorPos(past); 
            }
            




            
            

            ImGui::SetCursorPosX(0.0);
            if(ImGui::Button("Edit note", ImVec2(300.0, 75.0))){
                if(notes.empty()){
                    duzenlemeAcik = false;
                    noNoteEdit = true;
                }
                else{
                    duzenlemeAcik = true;
                    noNoteEdit = false;
                }
            }


            if(noNoteEdit){
                ImVec2 pastedit = ImGui::GetCursorPos(); 

                ImGui::SetCursorPos(ImVec2(330.0, 260.0)); 
                ImGui::PushFont(bigFont);
                ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "NO NOTES FOR EDIT!");
                ImGui::PopFont();

                ImGui::SetCursorPos(pastedit); 
            }




            
            


            ImGui::SetCursorPosX(0.0);
            if(ImGui::Button("Create txt", ImVec2(300.0, 75.0))){
                if(notes.empty()){
                    noNoteTXT = true;
                    txtAcik = false; 
                }else{
                    noNoteTXT = false;
                    txtAcik = true;           
                }
            }


            if(noNoteTXT){
                ImVec2 pastTXT = ImGui::GetCursorPos(); 
            
                ImGui::SetCursorPos(ImVec2(330.0, 340.0)); 
                ImGui::PushFont(bigFont);
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "NO NOTES FOR TXT!");
                ImGui::PopFont();
            
                ImGui::SetCursorPos(pastTXT); 
            }


            
            






            //ImGui::SetCursorPosX(0.0);
            //if(ImGui::Button("Search menu", ImVec2(300.0, 75.0))){
            //    aramaAcik = true;
            //    noNoteWarning = false;
            //}




            ImGui::SetCursorPosX(0.0);
            if (ImGui::Button("Exit", ImVec2(300.0, 75.0))) {
                glfwSetWindowShouldClose(window, GLFW_TRUE); 
            }




            float kalanBoslukY = ImGui::GetContentRegionAvail().y;
            float metinYuksekligi = ImGui::GetTextLineHeightWithSpacing();

            if (kalanBoslukY > metinYuksekligi) {
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + kalanBoslukY - metinYuksekligi - ImGui::GetStyle().ItemSpacing.y);
            }

            ImGui::Separator();


            const char* telifMetni = "Note_app v1.0.0 - Telif Hakki (c) 2026 - Licensed under MIT / GPLv3 / Apache 2.0";
            float pencereGenisligi = ImGui::GetWindowSize().x;         
            float metinGenisligi = ImGui::CalcTextSize(telifMetni).x;  


            ImGui::SetCursorPosX((pencereGenisligi - metinGenisligi) * 0.5f);

            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s",telifMetni);



            ImGui::End();
            ImGui::PopStyleVar();



        }
        else{
            if (eklemeAcik) {
                note_Class.add_note(notes, &eklemeAcik);
            }
            else if (listelemeAcik) {
                note_Class.view_note(notes, &listelemeAcik);
            }
            else if (silmeAcik) {
                note_Class.delete_note(notes, &silmeAcik);
            }
            else if (duzenlemeAcik) {
                note_Class.edit_note(notes, &duzenlemeAcik);
            }
            else if (txtAcik){
                note_Class.create_txt(notes, &txtAcik);
            }
            //else if (aramaAcik) {
            //    note_Class.search_menu(notes, &aramaAcik);
            //}
        }





        // =========================================================

        // --- 4. EKRANA ÇİZME VE TEMİZLİK ---
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // 💾 DÖNGÜDEN ÇIKILDI (Kullanıcı X tuşuna bastı)
    NotlariKaydet();

    // --- 5. KAPANIŞ VE TEMİZLİK ---
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
