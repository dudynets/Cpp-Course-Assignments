#include <iostream>

using namespace std;

class Course {
 private:
  string name;
  int code;
  string speciality;

 public:
  Course() : name(""), code(0), speciality("") {
  };
  Course(string _name, int _code, string _speciality) : name(_name), code(_code), speciality(_speciality) {
  };

  string getName() {
    return name;
  }

  int getCode() {
    return code;
  }

  string getSpeciality() {
    return speciality;
  }

  int showMenu() {
    cout << "--------------------------------\n";
    cout << "COURSE \"" << name << "\" MENU:\n\n";

    cout << "1. Show students\n";
    cout << "2. Remove course\n";
    cout << "3. Return\n\n";

    int choice;
    cout << "Enter your choice:\n";
    cout << "--> ";
    cin >> choice;

    cout << "--------------------------------\n\n";

    return choice;
  }

  friend ostream &operator<<(ostream &os, const Course &course) {
    os << "Name: " << course.name << endl;
    os << "Code: " << course.code << endl;
    os << "Speciality: " << course.speciality << endl;
    return os;
  };
};

class Student {
 private:
  string name;
  int id;
  string *specialities;
  int numberOfSpecialities;

 public:
  Student() : name(""), id(0), numberOfSpecialities(0) {
    specialities = new string[100];
  };
  Student(string _name) : name(_name), numberOfSpecialities(0) {
    id = rand() % 1000000000000;
    specialities = new string[100];
  };

  void addSpeciality(string speciality) {
    specialities[numberOfSpecialities++] = speciality;
  }

  string getName() {
    return name;
  }

  int getId() {
    return id;
  }

  string *getSpecialities() {
    return specialities;
  }

  int getNumberOfSpecialities() {
    return numberOfSpecialities;
  }

  int showMenu() {
    cout << "--------------------------------\n";
    cout << "STUDENT \"" << name << "\" MENU:\n\n";

    cout << "1. Show courses\n";
    cout << "2. Add speciality\n";
    cout << "3. Remove student\n";
    cout << "4. Return\n\n";

    int choice;
    cout << "Enter your choice:\n";
    cout << "--> ";
    cin >> choice;

    cout << "--------------------------------\n\n";

    return choice;
  }

  friend ostream &operator<<(ostream &os, const Student &student) {
    os << "Name: " << student.name << endl;
    os << "ID: " << student.id << endl;
    os << "Specialities: " << endl;
    for (int i = 0; i < student.numberOfSpecialities; i++) {
      os << "  - " << student.specialities[i] << endl;
    }
    return os;
  };
};

class University {
 private:
  string name;
  string location;
  Student *students;
  Course *courses;
  int numberOfStudents;
  int numberOfCourses;

 public:
  University(string _name, string _location)
      : name(_name), location(_location), numberOfStudents(0), numberOfCourses(0) {
    students = new Student[100];
    courses = new Course[100];
  };

  void addStudent(Student student, bool silently = false) {
    students[numberOfStudents++] = student;

    if (silently) {
      return;
    }

    cout << "--------------------------------\n";
    cout << "Student \"" << student.getName() << "\" has been added\n";
    cout << "--------------------------------\n\n";
  }

  void removeStudentById(int id) {
    string name;
    for (int i = 0; i < numberOfStudents; i++) {
      if (students[i].getId() == id) {
        name = students[i].getName();
        break;
      }
    }

    if (name == "") {
      cout << "--------------------------------\n";
      cout << "Student with id \"" << id << "\" has not been found\n";
      cout << "--------------------------------\n\n";
      return;
    }

    for (int i = 0; i < numberOfStudents; i++) {
      if (students[i].getId() == id) {
        for (int j = i; j < numberOfStudents; j++) {
          students[j] = students[j + 1];
        }
        numberOfStudents--;
        break;
      }
    }

    cout << "--------------------------------\n";
    cout << "Student \"" << name << "\" has been removed\n";
    cout << "--------------------------------\n\n";
  }

  void addCourse(Course course, bool silently = false) {
    courses[numberOfCourses++] = course;

    if (silently) {
      return;
    }

    cout << "--------------------------------\n";
    cout << "Course \"" << course.getName() << "\" has been added\n";
    cout << "--------------------------------\n\n";
  }

