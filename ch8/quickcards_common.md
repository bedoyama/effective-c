# Standard I/O Functions - Quick Reference Cards

## Common Case Functions (Most Frequently Used)

### `printf()` / `fprintf()`

```c
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
```

- **Purpose**: Print formatted output
- **Common use**: General output to stdout or files
- **Returns**: Number of characters written, negative on error
- **Example**:

```c
printf("Value: %d\n", 42);
fprintf(fp, "Name: %s, Age: %d\n", name, age);
```

---

### `scanf()` / `fscanf()`

```c
int scanf(const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
```

- **Purpose**: Read formatted input
- **Common use**: Parse structured text input
- **Returns**: Number of items successfully read, EOF on error
- **Example**:

```c
int age;
scanf("%d", &age);
fscanf(fp, "%d %s", &id, name);
```

---

### `fopen()` / `fclose()`

```c
FILE *fopen(const char *filename, const char *mode);
int fclose(FILE *stream);
```

- **Purpose**: Open and close files
- **Common use**: Every file operation starts with fopen, ends with fclose
- **Modes**: "r", "w", "a", "r+", "w+", "a+", add "b" for binary
- **Returns**: fopen returns FILE\* or NULL; fclose returns 0 or EOF
- **Example**:

```c
FILE *fp = fopen("data.txt", "r");
if (fp != NULL) {
    // ... use file
    fclose(fp);
}
```

---

### `fgets()` / `fputs()`

```c
char *fgets(char *str, int n, FILE *stream);
int fputs(const char *str, FILE *stream);
```

- **Purpose**: Read/write strings (lines)
- **Common use**: Line-based text file processing
- **Returns**: fgets returns pointer or NULL; fputs returns non-negative or EOF
- **Example**:

```c
char buffer[256];
while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    fputs(buffer, stdout);
}
```

---

### `fread()` / `fwrite()`

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```

- **Purpose**: Binary I/O (read/write blocks of data)
- **Common use**: Working with structures, arrays, binary files
- **Returns**: Number of items (not bytes) successfully read/written
- **Example**:

```c
struct record rec;
fread(&rec, sizeof(rec), 1, fp);
fwrite(&rec, sizeof(rec), 1, fp);
```

---

### `feof()` / `ferror()`

```c
int feof(FILE *stream);
int ferror(FILE *stream);
```

- **Purpose**: Check end-of-file and error conditions
- **Common use**: Distinguish between EOF and read errors
- **Returns**: Non-zero if condition is true
- **Example**:

```c
if (fread(buffer, 1, size, fp) < size) {
    if (feof(fp)) printf("End of file\n");
    if (ferror(fp)) printf("Read error\n");
}
```

---

### `fseek()` / `ftell()`

```c
int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);
```

- **Purpose**: File positioning (random access)
- **Common use**: Jump to specific locations in files
- **whence**: SEEK_SET (beginning), SEEK_CUR (current), SEEK_END (end)
- **Returns**: fseek returns 0 on success; ftell returns position or -1L
- **Example**:

```c
fseek(fp, 0, SEEK_END);        // Go to end
long size = ftell(fp);          // Get file size
fseek(fp, 100, SEEK_SET);      // Go to byte 100
```

---

## Summary of Common Patterns

### Opening Files

```c
FILE *fp = fopen("file.txt", "r");  // Read text
FILE *fp = fopen("file.txt", "w");  // Write text (truncate)
FILE *fp = fopen("file.bin", "rb"); // Read binary
FILE *fp = fopen("file.txt", "a");  // Append text
```

### Reading Text Files

```c
// Line by line
while (fgets(line, sizeof(line), fp) != NULL) { /* process */ }

// Formatted
while (fscanf(fp, "%d %s", &num, str) == 2) { /* process */ }

// Character by character
int ch;
while ((ch = fgetc(fp)) != EOF) { /* process */ }
```

### Writing to Files

```c
fprintf(fp, "Value: %d\n", value);     // Formatted
fputs("Line of text\n", fp);            // String
fputc('A', fp);                         // Character
```

### Error Handling Pattern

```c
FILE *fp = fopen("file.txt", "r");
if (fp == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
}
// ... use file
if (fclose(fp) == EOF) {
    perror("fclose");
}
```
