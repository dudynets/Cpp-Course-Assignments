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

// Generic class that represents a phone
class Phone {
 private:
  string name;
  string manufacturer;
  int price;
 public:
  // Constructor
  Phone(string _name, string _manufacturer, int _price)
      : name(std::move(_name)), manufacturer(std::move(_manufacturer)), price(_price) {}

  // Destructor
  virtual ~Phone() = default;

  // Overload << operator
  friend ostream &operator<<(ostream &os, const Phone &p) {
    os << "Name: " << replaceUnderscoreWithSpace(p.getName()) << endl;
    os << "Manufacturer: " << replaceUnderscoreWithSpace(p.getManufacturer()) << endl;
    os << "Price: " << p.getPrice() << " UAH" << endl;
    return os;
  }

  // Overload > operator
  friend bool operator>(const Phone &p1, const Phone &p2) {
    return p1.getPrice() > p2.getPrice();
  }

  // Getter for name
  [[nodiscard]] string getName() const {
    return name;
  }

  // Getter for manufacturer
  [[nodiscard]] string getManufacturer() const {
    return manufacturer;
  }

  // Getter for price
  [[nodiscard]] int getPrice() const {
    return price;
  }
};

// Class that represents a mobile phone
class MobilePhone : public Phone {
 private:
  string color;
  int memory;
 public:
  // Constructor
  MobilePhone(string _name, string _manufacturer, int _price, string _color, int _memory)
      : Phone(std::move(_name), std::move(_manufacturer), _price), color(std::move(_color)), memory(_memory) {}

  // Overload << operator
  friend ostream &operator<<(ostream &os, const MobilePhone &p) {
    os << static_cast<const Phone &>(p);
    os << "Color: " << replaceUnderscoreWithSpace(p.getColor()) << endl;
    os << "Memory: " << p.getMemory() << "GB" << endl;
    return os;
  }

  // Getter for color
  [[nodiscard]] string getColor() const {
    return color;
  }

  // Getter for memory
  [[nodiscard]] int getMemory() const {
    return memory;
  }
};

// Class that represents a radio phone
class RadioPhone : public Phone {
 private:
  int radius;
  bool autoAnswer;
 public:
  // Constructor
  RadioPhone(string _name, string _manufacturer, int _price, int _radius, bool _autoAnswer)
      : Phone(std::move(_name), std::move(_manufacturer), _price), radius(_radius), autoAnswer(_autoAnswer) {}

  // Overload << operator
  friend ostream &operator<<(ostream &os, const RadioPhone &p) {
    os << static_cast<const Phone &>(p);
    os << "Radius: " << p.getRadius() << "m" << endl;
    if (p.isAutoAnswer()) {
      os << "Auto answer: present" << endl;
    } else {
      os << "Auto answer: not present" << endl;
    }

    return os;
  }

  // Getter for radius
  [[nodiscard]] int getRadius() const {
    return radius;
  }

  // Getter for autoAnswer
  [[nodiscard]] bool isAutoAnswer() const {
    return autoAnswer;
  }
};

int main() {
  // Initialize file stream
  ifstream file("../src/homeworks/homework_019/input.txt");

  // Check if file is opened
  if (!file.is_open()) {
    cout << "Error opening file" << endl;
    return 1;
  }

  // Create a vector of phones
  vector<Phone *> phones;

  // Read file line by line
  string line;
  while (getline(file, line)) {
    // Split line by space
    vector<string> data = split(line, " ");

    // Create a phone object and add it to the vector
    if (data[0] == "mobile_phone") {
      phones.push_back(new MobilePhone(data[1], data[2], stoi(data[3]), data[4], stoi(data[5])));
    } else if (data[0] == "radio_phone") {
      phones.push_back(new RadioPhone(data[1], data[2], stoi(data[3]), stoi(data[4]), data[5] == "1"));
    }
  }

  // Close the file
  file.close();

  // Sort phones by price
  sort(phones.begin(), phones.end(), [](Phone *p1, Phone *p2) {
    return *p1 > *p2;
  });

  // Calculate total price
  int totalPrice = 0;
  for (auto phone : phones) {
    totalPrice += phone->getPrice();
  }

  // Initialize file stream
  ofstream fileOutSortedByPrice("../src/homeworks/homework_019/sorted_by_price.txt");

  // Check if file is opened
  if (!fileOutSortedByPrice.is_open()) {
    cout << "Error opening file" << endl;
    return 1;
  }

  // Write total price to file
  fileOutSortedByPrice << "Total price: " << totalPrice << " UAH" << endl;

  // Write header to file
  fileOutSortedByPrice << "\n=======================\n";
  fileOutSortedByPrice << "PHONES SORTED BY PRICE:" << endl;
  fileOutSortedByPrice << "=======================\n\n";

  // Write phones to file
  for (auto phone : phones) {
    // dynamic cast to mobile phone
    if (auto *mobilePhone = dynamic_cast<MobilePhone *>(phone)) {
      if (phone == phones.back()) {
        fileOutSortedByPrice << *mobilePhone;
      } else {
        fileOutSortedByPrice << *mobilePhone << endl;
      }
      continue;
    }

    // dynamic cast to radio phone
    if (auto *radioPhone = dynamic_cast<RadioPhone *>(phone)) {
      if (phone == phones.back()) {
        fileOutSortedByPrice << *radioPhone;
      } else {
        fileOutSortedByPrice << *radioPhone << endl;
      }
      continue;
    }
  }

  // Initialize file stream
  ofstream fileOutAutoAnswerOnly("../src/homeworks/homework_019/auto_answer_only.txt");

  // Check if file is opened
  if (!fileOutAutoAnswerOnly.is_open()) {
    cout << "Error opening file" << endl;
    return 1;
  }

  // Write header to file
  fileOutAutoAnswerOnly << "==============================\n";
  fileOutAutoAnswerOnly << "RADIO PHONES WITH AUTO ANSWER:" << endl;
  fileOutAutoAnswerOnly << "==============================\n\n";

  // Write phones to file
  for (auto phone : phones) {
    // dynamic cast to radio phone
    auto *radioPhone = dynamic_cast<RadioPhone *>(phone);
    if (radioPhone != nullptr && radioPhone->isAutoAnswer()) {
      if (phone == phones.back()) {
        fileOutAutoAnswerOnly << *phone;
      } else {
        fileOutAutoAnswerOnly << *phone << endl;
      }
    }
  }

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
