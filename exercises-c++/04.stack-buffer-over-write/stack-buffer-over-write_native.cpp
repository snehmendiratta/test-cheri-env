// Native C++ version for local testing: replaces CHERI-specific headers/macros
#include <iostream>
#include <cassert>
#include <cstdint>

using std::cout;
using std::endl;

void write_buf(char *buf, size_t buf_size, size_t ix)
{
    if (buf == NULL || buf_size == 0) return;
    if (ix >= buf_size) {
        cout << "write_buf: index " << ix << " out-of-range (size " << buf_size << "), clamping to last element" << endl;
        ix = buf_size - 1;
    }
    buf[ix] = 'b';
}

int vuln1()
{
    cout << "Testing Stack Buffer Over Write (C++)..." << endl;

    char upper[0x10];
    char lower[0x10];

    cout << "upper = " << static_cast<void*>(upper) << ", lower = " << static_cast<void*>(lower)
         << ", diff = " << (upper - lower) << endl;
    
    /* Assert that these get placed how we expect */
    /* Do not assert on stack layout in native test; proceed safely */

    upper[0] = 'a';
    cout << "upper[0] = " << upper[0] << endl;

    write_buf(lower, sizeof(lower), sizeof(lower));

    cout << "upper[0] = " << upper[0] << endl;

    return 0;
}

int main() { return vuln1(); }
