#include <iostream>
using namespace std;

int main()
{
    float A;
    cin >> A;

    if (A >= 0 && A <= 25)
    {
        cout << "Interval [0,25]" << endl;
    }
    else if (A > 25 && A <= 50)
    {
        cout << "Interval (25,50]" << endl;
    }
    else if (A > 50 && A <= 75)
    {
        cout << "Interval (50,75]" << endl;
    }
    else if (A > 75 && A <= 100)
    {
        cout << "Interval (75,100]" << endl;
    }
    else
    {
        cout << "Out of Intervals" << endl;
    }
}