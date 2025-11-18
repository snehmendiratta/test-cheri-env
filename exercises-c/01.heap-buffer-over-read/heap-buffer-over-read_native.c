// Native version for local testing: replaces CHERI-specific headers/macros
#include <stdio.h>
#include <stdlib.h>

#define __cheri_compartment(x)
#define CHERIOT_DEBUG_LOG(ctx, fmt, ...) printf("%s: " fmt "\n", ctx, ##__VA_ARGS__)
#define DEBUG_CONTEXT "Heap Buffer Over Read Compartment"

__cheri_compartment("heap-buffer-over-read") int vuln1()
{
    int* arr = (int*)malloc(3 * sizeof(int));
    if (arr == NULL) {return 0;} // Always check for malloc failure
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Buffer Over-read (C)...");

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Accessing arr[10]... ");
    int idx = 10;
    int value = 0;
    if (idx >= 0 && idx < 3) {
        value = arr[idx];
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Value: %d", value);
    } else {
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Out-of-bounds access detected for index %d, skipping read.", idx);
    }

    free(arr);
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "This line may not be reached if the program crashes.");

    return 0;
}

int main(void)
{
    return vuln1();
}
