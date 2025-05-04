#ifndef STORAGE_H  // Start of header guard
#define STORAGE_H

#include <logger.h>

#include <iostream>
#include <string>

class Storage {
public:
    class Borrow {
        friend class Storage;
        std::string br_date;
        std::string rt_date;
        std::string phone_nb;

        Borrow* next;

        Borrow(std::string br, std::string rt, std::string p)
            : br_date(br), rt_date(rt), phone_nb(p), next(nullptr) {};
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

    Storage() : root(nullptr) {};

    // ~BinarySearchTree() {};

    void addBook(int _id, std::string _title, std::string _author, int _quantity) {
        root = _addBook(root, _id, _title, _author, _quantity);
    };

    void viewAll() { _viewAll(root); }

    void searchBookById(int id) {
        Book* book = getBookByID(id);
        if (book == nullptr) {
            logger::warning("Cannot found book, try again!");
        } else {
            logger::succeed("Found successfully!");
            table::header();
            table::content(book->id, book->title, book->author, book->quantity);
        }
    }

    void searchBookByTitle(std::string title) {
        Book* book = getBookByTitle(title);
        if (book == nullptr) {
            logger::warning("Cannot found book, try again!");
        } else {
            logger::succeed("Found successfully!");
            table::header();
            table::content(book->id, book->title, book->author, book->quantity);
        }
    }

    void searchBookByAuthor(std::string author) {
        Book* book = getBookByAuthor(author);
        if (book == nullptr) {
            logger::warning("Cannot found book, try again!");
        } else {
            logger::succeed("Found successfully!");
            table::header();
            table::content(book->id, book->title, book->author, book->quantity);
        }
    }

    void issueBook(int id, std::string _br_date, std::string _rt_date, std::string _phone_nb) {
        Book* book = getBookByID(id);
        if (book == nullptr) {
            logger::warning("No book with given book id in library, please try again!");
        } else if (book->quantity > 0) {
            _issueBook(book, _br_date, _rt_date, _phone_nb);
            book->quantity -= 1;
            logger::succeed("Issue book succeeded");
        } else {
            logger::warning("There are no book left in library, please try later!");
        }
    }

    void returnBook(int id, std::string _phone_nb) {
        Book* book = getBookByID(id);
        int haha;
        if (book == nullptr) {
            logger::warning("Cannot found book with given book id, please try again!");
            return;
        }

        Borrow* current = book->borrowList;
        if (current == nullptr) {
            logger::warning("The book with the given ID is not listed as borrowed - null");
            return;
        }

        Borrow* head = book->borrowList;
        if (head->phone_nb == _phone_nb) {
            book->borrowList = book->borrowList->next;
            book->quantity += 1;
            delete current;
            logger::succeed("Book returned successfully!");
            return;
        }

        Borrow* before;
        while (current->next != nullptr) {
            before = current;
            current = current->next;

            if (current->next == nullptr && current->phone_nb == _phone_nb) {
                before->next = nullptr;
                book->quantity += 1;
                delete current;
                logger::succeed("Book returned successfully!");
                return;
            }

            if (current->phone_nb == _phone_nb) {
                before->next = current->next;
                book->quantity += 1;
                delete current;
                logger::succeed("Book returned successfully!");
                return;
            }
        }

        logger::warning("The book with the given ID is not listed as borrowed");
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
        if (target == nullptr) {
            return nullptr;
        } else if (id < target->id) {
            if (target->left == nullptr) {
                return nullptr;
            } else {
                return _getBookByID(target->left, id);
            }
        } else if (id > target->id) {
            if (target->right == nullptr) {
                return nullptr;
            } else {
                return _getBookByID(target->right, id);
            }
        } else {
            return target;
        }
    };

    Book* getBookByTitle(std::string title) { return _getBookByTitle(root, title); }

    Book* _getBookByTitle(Book* target, std::string title) {
        if (target == nullptr) {
            return nullptr;
        };
        if (_getBookByTitle(target->left, title) != nullptr) {
            return _getBookByTitle(target->left, title);
        } else if (target->title == title) {
            return target;
        } else if (_getBookByTitle(target->right, title) != nullptr) {
            return _getBookByTitle(target->right, title);
        } else {
            return nullptr;
        }
    }

    Book* getBookByAuthor(std::string author) { return _getBookByAuthor(root, author); }

    Book* _getBookByAuthor(Book* target, std::string author) {
        if (target == nullptr) {
            return nullptr;
        };
        if (_getBookByAuthor(target->left, author) != nullptr) {
            return _getBookByAuthor(target->left, author);
        } else if (target->author == author) {
            return target;
        } else if (_getBookByAuthor(target->right, author) != nullptr) {
            return _getBookByAuthor(target->right, author);
        } else {
            return nullptr;
        }
    }

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
