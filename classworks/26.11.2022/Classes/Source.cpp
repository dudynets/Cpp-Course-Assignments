#include <iostream>
#include <fstream>
using namespace std;

struct Point
{
    int x;
    int y;

    // input
    friend istream &operator>>(istream &is, Point &point)
    {
        // cout << "Enter x: " << endl;
        is >> point.x;

        // cout << "Enter y: " << endl;
        is >> point.y;

        return is;
    }

    // output
    friend ostream &operator<<(ostream &os, Point &point)
    {
        os << "- x = " << point.x << endl;
        os << "- y = " << point.y << endl;

        return os;
    }
};

class Circle
{
private:
    Point center;
    int radius;

public:
    Circle() : center(), radius(0) {}
    Circle(Point _center, int _radius) : center(_center), radius(_radius) {}
    Circle(const Circle &circle) : center(circle.center), radius(circle.radius) {}

    // input
    friend istream &operator>>(istream &is, Circle &circle)
    {
        // cout << "Enter radius: " << endl;
        is >> circle.radius;

        // cout << "Enter center: " << endl;
        is >> circle.center;

        return is;
    }

    // output
    friend ostream &operator<<(ostream &os, Circle &circle)
    {
        os << "radius = " << circle.radius << endl;
        os << "center:" << endl
           << circle.center << endl;

        return os;
    }
};

int main()
{
    Circle circle;

    // cout << "Введіть дані про коло:" << endl;
    // cin >> circle; // operator >> (cin, circle)

    // cout << circle;

    // input from file
    ifstream ifs;
    ifs.open("classworks/26.11.2022/Classes/input.txt");
    ifs >> circle;
    ifs.close();

    // output to file
    ofstream ofs("classworks/26.11.2022/Classes/output.txt");
    ofs << circle;
    ofs.close();

    return 0;
}
