// Native version for local testing: replaces CHERI-specific headers/macros
#include <stdio.h>
#include <stdlib.h>

#define __cheri_compartment(x)
#define CHERIOT_DEBUG_LOG(ctx, fmt, ...) printf("%s: " fmt "\n", ctx, ##__VA_ARGS__)
#define DEBUG_CONTEXT "Heap Buffer Over Write Compartment"

__cheri_compartment("heap-buffer-over-write") int vuln1(void)
{
    int* arr = (int*)malloc(3 * sizeof(int));
    if (arr == NULL) { return 0; }

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Buffer Over-write (C)...");

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Attempting to write arr[4]...");
    int idx = 4;
    if (idx >= 0 && idx < 3) {
        arr[idx] = 999; // Writing inside allocated memory
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "arr[4]: %d", arr[idx]);
    } else {
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Out-of-bounds write prevented for index %d.", idx);
    }

    free(arr);
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "This line may not be reached if the program crashes.");

    return 0;
}

int main(void) { return vuln1(); }
