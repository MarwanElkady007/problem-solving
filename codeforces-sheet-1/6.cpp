#include <iostream>

using namespace std;

int main()
{

    long long n, m;

    cin >> n >> m;

    long long n_last_digit = n % 10;
    long long m_last_digit = m % 10;

    cout << n_last_digit + m_last_digit << endl;
}