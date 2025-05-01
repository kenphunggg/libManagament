# --- Makefile for Project Structure ---

# Compiler settings
CC = g++
# C Preprocessor Flags (for -I include paths, -D definitions)
CPPFLAGS = -Iinclude
# C++ Compiler Flags (warnings, standard, optimization)
CXXFLAGS = -Wall -std=c++17
# Linker Flags (rarely needed for simple projects)
LDFLAGS =

# Executable name
EXECUTABLE = main

# --- Files ---
# List ALL your source (.cpp) files here, including paths
SOURCES = src/main.cpp src/logger.cpp 

# List ALL relevant header (.h, .hpp) files here, including paths
# This ensures recompilation if a header changes.
HEADERS = include/logger.h include/storage.h

# --- Automatic Variables ---
# Creates object file names based on SOURCES (e.g., src/main.o, src/logger.o)
OBJECTS = $(SOURCES:.cpp=.o)

# --- Rules ---

# Default target: Build the executable (first target in the file)
all: $(EXECUTABLE)

# Linking rule: Create the executable from object files
# Depends on all object files listed in $(OBJECTS)
# IMPORTANT: The command line below MUST start with a TAB character, not spaces.
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE) # Use $(CC) for linking C++

# Pattern rule for compiling .cpp files into .o files
# Handles files in src/ (e.g., src/main.cpp -> src/main.o)
# Depends on the corresponding .cpp file and ALL listed headers.
# $< is the first prerequisite (the .cpp file)
# $@ is the target (the .o file)
# IMPORTANT: The command line below MUST start with a TAB character, not spaces.
%.o: %.cpp $(HEADERS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ # <<< MAKE SURE THIS LINE STARTS WITH A TAB!

# --- Cleanup ---
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

# --- Phony Targets ---
# Tells make that 'all' and 'clean' are not actual files to be built
.PHONY: all clean

