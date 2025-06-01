#include "storage.h"

#include <logger.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Storage::Borrow::Borrow(std::string br, std::string rt, std::string p) {
    br_date = br;
    rt_date = rt;
    phone_nb = p;
    next = nullptr;
}

Storage::Book::Book(int i, std::string t, std::string a, int q) {
    id = i;
    title = t;
    author = a;
    quantity = q;
    left = nullptr;
    right = nullptr;
    borrowList = nullptr;
}

Storage::Storage(std::string mf, std::string bf, std::string tf) {
    root = nullptr;
    main_file = mf;
    borrow_file = bf;
    temp_file = tf;
    init_storage();
    init_borrow();
    init = false;
}

void Storage::addBook(int _id, std::string _title, std::string _author, int _quantity) {
    root = _addBook(root, _id, _title, _author, _quantity);
}

void Storage::viewAll() { _viewAll(root); }

void Storage::searchBookById(int id) {
    Book* book = getBookByID(id);
    if (book == nullptr) {
        logger::warning("Cannot found book, try again!");
    } else {
        logger::succeed("Found successfully!");
        table::header();
        table::content(book->id, book->title, book->author, book->quantity);
    }
}

void Storage::searchBookByTitle(std::string title) {
    Book* book = getBookByTitle(title);
    if (book == nullptr) {
        logger::warning("Cannot found book, try again!");
    } else {
        logger::succeed("Found successfully!");
        table::header();
        table::content(book->id, book->title, book->author, book->quantity);
    }
}

void Storage::searchBookByAuthor(std::string author) {
    Book* book = getBookByAuthor(author);
    if (book == nullptr) {
        logger::warning("Cannot found book, try again!");
    } else {
        logger::succeed("Found successfully!");
        table::header();
        table::content(book->id, book->title, book->author, book->quantity);
    }
}

void Storage::issueBook(int id, std::string _br_date, std::string _rt_date, std::string _phone_nb) {
    Book* book = getBookByID(id);
    if (book == nullptr) {
        logger::warning("No book with given book id in library, please try again!");
    } else if (book->quantity > 0) {
        if (!init) {
            book->quantity -= 1;
        }
        _issueBook(book, _br_date, _rt_date, _phone_nb);

        logger::succeed("Issue book successfully!");
    } else {
        logger::warning("There are no book left in library, please try later!");
    }
}

void Storage::returnBook(int id, std::string _phone_nb) {
    Book* book = getBookByID(id);
    if (book == nullptr) {
        logger::warning("Cannot found book with given book id, please try again!");
        return;
    }

    if (book->borrowList == nullptr) {
        logger::warning("The book with the given ID is not listed as borrowed - null");
        return;
    }

    Borrow* current = book->borrowList;
    Borrow* head = book->borrowList;

    if (head->phone_nb == _phone_nb) {
        book->borrowList = book->borrowList->next;
        book->quantity += 1;
        update_storage();
        update_borrow_rm(id, _phone_nb);
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
            update_storage();
            update_borrow_rm(id, _phone_nb);
            delete current;
            logger::succeed("Book returned successfully!");
            return;
        }

        if (current->phone_nb == _phone_nb) {
            before->next = current->next;
            book->quantity += 1;
            update_storage();
            update_borrow_rm(id, _phone_nb);
            delete current;
            logger::succeed("Book returned successfully!");
            return;
        }
    }

    logger::warning("The book with the given ID is not listed as borrowed");
}

bool Storage::isNull() {
    if (root == nullptr) {
        return true;
    } else {
        return false;
    }
}

void Storage::init_storage() {
    std::fstream _mainfile;

    _mainfile.open(main_file, std::ios::in);
    if (!_mainfile.is_open()) {
        logger::warning("Error: Could not open file data/main.csv");
        return;  // Exit the function if the file can't be opened
    }

    // Read the Data from the file as string vector
    std::vector<std::string> row;
    std::string line, word, temp;

    getline(_mainfile, line);
    while (std::getline(_mainfile, line)) {
        row.clear();

        // used for breaking words
        std::stringstream s(line);

        while (getline(s, word, ',')) {
            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }

        if (!row.empty()) {
            // logger::debug(row[0] + row[1] + row[2] + row[3]);
            addBook(std::stoi(row[0]), row[1], row[2], std::stoi(row[3]));
        }
    }

    _mainfile.close();
}

void Storage::init_borrow() {
    std::fstream _mainfile;

    _mainfile.open(borrow_file, std::ios::in);
    if (!_mainfile.is_open()) {
        logger::warning("Error: Could not open file data/main.csv");
        return;  // Exit the function if the file can't be opened
    }

    // Read the Data from the file as string vector
    std::vector<std::string> row;
    std::string line, word, temp;

    getline(_mainfile, line);
    while (std::getline(_mainfile, line)) {
        row.clear();

        // used for breaking words
        std::stringstream s(line);

        while (getline(s, word, ',')) {
            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }

        if (!row.empty()) {
            issueBook(std::stoi(row[0]), row[1], row[2], row[3]);
        }
    }
    init = false;

    _mainfile.close();
}

