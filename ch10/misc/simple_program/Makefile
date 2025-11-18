# Simple Calculator Makefile
# Demonstrates building a multi-file C program

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
DEBUGFLAGS = -g -O0

# Target executable
TARGET = calculator

# Source files
SOURCES = main.c math.c ui.c

# Object files (automatically generated from sources)
OBJECTS = $(SOURCES:.c=.o)

# Header files (for dependency tracking)
HEADERS = math.h ui.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)
	@echo "Build complete: $(TARGET)"

# Compile source files to object files
%.o: %.c $(HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build
debug: CFLAGS += $(DEBUGFLAGS)
debug: clean all
	@echo "Debug build complete"

# Clean build artifacts
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete"

# Rebuild everything
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Show makefile variables (for debugging makefile)
info:
	@echo "CC:       $(CC)"
	@echo "CFLAGS:   $(CFLAGS)"
	@echo "TARGET:   $(TARGET)"
	@echo "SOURCES:  $(SOURCES)"
	@echo "OBJECTS:  $(OBJECTS)"
	@echo "HEADERS:  $(HEADERS)"

# Phony targets (not actual files)
.PHONY: all clean rebuild run debug info

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the calculator (default)"
	@echo "  debug   - Build with debug symbols"
	@echo "  clean   - Remove build artifacts"
	@echo "  rebuild - Clean and build"
	@echo "  run     - Build and run the calculator"
	@echo "  info    - Show build configuration"
	@echo "  help    - Show this help message"
