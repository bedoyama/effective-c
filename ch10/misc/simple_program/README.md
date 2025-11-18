# Simple Calculator

A demonstration of structuring a simple C program with multiple source files.

## Structure

```
simple_program/
├── math.h          - Math operations interface
├── math.c          - Math operations implementation
├── ui.h            - User interface interface
├── ui.c            - User interface implementation
├── main.c          - Main program
├── Makefile        - Build automation
└── README.md       - This file
```

## Modules

### math module

- Basic arithmetic: add, subtract, multiply, divide
- Advanced operations: power, factorial
- Demonstrates: static helper functions, error handling

### ui module

- Display functions: menu, results, errors
- Input functions: get numbers, get operations
- Demonstrates: separation of I/O from logic

### main

- Program entry point
- Connects math and ui modules
- Demonstrates: module integration

## Building

### Method 1: Using Makefile (recommended)

```bash
make              # Build the calculator
make run          # Build and run
make debug        # Build with debug symbols
make clean        # Remove build artifacts
make rebuild      # Clean and build
```

### Method 2: Compile and link separately

```bash
gcc -c math.c -o math.o
gcc -c ui.c -o ui.o
gcc -c main.c -o main.o
gcc math.o ui.o main.o -o calculator
```

### Method 3: Compile all at once

```bash
gcc math.c ui.c main.c -o calculator
```

### Method 4: With optimization and warnings

```bash
gcc -Wall -Wextra -std=c11 -O2 math.c ui.c main.c -o calculator
```

## Running

```bash
./calculator
```

Follow the on-screen menu to perform calculations.

## Program Structure Benefits

1. **Modularity**: Each file has a specific purpose
2. **Reusability**: Math module can be used in other programs
3. **Maintainability**: Easy to find and modify code
4. **Testability**: Can test modules independently
5. **Scalability**: Easy to add new operations or UI modes

## Design Principles Demonstrated

- **Separation of concerns**: Math, UI, and main logic are separate
- **Information hiding**: Implementation details in .c files
- **Interface design**: Clean APIs in .h files
- **Error handling**: Division by zero handling
- **Resource management**: Proper input handling

## Extending

To add a new operation:

1. Add declaration to `math.h`
2. Implement in `math.c`
3. Add case to switch statement in `main.c`
4. Update menu in `ui.c`
5. Rebuild with `make`

## Learning Points

This example teaches:

- Multi-file C program structure
- Header files and implementation files
- Compilation and linking process
- Using Makefiles for builds
- Module design and organization
- API design principles
