#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    // initialize arrays
    int a[999];
    int sumOfA[999];
    long double b[999];

    // prompt user for a number
    int n;
    cout << "Please, enter your number" << endl;
    cout << "--> ";
    cin >> n;

    // get "a" array
    for (int i = 1; i <= n; i++)
    {
        a[i] = i;
        if (i == 1)
        {
            sumOfA[1] = 1;
        }
        else {
            sumOfA[i] = sumOfA[i - 1] + i;
        }
    }

    // get "b" array
    for (int i = 1; i <= n; i++)
    {
        b[i] = a[i] / (1 + pow(sumOfA[i], 2));
    }

    // output results
    for (int i = 1; i <= n; i++)
    {
        cout << "b[" << i << "] = " << b[i] << endl;
    }

    return 0;
}
