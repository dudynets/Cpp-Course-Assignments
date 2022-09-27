#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    // initialize radius variable
    int radius;

    // prompt user for radius
    cout << "Please, enter the radius:" << endl;
    cout << "-> ";
    cin >> radius;

    // calculate circumference of circle, area of circle, and volume of sphere
    double circumference = 2 * M_PI * radius;
    double area = M_PI * pow(radius, 2);
    double volume = 4.0 / 3.0 * M_PI * pow(radius, 3);

    // set precision of output to 3 decimal places
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(3);

    // output the results
    cout << endl;
    cout << "RESULTS:" << endl;
    cout << "- Circumference of circle:   " << circumference << endl;
    cout << "- Area of circle:            " << area << endl;
    cout << "- Volume of sphere:          " << volume << endl;

    return 0;
}
