# Universal I/O Functions Quick Reference

These functions work with **any** FILE stream (stdin, stdout, stderr, or file streams).

## Character I/O

### `fgetc()` / `getc()`

```c
int fgetc(FILE *stream);
int getc(FILE *stream);  // May be a macro
```

- **Works with**: Any FILE stream
- **Purpose**: Read single character
- **Returns**: Character as int, or EOF
- **Examples**:

```c
int ch1 = fgetc(stdin);          // From stdin
int ch2 = fgetc(fp);             // From file
int ch3 = getc(stdin);           // Macro version
```

---

### `fputc()` / `putc()`

```c
int fputc(int c, FILE *stream);
int putc(int c, FILE *stream);  // May be a macro
```

- **Works with**: Any FILE stream
- **Purpose**: Write single character
- **Returns**: Character written, or EOF on error
- **Examples**:

```c
fputc('A', stdout);              // To stdout
fputc('B', stderr);              // To stderr
fputc('C', fp);                  // To file
```

---

### `ungetc()`

```c
int ungetc(int c, FILE *stream);
```

- **Works with**: Any FILE stream
- **Purpose**: Push character back to stream
- **Returns**: Character pushed, or EOF on error
- **Examples**:

```c
int ch = fgetc(fp);
if (ch == '#') {
    ungetc(ch, fp);              // Push back for reprocessing
}
```

---

## String/Line I/O

### `fgets()`

```c
char *fgets(char *str, int n, FILE *stream);
```

- **Works with**: Any FILE stream
- **Purpose**: Read line (up to n-1 chars)
- **Returns**: Pointer to str, or NULL on EOF/error
- **Examples**:

```c
char line[256];
fgets(line, sizeof(line), stdin);     // From stdin
fgets(line, sizeof(line), fp);        // From file
fgets(line, sizeof(line), stderr);    // Even stderr (rarely used)
```

---

### `fputs()`

```c
int fputs(const char *str, FILE *stream);
```

- **Works with**: Any FILE stream
- **Purpose**: Write string (no automatic newline)
- **Returns**: Non-negative on success, EOF on error
- **Examples**:

```c
fputs("Message\n", stdout);           // To stdout
fputs("Error\n", stderr);             // To stderr
fputs("Data\n", fp);                  // To file
```

---

## Formatted I/O

### `fprintf()`

```c
int fprintf(FILE *stream, const char *format, ...);
```

- **Works with**: Any FILE stream
- **Purpose**: Write formatted output
- **Returns**: Number of characters written
- **Examples**:

```c
fprintf(stdout, "Value: %d\n", x);    // Same as printf()
fprintf(stderr, "Error: %s\n", msg);  // Error message
fprintf(fp, "Data: %d\n", data);      // To file
```

---

### `fscanf()`

```c
int fscanf(FILE *stream, const char *format, ...);
```

- **Works with**: Any FILE stream
- **Purpose**: Read formatted input
- **Returns**: Number of items read, EOF on error
- **Examples**:

```c
int x;
fscanf(stdin, "%d", &x);              // Same as scanf()
fscanf(fp, "%d %s", &id, name);       // From file
```

---

### `vfprintf()` Family

```c
int vfprintf(FILE *stream, const char *format, va_list ap);
```

- **Works with**: Any FILE stream
- **Purpose**: Variable argument formatted output
- **Common use**: Creating custom printf-like functions
- **Example**:

```c
void my_printf(FILE *stream, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stream, fmt, args);
    va_end(args);
}

my_printf(stdout, "Value: %d\n", 42);
my_printf(stderr, "Error: %s\n", "fail");
my_printf(fp, "Data: %d\n", data);
```

---

## Binary I/O

