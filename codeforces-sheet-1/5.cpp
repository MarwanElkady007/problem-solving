#include <iostream>
#include <iomanip> // for setprecision and fixed
using namespace std;

int main()
{
    double Radius, Area;
    cin >> Radius;

    const double pi = 3.141592653;
    Area = pi * Radius * Radius;

    cout << fixed << setprecision(9) << Area << endl;
}
