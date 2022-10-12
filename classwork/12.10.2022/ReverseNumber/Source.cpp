#include <iostream>
#include <string>
using namespace std;

int main()
{
    // initialize variables
    int number;
    string reversedNumber;
    bool isNegative = false;

    // prompt user for number
    cout << "Enter your number: " << endl;
    cout << "-> ";
    cin >> number;
    cout << endl;

    // check if number is zero
    if (number == 0)
    {
        cout << "The reversed number is: 0" << endl;
        return 0;
    }

    // check if number is negative
    if (number < 0)
    {
        isNegative = true;
        number *= -1;
    }

    // loop to reverse number
    while (number > 0)
    {
        reversedNumber += to_string(number % 10);
        number /= 10;
    }

    // if the number was negative add a negative sign
    if (isNegative)
    {
        reversedNumber += "-";
    }

    // output the results
    cout << "The reversed number is: " << reversedNumber << endl;

    return 0;
}
