// Native C++ version for local testing: replaces CHERI-specific headers/macros
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int vuln1()
{
    cout << "Testing Double Free..." << endl;
    int *ptr = (int*)malloc(sizeof(int));
    if (!ptr) { cout << "malloc returned NULL" << endl; return 0; }
    *ptr = 42;
    int *ptr2 = ptr;
    if (ptr != nullptr) {
        free(ptr);
        cout << "First free done" << endl;
        ptr = nullptr;
    } else {
        cout << "First free: pointer already null" << endl;
    }

    if (ptr2 != nullptr) {
        cout << "Second free attempt detected; skipping to avoid double-free." << endl;
    } else {
        cout << "Second free: pointer is null, nothing to do." << endl;
    }
    return 0;
}

int main() { return vuln1(); }
