#include <iostream>
using namespace std;

int main()
{
    double N;
    cin >> N;

    int intPart = (int)N;

    if (intPart == N) // It's an integer
    {
        cout << "int " << intPart << endl;
    }
    else // It's a float
    {
        double decimalPart = N - intPart;
        cout << "float " << intPart << " " << decimalPart << endl;
    }

    return 0;
}