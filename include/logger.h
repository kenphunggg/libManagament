#ifndef LOGGER_H  // Start of header guard
#define LOGGER_H

#include <string>  // Needed for std::string

// Define ANSI color codes in a separate namespace for clarity
// These constants are typically defined in the header for use by the implementation
// and potentially other files if needed directly.
namespace Color {
extern const std::string RESET;  // Use extern for constants defined in .cpp
extern const std::string FG_RED;
extern const std::string FG_GREEN;
extern const std::string FG_YELLOW;
extern const std::string FG_BLUE;
extern const std::string FG_MAGENTA;

extern const std::string FG_BOLD_RED;
extern const std::string FG_BOLD_GREEN;
extern const std::string FG_BOLD_YELLOW;
extern const std::string FG_BOLD_BLUE;
extern const std::string FG_BOLD_MAGENTA;
}  // namespace Color

// Namespace to group the logger functions
namespace logger {

// --- Function Declarations ---

// Println Functions (with newline)
void normal(const std::string& text);
void warning(const std::string& text);
void succeed(const std::string& text);
void info(const std::string& text);
void debug(const std::string& text);
void critical(const std::string& text);
void nextSession();

}  // namespace logger

namespace table {
// Define column widths (adjust as needed)
extern const int idWidth;        // Width for ID column
extern const int titleWidth;     // Width for Title column (needs to be large)
extern const int authorWidth;    // Width for Author column
extern const int quantityWidth;  // Width for Quantity column

void header();

void content(int id, std::string title, std::string author, int quantity);

}  // namespace table

#endif  // LOGGER_H // End of header guard
