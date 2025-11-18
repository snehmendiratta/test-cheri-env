// Native version for local testing: replaces CHERI-specific headers/macros
#include <stdio.h>
#include <stdlib.h>

#define __cheri_compartment(x)
#define CHERIOT_DEBUG_LOG(ctx, fmt, ...) printf("%s: " fmt "\n", ctx, ##__VA_ARGS__)
#define DEBUG_CONTEXT "Use After Free Compartment"

__cheri_compartment("use-after-free") int vuln1()
{
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Use-After-Free (C)...");
    int* ptr = (int*)malloc(sizeof(int));
    if (ptr == NULL) {return 0;}
    *ptr = 123;
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "ptr points to memory with value: %d", *ptr);

    free(ptr);
    ptr = NULL;
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Memory has been freed.");

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Attempting to dereference dangling pointer... ");
    if (ptr != NULL) {
        *ptr = 456; // safe write
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Value is now: %d", *ptr);
    } else {
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Pointer is NULL after free; skipping dereference.");
    }

    return 0;
}

int main(void) { return vuln1(); }
