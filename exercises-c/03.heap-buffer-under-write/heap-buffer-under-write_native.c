// Native version for local testing: replaces CHERI-specific headers/macros
#include <stdio.h>
#include <stdlib.h>

#define __cheri_compartment(x)
#define CHERIOT_DEBUG_LOG(ctx, fmt, ...) printf("%s: " fmt "\n", ctx, ##__VA_ARGS__)
#define DEBUG_CONTEXT "Heap Buffer Under Write Compartment"

__cheri_compartment("heap-buffer-under-write") int vuln1(void)
{
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Heap Buffer Under-write (C)...");

    int *arr = (int *)malloc(3 * sizeof(int));
    if (arr == NULL) { return 0; }
    arr[0] = 10; arr[1] = 20; arr[2] = 30;

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Attempting under-write arr[-1] = 999 ...");
    int idx = -1;
    if (idx >= 0 && idx < 3) {
        arr[idx] = 999;
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "arr[-1]: %d", arr[idx]);
    } else {
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Detected invalid negative index %d, skipping write.", idx);
    }

    free(arr);
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Freed array (if we reached here).");
    return 0;
}

int main(void) { return vuln1(); }
