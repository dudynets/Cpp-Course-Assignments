#include <iostream>
#include <string>
using namespace std;

int main()
{
    // initialize variables
    string input;
    int spacesQuantity = 0;

    // prompt user for string
    cout << "Enter a string: " << endl;
    cout << "-> ";
    getline(cin, input);  

    // iterate throught every character in the string
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == ' ') {
            spacesQuantity++;
        }
    }

    // output the quantity of words
    cout << endl << "The number of words in the string is: " << spacesQuantity + 1 << endl;

    return 0;
}
