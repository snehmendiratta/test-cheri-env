// Native C++ version for local testing: replaces CHERI-specific headers/macros
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int vuln1()
{
    int* arr = (int*)malloc(3 * sizeof(int));
    if (arr == nullptr) { return 0; }
    arr[0] = 1; arr[1] = 2; arr[2] = 3;
    cout << "Testing Buffer Over-write (C++)..." << endl;
    cout << "Attempting to write arr[4]..." << endl;
    int idx = 4;
    if (idx >= 0 && idx < 3) {
        arr[idx] = 999;
        cout << "arr[4]: " << arr[idx] << endl;
    } else {
        cout << "Out-of-bounds write prevented for index " << idx << "." << endl;
    }
    free(arr);
    cout << "This line may not be reached if the program crashes." << endl;
    return 0;
}

int main() { return vuln1(); }