  void removeCourseByCode(int code) {
    string name;
    for (int i = 0; i < numberOfCourses; i++) {
      if (courses[i].getCode() == code) {
        name = courses[i].getName();
        break;
      }
    }

    if (name == "") {
      cout << "--------------------------------\n";
      cout << "Course with code \"" << code << "\" has not been found\n";
      cout << "--------------------------------\n\n";
      return;
    }

    for (int i = 0; i < numberOfCourses; i++) {
      if (courses[i].getCode() == code) {
        for (int j = i; j < numberOfCourses; j++) {
          courses[j] = courses[j + 1];
        }
        numberOfCourses--;
        break;
      }
    }

    cout << "--------------------------------\n";
    cout << "Course \"" << name << "\" has been removed\n";
    cout << "--------------------------------\n\n";
  }

  void printStudentsByCourseCode(int code) {
    bool hasStudents = false;
    bool isCourseFound = false;
    string speciality = "";

    for (int i = 0; i < numberOfCourses; i++) {
      if (courses[i].getCode() == code) {
        isCourseFound = true;
        speciality = courses[i].getSpeciality();

        cout << "--------------------------------\n";
        cout << "STUDENTS OF \"" << courses[i].getName() << "\":\n\n";
        break;
      }
    }

    if (!isCourseFound) {
      cout << "--------------------------------\n";
      cout << "Course with code \"" << code << "\" has not been found\n";
      cout << "--------------------------------\n\n";
      return;
    }

    for (int i = 0; i < numberOfStudents; i++) {
      for (int j = 0; j < students[i].getNumberOfSpecialities(); j++) {
        if (students[i].getSpecialities()[j] == speciality) {
          cout << students[i] << endl;
          hasStudents = true;
          break;
        }
      }
    }

    if (!hasStudents) {
      cout << "No students\n";
    }

    cout << "--------------------------------\n\n";
  }

  void printCoursesByStudentId(int id) {
    bool hasSpeciality = false;
    bool isStudentFound = false;

    for (int i = 0; i < numberOfStudents; i++) {
      if (students[i].getId() == id) {
        isStudentFound = true;

        cout << "--------------------------------\n";
        cout << "COURSES OF \"" << students[i].getName() << "\":\n\n";
        break;
      }
    }

    if (!isStudentFound) {
      cout << "--------------------------------\n";
      cout << "Student with id \"" << id << "\" has not been found\n";
      cout << "--------------------------------\n\n";
      return;
    }

    for (int i = 0; i < numberOfCourses; i++) {
      for (int j = 0; j < numberOfStudents; j++) {
        if (students[j].getId() == id) {
          for (int k = 0; k < students[j].getNumberOfSpecialities(); k++) {
            if (students[j].getSpecialities()[k] == courses[i].getSpeciality()) {
              hasSpeciality = true;
              cout << courses[i] << "\n";
            }
          }
        }
      }
    }

    if (!hasSpeciality) {
      cout << "No courses\n";
    }

    cout << "--------------------------------\n\n";
  }

  void printAllStudents() {
    bool hasStudents = false;

    cout << "--------------------------------\n";
    cout << "ALL STUDENTS:\n\n";

    for (int i = 0; i < numberOfStudents; i++) {
      hasStudents = true;
      cout << students[i];

      if (i != numberOfStudents - 1) {
        cout << "\n";
      }
    }

    if (!hasStudents) {
      cout << "No students\n";
    }

    cout << "--------------------------------\n\n";
  }

  void printAllCourses() {
    bool hasCourses = false;

    cout << "--------------------------------\n";
    cout << "ALL COURSES:\n\n";

    for (int i = 0; i < numberOfCourses; i++) {
      hasCourses = true;
      cout << courses[i];

      if (i != numberOfCourses - 1) {
        cout << "\n";
      }
    }

    if (!hasCourses) {
      cout << "No courses\n";
    }

    cout << "--------------------------------\n\n";
  }

  Student *findStudentByName(string name) {
    for (int i = 0; i < numberOfStudents; i++) {
      if (students[i].getName() == name) {
        return &students[i];
      }
    }

    return nullptr;
  }

  Course *findCourseByName(string name) {
    for (int i = 0; i < numberOfCourses; i++) {
      if (courses[i].getName() == name) {
        return &courses[i];
      }
    }

    return nullptr;
  }

