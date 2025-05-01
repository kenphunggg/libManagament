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
        std::cout << "1. Add new books\n";
        std::cout << "2. View all books\n";
        std::cout << "3. Search for books\n";
        std::cout << "0. Exit\n";
        logger::info("----- Your choice -----");

        int action;
        std::cin >> action;

        if (action == 1) {  // --- 1. Add new books ---
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

        } else if (action == 2) {  // --- 2. View all books ---
            logger::debug("View all books");
            if (bookstorage.isNull()) {
                logger::warning("Book storage is null, please try later!");
                std::cout << "\n" << "\n" << "\n";
            } else {
                table::header();
                bookstorage.viewAll();

                logger::info("----- Choose your action -----");
                std::cout << "1. Issue book\n";
                std::cout << "0. Back\n";
                logger::info("----- Your choice -----");

                int view_action;
                std::cin >> view_action;

                if (view_action == 1) {
                    logger::debug("Issue a book");

                    int book_id;
                    std::string borrow_date;
                    std::string return_date;
                    std::string phone_number;

                    std::cout << ">>> Please insert book id >>> ";
                    std::cin >> book_id;

                    std::cout << ">>> Please insert borrow date >>> ";
                    std::cin >> borrow_date;

                    std::cout << ">>> Please insert return date >>> ";
                    std::cin >> return_date;

                    std::cout << ">>> Please insert phone number >>> ";
                    std::cin >> phone_number;

                    bookstorage.issueBook(book_id, borrow_date, return_date, phone_number);
                } else if (view_action == 0) {
                    continue;
                } else {
                    logger::warning("Wrong syntax, you are forwarded to main page");
                }

                std::cout << "\n" << "\n" << "\n";
            }

        } else if (action == 3) {  // --- 3. Search for books ---
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
                std::cout << "Received book id" << id << std::endl;
            } else if (search_action == 2) {  // --- 3.2. Search by title ---
                std::cout << ">>> Please insert book title >>> ";
            } else if (search_action == 3) {  // --- 3.3. Search by author ---
                std::cout << ">>> Please insert book author >>> ";
            } else if (search_action == 0) {  // --- 3.0. Back ---
                continue;
            } else {
                logger::warning("Wrong syntax, try another action (1-3) :<<<");
                continue;
            }

            logger::info("----- Your choice -----");
            std::cout << "\n" << "\n" << "\n";
        } else if (action == 0) {  // --- 0. Exit ---
            logger::succeed("End session, see you later!");
            return 0;
        } else {
            logger::warning("Wrong syntax, try another action (1-3) :<<<");
        };
    };

    return 0;
}
