#include <logger.h>
#include <session.h>
#include <storage.h>

#include <iomanip>
#include <iostream>

int main() {
    int const ADD_NEW_BOOK = 1;
    int const VIEW_ALL_BOOK = 2;
    int const SEARCH_BOOK = 3;
    int const ISSUE_BOOK = 4;
    int const RETURN_BOOK = 5;
    int const EXIT = 0;

    std::cout << R"(
     _     _ _                                _                _ _           _   _             
    | |   (_) |__  _ __ __ _ _ __ _   _      / \   _ __  _ __ | (_) ___ __ _| |_(_) ___  _ __  
    | |   | | '_ \| '__/ _` | '__| | | |    / _ \ | '_ \| '_ \| | |/ __/ _` | __| |/ _ \| '_ \ 
    | |___| | |_) | | | (_| | |  | |_| |   / ___ \| |_) | |_) | | | (_| (_| | |_| | (_) | | | |
    |_____|_|_.__/|_|  \__,_|_|   \__, |  /_/   \_\ .__/| .__/|_|_|\___\__,_|\__|_|\___/|_| |_|
                                  |___/           |_|   |_|                                     
    )" << std::endl;

    Storage* bookstorage;
    std::string main_file = "./data/main.csv";
    std::string borrow_file = "./data/borrow.csv";
    std::string temp_file = "./data/temp.csv";

    bookstorage = new Storage(main_file, borrow_file, temp_file);
    // bookstorage->initStorage();

    while (true) {
        logger::info("----- Choose your action -----");
        std::cout << "1. Add new books\n";
        std::cout << "2. View all books\n";
        std::cout << "3. Search for books\n";
        std::cout << "4. Issue book\n";
        std::cout << "5. Return book\n";
        std::cout << "0. Exit\n";
        logger::info("----- Your choice -----");

        int action;
        std::cin >> action;

        if (action == ADD_NEW_BOOK) {  // --- 1. Add new books ---
            session::add_new_book(bookstorage);
        } else if (action == VIEW_ALL_BOOK) {  // --- 2. View all books ---
            session::view_all_book(bookstorage);
        } else if (action == SEARCH_BOOK) {  // --- 3. Search for books ---
            session::search_book(bookstorage);
        } else if (action == ISSUE_BOOK) {  // --- 4. Issue book ---
            session::issue_book(bookstorage);
        } else if (action == RETURN_BOOK) {  // --- 5. Return book ---
            session::return_book(bookstorage);
        } else if (action == EXIT) {  // --- 0. Exit ---
            logger::succeed("End session, see you later!");
            return 0;
        } else {
            logger::warning("Wrong syntax, try another action (1-3) :<<<");
        };
    };

    return 0;
}
