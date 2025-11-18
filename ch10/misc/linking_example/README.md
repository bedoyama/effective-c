# Prime Testing Example - Linking and Building

This example demonstrates building a C program with separate compilation and linking, including creating and using a static library.

## Project Structure

```
linking_example/
├── isprime.h           - Prime testing interface
├── isprime.c           - Prime testing implementation
├── driver.c            - Main program
├── Makefile            - Build automation
├── README.md           - This file
└── bin/                - Build output directory
```

## What This Example Demonstrates

- Separate compilation of source files
- Creating static libraries (.a files)
- Linking object files with libraries
- Using compiler flags for strict checking
- Build automation with Make

## Manual Build Commands

### Step 1: Create the bin directory

```bash
mkdir -p bin
```

### Step 2: Compile the isprime module to object file

```bash
clang -c -std=c17 -Wall -Wextra -pedantic -Werror isprime.c -o bin/isprime.o
```

**Flags explained:**

- `-c` - Compile to object file (don't link)
- `-std=c17` - Use C17 standard
- `-Wall -Wextra` - Enable all warnings
- `-pedantic` - Strict ISO C compliance
- `-Werror` - Treat warnings as errors
- `-o bin/isprime.o` - Output file

### Step 3: Compile the driver program to object file

```bash
clang -c -std=c17 -Wall -Wextra -pedantic -Werror driver.c -o bin/driver.o
```

### Step 4: Create a static library from isprime.o

```bash
ar rcs bin/libPrimalityUtilities.a bin/isprime.o
```

**ar command explained:**

- `ar` - Archive tool for creating libraries
- `r` - Replace or add files to archive
- `c` - Create archive if it doesn't exist
- `s` - Create/update index (symbol table)
- `libPrimalityUtilities.a` - Library name (must start with `lib`)

### Step 5: Link the driver with the library

```bash
clang bin/driver.o -Lbin -lPrimalityUtilities -o bin/primetest
```

**Linker flags explained:**

- `-Lbin` - Add `bin/` to library search path
- `-lPrimalityUtilities` - Link with `libPrimalityUtilities.a`
  (Note: `-l` removes `lib` prefix and `.a` suffix)
- `-o bin/primetest` - Output executable name

### Step 6: Run the program

```bash
bin/primetest 17 19 20 97 100
```

## Build with Makefile (Recommended)

Instead of running the commands manually, use the provided Makefile:

### Build everything

```bash
make
```

### Run the program

```bash
make run
```

### Clean build artifacts

```bash
make clean
```

### Rebuild from scratch

```bash
make rebuild
```

### View available targets

```bash
make help
```

## Testing Examples

```bash
# Test some prime numbers
bin/primetest 2 3 5 7 11 13 17 19 23 29

# Test some composite numbers
bin/primetest 4 6 8 9 10 12 14 15 16 18

# Test large primes
bin/primetest 104729 104743

# Test mixed
bin/primetest 100 101 102 103 104 105
```

## Understanding the Build Process

### Compilation Stage

```
isprime.c  →  [Compiler]  →  isprime.o
driver.c   →  [Compiler]  →  driver.o
```

Each `.c` file is compiled independently to an object file (`.o`).

### Library Creation Stage

```
isprime.o  →  [Archiver]  →  libPrimalityUtilities.a
```

The `ar` tool packages object files into a static library archive.

### Linking Stage

```
driver.o + libPrimalityUtilities.a  →  [Linker]  →  primetest
```

The linker combines the object file with the library to create the final executable.

## Why Separate Compilation?

1. **Modularity** - Code organized into logical units
2. **Reusability** - `libPrimalityUtilities.a` can be used in other programs
3. **Faster Builds** - Only recompile changed files
4. **Team Development** - Different people can work on different modules
5. **Binary Distribution** - Can distribute library without source code

## Static vs Dynamic Libraries

This example uses a **static library** (`.a` file):

- Code is copied into executable at link time
- Larger executable size
- No runtime dependencies
- Faster program startup

Alternative: **Dynamic library** (`.so` on Linux, `.dylib` on macOS, `.dll` on Windows):

- Code loaded at runtime
- Smaller executable size
- Shared between multiple programs
- Can update library without recompiling program

To create a dynamic library:

```bash
# Compile with position-independent code
clang -c -fPIC -std=c17 isprime.c -o bin/isprime.o

# Create shared library
clang -shared bin/isprime.o -o bin/libPrimalityUtilities.dylib

# Link with dynamic library
clang bin/driver.o -Lbin -lPrimalityUtilities -o bin/primetest
```

## Viewing Library Contents

```bash
# List symbols in the library
nm bin/libPrimalityUtilities.a

# View archive contents
ar -t bin/libPrimalityUtilities.a

# Detailed information
ar -tv bin/libPrimalityUtilities.a
```

## Troubleshooting

### "undefined reference to is_prime"

- Make sure `isprime.h` is included in `driver.c`
- Check that library is being linked: `-lPrimalityUtilities`
- Verify library path: `-Lbin`

### "cannot find -lPrimalityUtilities"

- Make sure the library file exists: `bin/libPrimalityUtilities.a`
- Library name must start with `lib` and end with `.a`
- Check that `-Lbin` is specified before `-lPrimalityUtilities`

### Compiler warnings/errors

- Review the compiler output carefully
- Make sure all required headers are included
- Check that function signatures match between `.h` and `.c` files

## Learning Points

This example teaches:

- **Separate compilation** - Compiling source files independently
- **Object files** - Intermediate compilation output (`.o` files)
- **Static libraries** - Creating and using `.a` archives
- **Linker** - Combining object files and libraries
- **Makefiles** - Automating the build process
- **Compiler flags** - Enabling strict checking and standards compliance
