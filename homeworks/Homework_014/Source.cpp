#include <iostream>
#include <string>
using namespace std;

int main()
{
    // prompt user for string
    string input;
    cout << "Enter a string: " << endl;
    cout << "-> ";
    getline(cin, input);

    // initialize variables
    int currentLetter = 0;
    string *words = new string[input.size()]; // an array that stores words with uneven number of letters
    int wordsIndex = 0;

    // if the last char of the string is not a full-stop then add it manually
    if (input[input.size() - 1] != '.')
    {
        input += ".";
    }

    // iterate throught every character in the string
    for (int i = 0; i < input.size(); i++)
    {
        // if current letter is neither a space nor a full-stop then it's a part of a word,
        // so we increment the current word number of letters counter
        if (input[i] != ' ' && input[i] != '.')
        {
            currentLetter++;
            continue;
        }

        // if it is a space or a full-stop then the current word is finished, so
        // concatenate the specific amount of previous word letters into a single word
        string previousWord;
        while (currentLetter != 0)
        {
            previousWord += input[i - currentLetter];
            currentLetter--;
        }

        // check if the number of letters in it is uneven and if it is store it in the array
        if (previousWord.size() != 0 && previousWord.size() % 2 != 0)
        {
            words[wordsIndex] = previousWord;
            wordsIndex++;
        }
    }

    cout << "\n----------------\n\n";

    // print the result
    cout << "Words with uneven number of letters: " << endl;
    for (int i = 0; i < wordsIndex; i++)
    {
        cout << "- " << words[i] << endl;
    }

    return 0;
}
