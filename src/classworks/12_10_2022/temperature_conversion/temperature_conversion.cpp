#include <iostream>
using namespace std;

int main()
{
    // iterate through the temperatures
    for (int degreesCelsius = 1; degreesCelsius <= 100; degreesCelsius++)
    {
        // convert to fahrenheit
        double degreesFahrenheit = (9.0 / 5.0) * degreesCelsius + 32;

        // output the result
        cout << endl;
        cout << "Degrees Celsius:       " << degreesCelsius << "\370C" << endl;
        cout << "Degrees Fahrenheit:    " << degreesFahrenheit << "\370F" << endl;
    }
    
    return 0;
}
