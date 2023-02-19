#include <iostream>
#include <string>
using namespace std;

int main()
{
    // initialize variables
    int hours, minutes, seconds;
    bool isValid = true;

    // prompt user for hours
    cout << "Please, enter your hours: " << endl;
    cout << "-> ";
    cin >> hours;

    // prompt user for minutes
    cout << endl;
    cout << "Please, enter your minutes: " << endl;
    cout << "-> ";
    cin >> minutes;

    // prompt user for seconds
    cout << endl;
    cout << "Please, enter your seconds: " << endl;
    cout << "-> ";
    cin >> seconds;


    // check if hours minutes and seconds are valid
    if (hours < 0 || hours > 23)
    {
        isValid = false;
    }
    if (minutes < 0 || minutes > 59)
    {
        isValid = false;
    }
    if (seconds < 0 || seconds > 59)
    {
        isValid = false;
    }

    // output validation result
    if (!isValid)
    {
        cout << endl << "The time is invalid." << endl;
        return -1;
    }

    // add 0 to the left of the number if it is less than 10
    string hoursStr = hours < 10 ? "0" + to_string(hours) : to_string(hours);
    string minutesStr = minutes < 10 ? "0" + to_string(minutes) : to_string(minutes);
    string secondsStr = seconds < 10 ? "0" + to_string(seconds) : to_string(seconds);

    // output result
    cout << endl << "The time is valid (" << hoursStr << ":" << minutesStr << ":" << secondsStr << ")" << endl;

    return 0;
}
