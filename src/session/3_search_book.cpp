#include <logger.h>
#include <session.h>
#include <storage.h>

#include <iomanip>
#include <iostream>

namespace session {
void search_book(Storage* bookstorage) {
    int search_action;

    logger::debug("Search for books");
    logger::info("----- Choose your action -----");
    std::cout << "1. By book id\n";
    std::cout << "2. By book title\n";
    std::cout << "3. By book author\n";
    std::cout << "0. Back \n";
    logger::info("----- Your choice -----");

    std::cin >> search_action;

    if (search_action == 1) {  // --- 3.1. Search by id ---
        int id;
        std::cout << ">>> Please insert book id >>> ";
        std::cin >> id;
        bookstorage->searchBookById(id);

    } else if (search_action == 2) {  // --- 3.2. Search by title ---
        std::string title;
        std::cout << ">>> Please insert book title >>> ";
        std::getline(std::cin >> std::ws, title);
        bookstorage->searchBookByTitle(title);

    } else if (search_action == 3) {  // --- 3.3. Search by author ---
        std::string author;
        std::cout << ">>> Please insert book author >>> ";
        std::getline(std::cin >> std::ws, author);
        bookstorage->searchBookByAuthor(author);

    } else if (search_action == 0) {  // --- 3.0. Back ---
                                      // Next session
    } else {
        logger::warning("Wrong syntax, try another action (1-3) :<<<");
    }
};

};  // namespace session
