#include <iostream>

using namespace std;

// Визначити клас Студент з полями повне ім’я, конструктором дефолтним та операторами зсуву влів
// та вправо, методами get та set доступу до поля.

// Визначити клас Група з полями: динамічний масив студентів, кількість студентів, назва групи, рік вступу.
// В класі визначити конструктори дефолтний, копіювання, з параметрами, оператор присвоєння, індексування,
// деструктор, оператор зсуву вліво та вправо, а також методи get та set доступу до полів.

// Ввести дані про дві групи. Видрукувати дані про ці групи у алфавітному порядку назв груп.
// Вивести список студентів, в яких група має пізніший рік вступу.
// Створити нову групу, скопіювавши її з групи, кількість студентів в якій є менша.

class Student {
 private:
  string name;

 public:
  Student() : name("") {}

  // Getter
  string getName() const { return name; }

  // Setter
  void setName(string _name) { name = _name; }

  // Overload operators
  friend ostream &operator<<(ostream &out, const Student &student) {
    out << "    - " << student.name;
    return out;
  }

  friend istream &operator>>(istream &in, Student &student) {
    cout << "    Enter student name:\n";
    cout << "    --> ";
    in >> student.name;
    return in;
  }
};

class Group {
 private:
  Student *students;
  int studentsCount;
  string name;
  int year;

 public:
  // Constructors
  Group() : students(nullptr), studentsCount(0), name(""), year(0) {}
  Group(const Group &group) : studentsCount(group.studentsCount), name(group.name), year(group.year) {
    students = new Student[studentsCount];
    for (int i = 0; i < studentsCount; i++) {
      students[i] = group.students[i];
    }
  }
  Group(int _studentsCount, string _name, int _year) : studentsCount(_studentsCount), name(_name), year(_year) {
    students = new Student[studentsCount];
  }

  // Destructor
  ~Group() {
    delete[] students;
  }

  // Getters
  int getStudentsCount() const { return studentsCount; }
  string getName() const { return name; }
  int getYear() const { return year; }
  Student *getStudents() const { return students; }

  // Setters
  void setStudentsCount(int _studentsCount) { studentsCount = _studentsCount; }
  void setName(string _name) { name = _name; }
  void setYear(int _year) { year = _year; }
  void setStudents(Student *_students) { students = _students; }

  // Overload operators
  friend ostream &operator<<(ostream &out, const Group &group) {
    out << "Group name: " << group.name << endl;
    out << "Group year: " << group.year << endl;
    out << "Group students: " << endl;
    for (int i = 0; i < group.studentsCount; i++) {
      out << group.students[i] << endl;
    }
    return out;
  }

  friend istream &operator>>(istream &in, Group &group) {
    cout << "Enter group name:\n";
    cout << "--> ";
    in >> group.name;

    cout << "\nEnter group year:\n";
    cout << "--> ";
    in >> group.year;

    cout << "\nEnter group students count:\n";
    cout << "--> ";
    in >> group.studentsCount;

    group.students = new Student[group.studentsCount];
    for (int i = 0; i < group.studentsCount; i++) {
      cout << "\n";
      in >> group.students[i];
    }
    return in;
  }

  Group &operator=(const Group &group) {
    if (this == &group) {
      return *this;
    }
    delete[] students;
    studentsCount = group.studentsCount;
    name = group.name;
    year = group.year;
    students = new Student[studentsCount];
    for (int i = 0; i < studentsCount; i++) {
      students[i] = group.students[i];
    }
    return *this;
  }

  bool operator<(const Group &group) {
    return name < group.name;
  }

  Student &operator[](int index) {
    if (index < 0 || index >= studentsCount) {
      cout << "Index out of range" << endl;
      exit(1);
    }
    return students[index];
  }
};

int main() {
  Group group1;
  Group group2;

  cout << "ENTER FIRST GROUP DATA:\n";
  cin >> group1;

  cout << "\n-------------------------\n\n";

  cout << "ENTER SECOND GROUP DATA:\n";
  cin >> group2;

  cout << "\n-------------------------\n\n";

  cout << "GROUPS IN ALPHABETICAL ORDER:\n\n";

  if (group1 < group2) {
    cout << group1 << endl;
    cout << group2 << endl;
  } else {
    cout << group2 << endl;
    cout << group1 << endl;
  }

  cout << "-------------------------\n\n";

  cout << "STUDENTS OF THE MOST RECENT GROUP:\n";

  if (group1.getYear() > group2.getYear()) {
    for (int i = 0; i < group1.getStudentsCount(); i++) {
      cout << group1[i] << endl;
    }
  } else {

    for (int i = 0; i < group2.getStudentsCount(); i++) {
      cout << group2[i] << endl;
    }
  }

  cout << "\n-------------------------\n\n";

  cout << "NEW GROUP (Copied from the group with the least amount of students):\n\n";

  Group group3;

  if (group1.getStudentsCount() < group2.getStudentsCount()) {
    group3 = group1;
  } else {
    group3 = group2;
  }

  cout << group3 << endl;

  return 0;
}
