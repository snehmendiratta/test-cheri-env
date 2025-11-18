// Native C++ version for local testing: replaces CHERI-specific headers/macros
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int vuln1()
{
    cout << "Testing Use-After-Free (C++)..." << endl;
    int* ptr = (int*)malloc(sizeof(int));
    if (ptr == nullptr) { return 0; }
    *ptr = 123;
    cout << "ptr points to memory with value: " << *ptr << endl;
    free(ptr);
    ptr = nullptr;
    cout << "Memory has been freed." << endl;
    cout << "Attempting to dereference dangling pointer... " << endl;
    if (ptr != nullptr) {
        *ptr = 456; // safe write
        cout << "Value is now: " << *ptr << endl;
    } else {
        cout << "Pointer is nullptr after free; skipping dereference." << endl;
    }
    return 0;
}

int main() { return vuln1(); }
