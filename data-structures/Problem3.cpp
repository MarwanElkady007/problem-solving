#include <iostream>
#include <fstream>
using namespace std;

void flipSegment(int* arr, int start, int end) {
    for (int i = start; i <= end; ++i) {
        arr[i] = 1 - arr[i]; 
    }
}

void printArray(const int* arr, int size) {
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    ifstream input("Problem3.txt");

    if (!input.is_open()) {
        cout << "Failed to open input3.txt" << endl;
        return 1;
    }

    int size;
    input >> size;

    int* arr = new int[size];
    for (int i = 0; i < size; ++i) {
        input >> arr[i];
    }

    int start, end;
    input >> start >> end;

    input.close();

    cout << "Original array:\n";
    printArray(arr, size);

    if (start >= 0 && end < size && start <= end) {
        flipSegment(arr, start, end);
        cout << "Array after flipping segment [" << start << ", " << end << "]:\n";
        printArray(arr, size);
    } else {
        cout << "Invalid segment indices.\n";
    }

    delete[] arr;
    return 0;
}
