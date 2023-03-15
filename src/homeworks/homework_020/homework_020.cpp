#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>

using namespace std;

// Class that represents a cheat sheet
class CheatSheet {
 private:
  string subject;
  int number = 0;
 public:
  // Constructors
  CheatSheet() = default;
  CheatSheet(string _subject, int _number) : subject(std::move(_subject)), number(_number) {}

  // Destructor
  virtual ~CheatSheet() = default;

  // Getter for subject
  [[nodiscard]] string getSubject() const {
    return subject;
  }

  // Getter for number
  [[nodiscard]] int getNumber() const {
    return number;
  }

  // Overload << operator
  friend ostream &operator<<(ostream &os, const CheatSheet &cheat_sheet) {
    os << "      - Subject: " << cheat_sheet.getSubject() << endl;
    os << "      - Number: " << cheat_sheet.getNumber() << endl;
    return os;
  }
};

// Class that represents a paper cheat sheet inherited from the base class CheatSheet
class PaperCheatSheet : public CheatSheet {
 private:
  string size;
  string place;
 public:
  // Constructor
  PaperCheatSheet(string _subject, int _number, string _size, string _place) : CheatSheet(std::move(_subject), _number),
                                                                               size(std::move(_size)),
                                                                               place(std::move(_place)) {}

  // Getter for size
  [[nodiscard]] string getSize() const {
    return size;
  }

  // Getter for place
  [[nodiscard]] string getPlace() const {
    return place;
  }

  // Overload << operator
  friend ostream &operator<<(ostream &os, const PaperCheatSheet &paper_cheat_sheet) {
    os << "Paper cheat sheet:" << endl;
    os << static_cast<CheatSheet>(paper_cheat_sheet);
    os << "      - Size: " << paper_cheat_sheet.getSize() << endl;
    os << "      - Place: " << paper_cheat_sheet.getPlace() << endl;
    return os;
  }
};

// Class that represents an electronic cheat sheet inherited from the base class CheatSheet
class ElectronicCheatSheet : public CheatSheet {
 private:
  string carrier;
 public:
  // Constructor
  ElectronicCheatSheet(string _subject, int _number, string _name) : CheatSheet(std::move(_subject), _number),
                                                                     carrier(std::move(_name)) {}

  // Getter for carrier
  [[nodiscard]] string getCarrier() const {
    return carrier;
  }

  // Overload << operator
  friend ostream &operator<<(ostream &os, const ElectronicCheatSheet &electronic_cheat_sheet) {
    os << "Electronic cheat sheet:" << endl;
    os << static_cast<CheatSheet>(electronic_cheat_sheet);
    os << "      - Carrier: " << electronic_cheat_sheet.getCarrier() << endl;
    return os;
  }
};

// Class that represents a student
class Student {
 private:
  string name;
  string group;
  vector<CheatSheet *> cheat_sheets;
 public:
  // Constructor
  Student(string _name, string _group, vector<CheatSheet *> _cheat_sheets)
      : name(std::move(_name)), group(std::move(_group)), cheat_sheets(std::move(_cheat_sheets)) {}

  // Destructor
  virtual ~Student() = default;

  // Getter for name
  [[nodiscard]] string getName() const {
    return name;
  }

  // Getter for group
  [[nodiscard]] string getGroup() const {
    return group;
  }

  // Getter for cheat sheets
  [[nodiscard]] vector<CheatSheet *> getCheatSheets() const {
    return cheat_sheets;
  }

  // Overload << operator
  friend ostream &operator<<(ostream &os, const Student &student) {
    os << "Student:" << endl;
    os << "  Name: " << student.getName() << endl;
    os << "  Group: " << student.getGroup() << endl;
    os << "  Cheat sheets (" << student.getCheatSheets().size() << "):" << endl;

    int count = 1;
    for (const auto cheatSheet : student.getCheatSheets()) {
      if (const auto *paperCheatSheet = dynamic_cast<PaperCheatSheet *>(cheatSheet))
        os << "    " << count++ << ". " << *paperCheatSheet << endl;
      else if (const auto *electronicCheatSheet = dynamic_cast<ElectronicCheatSheet *>(cheatSheet))
        os << "    " << count++ << ". " << *electronicCheatSheet << endl;
    }
    return os;
  }
};

// Functions declarations
// Core functions
vector<Student *> parseStudents();
vector<CheatSheet *> parseCheatSheets(string line);
void outputAllData(const vector<Student *> &students);
void outputSortedCheatSheets(const vector<Student *> &students);
void outputElectronicCheatSheetsByCarrier(const vector<Student *> &students, const string &carrier);

// Helper functions
vector<string> split(const string &str, const string &delimiter);
string replaceUnderscoreWithSpace(string str);

