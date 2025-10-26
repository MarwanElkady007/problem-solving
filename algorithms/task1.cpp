#include <iostream>
using namespace std;

// ----------------------------------------------------
// Fibonacci using Recursion
// Time complexity : O(2^n)
// ----------------------------------------------------
long long fibRecursive(int n)
{
    if (n <= 1)
        return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// ----------------------------------------------------
// Fibonacci using Matrix Multiplication (Divide & Conquer)
// Time complexity : O(log n)
// ----------------------------------------------------

// Helper function to multiply two 2x2 matrices
void multiply(long long F[2][2], long long M[2][2])
{
    long long x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    long long y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    long long z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    long long w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

// Helper function to raise matrix F to the (n-1)th power
void power(long long F[2][2], int n)
{
    if (n == 0 || n == 1)
        return;
    long long M[2][2] = {{1, 1}, {1, 0}};
    power(F, n / 2);
    multiply(F, F);

    if (n % 2 != 0)
        multiply(F, M);
}

// Fibonacci using matrix exponentiation
long long fibMatrix(int n)
{
    if (n == 0)
        return 0;
    long long F[2][2] = {{1, 1}, {1, 0}};
    power(F, n - 1);
    return F[0][0];
}

// ----------------------------------------------------
// Fibonacci using Dynamic Programming
// Time complexity : O(n)
// ----------------------------------------------------
long long fibDP(int n)
{
    if (n <= 1)
        return n;

    long long prev2 = 0, prev1 = 1, curr;
    for (int i = 2; i <= n; i++)
    {
        curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

// ----------------------------------------------------
// Main Function for Testing
// ----------------------------------------------------
int main()
{
    int n;
    cout << "Enter n: ";
    cin >> n;

    cout << "\nFibonacci(" << n << ") using recursion = " << fibRecursive(n);
    cout << "\nFibonacci(" << n << ") using matrix multiplication = " << fibMatrix(n);
    cout << "\nFibonacci(" << n << ") using dynamic programming = " << fibDP(n);

    cout << endl;
    return 0;
}
