#include <iostream>
using namespace std;

int main()
{
    long long A;
    cin >> A;
    long long B = A / 1000;
    if (B % 2 == 0)
    {
        cout << "EVEN";
    }
    else
    {
        cout << "ODD";
    }
}