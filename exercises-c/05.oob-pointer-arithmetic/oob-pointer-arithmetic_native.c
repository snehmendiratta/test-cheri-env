// Native version for local testing: replaces CHERI-specific headers/macros
#include <stdio.h>
#include <stdint.h>

#define __cheri_compartment(x)
#define CHERIOT_DEBUG_LOG(ctx, fmt, ...) printf("%s: " fmt "\n", ctx, ##__VA_ARGS__)
#define DEBUG_CONTEXT "OOB Pointer Arithmetic Compartment"

__cheri_compartment("oob-pointer-arithmetic") int vuln1(void)
{
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Out-Of-Bounds Pointer Arithmetic (C)...");
    int arr[4] = {100, 200, 300, 400};
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Array base: %p", (void*)arr);

    /* Make a pointer well past the end via arithmetic */
    int *p = arr + 10; // pointer now points far beyond arr
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Pointer moved to arr + 10: %p", (void*)p);

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Dereferencing OOB pointer ...");
    int val = 0;
    if (p >= arr && p < arr + 4) {
        val = *p; // safe
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Read value: %d", val);
    } else {
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Detected OOB pointer dereference, skipping read.");
    }

    return 0;
}

int main(void) { return vuln1(); }
