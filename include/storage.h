#ifndef STORAGE_H  // Start of header guard
#define STORAGE_H

#include <logger.h>

#include <iostream>
#include <string>

class Storage {
private:
    class Book {
    public:
        int id;
        std::string title;
        std::string author;
        int quantity;

        Book* left;
        Book* right;

        Book(int i, const std::string& t, const std::string& a, int q)
            : id(i), title(t), author(a), quantity(q), left(nullptr), right(nullptr) {}
    };

    Book* root;

public:
    Storage() : root(nullptr) {};

    // ~BinarySearchTree() {};

    void addBook(int _id, std::string _title, std::string _author, int _quantity) {
        root = _addBook(root, _id, _title, _author, _quantity);
    };

    void viewAll() { _viewAll(root); }

    Book* getBookByID(int id) { return _getBookByID(root, id); };

    bool isNull() {
        if (root == nullptr) {
            return true;
        } else {
            return false;
        }
    }

private:
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

    Book* _getBookByID(Book* target, int id) {
        if (id < target->id) {
            return _getBookByID(target->left, id);
        } else if (id > target->id) {
            return _getBookByID(target->right, id);
        } else {
            return target;
        }
    };
};

#endif  // STORAGE_H // End of header guard
