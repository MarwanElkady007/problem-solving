#include <iostream>
using namespace std;

int main()
{

    long long A;
    cin >> A;

    long long y = A / 365;
    long long m = (A % 365) / 30;
    long long d = (A % 365) % 30;

    cout << y << " years" << endl;
    cout << m << " months" << endl;
    cout << d << " days" << endl;
}