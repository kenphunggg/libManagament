#include <logger.h>
#include <session.h>
#include <storage.h>

#include <iomanip>
#include <iostream>

namespace session {
void return_book(Storage* bookstorage) {
    int book_id;
    std::string phone_number;

    std::cout << ">>> Please insert book id >>> ";
    std::cin >> book_id;

    std::cout << ">>> Please insert phone number >>> ";
    std::cin >> phone_number;

    bookstorage->returnBook(book_id, phone_number);
};

};  // namespace session
