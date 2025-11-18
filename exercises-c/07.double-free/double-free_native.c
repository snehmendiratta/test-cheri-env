// Native version for local testing: replaces CHERI-specific headers/macros
#include <stdio.h>
#include <stdlib.h>

#define __cheri_compartment(x)
#define CHERIOT_DEBUG_LOG(ctx, fmt, ...) printf("%s: " fmt "\n", ctx, ##__VA_ARGS__)
#define DEBUG_CONTEXT "Double Free Compartment"

__cheri_compartment("double-free") int vuln1(void)
{
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Double Free...");

    int *ptr = (int*)malloc(sizeof(int));
    if (!ptr) { CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "malloc returned NULL"); return 0; }
    *ptr = 42;

    int *ptr2 = ptr;

        /* Defensive free: check pointer before freeing, then null it to avoid double free */
        if (ptr != NULL) {
            free(ptr);
            CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "First free done");
            ptr = NULL;
        } else {
            CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "First free: pointer already NULL");
        }

        if (ptr2 != NULL) {
            /* If ptr2 still points to the same memory (and ptr was nulled), this indicates a possible double free attempt; avoid calling free again */
            CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Second free attempt detected; skipping to avoid double-free.");
        } else {
            CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Second free: pointer is NULL, nothing to do.");
        }

    return 0;
}

int main(void) { return vuln1(); }
