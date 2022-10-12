#include <iostream>
using namespace std;

int main()
{
    // iterate through the temperatures
    for (int degreesCelcius = 1; degreesCelcius <= 100; degreesCelcius++)
    {
        // convert to fahrenheit
        double degreesFahrenheit = (9.0 / 5.0) * degreesCelcius + 32;

        // output the result
        cout << endl;
        cout << "Degrees Celcius:       " << degreesCelcius << "\370C" << endl;
        cout << "Degrees Fahrenheit:    " << degreesFahrenheit << "\370F" << endl;
    }
    
    return 0;
}
