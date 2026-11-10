#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{

    int x, p;
    float o;
    cin >> x >> p;

    o = p * 100.0 / (100 - x);
    o = ceil(o * 100) / 100;
    cout << fixed << setprecision(2) << o << endl;

    return 0;
}