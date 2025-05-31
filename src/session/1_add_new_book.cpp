#include <logger.h>
#include <session.h>
#include <storage.h>

#include <fstream>
#include <iomanip>
#include <iostream>

namespace session {
void add_new_book(Storage* bookstorage) {
    int id;
    std::string title;
    std::string author;
    int quantity;

    logger::debug("----- Please add new book -----");

    std::cout << ">>> Please insert book id >>> ";
    std::cin >> id;

    std::cout << ">>> Please insert book title >>> ";
    std::getline(std::cin >> std::ws, title);

    std::cout << ">>> Please insert book author >>> ";
    std::getline(std::cin >> std::ws, author);

    std::cout << ">>> Please insert book quantity >>> ";
    std::cin >> quantity;

    bookstorage->addBook(id, title, author, quantity);
};

};  // namespace session
