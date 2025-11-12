# Effective C - Code Examples

A comprehensive collection of C programming examples based on the book "Effective C" by Robert C. Seacord. This repository contains practical, well-documented code examples organized by chapter, covering fundamental to advanced C programming concepts.

## 📚 Repository Structure

```
effective-c/
├── ch1/          # Introduction to C (Hello World, basics)
├── ch2/          # Objects, Functions, and Types
├── ch3/          # Arithmetic Types
├── ch4/          # Expressions and Operators
├── ch5/          # Control Flow
├── ch6/          # Dynamic Memory Management
├── ch7/          # Characters and Strings
├── ch8/          # Standard I/O Streams
├── ch9/          # Preprocessor
├── run.sh        # Compilation and execution utility
└── README.md     # This file
```

Each chapter contains:

- **`listings/`** - Core examples from the book
- **`misc/`** - Additional examples and edge cases

## 🚀 Quick Start

### Prerequisites

- **C Compiler**: GCC or Clang
- **Operating System**: macOS, Linux, or WSL on Windows
- **Shell**: Bash or Zsh

### Using the `run.sh` Utility

The `run.sh` script simplifies compiling and running C examples.

#### Basic Usage

```bash
# Compile and run a single file
./run.sh ch1/listing1/hello.c

# Quick mode: skip code listing before compilation
./run.sh -q ch8/listings/opening_files.c

# Compile all files in the repository
./run.sh -a

# Clean all compiled binaries
./run.sh -c
```

#### Command Options

| Option                 | Description                                              |
| ---------------------- | -------------------------------------------------------- |
| `./run.sh <file.c>`    | Compile and run a specific C file                        |
| `./run.sh -q <file.c>` | **Quick mode** - Skip code listing, just compile and run |
| `./run.sh -a`          | Compile all `.c` files in the repository                 |
| `./run.sh -c`          | Clean all compiled binaries from `build/` directory      |

#### Examples

```bash
# Run a specific example with code listing
./run.sh ch7/listings/string_basics.c

# Quick run without seeing the source code first
./run.sh -q ch6/listings/malloc_example.c

# Compile everything
./run.sh -a

# Clean up compiled files
./run.sh -c
```

### Manual Compilation

If you prefer to compile manually:

```bash
# Basic compilation
gcc -Wall -Wextra -std=c11 -O2 -o program file.c

# Run the compiled program
./program

# View preprocessed output (useful for Chapter 9)
gcc -E -o translation.i file.c
```

## 📖 Chapter Overview

### Chapter 1: Introduction to C

- Hello World programs
- Basic syntax and structure
- Comments, format specifiers, escape sequences
- Command-line arguments

### Chapter 2: Objects, Functions, and Types

- Variable declarations
- Function definitions
- Static variables and scope

### Chapter 3: Arithmetic Types

- Integer and floating-point types
- Type limits and ranges
- Arithmetic operations

### Chapter 4: Expressions and Operators

- Operator precedence
- Type conversions
- Expression evaluation

### Chapter 5: Control Flow

- Conditional statements
- Loops and iteration
- Switch statements

### Chapter 6: Dynamic Memory Management

- `malloc()`, `calloc()`, `realloc()`, `free()`
- Memory leaks and double frees
- Dangling pointers
- Aligned allocation

### Chapter 7: Characters and Strings

- String manipulation
- Character classification
- String searching and tokenization

### Chapter 8: Standard I/O Streams

- File operations (`fopen`, `fclose`, `fread`, `fwrite`)
- Formatted I/O (`printf`, `scanf` families)
- POSIX I/O (`open`, `read`, `write`, `lseek`)
- Wide character I/O
- Binary I/O with structures
- **Quick Reference Cards** available in markdown format

### Chapter 9: Preprocessor

- Compilation process (`-E`, `-S`, `-c` flags)
- File inclusion (`#include`)
- Conditional compilation (`#ifdef`, `#if`)
- Macro definitions and techniques

## 🎯 Key Features

- **Comprehensive Examples**: Each topic includes multiple test cases
- **Error Handling**: Demonstrates proper error checking patterns
- **Best Practices**: Includes notes on common pitfalls and recommendations
- **Platform Compatibility**: Works on macOS, Linux, and WSL
- **Quick Reference**: Markdown cheat sheets for I/O functions (Chapter 8)

## 🔧 Compiler Configuration

The `run.sh` script uses these default settings:

```bash
CC=gcc                              # Compiler (can use clang)
CFLAGS="-Wall -Wextra -std=c11 -O2" # Compilation flags
```

To override:

```bash
# Use Clang instead of GCC
CC=clang ./run.sh file.c

# Add debugging symbols
CFLAGS="-Wall -Wextra -std=c11 -g" ./run.sh file.c
```

## 📝 Code Style

All examples follow consistent conventions:

- **C11 standard** compliance
- Comprehensive **error checking**
- Clear **comments** and explanations
- Multiple **test cases** per file
- **Best practices** noted in comments

## 🛠️ Build Artifacts

Compiled binaries are stored in the `build/` directory, mirroring the source structure:

```
build/
├── ch1/
│   └── listing1/
│       └── hello
├── ch8/
│   └── listings/
│       └── opening_files
...
```

## 🧹 Cleaning Up

```bash
# Remove all compiled binaries
./run.sh -c

# Or manually
rm -rf build/
```

## 📚 Learning Path

1. **Start with Chapter 1** - Get familiar with basic C syntax
2. **Use `run.sh`** - Learn the workflow: `./run.sh -q <file.c>`
3. **Modify Examples** - Edit code and rerun to see changes
4. **Explore `misc/` Folders** - Additional examples for deeper understanding
5. **Read the Notes** - Each file contains important comments and best practices

## 🐛 Troubleshooting

### Compilation Errors

```bash
# Check your compiler version
gcc --version
clang --version

# Ensure you have a C compiler installed
which gcc
which clang
```

### Permission Issues

```bash
# Make run.sh executable
chmod +x run.sh
```

### Missing Dependencies

Most examples use only standard C library. For Chapter 8 POSIX examples, ensure you're on a POSIX-compliant system (Linux, macOS, WSL).

## 📖 Additional Resources

- **Book**: "Effective C: An Introduction to Professional C Programming" by Robert C. Seacord
- **C Standard**: ISO/IEC 9899:2011 (C11)
- **Online Reference**: [cppreference.com](https://en.cppreference.com/w/c)

## 🤝 Contributing

Feel free to:

- Add more examples
- Improve existing code
- Fix bugs or issues
- Enhance documentation

## 📄 License

Educational purposes - based on "Effective C" by Robert C. Seacord.

---

**Happy Coding!** 🚀

For questions or issues, refer to the book or C standard documentation.
