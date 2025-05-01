#include <logger.h>
#include <storage.h>

#include <iomanip>
#include <iostream>

int main() {
    std::cout << R"(
     _     _ _                                _                _ _           _   _             
    | |   (_) |__  _ __ __ _ _ __ _   _      / \   _ __  _ __ | (_) ___ __ _| |_(_) ___  _ __  
    | |   | | '_ \| '__/ _` | '__| | | |    / _ \ | '_ \| '_ \| | |/ __/ _` | __| |/ _ \| '_ \ 
    | |___| | |_) | | | (_| | |  | |_| |   / ___ \| |_) | |_) | | | (_| (_| | |_| | (_) | | | |
    |_____|_|_.__/|_|  \__,_|_|   \__, |  /_/   \_\ .__/| .__/|_|_|\___\__,_|\__|_|\___/|_| |_|
                                  |___/           |_|   |_|                                     
    )" << std::endl;

    Storage bookstorage;

    while (true) {
        logger::info("----- Choose your action -----");
        std::cout << "1. Add new books\t";
        std::cout << "2. View all books\t";
        std::cout << "3. Search for books\t";
        std::cout << "0. Exit\n";
        logger::info("----- Your choice -----");

        int action;
        std::cin >> action;

        if (action == 1) {
            int id;
            std::string title;
            std::string author;
            int quantity;

            logger::debug("Please add new book");

            std::cout << ">>> Please insert book id >>> ";
            std::cin >> id;

            std::cout << ">>> Please insert book title >>> ";
            std::getline(std::cin >> std::ws, title);

            std::cout << ">>> Please insert book author >>> ";
            std::getline(std::cin >> std::ws, author);

            std::cout << ">>> Please insert book quantity >>> ";
            std::cin >> quantity;

            bookstorage.addBook(id, title, author, quantity);

            std::cout << "\n" << "\n" << "\n";
        } else if (action == 2) {
            logger::debug("View all books");
            if (bookstorage.isNull()) {
                logger::warning("Book storage is null, please try later!");
                std::cout << "\n" << "\n" << "\n";
            } else {
                table::header();
                bookstorage.viewAll();
                std::cout << "\n" << "\n" << "\n";
            }

        } else if (action == 3) {
            logger::debug("Search for books");
            std::cout << "\n" << "\n" << "\n";
        } else if (action == 0) {
            logger::succeed("End session, see you later!");
            return 0;
        } else {
            logger::warning("Wrong syntax, try another action (1-3) :<<<");
        };
    };

    return 0;
}