### `fread()`

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
```

- **Works with**: Any FILE stream (use binary mode)
- **Purpose**: Read blocks of binary data
- **Returns**: Number of items read
- **Examples**:

```c
char buffer[1024];
fread(buffer, 1, sizeof(buffer), stdin);  // From stdin (rare)
fread(buffer, 1, sizeof(buffer), fp);     // From file (common)
```

---

### `fwrite()`

```c
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```

- **Works with**: Any FILE stream (use binary mode)
- **Purpose**: Write blocks of binary data
- **Returns**: Number of items written
- **Examples**:

```c
struct data d;
fwrite(&d, sizeof(d), 1, stdout);         // To stdout (rare)
fwrite(&d, sizeof(d), 1, fp);             // To file (common)
```

---

## File Positioning

### `fseek()`

```c
int fseek(FILE *stream, long offset, int whence);
```

- **Works with**: Any FILE stream (seekable)
- **Purpose**: Set file position
- **Returns**: 0 on success, -1 on error
- **Examples**:

```c
fseek(fp, 0, SEEK_SET);                   // Works on files
// Note: Cannot seek on stdin/stdout/stderr (terminal)
```

---

### `ftell()`

```c
long ftell(FILE *stream);
```

- **Works with**: Any FILE stream (seekable)
- **Purpose**: Get current position
- **Returns**: Position, or -1L on error
- **Examples**:

```c
long pos = ftell(fp);                     // Works on files
// Note: May fail on stdin/stdout/stderr
```

---

### `rewind()`

```c
void rewind(FILE *stream);
```

- **Works with**: Any FILE stream (seekable)
- **Purpose**: Reset to beginning, clear errors
- **Example**:

```c
rewind(fp);                               // Reset file position
```

---

### `fgetpos()` / `fsetpos()`

```c
int fgetpos(FILE *stream, fpos_t *pos);
int fsetpos(FILE *stream, const fpos_t *pos);
```

- **Works with**: Any FILE stream (seekable)
- **Purpose**: Save/restore position (large file support)
- **Returns**: 0 on success
- **Example**:

```c
fpos_t pos;
fgetpos(fp, &pos);
// ... operations
fsetpos(fp, &pos);
```

---

## Stream Status

### `feof()`

```c
int feof(FILE *stream);
```

- **Works with**: Any FILE stream
- **Purpose**: Check if EOF reached
- **Returns**: Non-zero if EOF
- **Examples**:

```c
if (feof(stdin)) printf("stdin at EOF\n");
if (feof(fp)) printf("file at EOF\n");
```

---

### `ferror()`

```c
int ferror(FILE *stream);
```

- **Works with**: Any FILE stream
- **Purpose**: Check if error occurred
- **Returns**: Non-zero if error
- **Examples**:

```c
if (ferror(stdin)) fprintf(stderr, "stdin error\n");
if (ferror(fp)) fprintf(stderr, "file error\n");
```

---

### `clearerr()`

```c
void clearerr(FILE *stream);
```

- **Works with**: Any FILE stream
- **Purpose**: Clear EOF and error indicators
- **Examples**:

```c
clearerr(stdin);
clearerr(fp);
```

---

## Buffer Control

### `fflush()`

```c
int fflush(FILE *stream);
```

- **Works with**: Any **output** FILE stream, or NULL for all
- **Purpose**: Flush output buffer
- **Returns**: 0 on success, EOF on error
- **Examples**:

```c
fflush(stdout);                           // Flush stdout
fflush(stderr);                           // Flush stderr (usually unnecessary)
fflush(fp);                               // Flush file
fflush(NULL);                             // Flush ALL output streams
```

---

### `setvbuf()`

```c
int setvbuf(FILE *stream, char *buffer, int mode, size_t size);
```

- **Works with**: Any FILE stream (call before I/O)
- **Purpose**: Set buffering mode
- **Modes**: `_IONBF` (unbuffered), `_IOLBF` (line), `_IOFBF` (full)
- **Returns**: 0 on success
- **Examples**:

```c
setvbuf(stdout, NULL, _IONBF, 0);        // Make stdout unbuffered
setvbuf(stderr, NULL, _IONBF, 0);        // Make stderr unbuffered
setvbuf(fp, NULL, _IOFBF, 4096);         // Full buffering for file
```

---

### `setbuf()`

```c
void setbuf(FILE *stream, char *buffer);
```

- **Works with**: Any FILE stream
- **Purpose**: Simpler buffering control
- **Examples**:

```c
setbuf(stdout, NULL);                     // Unbuffered
char buffer[BUFSIZ];
setbuf(fp, buffer);                       // Full buffering
```

---

## Utility Functions

### `fileno()`

```c
int fileno(FILE *stream);
```

- **Works with**: Any FILE stream
- **Purpose**: Get underlying file descriptor
- **Returns**: File descriptor, or -1 on error
- **Examples**:

```c
int fd_in = fileno(stdin);                // Usually 0
int fd_out = fileno(stdout);              // Usually 1
int fd_err = fileno(stderr);              // Usually 2
int fd_file = fileno(fp);                 // System file descriptor
```

---

## Universal Patterns

### Generic Read Loop

```c
void process_stream(FILE *stream) {
    char line[256];
    while (fgets(line, sizeof(line), stream) != NULL) {
        // Process line from any stream
        printf("Read: %s", line);
    }

    if (ferror(stream)) {
        fprintf(stderr, "Error reading stream\n");
    }
}

// Works with any stream:
process_stream(stdin);
process_stream(fp);
```

---

### Generic Error Handling

```c
void check_stream(FILE *stream, const char *name) {
    if (ferror(stream)) {
        fprintf(stderr, "Error on %s\n", name);
        clearerr(stream);
    }
    if (feof(stream)) {
        printf("%s reached EOF\n", name);
    }
}

// Works with any stream:
check_stream(stdin, "stdin");
check_stream(fp, "file");
```

---

### Redirecting Streams

```c
// Save original stdout
FILE *original_stdout = stdout;

// Redirect to file
FILE *fp = fopen("output.txt", "w");
stdout = fp;

// Now all printf() goes to file
printf("This goes to file\n");

// Restore
stdout = original_stdout;
fclose(fp);
```

---

## Stream Comparison

| Stream       | Type   | Seekable   | Buffering  | Typical Use    |
| ------------ | ------ | ---------- | ---------- | -------------- |
| `stdin`      | Input  | Usually no | Line/Full  | User input     |
| `stdout`     | Output | Usually no | Line/Full  | Normal output  |
| `stderr`     | Output | Usually no | Unbuffered | Error messages |
| File streams | Both   | Yes        | Full       | File I/O       |

---

## Key Takeaways

✅ **Universal Functions Work Everywhere:**

- `fgetc/fputc`, `fgets/fputs`
- `fprintf/fscanf`
- `fread/fwrite`
- `feof/ferror/clearerr`
- `fflush/setvbuf`

⚠️ **Positioning Functions Limited:**

- `fseek/ftell/rewind` only work on seekable streams (files)
- Cannot seek on stdin/stdout/stderr when connected to terminal

💡 **Best Practice:**

- Write functions that accept `FILE *` parameter
- Makes code work with any stream
- Easier to test (can pass file instead of stdin)
