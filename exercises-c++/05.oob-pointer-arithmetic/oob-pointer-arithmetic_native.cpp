// Native C++ version for local testing: replaces CHERI-specific headers/macros
#include <iostream>

using std::cout;
using std::endl;

int vuln1()
{
    cout << "Testing Out-Of-Bounds Pointer Arithmetic (C++)..." << endl;
    int arr[4] = {100,200,300,400};
    cout << "Array base: " << static_cast<void*>(arr) << endl;
    int *p = arr + 10; // pointer now points far beyond arr
    cout << "Pointer moved to arr + 10: " << static_cast<void*>(p) << endl;
    cout << "Dereferencing OOB pointer ..." << endl;
    if (p >= arr && p < arr + 4) {
        int val = *p;
        cout << "Read value: " << val << endl;
    } else {
        cout << "Detected OOB pointer; skipping dereference." << endl;
    }
    return 0;
}

int main() { return vuln1(); }