// Main function
int main() {
  // Parse students from input.txt
  vector<Student *> students = parseStudents();

  // Output all data
  outputAllData(students);

  // Output all cheat sheets sorted by subject and number
  outputSortedCheatSheets(students);

  // Output all electronic cheat sheets by carrier
  outputElectronicCheatSheetsByCarrier(students, "Computer");

  return 0;
}

// Function to parse students from input.txt
vector<Student *> parseStudents() {
  // Open file with students data
  ifstream inputFile("../src/homeworks/homework_020/input.txt");

  // Check if file is opened
  if (!inputFile.is_open()) {
    cout << "Error opening file" << endl;
    exit(1);
  }

  // Initialize vector of students
  vector<Student *> students;

  // Get each line from input.txt
  string line;
  while (getline(inputFile, line)) {
    // Get student name
    string name = replaceUnderscoreWithSpace(line.substr(0, line.find(' ')));
    line = line.substr(line.find(' ') + 1);

    // Get student group
    string group = replaceUnderscoreWithSpace(line.substr(0, line.find(' ')));
    line = line.substr(line.find(' ') + 1);

    // Parse student cheat sheets
    vector<CheatSheet *> cheat_sheets = parseCheatSheets(line);

    // Create a new student and add it to vector of students
    students.push_back(new Student(name, group, cheat_sheets));
  }

  // Close file
  inputFile.close();

  // Return students
  return students;
}

// Function to parse cheat sheets from line
vector<CheatSheet *> parseCheatSheets(string line) {
  // Initialize vector of cheat sheets tokens
  vector<string> cheatSheetsTokens;

  // Define delimiter
  string delimiter = "] [";
  size_t position;
  string token;

  // Iterate over line
  while ((position = line.find(delimiter)) != string::npos) {
    // Get token
    token = line.substr(0, position);

    // Check if token starts with '['
    if (token[0] == '[') {
      // Remove '['
      token = token.substr(1);
    }

    // Check if token ends with ']'
    if (token[token.length() - 1] == ']') {
      // Remove ']'
      token = token.substr(0, token.length() - 1);
    }

    // Add token to vector
    cheatSheetsTokens.push_back(token);

    // Remove token from line
    line.erase(0, position + delimiter.length());
  }

  // Check if line ends with ']'
  if (line[line.length() - 1] == ']') {
    // Remove ']'
    line = line.substr(0, line.length() - 1);
  }

  // Add last token to vector
  cheatSheetsTokens.push_back(line);

  // Initialize vector of cheat sheets
  vector<CheatSheet *> cheatSheets;

  // Iterate over cheat sheets tokens
  for (auto &cheatSheetTokens : cheatSheetsTokens) {
    // Split token by space
    vector<string> tokens = split(cheatSheetTokens, " ");

    // Get cheat sheet type
    string cheatSheetType = tokens[0];

    // Get cheat sheet subject
    string subject = replaceUnderscoreWithSpace(tokens[1]);

    // Get cheat sheet number
    int number = stoi(tokens[2]);

    // Check if cheat sheet is paper
    if (cheatSheetType == "p") {
      // Get size
      string size = tokens[3];

      // Get place
      string place = tokens[4];

      // Create PaperCheatSheet object and add it to vector
      cheatSheets.push_back(new PaperCheatSheet(subject, number, size, place));
    } else if (cheatSheetType == "e") {
      // If cheat sheet is electronic

      // Get carrier
      string carrier = tokens[3];

      // Create ElectronicCheatSheet object and add it to vector
      cheatSheets.push_back(new ElectronicCheatSheet(subject, number, carrier));
    }
  }

  // Return vector of cheat sheets
  return cheatSheets;
}

// Function to output all data
void outputAllData(const vector<Student *> &students) {
  // Open file for writing
  ofstream outputFile("../src/homeworks/homework_020/output.txt");

  // Check if file is opened
  if (!outputFile.is_open()) {
    cout << "Error opening file" << endl;
    exit(1);
  }

  // Iterate over students
  for (auto &student : students) {
    // Write student to file
    outputFile << *student << endl;
  }

  // Close file
  outputFile.close();
}

