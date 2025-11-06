#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Flexible Array Member (FAM) - C99 feature
// The last member of a struct can be an array of unspecified size
typedef struct
{
    size_t length;
    int data[]; // Flexible array member - MUST be last member
} IntArray;

typedef struct
{
    int id;
    size_t name_length;
    char name[]; // Flexible array member for variable-length string
} Person;

typedef struct
{
    int type;
    size_t count;
    double values[]; // Flexible array member
} DataPacket;

// Function to create an IntArray with n elements
IntArray *create_int_array(size_t n)
{
    // Allocate space for the struct + n integers
    IntArray *arr = malloc(sizeof(IntArray) + n * sizeof(int));
    if (arr)
    {
        arr->length = n;
        // Initialize array
        for (size_t i = 0; i < n; i++)
        {
            arr->data[i] = 0;
        }
    }
    return arr;
}

// Function to create a Person with a given name
Person *create_person(int id, const char *name)
{
    size_t name_len = strlen(name);
    // Allocate space for struct + string + null terminator
    Person *p = malloc(sizeof(Person) + name_len + 1);
    if (p)
    {
        p->id = id;
        p->name_length = name_len;
        strcpy(p->name, name);
    }
    return p;
}

// Function to create a DataPacket with n values
DataPacket *create_packet(int type, size_t count)
{
    DataPacket *pkt = malloc(sizeof(DataPacket) + count * sizeof(double));
    if (pkt)
    {
        pkt->type = type;
        pkt->count = count;
        for (size_t i = 0; i < count; i++)
        {
            pkt->values[i] = 0.0;
        }
    }
    return pkt;
}

