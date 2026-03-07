#include <iostream>
using namespace std;

int main()
{
    long long A, B, C, D;
    cin >> A >> B >> C >> D;
    long long last2A = A % 100;
    long long last2B = B % 100;
    long long last2C = C % 100;
    long long last2D = D % 100;

    long long result = last2A * last2B * last2C * last2D;

    if (result % 100 <= 9)
    {
        cout << "0" << result % 100 << endl;
    }
    else
    {
        cout << result % 100 << endl;
    }
}