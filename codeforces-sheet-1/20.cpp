#include <iostream>

using namespace std;

int main()
{

    int A, B, C;
    cin >> A >> B >> C;

    // Store original values
    int original[3] = {A, B, C};

    // Create an array for sorting
    int arr[3] = {A, B, C};

    // Sort the array (bubble sort)
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Print sorted values
    for (int i = 0; i < 3; i++)
    {
        cout << arr[i] << endl;
    }

    // Print blank line
    cout << endl;

    // Print original values
    for (int i = 0; i < 3; i++)
    {
        cout << original[i] << endl;
    }

    return 0;
}