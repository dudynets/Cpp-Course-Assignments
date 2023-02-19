#include <iostream>
#include <math.h>
using namespace std;

// declare functions
bool isValid(int m);

int main()
{
    // initialize variables
    int k = 0;

    // prompt user for input
    int m;
    cout << "Enter your number: " << endl;
    cin >> m;
    cout << endl;

    // check if number is valid
    if (!isValid(m))
    {
        cout << "Your number is invalid" << endl;
        return -1;
    }

    // loop while 4 in power of k is less than m
    while(pow(4, k) < m)
    {
        k++;
    }

    // output the results
    cout << "The biggest k is: " << k - 1 << endl;
    
    return 0;
}

// function that checks if number is valid
bool isValid(int m)
{
    return m > 1;
}
