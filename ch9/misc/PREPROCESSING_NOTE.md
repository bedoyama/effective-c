# Viewing the Preprocessed Output

To see what the preprocessor does to your C source code, you can view the **translation unit** (the preprocessed output) before compilation.

## Command to Generate Preprocessed Output

```bash
clang -E -o translation.i foo.c
```

Or with GCC:

```bash
gcc -E -o translation.i foo.c
```

## What This Does

- **`-E`** flag: Stop after preprocessing stage (don't compile)
- **`-o translation.i`**: Output the preprocessed code to `translation.i`
- **`foo.c`**: Your source file

## What Gets Processed

The preprocessor:

1. **Expands `#include` directives** - Copies entire header file contents
2. **Expands macros** - Replaces `#define` macros with their values
3. **Processes conditional compilation** - Removes `#ifdef`/`#ifndef` blocks
4. **Removes comments** - All `//` and `/* */` comments are stripped
5. **Handles line continuations** - Processes backslash line breaks

## Example

**Original `foo.c`:**

```c
#include <stdio.h>
#define PI 3.14159

int main(void) {
    printf("PI = %f\n", PI);  // Print PI value
    return 0;
}
```

**After preprocessing (`translation.i`):**

```c
// Thousands of lines from stdio.h appear here first...

int main(void) {
    printf("PI = %f\n", 3.14159);
    return 0;
}
```

Notice:

- `#include <stdio.h>` is replaced with the entire contents of stdio.h (very long!)
- `PI` macro is replaced with `3.14159`
- Comments are removed
- No more preprocessor directives

## Viewing the Output

```bash
# Generate the file
clang -E -o translation.i foo.c

# View it (it will be very long due to includes!)
less translation.i
# or
cat translation.i
```

## Why This Is Useful

- **Understanding includes**: See exactly what headers bring in
- **Debugging macros**: See how complex macros expand
- **Learning**: Understand what the preprocessor actually does
- **Troubleshooting**: Debug preprocessor-related issues

## Note

The `.i` extension is conventional for preprocessed C source files, similar to how `.s` is used for assembly and `.o` for object files.