void Storage::update_storage() {
    std::fstream _mainfile;
    _mainfile.open(main_file, std::ios::out);

    if (!_mainfile.is_open()) {
        logger::warning("Error: Could not open file data/main.csv");
        return;  // Exit the function if the file can't be opened
    }

    update_main_db(_mainfile);

    _mainfile.close();
}

void Storage::update_main_db(std::fstream& db) {
    db << "id,title,author,quantity\n";
    _update_main_db(root, db);
}

void Storage::_update_main_db(Book* target, std::fstream& db) {
    if (target == nullptr) {
        return;
    }
    _update_main_db(target->left, db);
    db << target->id << "," << target->title << "," << target->author << "," << target->quantity
       << "\n";

    _update_main_db(target->right, db);
}

Storage::Book* Storage::_addBook(Storage::Book* target, int _id, std::string _title,
                                 std::string _author, int _quantity) {
    if (target == nullptr) {
        Storage::Book* newBook = new Storage::Book(_id, _title, _author, _quantity);
        if (!init) {
            std::fstream _mainfile;

            _mainfile.open(main_file, std::ios::out | std::ios::app);

            if (!_mainfile.is_open()) {
                logger::warning("Error: Could not open file data/main.csv");
                return nullptr;  // Exit the function if the file can't be opened
            }

            _mainfile << _id << "," << _title << "," << _author << "," << _quantity << "\n";

            _mainfile.close();
        }
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
                update_storage();
                logger::succeed("Update book quantity successfully!");
            };
        }
    }

    return target;
}

void Storage::_viewAll(Book* target) {
    if (target == nullptr) {
        return;
    };
    _viewAll(target->left);
    table::content(target->id, target->title, target->author, target->quantity);
    _viewAll(target->right);
}

Storage::Book* Storage::getBookByID(int id) { return _getBookByID(root, id); }

Storage::Book* Storage::_getBookByID(Book* target, int id) {
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

Storage::Book* Storage::getBookByTitle(std::string title) { return _getBookByTitle(root, title); }

Storage::Book* Storage::_getBookByTitle(Book* target, std::string title) {
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

Storage::Book* Storage::getBookByAuthor(std::string author) {
    return _getBookByAuthor(root, author);
}

Storage::Book* Storage::_getBookByAuthor(Book* target, std::string author) {
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

void Storage::_issueBook(Book* targetBook, std::string _br_date, std::string _rt_date,
                         std::string _phone_nb) {
    Borrow* newBorrow = new Borrow(_br_date, _rt_date, _phone_nb);
    if (!init) {
        std::fstream _borrowfile;

        _borrowfile.open(borrow_file, std::ios::out | std::ios::app);

        if (!_borrowfile.is_open()) {
            logger::warning("Error: Could not open file data/borrow.csv");
            return;  // Exit the function if the file can't be opened
        }

        _borrowfile << targetBook->id << "," << _br_date << "," << _rt_date << "," << _phone_nb
                    << "\n";

        _borrowfile.close();

        update_storage();
    }

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

void Storage::update_borrow_rm(int id, std::string _phone_nb) {
    std::fstream _borrowfile, _tempfile;

    _borrowfile.open(borrow_file, std::ios::in);
    _tempfile.open(temp_file, std::ios::out);

    if (!_borrowfile.is_open()) {
        logger::warning("Error: Could not open file data/borrow.csv");
    }

    if (!_tempfile.is_open()) {
        logger::warning("Error: Could not open file data/borrow.csv");
    }

    _tempfile << "id,borrow date,return date,phone number" << "\n";

    logger::critical("Update borrow rm");

    std::vector<std::string> row;
    std::string line, word;

    bool found_book = false;

    getline(_borrowfile, line);
    while (getline(_borrowfile, line)) {
        row.clear();

        if (line.empty()) {
            continue;
        }

        std::stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        if (id != std::stoi(row[0]) || _phone_nb != row[3]) {
            for (int i = 0; i < (row.size() - 1); i++) {
                std::cout << row[i] << " ";
                _tempfile << row[i] << ",";
            }
            std::cout << row[row.size() - 1] << "\n";
            _tempfile << row[row.size() - 1] << "\n";
        } else {
            found_book = true;
        }
    }

    if (!found_book) {
        logger::warning("Book not found in database");
    }

    _borrowfile.close();
    _tempfile.close();

    remove("data/borrow.csv");

    rename("data/temp.csv", "data/borrow.csv");
}