#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>

using namespace std;

vector<string> split(const string &str, const string &delimiter);

class Person {
 private:
  int id;
  string name;
  int age;
 public:
  Person(int _id, string _name, int _age) : id(_id), name(std::move(_name)), age(_age) {}
  virtual ~Person() = default;

  [[nodiscard]] virtual int getPayment() const = 0;

  [[nodiscard]] int getId() const {
    return id;
  }

  [[nodiscard]] string getName() const {
    return name;
  }

  [[nodiscard]] int getAge() const {
    return age;
  }

  friend bool operator<(const Person &p1, const Person &p2) {
    return p1.getName() < p2.getName();
  }

  friend ostream &operator<<(ostream &os, const Person &p) {
    os << "\n    Name: " << p.getName() << endl;
    os << "    Age: " << p.getAge() << " years old" << endl;
    return os;
  }
};

class Student : public Person {
 private:
  int scholarship;
  string group;
 public:
  Student(int _id, string _name, int _age, int _scholarship, string _group) : Person(_id, std::move(_name), _age),
                                                                              scholarship(_scholarship),
                                                                              group(std::move(_group)) {}

  [[nodiscard]] int getPayment() const override {
    return scholarship;
  }

  [[nodiscard]] string getGroup() const {
    return group;
  }

  friend ostream &operator<<(ostream &os, const Student &s) {

    os << static_cast<const Person &>(s);
    os << "    Scholarship: " << s.getPayment() << " UAH" << endl;
    os << "    Group: " << s.getGroup() << endl;
    return os;
  }
};

class Worker : public Person {
 private:
  int salary;
 public:
  Worker(int _id, string _name, int _age, int _salary) : Person(_id, std::move(_name), _age),
                                                         salary(_salary) {}

  [[nodiscard]] int getPayment() const override {
    return salary;
  }

  friend ostream &operator<<(ostream &os, const Worker &w) {
    os << static_cast<const Person &>(w);
    os << "    Salary: " << w.getPayment() << " UAH" << endl;
    return os;
  }
};

int main() {
  // Open input file
  ifstream file("../src/classworks/02_03_2023/class_inheritance/input.txt");

  // Check if file was opened successfully
  if (!file.is_open()) {
    cout << "Error opening file" << endl;
    return 1;
  }

  // Initialize vector to store persons
  vector<Person *> people;

  // Loop over file and read each line
  string line;
  while (getline(file, line)) {
    // Split line into tokens
    vector<string> tokens = split(line, " ");

    // Check if person is a student or a worker
    if (tokens[0] == "1") {
      // Create student object and add to persons vector
      auto *student = new Student(stoi(tokens[0]), tokens[1], stoi(tokens[2]), stoi(tokens[4]), tokens[3]);
      people.push_back(student);
    } else {
      // Create worker object and add to persons vector
      auto *worker = new Worker(stoi(tokens[0]), tokens[1], stoi(tokens[2]), stoi(tokens[3]));
      people.push_back(worker);
    }
  }

  // Close input file
  file.close();

  // Calculate total payments
  int total_payments = 0;
  for (Person *person : people) {
    auto *student = dynamic_cast<Student *>(person);
    if (student) {
      total_payments += student->getPayment();
    }
    auto *worker = dynamic_cast<Worker *>(person);
    if (worker) {
      total_payments += worker->getPayment();
    }
  }

  // Sort people by name
  sort(people.begin(), people.end(), [](Person *p1, Person *p2) { return *p1 < *p2; });

  // Count people
  int count = 0;

  // Print list of people
  for (Person *person : people) {
    auto *student = dynamic_cast<Student *>(person);
    if (student) {
      cout << "Student (" << person->getId() << "): " << *student << endl;
    }

    auto *worker = dynamic_cast<Worker *>(person);
    if (worker) {
      cout << "Worker (" << person->getId() << "): " << *worker << endl;
    }

    count++;
  }

  // Print total people
  cout << "Total people: " << count << endl;

  // Print total payments
  cout << "Total payments: " << total_payments << " UAH" << endl;

  // Free memory allocated for persons
  for (Person *person : people) {
    delete person;
  }

  return 0;
}

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
