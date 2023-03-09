#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>

using namespace std;

// Functions declarations
vector<string> split(const string &str, const string &delimiter);
string replaceUnderscoreWithSpace(string str);

// Generic class that represents a computer
class Computer {
 private:
  string manufacturer;
  string model;
  int price;
 public:
  // Constructor
  Computer(string _manufacturer, string _model, int _price)
      : manufacturer(std::move(_manufacturer)), model(std::move(_model)), price(_price) {}

  // Destructor
  virtual ~Computer() = default;

  // Getter for manufacturer
  [[nodiscard]] string getManufacturer() const {
    return manufacturer;
  }

  // Getter for model
  [[nodiscard]] string getModel() const {
    return model;
  }

  // Getter for price
  [[nodiscard]] int getPrice() const {
    return price;
  }

  // Overload << operator
  friend ostream &operator<<(ostream &os, const Computer &c) {
    os << "Manufacturer: " << replaceUnderscoreWithSpace(c.getManufacturer()) << endl;
    os << "Model: " << replaceUnderscoreWithSpace(c.getModel()) << endl;
    os << "Price: " << c.getPrice() << " UAH" << endl;
    return os;
  }

  // Overload > operator
  friend bool operator>(const Computer &c1, const Computer &c2) {
    return c1.getPrice() > c2.getPrice();
  }
};

// Class that represents a desktop computer
class DesktopComputer : public Computer {
 private:
  string type;
  string cpuModel;
 public:
  // Constructor
  DesktopComputer(string _manufacturer, string _model, int _price, string _type, string _cpuModel)
      : Computer(std::move(_manufacturer), std::move(_model), _price),
        type(std::move(_type)),
        cpuModel(std::move(_cpuModel)) {}

  // Destructor
  ~DesktopComputer() override = default;

  // Getter for type
  [[nodiscard]] string getType() const {
    return type;
  }

  // Getter for cpuModel
  [[nodiscard]] string getCpuModel() const {
    return cpuModel;
  }

  // Overload << operator
  friend ostream &operator<<(ostream &os, const DesktopComputer &desktopComputer) {
    os << "=== DESKTOP COMPUTER ===" << endl;
    os << static_cast<const Computer &>(desktopComputer);
    os << "Type: " << replaceUnderscoreWithSpace(desktopComputer.getType()) << endl;
    os << "CPU model: " << replaceUnderscoreWithSpace(desktopComputer.getCpuModel()) << endl;
    return os;
  }
};

// Class that represents a laptop computer
class LaptopComputer : public Computer {
 private:
  int screenSize;
  int memory;
 public:
  // Constructor
  LaptopComputer(string _manufacturer, string _model, int _price, int _screenSize, int _memory)
      : Computer(std::move(_manufacturer), std::move(_model), _price), screenSize(_screenSize), memory(_memory) {}

  // Destructor
  ~LaptopComputer() override = default;

  // Getter for screenSize
  [[nodiscard]] int getScreenSize() const {
    return screenSize;
  }

  // Getter for memory
  [[nodiscard]] int getMemory() const {
    return memory;
  }

  // Overload << operator
  friend ostream &operator<<(ostream &os, const LaptopComputer &laptopComputer) {
    os << "=== LAPTOP COMPUTER ===" << endl;
    os << static_cast<const Computer &>(laptopComputer);
    os << "Screen size: " << laptopComputer.getScreenSize() << " inches" << endl;
    os << "Memory: " << laptopComputer.getMemory() << "GB" << endl;
    return os;
  }
};

