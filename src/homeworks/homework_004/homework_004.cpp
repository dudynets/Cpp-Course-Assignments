#include <iostream>
#include <string>
using namespace std;

// declare functions
bool isMonthValid(int month);
string getMonthName(int month);

// main app runtime
int main()
{
    // initialize month variable
    int month;

    // prompt user for month
    cout << "Please, enter your month index: " << endl;
    cout << "-> ";
    cin >> month;

    // check if month is valid
    bool isValid = isMonthValid(month);
    if (!isValid)
    {
        cout << endl << "The month is invalid. Quiting..." << endl;
        return -1;
    }

    // get and output the result
    string monthName = getMonthName(month);
    cout << endl << "Your month is " << monthName << "." << endl;

    return 0;
}

// function that checks if month is valid
bool isMonthValid(int month)
{
    if (month < 1 || month > 12)
    {
        return false;
    }
    return true;
}

// function that get month name
string getMonthName(int month)
{
    switch (month)
    {
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    default:
        return "Invalid month";
    }
}
