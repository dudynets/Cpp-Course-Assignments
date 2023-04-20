#include <iostream>
#include <list>
#include <regex>

using namespace std;

// Pattern of characters to filter out
const string FILTER_REGEX_PATTERN = "[^a-zA-Z0-9]";

// Function prototypes
list<wchar_t> promptForInput();
list<wchar_t> filterListByRegex(const string &regex, const list<wchar_t> &list);
list<wchar_t> getSortedUniqueList(const list<wchar_t> &inputList);

// Main function
int main() {
  // Prompt for input
  list<wchar_t> inputList = promptForInput();

  // Filter out unwanted characters
  list<wchar_t> filteredList = filterListByRegex(FILTER_REGEX_PATTERN, inputList);

  // Sort and remove duplicates
  list<wchar_t> sortedUniqueChars = getSortedUniqueList(filteredList);

  // Output regex pattern
  cout << "REGEX PATTERN:\n";
  cout << FILTER_REGEX_PATTERN << "\n\n";

  // Output input list
  cout << "INPUT LIST:\n";
  for (auto &it : inputList) {
    wcout << it;
  }

  // Output filtered list
  cout << "\n\nFILTERED LIST:\n";
  for (auto &it : filteredList) {
    wcout << it;
  }

  // Output sorted unique list
  cout << "\n\nSORTED UNIQUE LIST:\n";
  for (auto &it : sortedUniqueChars) {
    wcout << it;
  }

  return 0;
}

// Function that prompts the user for input
list<wchar_t> promptForInput() {
  // Define input list
  list<wchar_t> inputList;

  // Prompt for input
  wstring input;
  cout << "Please enter a string:\n";
  cout << "-> ";
  getline(wcin, input);
  cout << "\n--------------------------\n\n";

  // Split input into list
  for (wchar_t i : input) {
    inputList.push_back(i);
  }

  // Return input list
  return inputList;
}

// Function that filters a list by a regex pattern
list<wchar_t> filterListByRegex(const string &regexStr, const list<wchar_t> &inputList) {
  // Define filtered list
  list<wchar_t> filteredList;

  // Compile regex pattern
  regex regex(regexStr);

  // Filter out unwanted characters
  for (wchar_t it : inputList) {
    // Convert char to string
    string str(1, it);

    // Check if char matches regex pattern
    if (regex_search(str, regex)) {
      // Add char to filtered list
      filteredList.push_back(it);
    }
  }

  // Return filtered list
  return filteredList;
}

// Function that sorts and removes duplicates from a list
list<wchar_t> getSortedUniqueList(const list<wchar_t> &inputList) {
  // Copy input list
  list<wchar_t> sortedUniqueList = inputList;

  // Sort and remove duplicates
  sortedUniqueList.sort();
  sortedUniqueList.unique();

  // Return sorted unique list
  return sortedUniqueList;
}

