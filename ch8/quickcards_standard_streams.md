# Standard Streams Quick Reference (stdin/stdout/stderr)

## stdin Functions (Standard Input)

### `scanf()`

```c
int scanf(const char *format, ...);
```

- **Purpose**: Read formatted input from stdin
- **Common use**: Interactive user input
- **Returns**: Number of items read, EOF on error
- **Example**:

```c
int age;
printf("Enter age: ");
scanf("%d", &age);
```

- **⚠️ Warning**: Always check return value; leaves newline in buffer

---

### `getchar()`

```c
int getchar(void);
```

- **Purpose**: Read single character from stdin
- **Common use**: Character-by-character input
- **Returns**: Character as int, or EOF
- **Example**:

```c
int ch;
while ((ch = getchar()) != EOF && ch != '\n') {
    // process character
}
```

- **Note**: Equivalent to `getc(stdin)` or `fgetc(stdin)`

---

### `gets()` - **NEVER USE!**

```c
char *gets(char *str);  // REMOVED in C11
```

- **⚠️ DEPRECATED**: No bounds checking - buffer overflow risk!
- **Use instead**: `fgets(buffer, size, stdin)`

---

### `fgets()` with stdin

```c
char *fgets(char *str, int n, FILE *stream);
```

- **Purpose**: Safe line input from stdin
- **Common use**: Reading user input safely
- **Returns**: Pointer to string, or NULL on EOF/error
- **Example**:

```c
char name[50];
printf("Enter name: ");
if (fgets(name, sizeof(name), stdin) != NULL) {
    // Remove newline if present
    name[strcspn(name, "\n")] = '\0';
}
```

---

### Clearing Input Buffer

```c
// Method 1: Read until newline
int c;
while ((c = getchar()) != '\n' && c != EOF);

// Method 2: With fgets
char buffer[256];
fgets(buffer, sizeof(buffer), stdin);
```

---

## stdout Functions (Standard Output)

### `printf()`

```c
int printf(const char *format, ...);
```

- **Purpose**: Print formatted output to stdout
- **Common use**: Most common output function
- **Returns**: Number of characters printed
- **Example**:

```c
printf("Hello, %s! You are %d years old.\n", name, age);
```

- **Note**: Equivalent to `fprintf(stdout, ...)`

---

### `putchar()`

```c
int putchar(int c);
```

- **Purpose**: Write single character to stdout
- **Common use**: Character output
- **Returns**: Character written, or EOF on error
- **Example**:

```c
putchar('A');
putchar('\n');
```

- **Note**: Equivalent to `putc(ch, stdout)` or `fputc(ch, stdout)`

---

### `puts()`

```c
int puts(const char *str);
```

- **Purpose**: Write string to stdout with newline
- **Common use**: Simple string output
- **Returns**: Non-negative on success, EOF on error
- **Example**:

```c
puts("Hello, World!");  // Automatically adds \n
```

- **Note**: Adds newline automatically (unlike fputs)

---

### `fputs()` with stdout

```c
int fputs(const char *str, FILE *stream);
```

- **Purpose**: Write string without automatic newline
- **Common use**: When you control newline placement
- **Example**:

```c
fputs("Enter choice: ", stdout);
fflush(stdout);  // Force immediate display
```

---

## stderr Functions (Standard Error)

### `fprintf()` to stderr

```c
int fprintf(FILE *stream, const char *format, ...);
```

- **Purpose**: Print error messages
- **Common use**: All error output should go to stderr
- **Example**:

```c
fprintf(stderr, "Error: Could not open %s\n", filename);
```

- **Note**: stderr is usually unbuffered (immediate output)

---

### `fputs()` to stderr

```c
int fputs(const char *str, FILE *stream);
```

- **Purpose**: Simple error messages
- **Example**:

```c
fputs("Error: Invalid input\n", stderr);
```

---

### `perror()`

```c
void perror(const char *s);
```

- **Purpose**: Print system error message to stderr
- **Common use**: After system call failures
- **Example**:

```c
FILE *fp = fopen("file.txt", "r");
if (fp == NULL) {
    perror("fopen");  // Prints: "fopen: No such file or directory"
    return EXIT_FAILURE;
}
```

- **Note**: Automatically includes strerror(errno)

---

## Stream Properties

| Stream   | Buffering                                         | Use Case                   |
| -------- | ------------------------------------------------- | -------------------------- |
| `stdin`  | Line-buffered (terminal) or fully buffered (file) | User input                 |
| `stdout` | Line-buffered (terminal) or fully buffered (file) | Normal output              |
| `stderr` | Unbuffered                                        | Error messages (immediate) |

---

## Common Patterns

### Interactive Prompt

```c
printf("Enter value: ");
fflush(stdout);  // Force prompt to appear
scanf("%d", &value);
```

### Error Reporting

```c
if (error_condition) {
    fprintf(stderr, "Error: %s\n", error_message);
    return EXIT_FAILURE;
}
```

### Reading a Line Safely

```c
char input[100];
printf("Enter text: ");
if (fgets(input, sizeof(input), stdin) != NULL) {
    input[strcspn(input, "\n")] = '\0';  // Remove newline
}
```

### Mixed Input Types

```c
int num;
char str[50];

printf("Enter number: ");
scanf("%d", &num);
getchar();  // Consume newline left by scanf

printf("Enter string: ");
fgets(str, sizeof(str), stdin);
```

---

## Best Practices

✅ **DO:**

- Use `fgets()` instead of `gets()` or `scanf("%s")`
- Write errors to `stderr`, not `stdout`
- Use `perror()` after system call failures
- Check return values of input functions
- Clear input buffer after `scanf()`
- Use `fflush(stdout)` for prompts without newlines

❌ **DON'T:**

- Use `gets()` - it's dangerous and removed from C11
- Use `scanf("%s")` without width limit
- Write error messages to `stdout`
- Ignore return values
- Mix line-based and character-based input without clearing buffer
