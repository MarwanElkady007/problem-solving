#include <iostream>
using namespace std;

// ----------------------------------------------------
// Sequential Search (Iterative)
// time complexity: O(n)
// ----------------------------------------------------
int sequentialSearchIterative(int arr[], int n, int target)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

// ----------------------------------------------------
// Sequential Search (Recursive)
// time complexity: O(n)
// ----------------------------------------------------
int sequentialSearchRecursive(int arr[], int n, int target, int index = 0)
{
    if (index >= n)
        return -1;
    if (arr[index] == target)
        return index;
    return sequentialSearchRecursive(arr, n, target, index + 1);
}

// ----------------------------------------------------
// Binary Search (Iterative)
// time complexity: O(log n)
// ----------------------------------------------------
int binarySearchIterative(int arr[], int n, int target)
{
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        // int mid = low + (high - low) / 2; to avoid overflow
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// ----------------------------------------------------
// Binary Search (Recursive)
// time complexity: O(log n)
// ----------------------------------------------------
int binarySearchRecursive(int arr[], int low, int high, int target)
{
    if (low > high)
        return -1;

    int mid = (low + high) / 2;
    if (arr[mid] == target)
        return mid;
    else if (arr[mid] < target)
        return binarySearchRecursive(arr, mid + 1, high, target);
    else
        return binarySearchRecursive(arr, low, mid - 1, target);
}

// ----------------------------------------------------
// Main Function for Testing
// ----------------------------------------------------
int main()
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[100];
    cout << "Enter " << n << " elements (sorted for binary search): ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int target;
    cout << "Enter target value: ";
    cin >> target;

    cout << "\nSequential Search (Iterative): ";
    int result = sequentialSearchIterative(arr, n, target);
    if (result != -1)
        cout << "Found at index " << result;
    else
        cout << "Not found";

    cout << "\nSequential Search (Recursive): ";
    result = sequentialSearchRecursive(arr, n, target);
    if (result != -1)
        cout << "Found at index " << result;
    else
        cout << "Not found";

    cout << "\nBinary Search (Iterative): ";
    result = binarySearchIterative(arr, n, target);
    if (result != -1)
        cout << "Found at index " << result;
    else
        cout << "Not found";

    cout << "\nBinary Search (Recursive): ";
    result = binarySearchRecursive(arr, 0, n - 1, target);
    if (result != -1)
        cout << "Found at index " << result;
    else
        cout << "Not found";

    cout << endl;
    return 0;
}
