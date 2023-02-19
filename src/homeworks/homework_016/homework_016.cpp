#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

struct Point
{
    int x;
    int y;

    // output
    friend ostream &operator<<(ostream &os, Point &point)
    {
        os << "- z = " << point.x << endl;
        os << "- y = " << point.y << endl;

        return os;
    }
};

struct Angle
{
    int degrees;

    // output
    friend ostream &operator<<(ostream &os, Angle &angle)
    {
        os << "- angle = " << angle.degrees << endl;

        return os;
    }
};

struct Coefficients
{
    int a;
    int b;
    int c;

    // input
    friend istream &operator>>(istream &is, Coefficients &coefficients)
    {
        cout << "- Enter a: " << endl;
        cout << "  --> ";
        is >> coefficients.a;

        cout << "\n- Enter b: " << endl;
        cout << "  --> ";
        is >> coefficients.b;

        cout << "\n- Enter c: " << endl;
        cout << "  --> ";
        is >> coefficients.c;

        return is;
    }

    // output
    friend ostream &operator<<(ostream &os, Coefficients &coefficients)
    {
        os << "- a = " << coefficients.a << endl;
        os << "- b = " << coefficients.b << endl;
        os << "- c = " << coefficients.c << endl;

        return os;
    }
};

class Line
{
private:
    Coefficients coefficients;

public:
    Line() : coefficients() {}
    Line(Coefficients _coefficients) : coefficients(_coefficients) {}
    Line(const Line &line) : coefficients(line.coefficients) {}

    // input
    friend istream &operator>>(istream &is, Line &line)
    {
        is >> line.coefficients;

        return is;
    }

    // output
    friend ostream &operator<<(ostream &os, Line &line)
    {
        os << "Coefficients:" << endl
           << line.coefficients << endl;

        return os;
    }

    // method that returns the point of intersection of two lines
    Point getIntersection(Line &line)
    {
        Point point;

        point.x =
            (line.coefficients.b * this->coefficients.c - this->coefficients.b * line.coefficients.c) /
            (line.coefficients.a * this->coefficients.b - this->coefficients.a * line.coefficients.b);
        point.y =
            (line.coefficients.a * this->coefficients.c - this->coefficients.a * line.coefficients.c) /
            (line.coefficients.b * this->coefficients.a - this->coefficients.b * line.coefficients.a);

        return point;
    }

    // method that returns the angle between two lines
    Angle getAngle(Line &line)
    {
        Angle angle;
        angle.degrees = (line.coefficients.a * this->coefficients.a + line.coefficients.b * this->coefficients.b) /
                        (sqrt(pow(line.coefficients.a, 2) + pow(line.coefficients.b, 2)) *
                         sqrt(pow(this->coefficients.a, 2) + pow(this->coefficients.b, 2)));

        return angle;
    }

    // method that checks if point belongs to line
    bool isPointBelong(Point &point)
    {
        return (this->coefficients.a * point.x + this->coefficients.b * point.y + this->coefficients.c == 0);
    }

    // method that checks if two lines are parallel
    bool isParallel(Line &line)
    {
        return (this->coefficients.a * line.coefficients.b == this->coefficients.b * line.coefficients.a);
    }
};

void listIntersectingLines(Line lines[]);
void listParallelToX(Line lines[]);
void listIntersectingAtRightAngles(Line lines[]);

int main()
{
    // get 10 lines
    Line lines[10];
    for (int i = 0; i < 10; i++)
    {
        cout << "Enter line #" << i + 1 << ":" << endl;
        cin >> lines[i];

        cout << "\n----------------------------------------\n"
             << endl;
    }

    // output results
    listIntersectingLines(lines);
    listParallelToX(lines);
    cout << endl;
    listIntersectingAtRightAngles(lines);

    return 0;
}

// function that list lines that intersect with each line and coordinates of intersection points
void listIntersectingLines(Line lines[])
{
    int size = 10;
    for (int i = 0; i < size; i++)
    {
        cout << "Line #" << i + 1 << " intersects with:" << endl;
        bool isIntersecting = false;

        for (int j = 0; j < size; j++)
        {
            if (i != j)
            {
                if (!lines[i].isParallel(lines[j]))
                {
                    isIntersecting = true;
                    cout << "- Line #" << j + 1 << " at point (" << lines[i].getIntersection(lines[j]).x << ", " << lines[i].getIntersection(lines[j]).y << ")" << endl;
                }
            }
        }

        if (!isIntersecting)
        {
            cout << "- No lines" << endl;
        }

        cout << endl;
    }
}

// function that list lines that are parallel to the X axis
void listParallelToX(Line lines[])
{
    int size = 10;

    Coefficients xAxisCoefficients;
    xAxisCoefficients.a = 0;
    xAxisCoefficients.b = 1;
    xAxisCoefficients.c = 0;

    Line xAxis = Line(xAxisCoefficients);

    for (int i = 0; i < size; i++)
    {
        if (lines[i].isParallel(xAxis))
        {
            cout << "Line #" << i + 1 << " is parallel to the X axis" << endl;
        }
        else
        {
            cout << "Line #" << i + 1 << " is not parallel to the X axis" << endl;
        }
    }
}

// function that list lines that intersect with the X axis at right angles
void listIntersectingAtRightAngles(Line lines[])
{
    int size = 10;

    Coefficients xAxisCoefficients;
    xAxisCoefficients.a = 0;
    xAxisCoefficients.b = 1;
    xAxisCoefficients.c = 0;

    Line xAxis = Line(xAxisCoefficients);

    for (int i = 0; i < size; i++)
    {
        if (lines[i].getAngle(xAxis).degrees == 90 || lines[i].getAngle(xAxis).degrees == -90 || lines[i].getAngle(xAxis).degrees == 270 || lines[i].getAngle(xAxis).degrees == -270)
        {
            cout << "Line #" << i + 1 << " intersects with the X axis at right angles" << endl;
        }
        else
        {
            cout << "Line #" << i + 1 << " does not intersect with the X axis at right angles" << endl;
        }
    }
}