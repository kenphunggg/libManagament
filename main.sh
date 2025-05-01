#!/bin/bash

# Clear the screen
clear

log_alert() {
  # Check if any arguments were provided
  if [ $# -eq 0 ]; then
    # Optionally print an error or usage message to standard error
    # >&2 redirects output to stderr
    printf "Usage: log_alert <text to display>\n" >&2
    return 1 # Indicate failure
  fi
  # "$@" passes all arguments exactly as they were received,
  # preserving spaces within quoted arguments.
  printf '\e[1;37;41m%s\e[0m\n' "$@"
}

# Clean previous build files
log_alert "---- Clean previous project -----"
make clean
echo "" # Add a blank line for spacing

# Build the project using the makefile
log_alert "----- Building project -----"
make
echo "" # Add a blank line for spacing

# Check if the build was successful (if the executable exists)
# The 'make' command usually returns a non-zero status on failure,
# but we can also explicitly check for the executable file.
if [ -f main ]; then
  log_alert "----- Running executable -----"
  # Execute the final program (not the .o file)
  clear
  ./main
else
  log_alert "--- Build failed, executable 'main' not found ---"
  # Exit with an error code if the build failed
  exit 1
fi