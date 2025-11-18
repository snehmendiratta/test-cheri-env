// Native C++ version for local testing: replaces CHERI-specific headers/macros
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int vuln1()
{
    cout << "Running Buffer Over-read (C++)..." << endl;
    int* arr = new int[3];
    if (arr == nullptr)
    {
        cout << "Allocation failed!" << endl;
        return -1;
    }
    cout << "Array created, assigning values..." << endl;
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    cout << "Accessing arr[10] (out-of-bounds)..." << endl;
    int idx = 10;
    if (idx >= 0 && idx < 3) {
        int value = arr[idx]; // safe
        cout << "Value: " << value << endl;
    } else {
        cout << "Out-of-bounds access detected for index " << idx << ", skipping read." << endl;
    }
    delete[] arr;
    cout << "Completed without crashing (unexpected)" << endl;
    return 0;
}

int main()
{
    return vuln1();
}
