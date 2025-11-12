# File-Specific I/O Functions Quick Reference

## File Opening & Closing

### `fopen()`

```c
FILE *fopen(const char *filename, const char *mode);
```

- **Purpose**: Open a file for reading, writing, or both
- **Modes**:
  - `"r"` - Read (file must exist)
  - `"w"` - Write (create/truncate)
  - `"a"` - Append (create if needed)
  - `"r+"` - Read/write (file must exist)
  - `"w+"` - Read/write (create/truncate)
  - `"a+"` - Read/append (create if needed)
  - Add `"b"` for binary mode: `"rb"`, `"wb"`, etc.
- **Returns**: FILE pointer or NULL on error
- **Example**:

```c
FILE *fp = fopen("data.txt", "r");
if (fp == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
}
```

---

### `fclose()`

```c
int fclose(FILE *stream);
```

- **Purpose**: Close file and flush buffers
- **Returns**: 0 on success, EOF on error
- **Example**:

```c
if (fclose(fp) == EOF) {
    perror("fclose");
}
```

- **⚠️ Important**: Always close files! Pending data may be lost otherwise.

---

### `freopen()`

```c
FILE *freopen(const char *filename, const char *mode, FILE *stream);
```

- **Purpose**: Reopen a stream with different file
- **Common use**: Redirect stdout/stderr to file
- **Example**:

```c
freopen("output.txt", "w", stdout);
printf("This goes to file\n");
```

---

## File Reading

### `fgetc()` / `getc()`

```c
int fgetc(FILE *stream);
int getc(FILE *stream);  // May be a macro
```

- **Purpose**: Read single character
- **Returns**: Character as int, or EOF
- **Example**:

```c
int ch;
while ((ch = fgetc(fp)) != EOF) {
    putchar(ch);
}
```

---

### `fgets()`

```c
char *fgets(char *str, int n, FILE *stream);
```

- **Purpose**: Read line (up to n-1 chars or newline)
- **Returns**: Pointer to str, or NULL on EOF/error
- **Example**:

```c
char line[256];
while (fgets(line, sizeof(line), fp) != NULL) {
    printf("Line: %s", line);
}
```

- **Note**: Includes newline character if present

---

### `fscanf()`

```c
int fscanf(FILE *stream, const char *format, ...);
```

- **Purpose**: Read formatted data from file
- **Returns**: Number of items read, EOF on error
- **Example**:

```c
int id;
char name[50];
double salary;
while (fscanf(fp, "%d %49s %lf", &id, name, &salary) == 3) {
    printf("ID: %d, Name: %s, Salary: %.2f\n", id, name, salary);
}
```

---

