// Native C++ version for local testing: replaces CHERI-specific headers/macros
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int vuln1()
{
    cout << "Testing Heap Buffer Under-write (C++)..." << endl;
    int *arr = (int *)malloc(3 * sizeof(int));
    if (arr == NULL) { return 0; }
    arr[0] = 10; arr[1] = 20; arr[2] = 30;
    cout << "Attempting under-write arr[-1] = 999 ..." << endl;
    int idx = -1;
    if (idx >= 0 && idx < 3) {
        arr[idx] = 999;
        cout << "arr[-1]: " << arr[idx] << endl;
    } else {
        cout << "Detected invalid negative index " << idx << ", skipping write." << endl;
    }
    free(arr);
    cout << "Freed array (if we reached here)." << endl;
    return 0;
}

int main() { return vuln1(); }
