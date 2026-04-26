# <p align="center"> Get Next Line - File Reading Utility </p>

**42 Project | File I/O & Static Variables**  
**Objective:** Implement a function that reads a line from a file descriptor, handling multiple file descriptors and variable buffer sizes.

---

## Overview

**Get Next Line** teaches file I/O operations, static variables, and memory management in C. The function reads from a file descriptor line by line, handling edge cases like empty files, files without newlines, and multiple file descriptors simultaneously.

---

## Skills Demonstrated

- **File I/O:** Reading from file descriptors using `read()` system call
- **Static Variables:** Maintaining state between function calls
- **Memory Management:** Dynamic allocation and buffer management
- **Buffer Handling:** Efficient reading with configurable buffer sizes
- **Edge Case Handling:** Empty files, files without newlines, multiple FDs

---

## Project Structure

```
gnl/
├── get_next_line.c			    # Mandatory version (single FD)
├── get_next_line.h			    # Header for mandatory version
├── get_next_line_utils.c		# Utility functions for mandatory
├── get_next_line_bonus.c		# Bonus version (multiple FDs)
├── get_next_line_bonus.h		# Header for bonus version
├── get_next_line_utils_bonus.c	# Utility functions for bonus
└── main.c				        # Sample usage program (for testing)
└── Makefile				    # (for testing)
```

**Key Files:**
- **Mandatory:** [`get_next_line.c`](get_next_line.c) + [`get_next_line_utils.c`](get_next_line_utils.c) - Handles single file descriptor
- **Bonus:** [`get_next_line_bonus.c`](get_next_line_bonus.c) + [`get_next_line_utils_bonus.c`](get_next_line_utils_bonus.c) - Handles multiple file descriptors simultaneously
- **Sample:** [`main.c`](main.c) - Example usage for testing (not required for project)

---

## Technical Implementation

### Core Concepts

**Static Buffer:**
- Uses static variables to maintain state between calls
- Stores leftover data from previous reads
- Handles multiple file descriptors independently (bonus version)

**Reading Strategy:**
1. Read data into buffer using `read()` system call
2. Check for newline character in buffer
3. Extract line up to newline
4. Store remaining data for next call
5. Return extracted line

**Memory Management:**
- Dynamically allocates memory for lines
- Properly frees memory when appropriate
- Handles memory allocation failures

---

## Features

### Mandatory Version
- Reads one line at a time from file descriptor
- Handles files without newlines
- Handles empty files
- Configurable `BUFFER_SIZE` via compilation flag
- Proper memory management

### Bonus Version
- Handles multiple file descriptors simultaneously
- Maintains separate state for each file descriptor
- Efficient memory usage across multiple files

---

## Usage

**Example Usage:**
See [`main.c`](main.c) for example usage demonstrating how to read from files line by line.

The function is used by including the header file and calling `get_next_line()` in a loop until it returns `NULL` or `-1`.

---

## Testing

The project has been tested with:
- **[gnlTester](https://github.com/Tripouille/gnlTester)** - Comprehensive test suite for various buffer sizes and edge cases
- Custom test cases for empty files, files without newlines, and large files

---

## Resources

[Reading and Writing Files in C (fopen vs. open)](https://www.youtube.com/watch?v=BQJBe4IbsvQ)
[Oceano - gnl explained](https://www.youtube.com/watch?v=8E9siq7apUU)

*This project demonstrates mastery of file I/O operations, static variables, and efficient memory management in C.*
