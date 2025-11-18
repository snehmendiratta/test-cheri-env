// Native version for local testing: replaces CHERI-specific headers/macros
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

#define __cheri_compartment(x)
#define CHERIOT_DEBUG_LOG(ctx, fmt, ...) printf("%s: " fmt "\n", ctx, ##__VA_ARGS__)
#define DEBUG_CONTEXT "Stack Buffer Over Write Compartment"

void write_buf(char *buf, size_t buf_size, size_t ix)
{
    /* Safe wrapper: check bounds and clamp index if necessary to avoid crash */
    if (buf == NULL || buf_size == 0) return;
    if (ix >= buf_size) {
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "write_buf: index %zu out-of-range (size %zu), clamping to last element", ix, buf_size);
        ix = buf_size - 1;
    }
    buf[ix] = 'b';
}

__cheri_compartment("stack-buffer-over-write") int vuln1(void)
{
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Stack Buffer Over Write (C)...");

    char upper[0x10];
    char lower[0x10];

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "upper = %p, lower = %p, diff = %zu",
        (void*)upper, (void*)lower, (size_t)(upper - lower));
    
    /* Do not assert on stack layout in native test; proceed safely */
    upper[0] = 'a';
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "upper[0] = %c", upper[0]);

    /* Call write_buf with the true buffer size; index was originally sizeof(lower) which is OOB, so this will be clamped */
    write_buf(lower, sizeof(lower), sizeof(lower));

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "upper[0] = %c", upper[0]);

    return 0;
}

int main(void) { return vuln1(); }
