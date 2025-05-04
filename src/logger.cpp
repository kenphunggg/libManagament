#include "logger.h"  // Include the header file with declarations

#include <iomanip>
#include <iostream>  // Needed for std::cout

// Define the constants declared as extern in the header
namespace Color {
const std::string RESET = "\033[0m";
const std::string FG_RED = "\033[31m";
const std::string FG_GREEN = "\033[32m";
const std::string FG_YELLOW = "\033[33m";
const std::string FG_BLUE = "\033[34m";
const std::string FG_MAGENTA = "\033[35m";
// --- Bold Color Options ---
const std::string FG_BOLD_RED = "\033[1;31m";
const std::string FG_BOLD_GREEN = "\033[1;32m";
const std::string FG_BOLD_YELLOW = "\033[1;33m";
const std::string FG_BOLD_BLUE = "\033[1;34m";
const std::string FG_BOLD_MAGENTA = "\033[1;35m";
}  // namespace Color

// Define the functions declared in logger.h within the Logger namespace
namespace logger {
// --- Println Functions (with newline) ---
void normal(const std::string& text) { std::cout << text << std::endl; }

void warning(const std::string& text) {
    std::cout << Color::FG_BOLD_RED << text << Color::RESET << std::endl;
}

void succeed(const std::string& text) {
    std::cout << Color::FG_BOLD_GREEN << text << Color::RESET << std::endl;
}

void info(const std::string& text) {
    std::cout << Color::FG_BOLD_BLUE << text << Color::RESET << std::endl;
}

void debug(const std::string& text) {
    std::cout << Color::FG_BOLD_YELLOW << text << Color::RESET << std::endl;
}

void critical(const std::string& text) {
    std::cout << Color::FG_BOLD_MAGENTA << text << Color::RESET << std::endl;
}

void nextSession() {
    std::cout << "======================================" << std::endl;
    std::cout << "\n" << "\n" << "\n";
    std::cout << "======================================" << std::endl;
};
}  // namespace logger

namespace table {
// Define column widths (adjust as needed)
const int idWidth = 5;         // Width for ID column
const int titleWidth = 40;     // Width for Title column (needs to be large)
const int authorWidth = 35;    // Width for Author column
const int quantityWidth = 10;  // Width for Quantity column

void header() {
    std::cout << std::left  // Set left alignment for subsequent text outputs
              << std::setw(idWidth) << "ID" << std::setw(titleWidth) << "TITLE"
              << std::setw(authorWidth) << "AUTHOR" << std::setw(quantityWidth) << "QUANTITY"
              << std::endl;
};

void content(int id, std::string title, std::string author, int quantity) {
    std::cout << std::left  // Ensure left alignment (though it's sticky)
              << std::setw(idWidth) << id << std::setw(titleWidth) << title
              << std::setw(authorWidth) << author << std::setw(quantityWidth) << quantity
              << std::endl;
};

}  // namespace table
