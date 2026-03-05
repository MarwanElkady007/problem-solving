#include <iostream>

using namespace std;

int main()
{

    int A, B, C;
    cin >> A >> B >> C;

    int arr[3] = {A, B, C};

    int max = arr[0];
    int min = arr[0];

    for (int i = 1; i < 3; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    cout << min << " " << max << endl;
}