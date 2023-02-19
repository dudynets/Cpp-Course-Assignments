#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    // initialize number variables
    int num1, num2;

    // prompt user for first number
    cout << "Please, enter the first number:" << endl;
    cout << "-> ";
    cin >> num1;

    // prompt user for second number
    cout << endl;
    cout << "Please, enter the second number:" << endl;
    cout << "-> ";
    cin >> num2;

    // calculate arithmetic and geometric means
    double arithmeticMean = (num1 + num2) / 2.0;
    double geometricMean = sqrt(num1 * num2);

    // set precision of output to 3 decimal places
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(3);

    // output the results
    cout << endl;
    cout << "RESULTS:" << endl;
    cout << "- Arithmetic mean:   " << arithmeticMean << endl;
    cout << "- Geometric mean:    " << geometricMean << endl;

    return 0;
}
