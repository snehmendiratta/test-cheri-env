// Native version for local testing: replaces CHERI-specific headers/macros
#include <stdio.h>

#define __cheri_compartment(x)
#define CHERIOT_DEBUG_LOG(ctx, fmt, ...) printf("%s: " fmt "\n", ctx, ##__VA_ARGS__)
#define DEBUG_CONTEXT "Type Confusion Compartment"

const char hello[] = "Hello World!";

union long_ptr {
    long l;
    const char *ptr;
} lp = { .ptr = hello };

void inc_long_ptr(union long_ptr *lpp) {
    lpp->l++;
}

__cheri_compartment("type-confusion") int vuln1(void)
{
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Type confusion (C)...");

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Before inc_long_ptr: lp.ptr = %s", (char*)lp.ptr);
    /* Defensive: ensure the union is in a sensible state before incrementing.
       This is a synthetic test; incrementing the long may change the pointer.
       We'll check for a plausible pointer value after the increment. */
    inc_long_ptr(&lp);
    if (lp.ptr != NULL) {
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "After inc_long_ptr: lp.ptr = %s", (char*)lp.ptr);
    } else {
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "After inc_long_ptr: pointer became NULL or invalid, skipping print.");
    }

    return 0;
}

int main(void) { return vuln1(); }
