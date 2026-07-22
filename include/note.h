#pragma once
#include <vector>
#include <string>

struct Note {
    int id;
    std::string title;
    std::string content;
    std::string createdAt;
};

class note_class {
private:
    int i = 1;

public:
    void add_note(std::vector<Note> &notes);
    void view_note(const std::vector<Note> &notes);
    void delete_note(std::vector<Note> &notes);
    void edit_note(std::vector<Note> &notes);
    void create_txt(const std::vector<Note> &notes);
    void search_note_title(const std::vector<Note> &notes);
    void search_note_content(const std::vector<Note> &notes);
    void search_note_createdAt(const std::vector<Note> &notes);
    void search_menu(const std::vector<Note> &notes);
};
