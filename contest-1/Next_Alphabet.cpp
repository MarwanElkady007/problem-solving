#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    string c ;
    cin >> c; 

    if (c[0] == 'z')
    {
        cout << 'a' << endl;
    }
    else
    {
    
    cout << (char)(c[0]+1) << endl;
    return 0;
    }
}