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
public:
    void add_note(std::vector<Note> &notes, bool* pencereDurumu);
    void view_note(const std::vector<Note> &notes, bool* pencereDurumu);
    void delete_note(std::vector<Note> &notes, bool* pencereDurumu);
    void edit_note(std::vector<Note> &notes, bool* pencereDurumu);
    
    void create_txt(const std::vector<Note> &notes, bool* pencereDurumu);

    void search_menu(const std::vector<Note> &notes, bool* pencereDurumu, bool* searchIDopen, bool* searchTITLEopen, bool* searchCONTENTopen);

private:

    void search_note_ID(const std::vector<Note> &notes, bool *pencereDurumu, bool* searchIDopen, bool* searchTITLEopen, bool* searchCONTENTopen);
    void search_note_title(const std::vector<Note> &notes, bool *pencereDurumu, bool* searchIDopen, bool* searchTITLEopen, bool* searchCONTENTopen);
    void search_note_content(const std::vector<Note> &notes, bool *pencereDurumu, bool* searchIDopen, bool* searchTITLEopen, bool* searchCONTENTopen);
};
