#include <iostream>
using namespace std;

int main()
{
    // initialize variables
    int n, m;

    // prompt user for numbers
    cout << "Enter the first number: " << endl;
    cout << "-> ";
    cin >> n;
    cout << endl;

    cout << "Enter the second number: " << endl;
    cout << "-> ";
    cin >> m;
    cout << endl;

    // check if numbers are valid
    if (n <= 0 || m <= 0)
    {
        cout << "Invalid input. Please enter positive integers." << endl;
        return -1;
    }

    // calculate GCD
    while (n != m)
    {
        if (n > m)
        {
            n = n - m;
        }
        else
        {
            m = m - n;
        }
    }

    // output the results
    cout << "The greatest common divisor is: " << n << endl;

    return 0;
}
