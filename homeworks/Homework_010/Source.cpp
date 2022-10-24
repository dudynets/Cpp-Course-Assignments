#include <iostream>
#include <math.h>
using namespace std;

// declare constants
const double E_PRECISION = 0.00001;

// declare functions
double getS(int x);
double getY(int x);
int getFactorial(int n);
double getPercentageError(double approximate, double exact);

int main()
{
    // declare variables
    int start;
    int step;

    // prompt user for start value
    cout << "Enter start value (a): " << endl;
    cout << "--> ";
    cin >> start;
    cout << endl;

    // prompt user for step value
    cout << "Enter step value (h): " << endl;
    cout << "--> ";
    cin >> step;
    cout << endl;

    // set output precision
    cout.setf(ios::fixed);
    cout.precision(10);

    // iterate through 10 values beginning at user defined start value with user defined step value
    for (int i = 0; i < 10; i++)
    {
        // declare and initialize variables
        int x = start + (i * step);
        double s = getS(x);
        double y = getY(x);
        double error = getPercentageError(s, y);

        // output results
        cout << "x -------> " << x << endl;
        cout << "S -------> " << s << endl;
        cout << "y -------> " << y << endl;
        cout << "Error ---> " << error << "%" << endl;
        cout << endl;
    }

    return 0;
}

// function that gets the value of S
double getS(int x)
{
    // declare variables
    double prevS = 0;
    double lastS = 0;
    int k = 0;

    // iterate until the difference between the current and previous value of S is less than the precision
    do
    {
        prevS = lastS;
        lastS += pow(x, k + 2) / (getFactorial(k) * (k + 2));
        k++;
    } while (lastS - prevS > E_PRECISION);

    return lastS;
}

// function that gets the value of y
double getY(int x)
{
    return (x - 1) * pow(exp(1.0), x) + 1;
}

// function that gets the factorial of a number
int getFactorial(int n)
{
    int result = 1;
    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

// function that gets the percentage error
double getPercentageError(double approximate, double exact)
{
    // if the exact value is 0, return 0 to avoid division by 0
    return exact == 0 ? 0 : fabs((approximate - exact) / exact) * 100;
}
