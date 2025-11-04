#!/usr/bin/env bash

# Utility script to compile and run C examples
# Usage: ./run.sh <file.c>
#    or: ./run.sh <chapter> <file.c>
#    or: ./run.sh -a (compile all)
#    or: ./run.sh -c (clean all executables)

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Compiler settings
CC="${CC:-gcc}"
CFLAGS="${CFLAGS:--Wall -Wextra -std=c11 -O2}"

# Function to compile a C file
compile() {
    local source_file="$1"
    local executable="${source_file%.c}"
    
    echo -e "${BLUE}Compiling:${NC} $source_file"
    if $CC $CFLAGS -o "$executable" "$source_file"; then
        echo -e "${GREEN}✓ Compiled successfully:${NC} $executable"
        return 0
    else
        echo -e "${RED}✗ Compilation failed${NC}"
        return 1
    fi
}

# Function to print source code
print_source() {
    local source_file="$1"
    
    echo -e "\n${YELLOW}Source Code:${NC} $source_file"
    echo "========================================"
    
    if command -v bat > /dev/null 2>&1; then
        # Use bat if available (syntax highlighting)
        bat --style=numbers --color=always "$source_file"
    else
        # Fallback to cat with line numbers
        cat -n "$source_file"
    fi
    
    echo "========================================"
}

# Function to run an executable
run_executable() {
    local executable="$1"
    
    if [ -x "$executable" ]; then
        echo -e "\n${YELLOW}Running:${NC} $executable"
        echo "----------------------------------------"
        ./"$executable"
        local exit_code=$?
        echo "----------------------------------------"
        echo -e "${BLUE}Exit code:${NC} $exit_code\n"
        return $exit_code
    else
        echo -e "${RED}✗ Executable not found or not executable:${NC} $executable"
        return 1
    fi
}

# Function to compile and run
compile_and_run() {
    local source_file="$1"
    
    if [ ! -f "$source_file" ]; then
        echo -e "${RED}✗ File not found:${NC} $source_file"
        return 1
    fi
    
    # Print source code first
    print_source "$source_file"
    
    if compile "$source_file"; then
        local executable="${source_file%.c}"
        run_executable "$executable"
    fi
}

# Function to compile all C files
compile_all() {
    echo -e "${BLUE}Compiling all C files...${NC}\n"
    local count=0
    local failed=0
    
    for source_file in $(find . -name "*.c" -type f | sort); do
        echo "[$((count + 1))] $source_file"
        if compile "$source_file"; then
            ((count++))
        else
            ((failed++))
        fi
        echo ""
    done
    
    echo -e "${GREEN}Successfully compiled:${NC} $count"
    if [ $failed -gt 0 ]; then
        echo -e "${RED}Failed:${NC} $failed"
    fi
}

# Function to clean all executables
clean_all() {
    echo -e "${BLUE}Cleaning executables...${NC}\n"
    local count=0
    
    # Find all C files and remove their corresponding executables
    for source_file in $(find . -name "*.c" -type f); do
        local executable="${source_file%.c}"
        if [ -f "$executable" ] && [ -x "$executable" ]; then
            rm -f "$executable"
            echo -e "${GREEN}Removed:${NC} $executable"
            ((count++))
        fi
    done
    
    echo -e "\n${GREEN}Cleaned $count executable(s)${NC}"
}

# Function to show usage
show_usage() {
    cat << EOF
${BLUE}Usage:${NC}
  ./run.sh <file.c>              Compile and run a C file
  ./run.sh <chapter> <file>      Compile and run from specific chapter
  ./run.sh -a, --all             Compile all C files
  ./run.sh -c, --clean           Clean all executables
  ./run.sh -h, --help            Show this help message

${BLUE}Examples:${NC}
  ./run.sh ch1/listing1/hello.c
  ./run.sh ch4 bitwise.c
  ./run.sh ch4/listings/bitwise.c
  ./run.sh --all
  ./run.sh --clean

${BLUE}Environment Variables:${NC}
  CC                             C compiler (default: gcc)
  CFLAGS                         Compiler flags (default: -Wall -Wextra -std=c11 -O2)

${BLUE}Examples with custom settings:${NC}
  CC=clang ./run.sh ch4/listings/bitwise.c
  CFLAGS="-Wall -g" ./run.sh ch1/listing1/hello.c
EOF
}

# Main script logic
main() {
    if [ $# -eq 0 ]; then
        show_usage
        exit 1
    fi
    
    case "$1" in
        -h|--help)
            show_usage
            exit 0
            ;;
        -a|--all)
            compile_all
            exit 0
            ;;
        -c|--clean)
            clean_all
            exit 0
            ;;
        ch*)
            # Handle: ./run.sh ch4 bitwise.c
            if [ $# -eq 2 ]; then
                local chapter="$1"
                local filename="$2"
                
                # Ensure filename has .c extension
                if [[ ! "$filename" =~ \.c$ ]]; then
                    filename="${filename}.c"
                fi
                
                # Try to find the file in chapter directories
                local found_file=""
                for dir in "$chapter/listings" "$chapter/misc"; do
                    if [ -f "$dir/$filename" ]; then
                        found_file="$dir/$filename"
                        break
                    fi
                done
                
                if [ -n "$found_file" ]; then
                    compile_and_run "$found_file"
                else
                    echo -e "${RED}✗ File not found in $chapter/listings or $chapter/misc:${NC} $filename"
                    exit 1
                fi
            else
                # Handle: ./run.sh ch4/listings/bitwise.c
                local file="$1"
                # Ensure it's a .c file
                if [[ ! "$file" =~ \.c$ ]]; then
                    file="${file}.c"
                fi
                compile_and_run "$file"
            fi
            ;;
        *)
            # Handle: ./run.sh path/to/file.c
            local file="$1"
            # Ensure it's a .c file
            if [[ ! "$file" =~ \.c$ ]]; then
                file="${file}.c"
            fi
            compile_and_run "$file"
            ;;
    esac
}

main "$@"