### `fread()`

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
```

- **Purpose**: Read binary data (blocks)
- **Returns**: Number of items (not bytes!) successfully read
- **Example**:

```c
struct record rec;
if (fread(&rec, sizeof(rec), 1, fp) != 1) {
    if (feof(fp)) {
        printf("End of file\n");
    } else {
        fprintf(stderr, "Read error\n");
    }
}
```

---

## File Writing

### `fputc()` / `putc()`

```c
int fputc(int c, FILE *stream);
int putc(int c, FILE *stream);  // May be a macro
```

- **Purpose**: Write single character
- **Returns**: Character written, or EOF on error
- **Example**:

```c
for (char c = 'A'; c <= 'Z'; c++) {
    fputc(c, fp);
}
```

---

### `fputs()`

```c
int fputs(const char *str, FILE *stream);
```

- **Purpose**: Write string to file
- **Returns**: Non-negative on success, EOF on error
- **Example**:

```c
fputs("First line\n", fp);
fputs("Second line\n", fp);
```

- **Note**: Does NOT add newline automatically

---

### `fprintf()`

```c
int fprintf(FILE *stream, const char *format, ...);
```

- **Purpose**: Write formatted data to file
- **Returns**: Number of characters written
- **Example**:

```c
fprintf(fp, "Name: %s, Age: %d, Score: %.2f\n", name, age, score);
```

---

### `fwrite()`

```c
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```

- **Purpose**: Write binary data (blocks)
- **Returns**: Number of items successfully written
- **Example**:

```c
struct record rec = {1, "Alice", 95.5};
if (fwrite(&rec, sizeof(rec), 1, fp) != 1) {
    fprintf(stderr, "Write error\n");
}
```

---

## File Positioning

### `fseek()`

```c
int fseek(FILE *stream, long offset, int whence);
```

- **Purpose**: Move file position indicator
- **whence**: `SEEK_SET` (beginning), `SEEK_CUR` (current), `SEEK_END` (end)
- **Returns**: 0 on success, -1 on error
- **Example**:

```c
fseek(fp, 0, SEEK_END);           // Go to end
long size = ftell(fp);             // Get size
fseek(fp, 100, SEEK_SET);          // Go to byte 100
fseek(fp, -50, SEEK_CUR);          // Back 50 bytes
```

---

### `ftell()`

```c
long ftell(FILE *stream);
```

- **Purpose**: Get current file position
- **Returns**: Position as long, or -1L on error
- **Example**:

```c
long pos = ftell(fp);
printf("Current position: %ld\n", pos);
```

---

### `rewind()`

```c
void rewind(FILE *stream);
```

- **Purpose**: Reset position to beginning, clear errors
- **Example**:

```c
rewind(fp);  // Equivalent to fseek(fp, 0, SEEK_SET)
```

---

### `fgetpos()` / `fsetpos()`

```c
int fgetpos(FILE *stream, fpos_t *pos);
int fsetpos(FILE *stream, const fpos_t *pos);
```

- **Purpose**: Save/restore file position (for large files)
- **Returns**: 0 on success, non-zero on error
- **Example**:

```c
fpos_t pos;
fgetpos(fp, &pos);      // Save position
// ... do work
fsetpos(fp, &pos);      // Restore position
```

---

## File Status & Control

### `feof()`

```c
int feof(FILE *stream);
```

- **Purpose**: Check if end-of-file reached
- **Returns**: Non-zero if EOF
- **Example**:

```c
if (fread(buffer, 1, size, fp) < size) {
    if (feof(fp)) {
        printf("Reached end of file\n");
    }
}
```

---

### `ferror()`

```c
int ferror(FILE *stream);
```

- **Purpose**: Check if error occurred
- **Returns**: Non-zero if error
- **Example**:

```c
if (ferror(fp)) {
    fprintf(stderr, "File error occurred\n");
    clearerr(fp);
}
```

---

### `clearerr()`

```c
void clearerr(FILE *stream);
```

- **Purpose**: Clear EOF and error indicators
- **Example**:

```c
if (ferror(fp) || feof(fp)) {
    clearerr(fp);
    // Try operation again
}
```

---

### `fflush()`

```c
int fflush(FILE *stream);
```

- **Purpose**: Flush output buffer to file
- **Returns**: 0 on success, EOF on error
- **Example**:

```c
fprintf(fp, "Important data\n");
fflush(fp);  // Ensure data is written to disk
```

- **Note**: `fflush(NULL)` flushes all output streams

---

### `fileno()`

```c
int fileno(FILE *stream);
```

- **Purpose**: Get file descriptor from FILE\*
- **Common use**: Use POSIX operations on stdio streams
- **Example**:

```c
int fd = fileno(fp);
fsync(fd);  // Sync using POSIX call
```

---

## File Operations

### `remove()`

```c
int remove(const char *filename);
```

- **Purpose**: Delete file
- **Returns**: 0 on success, non-zero on error
- **Example**:

```c
if (remove("temp.txt") != 0) {
    perror("remove");
}
```

---

### `rename()`

```c
int rename(const char *oldname, const char *newname);
```

- **Purpose**: Rename or move file
- **Returns**: 0 on success, non-zero on error
- **Example**:

```c
if (rename("old.txt", "new.txt") != 0) {
    perror("rename");
}
```

---

### `tmpfile()`

```c
FILE *tmpfile(void);
```

- **Purpose**: Create temporary file (auto-deleted)
- **Returns**: FILE pointer or NULL
- **Example**:

```c
FILE *tmp = tmpfile();
if (tmp != NULL) {
    fprintf(tmp, "Temporary data\n");
    rewind(tmp);
    // ... read back
    fclose(tmp);  // File automatically deleted
}
```

---

## Common File Patterns

### Read Entire Text File

```c
FILE *fp = fopen("file.txt", "r");
if (fp != NULL) {
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    fclose(fp);
}
```

### Write Text File

```c
FILE *fp = fopen("output.txt", "w");
if (fp != NULL) {
    fprintf(fp, "Line 1\n");
    fprintf(fp, "Line 2\n");
    fclose(fp);
}
```

### Copy Binary File

```c
FILE *src = fopen("source.bin", "rb");
FILE *dst = fopen("dest.bin", "wb");
if (src && dst) {
    char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dst);
    }
}
fclose(src);
fclose(dst);
```

### Get File Size

```c
FILE *fp = fopen("file.bin", "rb");
if (fp != NULL) {
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    printf("File size: %ld bytes\n", size);
    fclose(fp);
}
```

### Random Access

```c
FILE *fp = fopen("records.dat", "rb");
if (fp != NULL) {
    struct record rec;
    int record_num = 5;

    // Jump to 5th record
    fseek(fp, record_num * sizeof(rec), SEEK_SET);
    fread(&rec, sizeof(rec), 1, fp);

    fclose(fp);
}
```