int main(void)
{
    printf("=== Flexible Array Members (FAM) Examples ===\n\n");

    // Test 1: Basic integer array with FAM
    printf("Test 1: IntArray with flexible array member\n");
    {
        size_t size = 5;
        IntArray *arr = create_int_array(size);
        if (!arr)
        {
            fprintf(stderr, "Failed to create array\n");
            return EXIT_FAILURE;
        }

        printf("Created IntArray with %zu elements\n", arr->length);
        printf("Size of IntArray struct: %zu bytes\n", sizeof(IntArray));
        printf("Total allocation: %zu bytes\n", sizeof(IntArray) + size * sizeof(int));

        // Fill the array
        for (size_t i = 0; i < arr->length; i++)
        {
            arr->data[i] = (int)(i * 10);
        }

        // Print the array
        printf("Array contents: ");
        for (size_t i = 0; i < arr->length; i++)
        {
            printf("%d ", arr->data[i]);
        }
        printf("\n\n");

        free(arr);
    }

    // Test 2: Person with variable-length name
    printf("Test 2: Person with flexible array for name\n");
    {
        Person *p1 = create_person(1, "Alice");
        Person *p2 = create_person(2, "Bob");
        Person *p3 = create_person(3, "Christopher");

        if (!p1 || !p2 || !p3)
        {
            fprintf(stderr, "Failed to create persons\n");
            free(p1);
            free(p2);
            free(p3);
            return EXIT_FAILURE;
        }

        printf("Person 1: id=%d, name='%s' (length=%zu)\n", p1->id, p1->name, p1->name_length);
        printf("Person 2: id=%d, name='%s' (length=%zu)\n", p2->id, p2->name, p2->name_length);
        printf("Person 3: id=%d, name='%s' (length=%zu)\n", p3->id, p3->name, p3->name_length);

        printf("\nMemory efficiency:\n");
        printf("  Base Person struct size: %zu bytes\n", sizeof(Person));
        printf("  Person 1 total: %zu bytes (5 char + null)\n", sizeof(Person) + strlen(p1->name) + 1);
        printf("  Person 3 total: %zu bytes (11 char + null)\n", sizeof(Person) + strlen(p3->name) + 1);

        free(p1);
        free(p2);
        free(p3);
    }
    printf("\n");

    // Test 3: DataPacket with different sizes
    printf("Test 3: DataPacket with variable number of values\n");
    {
        DataPacket *small = create_packet(1, 3);
        DataPacket *large = create_packet(2, 10);

        if (!small || !large)
        {
            fprintf(stderr, "Failed to create packets\n");
            free(small);
            free(large);
            return EXIT_FAILURE;
        }

        // Fill small packet
        for (size_t i = 0; i < small->count; i++)
        {
            small->values[i] = (double)i * 1.5;
        }

        // Fill large packet
        for (size_t i = 0; i < large->count; i++)
        {
            large->values[i] = (double)i * 2.5;
        }

        printf("Small packet (type=%d, count=%zu): ", small->type, small->count);
        for (size_t i = 0; i < small->count; i++)
        {
            printf("%.1f ", small->values[i]);
        }
        printf("\n");

        printf("Large packet (type=%d, count=%zu): ", large->type, large->count);
        for (size_t i = 0; i < large->count; i++)
        {
            printf("%.1f ", large->values[i]);
        }
        printf("\n");

        free(small);
        free(large);
    }
    printf("\n");

    // Test 4: Comparison with pointer approach (old style)
    printf("Test 4: FAM vs Pointer approach\n");
    {
        // Old style: using a pointer
        typedef struct
        {
            size_t length;
            int *data; // Pointer - requires separate allocation
        } IntArrayOld;

        IntArrayOld old;
        old.length = 5;
        old.data = malloc(old.length * sizeof(int));
        if (!old.data)
        {
            fprintf(stderr, "Failed to allocate\n");
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < old.length; i++)
        {
            old.data[i] = (int)(i * 10);
        }

        // New style: using FAM
        IntArray *new = create_int_array(5);
        if (!new)
        {
            fprintf(stderr, "Failed to create array\n");
            free(old.data);
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < new->length; i++)
        {
            new->data[i] = (int)(i * 10);
        }

        printf("Old style (pointer):\n");
        printf("  Two allocations required (struct + data)\n");
        printf("  Two frees required\n");
        printf("  Data may not be cache-friendly (separate allocations)\n");

        printf("\nNew style (FAM):\n");
        printf("  Single allocation (struct + data together)\n");
        printf("  Single free required\n");
        printf("  Better cache locality (contiguous memory)\n");

        free(old.data);
        free(new);
    }
    printf("\n");

    // Test 5: Resizing a FAM structure (requires realloc)
    printf("Test 5: Resizing with realloc\n");
    {
        IntArray *arr = create_int_array(3);
        if (!arr)
        {
            fprintf(stderr, "Failed to create array\n");
            return EXIT_FAILURE;
        }

        arr->data[0] = 10;
        arr->data[1] = 20;
        arr->data[2] = 30;

        printf("Original array (%zu elements): ", arr->length);
        for (size_t i = 0; i < arr->length; i++)
        {
            printf("%d ", arr->data[i]);
        }
        printf("\n");

        // Resize to 6 elements
        size_t new_size = 6;
        IntArray *resized = realloc(arr, sizeof(IntArray) + new_size * sizeof(int));
        if (!resized)
        {
            fprintf(stderr, "Failed to resize array\n");
            free(arr);
            return EXIT_FAILURE;
        }
        arr = resized;
        arr->length = new_size;

        // Initialize new elements
        arr->data[3] = 40;
        arr->data[4] = 50;
        arr->data[5] = 60;

        printf("Resized array (%zu elements): ", arr->length);
        for (size_t i = 0; i < arr->length; i++)
        {
            printf("%d ", arr->data[i]);
        }
        printf("\n");

        free(arr);
    }

    printf("\n=== Important Notes ===\n");
    printf("1. Flexible array member MUST be the LAST member of the struct\n");
    printf("2. Introduced in C99 standard\n");
    printf("3. The array has NO size specified: int data[] or char name[]\n");
    printf("4. sizeof(struct) does NOT include the flexible array\n");
    printf("5. Must allocate: sizeof(struct) + (n * sizeof(element))\n");
    printf("6. Benefits:\n");
    printf("   - Single allocation instead of two\n");
    printf("   - Better cache locality (contiguous memory)\n");
    printf("   - Only one free() needed\n");
    printf("   - Cleaner code and less pointer indirection\n");
    printf("7. Cannot be used with arrays of structs\n");
    printf("8. Cannot be copied with assignment (use memcpy with proper size)\n");
    printf("9. Use realloc() to resize the entire structure\n");

    printf("\n=== Common Use Cases ===\n");
    printf("✓ Variable-length strings in structs\n");
    printf("✓ Network packets with variable payload\n");
    printf("✓ Dynamic arrays within structures\n");
    printf("✓ Data structures that grow/shrink\n");
    printf("✓ Memory-efficient collections\n");

    return EXIT_SUCCESS;
}
