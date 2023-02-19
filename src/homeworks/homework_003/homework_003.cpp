#include <iostream>
#include <string>
using namespace std;

// declare functions
bool isDateValid(int day, int month);
string getZodiacSign(int day, int month);

// main app runtime
int main()
{
    // initialize day and month variables
    int day, month;

    // prompt user for day
    cout << "Please, enter your day index: " << endl;
    cout << "-> ";
    cin >> day;

    // prompt user for month
    cout << endl;
    cout << "Please, enter your month index: " << endl;
    cout << "-> ";
    cin >> month;

    // check if day and month are valid
    bool isValid = isDateValid(day, month);
    if (!isValid)
    {
        cout << "The date is invalid. Quiting..." << endl;
        return -1;
    }
    
    // get and output the result
    string zodiacSign = getZodiacSign(day, month);
    cout << endl << "Your zodiac sign is " << zodiacSign << "." << endl;

    return 0;
}

// function that checks if day and month are valid
bool isDateValid(int day, int month)
{
    if (day < 1 || day > 31 || month < 1 || month > 12)
    {
        return false;
    }

    if (month == 2 && day > 29)
    {
        return false;
    }
    if (month == 4 && day > 30)
    {
        return false;
    }
    if (month == 6 && day > 30)
    {
        return false;
    }
    if (month == 9 && day > 30)
    {
        return false;
    }
    if (month == 11 && day > 30)
    {
        return false;
    }

    return true;
}

// function that gets the Zodiac sign from day and month
string getZodiacSign(int day, int month)
{
    if (month == 1 && day >= 20 || month == 2 && day <= 18)
    {
        return "Aquarius";
    }
    else if (month == 2 && day >= 19 || month == 3 && day <= 20)
    {
        return "Pisces";
    }
    else if (month == 3 && day >= 21 || month == 4 && day <= 19)
    {
        return "Aries";
    }
    else if (month == 4 && day >= 20 || month == 5 && day <= 20)
    {
        return "Taurus";
    }
    else if (month == 5 && day >= 21 || month == 6 && day <= 20)
    {
        return "Gemini";
    }
    else if (month == 6 && day >= 21 || month == 7 && day <= 22)
    {
        return "Cancer";
    }
    else if (month == 7 && day >= 23 || month == 8 && day <= 22)
    {
        return "Leo";
    }
    else if (month == 8 && day >= 23 || month == 9 && day <= 22)
    {
        return "Virgo";
    }
    else if (month == 9 && day >= 23 || month == 10 && day <= 22)
    {
        return "Libra";
    }
    else if (month == 10 && day >= 23 || month == 11 && day <= 21)
    {
        return "Scorpio";
    }
    else if (month == 11 && day >= 22 || month == 12 && day <= 21)
    {
        return "Sagittarius";
    }
    else if (month == 12 && day >= 22 || month == 1 && day <= 19)
    {
        return "Capricorn";
    }
    else
    {
        return "Invalid date";
    }
}
