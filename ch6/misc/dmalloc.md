# Dmalloc - Debug Malloc Library

Dmalloc is a memory debugging library that helps detect memory-related errors in C programs.

## Installation

### macOS

```bash
brew install dmalloc
```

### Linux (Debian/Ubuntu)

```bash
sudo apt-get install libdmalloc-dev
```

### Linux (Fedora/RHEL)

```bash
sudo dnf install dmalloc-devel
```

## Usage

### 1. Compile with Dmalloc Support

```bash
gcc -DDMALLOC -o build/ch6/misc/dmalloc_example ch6/misc/dmalloc_example.c -ldmalloc
```

**Compiler flags:**

- `-DDMALLOC` - Defines the DMALLOC macro to enable Dmalloc features
- `-ldmalloc` - Links against the Dmalloc library

### 2. Configure Dmalloc Environment

Set debug options using the `dmalloc` utility:

```bash
# Low debug level (basic checking)
eval `dmalloc -b low`

# Medium debug level
eval `dmalloc -b medium`

# High debug level (comprehensive checking)
eval `dmalloc -b high`

# Custom options with log file
eval `dmalloc -b -l dmalloc.log low`
```

Or manually set environment variables:

```bash
export DMALLOC_OPTIONS=debug=0x4f47d03,log=dmalloc.log
```

### 3. Run Your Program

```bash
./build/ch6/misc/dmalloc_example
```

### 4. Check for Errors

View the log file:

```bash
cat dmalloc.log
```

Or use the dmalloc utility to interpret the log:

```bash
dmalloc -l dmalloc.log
```

## What Dmalloc Detects

Dmalloc can detect the following memory errors:

- ✅ **Memory leaks** - Allocated memory that was never freed
- ✅ **Double free** - Attempting to free the same memory twice
- ✅ **Use after free** - Accessing memory after it has been freed
- ✅ **Buffer overflow** - Writing beyond allocated memory boundaries
- ✅ **Buffer underflow** - Writing before allocated memory region
- ✅ **Invalid pointers** - Freeing or accessing invalid memory addresses
- ✅ **Uninitialized reads** - Reading memory before initialization
- ✅ **Heap corruption** - Detecting corrupted heap structures

## Quick Start Example

```bash
# 1. Install Dmalloc
brew install dmalloc

# 2. Compile the example
gcc -DDMALLOC -o build/ch6/misc/dmalloc_example ch6/misc/dmalloc_example.c -ldmalloc

# 3. Set up environment
eval `dmalloc -b low`

# 4. Run the program
./build/ch6/misc/dmalloc_example

# 5. Check the log
cat dmalloc.log
```

## Debug Levels

| Level     | Description                    | Use Case                 |
| --------- | ------------------------------ | ------------------------ |
| `low`     | Basic memory tracking          | Quick checks, production |
| `medium`  | Additional boundary checking   | Development              |
| `high`    | Comprehensive checking, slower | Deep debugging           |
| `runtime` | Runtime configurable options   | Custom configurations    |

## Alternative Memory Debugging Tools

- **Valgrind** - Comprehensive memory error detector

  ```bash
  valgrind --leak-check=full ./program
  ```

- **AddressSanitizer** - Fast memory error detector (GCC/Clang)

  ```bash
  gcc -fsanitize=address -g program.c -o program
  ```

- **Electric Fence** - Detects buffer overflows/underflows
  ```bash
  gcc program.c -o program -lefence
  ```

## Tips

1. **Start with low level** - Begin debugging with `low` to minimize overhead
2. **Use log files** - Always specify a log file for persistent results
3. **Recompile** - Must recompile your program with `-DDMALLOC`
4. **Check regularly** - Run Dmalloc frequently during development
5. **Clean build** - Remove all object files before compiling with Dmalloc

## Common Issues

### "dmalloc.h: No such file or directory"

- Install the Dmalloc development package
- Verify installation: `brew list dmalloc` or `dpkg -L libdmalloc-dev`

### "undefined reference to dmalloc functions"

- Make sure to link with `-ldmalloc`
- Check that the library is installed: `ldconfig -p | grep dmalloc`

### No log file generated

- Ensure `DMALLOC_OPTIONS` environment variable is set
- Use `eval \`dmalloc -b low\`` to set up properly
- Check write permissions in the current directory

## Resources

- Official Documentation: http://dmalloc.com/
- Man page: `man dmalloc`
- Library man page: `man libdmalloc`
