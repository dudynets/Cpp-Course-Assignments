#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    string name;
    string group;
    int id;

public:
    Student() : name(""), group(""), id(0) {}
    Student(string _name, string _group, int _id) : name(_name), group(_group), id(_id) {}

    void setName(string _name)
    {
        name = _name;
    }

    void setGroup(string _group)
    {
        group = _group;
    }

    void setId(int _id)
    {
        id = _id;
    }

    string getName()
    {
        return name;
    }

    string getGroup()
    {
        return group;
    }

    int getId()
    {
        return id;
    }

    void print()
    {
        cout << "Name: " << name << endl;
        cout << "Group: " << group << endl;
        cout << "ID: " << id << endl;
    }

    void promptAll()
    {
        promptName();
        promptGroup();
        promptId();
    }

    void promptName()
    {
        cout << "Enter the name of the student: " << endl;
        cout << "--> ";
        cin >> name;
        cout << endl;
    }

    void promptGroup()
    {
        cout << "Enter the group of the student: " << endl;
        cout << "--> ";
        cin >> group;
        cout << endl;
    }

    void promptId()
    {
        cout << "Enter the ID of the student: " << endl;
        cout << "--> ";
        cin >> id;
        cout << endl;
    }
};

void beautifulPrint(Student student);
int promptForNumberOfStudents();
void search(string criteria, string query, Student *students, int numberOfStudents);
Student *sortStudents(Student *students, int numberOfStudents);

int main()
{
    int numberOfStudents = promptForNumberOfStudents();
    Student *students = new Student[numberOfStudents];

    cout << "################\n\n";

    for (int i = 0; i < numberOfStudents; i++)
    {
        students[i].promptAll();
        cout << "------------------\n\n";
    }

    for (int i = 0; i < numberOfStudents; i++)
    {
        beautifulPrint(students[i]);
    }

    string groupSearchQuery;
    cout << "Enter the group to search: " << endl;
    cout << "--> ";
    cin >> groupSearchQuery;
    cout << endl;

    cout << "SEARCH BY GROUP --\n\n";

    search("group", groupSearchQuery, students, numberOfStudents);

    cout << "SEARCH BY NAME ---\n\n";

    string nameSearchQuery;
    cout << "Enter the name to search: " << endl;
    cout << "--> ";
    cin >> nameSearchQuery;
    cout << endl;

    search("name", nameSearchQuery, students, numberOfStudents);

    cout << "EDIT -------------\n\n";

    string nameToEdit;
    cout << "Enter the name of the student: " << endl;
    cout << "--> ";
    cin >> nameToEdit;
    cout << endl;

    int idToEdit;
    cout << "Enter the new ID of the student: " << endl;
    cout << "--> ";
    cin >> idToEdit;
    cout << endl;

    for (int i = 0; i < numberOfStudents; i++)
    {
        if (students[i].getName() == nameToEdit)
        {
            students[i].setId(idToEdit);
        }
    }

    cout << "SORT -------------\n\n";

    Student *sortedStudents = sortStudents(students, numberOfStudents);
    for (int i = 0; i < numberOfStudents; i++)
    {
        beautifulPrint(sortedStudents[i]);
    }

    return 0;
}

void beautifulPrint(Student student)
{
    student.print();
    cout << "\n------------------\n\n";
}

int promptForNumberOfStudents()
{
    int numberOfStudents;
    cout << "Enter the number of students: " << endl;
    cout << "--> ";
    cin >> numberOfStudents;
    cout << endl;

    return numberOfStudents;
}

void search(string criteria, string query, Student *students, int numberOfStudents)
{
    bool found = false;
    cout << "# Found students: " << endl;
    if (criteria == "name")
    {
        for (int i = 0; i < numberOfStudents; i++)
        {
            if (students[i].getName() == query)
            {
                found = true;
                students[i].print();
                cout << "\n------------------\n\n";
            }
        }
    }
    else if (criteria == "group")
    {
        for (int i = 0; i < numberOfStudents; i++)
        {
            if (students[i].getGroup() == query)
            {
                found = true;
                students[i].print();
                cout << "\n------------------\n\n";
            }
        }
    }
    else if (criteria == "id")
    {
        for (int i = 0; i < numberOfStudents; i++)
        {
            if (students[i].getId() == stoi(query))
            {
                found = true;
                students[i].print();
                cout << "\n------------------\n\n";
            }
        }
    }
    else
    {
        cout << "- Invalid search criteria!" << endl;
    }

    if (!found)
    {
        cout << "- No students found!" << endl;
    }
}

Student *sortStudents(Student *students, int numberOfStudents)
{
    for (int i = 0; i < numberOfStudents; i++)
    {
        for (int j = i + 1; j < numberOfStudents; j++)
        {
            if (students[i].getId() > students[j].getId())
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    return students;
}