int main() {
  // Initialize input file stream
  ifstream file("../src/tests/09_03_2023/inheritance/input.txt");

  // Check if file is opened
  if (!file.is_open()) {
    cout << "File not found" << endl;
    return 1;
  }

  // Create vector of computers
  vector<Computer *> computers;

  // Read file line by line
  string line;
  while (getline(file, line)) {
    // Split line by spaces
    vector<string> tokens = split(line, " ");

    // Create new computer object and add it to vector
    if (tokens[0] == "desktop") {
      computers.push_back(new DesktopComputer(tokens[1], tokens[2], stoi(tokens[3]), tokens[4], tokens[5]));
    } else if (tokens[0] == "laptop") {
      computers.push_back(new LaptopComputer(tokens[1], tokens[2], stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5])));
    }
  }

  // Close file
  file.close();

  // Initialize output file stream
  ofstream outputFile("../src/tests/09_03_2023/inheritance/output.txt");

  // Check if file is opened
  if (!outputFile.is_open()) {
    cout << "File not found" << endl;
    return 1;
  }

  // Sort computers by price
  sort(computers.begin(), computers.end(), [](Computer *c1, Computer *c2) {
    return *c1 > *c2;
  });

  // Get total price of all computers
  int totalPrice = 0;
  for (auto &computer : computers) {
    totalPrice += computer->getPrice();
  }

  // Get total price of all desktops
  int totalDesktopPrice = 0;
  for (auto &computer : computers) {
    if (auto *desktopComputer = dynamic_cast<DesktopComputer *>(computer)) {
      totalDesktopPrice += desktopComputer->getPrice();
    }
  }

  // Get total price of all laptops
  int totalLaptopPrice = 0;
  for (auto &computer : computers) {
    if (auto *laptopComputer = dynamic_cast<LaptopComputer *>(computer)) {
      totalLaptopPrice += laptopComputer->getPrice();
    }
  }


  // Output prices info to file
  outputFile << "Total price of all computers: " << totalPrice << " UAH" << endl;
  outputFile << "Total price of all desktops: " << totalDesktopPrice << " UAH" << endl;
  outputFile << "Total price of all laptops: " << totalLaptopPrice << " UAH\n\n";

  // Output divider to file
  outputFile << "==========================" << endl;
  outputFile << "COMPUTERS SORTED BY PRICE:" << endl;
  outputFile << "==========================\n\n";

  // Output computers sorted by price to file
  for (auto &computer : computers) {
    // dynamic cast to desktop or laptop
    if (auto *desktopComputer = dynamic_cast<DesktopComputer *>(computer)) {
      outputFile << *desktopComputer << endl;
    } else if (auto *laptopComputer = dynamic_cast<LaptopComputer *>(computer)) {
      outputFile << *laptopComputer << endl;
    }
  }

  // Initialize vector of manufacturers
  vector<string> manufacturers;

  // Add all manufacturers to vector
  for (auto &computer : computers) {
    if (find(manufacturers.begin(), manufacturers.end(), computer->getManufacturer()) == manufacturers.end()) {
      manufacturers.push_back(computer->getManufacturer());
    }
  }

  // Prompt user to choose manufacturer
  cout << "=== CHOOSE MANUFACTURER ===" << endl;
  for (int i = 0; i < manufacturers.size(); i++) {
    cout << "(" << i + 1 << ") " << replaceUnderscoreWithSpace(manufacturers[i]) << endl;
  }

  // Ask user to enter manufacturer index
  int manufacturerIndex;
  cout << "\nEnter manufacturer index:\n";
  cout << "--> ";
  cin >> manufacturerIndex;

  // Validate manufacturer index
  if (manufacturerIndex < 1 || manufacturerIndex > manufacturers.size()) {
    cout << "\n===========================" << endl;
    cout << "Invalid manufacturer index!" << endl;
    cout << "===========================" << endl;
    return 1;
  }

  // Get manufacturer name
  string chosenManufacturer = manufacturers[manufacturerIndex - 1];

  // Calculate divider length
  string divider;
  for (int i = 0; i < chosenManufacturer.length() + 2; i++) {
    divider += "=";
  }

  // Output desktops of chosen manufacturer to file
  outputFile << "=============" << divider << endl;
  outputFile << "DESKTOPS OF \"" << replaceUnderscoreWithSpace(chosenManufacturer) << "\":" << endl;
  outputFile << "=============" << divider << "\n\n";

  // Define if there are desktops of chosen manufacturer
  bool hasDesktops = false;

  // Iterate over computers
  for (auto &computer : computers) {
    // Check if computer is desktop and manufacturer is chosen
    if (auto *desktopComputer = dynamic_cast<DesktopComputer *>(computer)) {
      if (desktopComputer->getManufacturer() == chosenManufacturer) {
        hasDesktops = true;
        outputFile << *desktopComputer << endl;
      }
    }
  }

  // Output message if there are no desktops of chosen manufacturer
  if (!hasDesktops) {
    outputFile << "No desktops of this manufacturer" << endl;
  }

  // Print "Done!" message
  cout << "\n===========================" << endl;
  cout << "Done! Check output.txt file" << endl;
  cout << "===========================" << endl;

  // Close output file
  outputFile.close();

  return 0;
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