// Function to output all cheat sheets sorted by subject and number
void outputSortedCheatSheets(const vector<Student *> &students) {
  // Open file for writing
  ofstream outputFile("../src/homeworks/homework_020/sorted.txt");

  // Check if file is opened
  if (!outputFile.is_open()) {
    cout << "Error opening file" << endl;
    exit(1);
  }

  // Get all cheat sheets
  vector<CheatSheet *> cheatSheets;
  for (auto &student : students) {
    for (auto &cheatSheet : student->getCheatSheets()) {
      cheatSheets.push_back(cheatSheet);
    }
  }

  // Initialize vector of cheat sheets sorted by subject
  vector<CheatSheet *> cheatSheetsSortedBySubject;

  // Copy cheat sheets to cheatSheetsSortedBySubject
  for (auto &cheatSheet : cheatSheets) {
    cheatSheetsSortedBySubject.push_back(cheatSheet);
  }

  // Sort cheat sheets by subject
  sort(cheatSheetsSortedBySubject.begin(), cheatSheetsSortedBySubject.end(), [](CheatSheet *a, CheatSheet *b) {
    return a->getSubject() < b->getSubject();
  });

  // Initialize vector of cheat sheets sorted by number
  vector<CheatSheet *> cheatSheetsSortedByNumber;

  // Copy cheat sheets to cheatSheetsSortedByNumber
  for (auto &cheatSheet : cheatSheets) {
    cheatSheetsSortedByNumber.push_back(cheatSheet);
  }

  // Sort cheat sheets by number
  sort(cheatSheetsSortedByNumber.begin(), cheatSheetsSortedByNumber.end(), [](CheatSheet *a, CheatSheet *b) {
    return a->getNumber() < b->getNumber();
  });

  // Write cheat sheets sorted by subject to file
  outputFile << "===============================" << endl;
  outputFile << "CHEAT SHEETS SORTED BY SUBJECT:" << endl;
  outputFile << "===============================\n\n";
  for (auto &cheatSheet : cheatSheetsSortedBySubject) {
    // dynamic cast to PaperCheatSheet or ElectronicCheatSheet
    if (const auto paperCheatSheet = dynamic_cast<PaperCheatSheet *>(cheatSheet)) {
      outputFile << *paperCheatSheet << endl;
    } else if (const auto electronicCheatSheet = dynamic_cast<ElectronicCheatSheet *>(cheatSheet)) {
      outputFile << *electronicCheatSheet << endl;
    }
  }

  // Print divider
  outputFile << endl;

  // Write cheat sheets sorted by number to file
  outputFile << "==============================" << endl;
  outputFile << "CHEAT SHEETS SORTED BY NUMBER:" << endl;
  outputFile << "==============================\n\n";
  for (auto &cheatSheet : cheatSheetsSortedByNumber) {
    // dynamic cast to PaperCheatSheet or ElectronicCheatSheet
    if (const auto paperCheatSheet = dynamic_cast<PaperCheatSheet *>(cheatSheet)) {
      outputFile << *paperCheatSheet << endl;
    } else if (const auto electronicCheatSheet = dynamic_cast<ElectronicCheatSheet *>(cheatSheet)) {
      outputFile << *electronicCheatSheet << endl;
    }
  }

  // Close file
  outputFile.close();
}

// Function to output electronic cheat sheets by carrier provided
void outputElectronicCheatSheetsByCarrier(const vector<Student *> &students, const string &carrier) {
  // Open file for writing
  ofstream outputFile("../src/homeworks/homework_020/by_carrier.txt");

  // Check if file is open
  if (!outputFile.is_open()) {
    cout << "Error opening file" << endl;
    exit(1);
  }

  // Get all cheat sheets
  vector<CheatSheet *> cheatSheets;
  for (auto &student : students) {
    for (auto &cheatSheet : student->getCheatSheets()) {
      cheatSheets.push_back(cheatSheet);
    }
  }

  // Initialize vector of electronic cheat sheets by carrier
  vector<CheatSheet *> electronicCheatSheetsByCarrier;

  // Iterate over all cheat sheets
  for (auto &cheatSheet : cheatSheets) {
    // Check if cheat sheet is electronic and if carrier matches
    if (const auto electronicCheatSheet = dynamic_cast<ElectronicCheatSheet *>(cheatSheet)) {
      if (electronicCheatSheet->getCarrier() == carrier) {
        // Add cheat sheet to vector
        electronicCheatSheetsByCarrier.push_back(cheatSheet);
      }
    }
  }

  // Generate divider
  string divider;
  for (int i = 0; i < carrier.length(); i++) {
    divider += "=";
  }

  // Write electronic cheat sheets by carrier to file
  outputFile << "======================================" << divider << endl;
  outputFile << "ELECTRONIC CHEAT SHEETS BY CARRIER (" << carrier << "):" << endl;
  outputFile << "======================================" << divider << "\n\n";
  for (auto &cheatSheet : electronicCheatSheetsByCarrier) {
    // dynamic cast to electronic cheat sheet
    if (const auto electronicCheatSheet = dynamic_cast<ElectronicCheatSheet *>(cheatSheet)) {
      outputFile << *electronicCheatSheet << endl;
    }
  }

  // Close file
  outputFile.close();
}

// Function to split string by delimiter
vector<string> split(const string &str, const string &delimiter) {
  vector<string> tokens;
  size_t start = 0, end;
  while ((end = str.find(delimiter, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delimiter.length();
  }
  tokens.push_back(str.substr(start));
  return tokens;
}

// Function to replace underscore with space
string replaceUnderscoreWithSpace(string str) {
  for (char &i : str) {
    if (i == '_') {
      i = ' ';
    }
  }
  return str;
}
