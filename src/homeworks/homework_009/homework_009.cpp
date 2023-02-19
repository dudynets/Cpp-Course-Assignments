#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    // initialize variables
    long double sequence[105];
    sequence[1] = 0.3;
    sequence[2] = -0.3;

    // get the sequence
    for (int i = 3; i <= 100; i++)
    {
        sequence[i] = (long double)i + sin(sequence[i - 2]);
    }

    // get a closest to the whole number from the sequence
    long double closest;
    long double smallestFraction = 1.0;

    for (int i = 1; i <= 100; i++)
    {
        long double currentFraction = abs(sequence[i] - round(sequence[i]));
        if (smallestFraction > currentFraction)
        {
            closest = sequence[i];
            smallestFraction = currentFraction;
        }
    }

    // set precision of output to 10 decimal places
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(10);

    // output the result
    cout << "The closest to the whole number from the sequence is: " << closest << endl;

    return 0;
}
