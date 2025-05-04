#ifndef SESSION_H
#define SESSION_H

#include <logger.h>
#include <storage.h>

#include <iomanip>
#include <iostream>

namespace session {

void add_new_book(Storage* bookstorage);

void view_all_book(Storage* bookstorage);

void search_book(Storage* bookstorage);

void issue_book(Storage* bookstorage);

void return_book(Storage* bookstorage);

}  // namespace session

#endif
