#ifndef STORAGE_H  // Start of header guard
#define STORAGE_H

#include <string>

class Storage {
    std::string main_file;
    std::string borrow_file;
    std::string temp_file;
    bool init = true;

public:
    class Borrow {
        friend class Storage;
        std::string br_date;
        std::string rt_date;
        std::string phone_nb;
        Borrow* next;

        Borrow(std::string br, std::string rt, std::string p);
    };

    class Book {
        friend class Storage;
        int id;
        std::string title;
        std::string author;
        int quantity;
        Book* left;
        Book* right;
        Borrow* borrowList;  // Use for storing borrowed book

        Book(int i, std::string t, std::string a, int q);
    };

    Book* root;

    Storage(std::string mf, std::string bf, std::string tf);

    void addBook(int _id, std::string _title, std::string _author, int _quantity);

    void viewAll();

    void searchBookById(int id);

    void searchBookByTitle(std::string title);

    void searchBookByAuthor(std::string author);

    void issueBook(int id, std::string _br_date, std::string _rt_date, std::string _phone_nb);

    void returnBook(int id, std::string _phone_nb);

    bool isNull();

protected:
    void init_storage();

    void init_borrow();

    void update_storage();

    void update_main_db(std::fstream& db);

    void _update_main_db(Book* target, std::fstream& db);

    Book* _addBook(Book* target, int _id, std::string _title, std::string _author, int _quantity);

    void _viewAll(Book* target);

    Book* getBookByID(int id);

    Book* _getBookByID(Book* target, int id);

    Book* getBookByTitle(std::string title);

    Book* _getBookByTitle(Book* target, std::string title);

    Book* getBookByAuthor(std::string author);

    Book* _getBookByAuthor(Book* target, std::string author);

    void _issueBook(Book* targetBook, std::string _br_date, std::string _rt_date,
                    std::string _phone_nb);

    void update_borrow_rm(int id, std::string _phone_nb);
};

#endif  // STORAGE_H // End of header guard
