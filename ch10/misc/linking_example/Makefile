# Makefile for Prime Testing Example
# Demonstrates building with separate compilation and static library

# Compiler and tools
CC = clang
AR = ar
CFLAGS = -std=c17 -Wall -Wextra -pedantic -Werror

# Directories
BINDIR = bin

# Target executable
TARGET = $(BINDIR)/primetest

# Library
LIBNAME = PrimalityUtilities
LIBRARY = $(BINDIR)/lib$(LIBNAME).a

# Source files
SOURCES = isprime.c driver.c
HEADERS = isprime.h

# Object files
ISPRIME_OBJ = $(BINDIR)/isprime.o
DRIVER_OBJ = $(BINDIR)/driver.o
OBJECTS = $(ISPRIME_OBJ) $(DRIVER_OBJ)

# Default target
all: $(TARGET)

# Create bin directory
$(BINDIR):
	@echo "Creating $(BINDIR) directory..."
	@mkdir -p $(BINDIR)

# Compile isprime.c to object file
$(ISPRIME_OBJ): isprime.c isprime.h | $(BINDIR)
	@echo "Compiling isprime.c..."
	$(CC) -c $(CFLAGS) isprime.c -o $(ISPRIME_OBJ)

# Compile driver.c to object file
$(DRIVER_OBJ): driver.c isprime.h | $(BINDIR)
	@echo "Compiling driver.c..."
	$(CC) -c $(CFLAGS) driver.c -o $(DRIVER_OBJ)

# Create static library from isprime.o
$(LIBRARY): $(ISPRIME_OBJ)
	@echo "Creating static library $(LIBRARY)..."
	$(AR) rcs $(LIBRARY) $(ISPRIME_OBJ)
	@echo "Library created successfully"

# Link driver with library to create executable
$(TARGET): $(DRIVER_OBJ) $(LIBRARY)
	@echo "Linking $(TARGET)..."
	$(CC) $(DRIVER_OBJ) -L$(BINDIR) -l$(LIBNAME) -o $(TARGET)
	@echo "Build complete: $(TARGET)"

# Run the program with example input
run: $(TARGET)
	@echo "Testing prime numbers..."
	@$(TARGET) 2 3 5 7 11 13 17 19 23 29
	@echo ""
	@echo "Testing composite numbers..."
	@$(TARGET) 4 6 8 9 10 12 14 15 16 18
	@echo ""
	@echo "Testing large primes..."
	@$(TARGET) 104729 104743

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BINDIR)
	@echo "Clean complete"

# Rebuild everything
rebuild: clean all

# Show library contents
info: $(LIBRARY)
	@echo "Library contents:"
	@ar -t $(LIBRARY)
	@echo ""
	@echo "Library symbols:"
	@nm $(LIBRARY)

# Display build configuration
config:
	@echo "Build Configuration:"
	@echo "  CC:       $(CC)"
	@echo "  AR:       $(AR)"
	@echo "  CFLAGS:   $(CFLAGS)"
	@echo "  BINDIR:   $(BINDIR)"
	@echo "  TARGET:   $(TARGET)"
	@echo "  LIBRARY:  $(LIBRARY)"
	@echo "  SOURCES:  $(SOURCES)"
	@echo "  OBJECTS:  $(OBJECTS)"

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build the primetest executable (default)"
	@echo "  run      - Build and run the program with test cases"
	@echo "  clean    - Remove all build artifacts"
	@echo "  rebuild  - Clean and rebuild everything"
	@echo "  info     - Show library contents and symbols"
	@echo "  config   - Display build configuration"
	@echo "  help     - Show this help message"
	@echo ""
	@echo "Build stages:"
	@echo "  1. Compile isprime.c → bin/isprime.o"
	@echo "  2. Compile driver.c → bin/driver.o"
	@echo "  3. Archive isprime.o → bin/libPrimalityUtilities.a"
	@echo "  4. Link driver.o + library → bin/primetest"

# Phony targets (not actual files)
.PHONY: all run clean rebuild info config help

# Default goal
.DEFAULT_GOAL := all
