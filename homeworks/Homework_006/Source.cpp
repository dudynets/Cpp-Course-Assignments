#include <iostream>
using namespace std;

int main()
{
    // initialize code variable
    int number;

    // prompt user for number
    cout << "Please, enter your number: " << endl;
    cout << "-> ";
    cin >> number;

    // check if number is positive
    if (number < 0)
    {
        cout << endl << "Please, enter a positive number. Quiting..." << endl;
        return -1;
    }

    // get sum of digits of the number
    int sum = 0;
    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
    }

    // output result
    cout << endl << "The sum of digits is: " << sum << endl;

    return 0;
}
