#include <iostream>
using namespace std;

int main()
{
    // initialize variables
    unsigned long long int fib[100];

    // set first two numbers
    fib[0] = 0;
    fib[1] = 1;

    // loop to calculate fibonacci numbers
    for (int i = 2; i < 100; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    // output the results
    for (int i = 1; i <= 100; i++)
    {
        cout << "The Fibonacci number with index of " << i << " is: " << fib[i] << endl;
    }

    return 0;
}
