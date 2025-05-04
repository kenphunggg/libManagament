#include <logger.h>
#include <session.h>
#include <storage.h>

#include <iomanip>
#include <iostream>

namespace session {
void issue_book(Storage* bookstorage) {
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
};

};  // namespace session
