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

    // prompt user for start value
    int start;
    cout << "Enter start value: " << endl;
    cout << "--> ";
    cin >> start;
    cout << endl;

    // set output precision
    cout.setf(ios::fixed);
    cout.precision(10);

    for (int x = start; x <= start + 10; x++)
    {
        double s = getS(x);
        double y = getY(x);
        double error = getPercentageError(s, y);

        cout << "x = " << x << endl;
        cout << "S = " << s << endl;
        cout << "Y = " << y << endl;
        cout << "Error = " << error << "%" << endl
             << endl;
    }

    return 0;
}

double getS(int x)
{
    long double prevS = 0;
    long double lastS = 0;
    int k = 0;

    do
    {
        prevS = lastS;
        lastS += pow(x, k + 2) / (getFactorial(k) * (k + 2));
        k++;
    } while (fabs(lastS - prevS) <= E_PRECISION);

    return lastS;
}

double getY(int x)
{
    return (x - 1) * pow(exp(1.0), x) + 1;
}

int getFactorial(int n)
{
    int result = 1;
    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

double getPercentageError(double approximate, double exact)
{
    return fabs((approximate - exact) / exact) * 100;
}