  void showMenu() {
    cout << "--------------------------------\n";
    cout << "MAIN MENU:\n\n";

    cout << "1. Add student\n";
    cout << "2. Add course\n";
    cout << "3. Find student by name\n";
    cout << "4. Find course by name\n";
    cout << "5. Print all students\n";
    cout << "6. Print all courses\n";
    cout << "7. Exit\n\n";

    int choice;
    cout << "Enter your choice:\n";
    cout << "--> ";
    cin >> choice;

    cout << "--------------------------------\n\n";

    switch (choice) {
      case 1: {
        cout << "--------------------------------\n";
        cout << "ADD STUDENT\n\n";

        string name;

        cout << "Enter student name:\n";
        cout << "--> ";
        cin >> name;

        Student student(name);

        cout << "--------------------------------\n\n";

        addStudent(student);

        break;
      }
      case 2: {
        cout << "--------------------------------\n";
        cout << "ADD COURSE\n\n";

        string name;
        int code;
        string speciality;

        cout << "Enter course name:\n";
        cout << "--> ";
        cin >> name;
        cout << "\nEnter course code:\n";
        cout << "--> ";
        cin >> code;
        cout << "\nEnter course speciality:\n";
        cout << "--> ";
        cin >> speciality;

        Course course(name, code, speciality);

        cout << "--------------------------------\n\n";

        addCourse(course);
        break;
      }
      case 3: {
        cout << "--------------------------------\n";
        cout << "FIND STUDENT BY NAME\n";
        cout << "--------------------------------\n\n";

        string name;
        cout << "Enter student name:\n";
        cout << "--> ";
        cin >> name;

        cout << "\n";

        Student *student = findStudentByName(name);

        bool showMenu = true;

        while (showMenu) {
          int choice = student->showMenu();

          switch (choice) {
            case 1: {
              printCoursesByStudentId(student->getId());
              break;
            }
            case 2: {
              string speciality;
              cout << "Enter speciality:\n";
              cout << "--> ";
              cin >> speciality;

              student->addSpeciality(speciality);

              break;
            }
            case 3: {
              showMenu = false;
              removeStudentById(student->getId());
              break;
            }
            case 4: {
              showMenu = false;
              break;
            }
          }
        }

        break;
      }
      case 4: {
        cout << "--------------------------------\n";
        cout << "FIND COURSE BY NAME\n";
        cout << "--------------------------------\n\n";

        string name;
        cout << "Enter course name:\n";
        cout << "--> ";
        cin >> name;

        cout << "\n";

        Course *course = findCourseByName(name);

        bool showMenu = true;

        while (showMenu) {
          int choice = course->showMenu();

          switch (choice) {
            case 1: {
              printStudentsByCourseCode(course->getCode());
              break;
            }
            case 2: {
              showMenu = false;
              removeCourseByCode(course->getCode());
              break;
            }
            case 3: {
              showMenu = false;
              break;
            }
          }
        }

        break;
      }
      case 5: {
        printAllStudents();
        break;
      }
      case 6: {
        printAllCourses();
        break;
      }
      case 7: {
        exit(0);
      }
      default: {
        cout << "--------------------------------\n";
        cout << "Wrong choice\n";
        cout << "--------------------------------\n\n";
        break;
      }
    }
  }

};

int main() {
  University university("Lviv National University", "Lviv");

  Student student1("Ivan");
  student1.addSpeciality("Math");
  student1.addSpeciality("Physics");
  student1.addSpeciality("Chemistry");

  Student student2("Petro");
  student2.addSpeciality("Math");
  student2.addSpeciality("Physics");
  student2.addSpeciality("Biology");

  Student student3("Vasyl");
  student3.addSpeciality("Math");
  student3.addSpeciality("Physics");
  student3.addSpeciality("Chemistry");

  Student student4("Oleh");
  student4.addSpeciality("Math");
  student4.addSpeciality("Physics");
  student4.addSpeciality("Biology");

  Student student5("Mykola");
  student5.addSpeciality("Math");
  student5.addSpeciality("Physics");
  student5.addSpeciality("Chemistry");

  Course course1("Math", 1, "Math");
  Course course2("Physics", 2, "Physics");
  Course course3("Chemistry", 3, "Chemistry");
  Course course4("Biology", 4, "Biology");

  university.addStudent(student1, true);
  university.addStudent(student2, true);
  university.addStudent(student3, true);
  university.addStudent(student4, true);
  university.addStudent(student5, true);

  university.addCourse(course1, true);
  university.addCourse(course2, true);
  university.addCourse(course3, true);
  university.addCourse(course4, true);

  while (true) {
    university.showMenu();
  }

  return 0;
}
