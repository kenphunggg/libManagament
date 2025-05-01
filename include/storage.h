#ifndef STORAGE_H  // Start of header guard
#define STORAGE_H

#include <logger.h>

#include <iostream>
#include <string>

class Storage {
protected:
    class Borrow {
    public:
        std::string br_date;
        std::string rt_date;
        std::string phone_nb;

        Borrow* next;

        Borrow(std::string br, std::string rt, std::string p)
            : br_date(br), rt_date(rt), phone_nb(p), next(nullptr) {};
    };

    class Book {
    public:
        int id;
        std::string title;
        std::string author;
        int quantity;

        Book* left;
        Book* right;
        Borrow* borrowList;  // Use for storing borrowed book

        Book(int i, std::string t, std::string a, int q)
            : id(i),
              title(t),
              author(a),
              quantity(q),
              left(nullptr),
              right(nullptr),
              borrowList(nullptr) {}
    };
    Book* root;

public:
    Storage() : root(nullptr) {};

    // ~BinarySearchTree() {};

    void addBook(int _id, std::string _title, std::string _author, int _quantity) {
        root = _addBook(root, _id, _title, _author, _quantity);
    };

    void viewAll() { _viewAll(root); }

    void issueBook(int id, std::string _br_date, std::string _rt_date, std::string _phone_nb) {
        Book* book = getBookByID(id);
        _issueBook(book, _br_date, _rt_date, _phone_nb);
        book->quantity -= 1;
        logger::succeed("Issue book succeeded");
    }

    bool isNull() {
        if (root == nullptr) {
            return true;
        } else {
            return false;
        }
    }

protected:
    Book* _addBook(Book* target, int _id, std::string _title, std::string _author, int _quantity) {
        if (target == nullptr) {
            Book* newBook = new Book(_id, _title, _author, _quantity);
            logger::succeed("Insert successfully!");
            return newBook;
        } else {
            if (getBookByID(_id) == nullptr) {
                if (target->id > _id) {
                    target->left = _addBook(target->left, _id, _title, _author, _quantity);
                } else {
                    target->right = _addBook(target->right, _id, _title, _author, _quantity);
                };
            } else {
                Book* current;
                current = getBookByID(_id);
                if (current->title != _title) {
                    logger::warning("Wrong title, please try again");
                }
                if (current->author != _author) {
                    logger::warning("Wrong author, please try again");
                }
                if (current->author == _author && current->title == _title) {
                    current->quantity += _quantity;
                };
            }
        }

        return target;
    };

    void _viewAll(Book* target) {
        if (target == nullptr) {
            return;
        };
        _viewAll(target->left);
        table::content(target->id, target->title, target->author, target->quantity);
        _viewAll(target->right);
    }

    Book* getBookByID(int id) { return _getBookByID(root, id); };

    Book* _getBookByID(Book* target, int id) {
        if (id < target->id) {
            return _getBookByID(target->left, id);
        } else if (id > target->id) {
            return _getBookByID(target->right, id);
        } else {
            return target;
        }
    };

    void _issueBook(Book* targetBook, std::string _br_date, std::string _rt_date,
                    std::string _phone_nb) {
        // Create the new record (with error handling)
        Borrow* newBorrow = new Borrow(_br_date, _rt_date, _phone_nb);

        if (targetBook->borrowList == nullptr) {
            // List is empty, set the head
            targetBook->borrowList = newBorrow;
        } else {
            // Traverse to the end of the list
            Borrow* current = targetBook->borrowList;
            while (current->next != nullptr) {
                current = current->next;
            }
            // Append the new record at the end
            current->next = newBorrow;
        }
    }
};

#endif  // STORAGE_H // End of header guard
