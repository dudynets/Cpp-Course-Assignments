#include <iostream>
using namespace std;

int main()
{
    // initialize variables
    int n;

    // prompt user for n number
    cout << "Please, enter your number: " << endl;
    cout << "-> ";
    cin >> n;

    // initialize arrays
    int fib[99999], f[99999];

    // get the fibonacci array
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    // get the "f" array
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        f[i] = f[i - 1] + f[i - 2] + fib[i - 2];
    }

    // output result
    cout << endl << "Result for n = " << n << ":" << endl << endl;
    for (int i = 0; i < n; i++)
    {
        cout << f[i] << endl;
    }

    return 0;
}
