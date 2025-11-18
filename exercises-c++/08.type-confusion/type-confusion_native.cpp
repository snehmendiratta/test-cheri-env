// Native C++ version for local testing: replaces CHERI-specific headers/macros
#include <iostream>

using std::cout;
using std::endl;

const char hello[] = "Hello World!";

union long_ptr {
    long l;
    const char *ptr;
} lp = { .ptr = hello };

void inc_long_ptr(union long_ptr *lpp) {
    lpp->l++;
}

int vuln1()
{
    cout << "Testing Type confusion (C++)..." << endl;
    cout << "Before inc_long_ptr: lp.ptr = " << (char*)lp.ptr << endl;
    inc_long_ptr(&lp);
    if (lp.ptr != nullptr) {
        cout << "After inc_long_ptr: lp.ptr = " << (char*)lp.ptr << endl;
    } else {
        cout << "After inc_long_ptr: pointer became null or invalid, skipping print." << endl;
    }
    return 0;
}

int main() { return vuln1(); }
