#include <logger.h>
#include <session.h>
#include <storage.h>

#include <iomanip>
#include <iostream>

namespace session {

void view_all_book(Storage* bookstorage) {
    logger::debug("View all books");
    if (bookstorage->isNull()) {
        logger::warning("Book storage is null, please try later!");
    } else {
        table::header();
        bookstorage->viewAll();

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

            bookstorage->issueBook(book_id, borrow_date, return_date, phone_number);

        } else if (view_action == 0) {
            // Next session
        } else {
            logger::warning("Wrong syntax, you are forwarded to main page");
        }
    }
};
}  // namespace session
