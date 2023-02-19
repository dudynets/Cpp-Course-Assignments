#include <iostream>
#include <math.h>
using namespace std;

// core functions
int promptForNumberOfSegments();
int *promptForSegments(int numberOfSegments);
int **getCombinations(int segments[], int numberOfSegments);
void outputAreas(int **combinations, int numberOfSegments);

// helper functions
bool isTriangle(int combination[3]);
double getTriangleArea(int combination[3]);
int getNumberOfCombinations(int numberOfSegments);
void printDivider();

int main()
{
    // prompt for number of segments
    int numberOfSegments = promptForNumberOfSegments();

    // prompt user for segments
    int *segments = promptForSegments(numberOfSegments);

    // get all possible combinations of 3 segments
    int **combinations = getCombinations(segments, numberOfSegments);

    // print the divider
    printDivider();

    // output the areas of all valid triangles
    outputAreas(combinations, numberOfSegments);

    return 0;
}

// function that prompts user for number of segments
int promptForNumberOfSegments()
{
    int numberOfSegments;
    cout << "Enter the number of segments: ";
    cin >> numberOfSegments;

    if (numberOfSegments < 3)
    {
        cout << endl
             << "The number of segments must be at least 3. Quiting..." << endl;
        exit(1);
    }

    return numberOfSegments;
}

// function that prompts user for segments and returns a dynamic array of it
int *promptForSegments(int numberOfSegments)
{
    // initialize dynamic array of segments
    int *segments = new int[numberOfSegments];

    // prompt for segments
    for (int i = 0; i < numberOfSegments; i++)
    {
        cout << "Enter segment \"" << char('a' + i) << "\" (in cm): ";
        cin >> segments[i];
        cout << endl;

        if (segments[i] <= 0)
        {
            cout << "The length of a segment must be a number greater than 0. Quiting..." << endl;
            exit(1);
        }
    }

    return segments;
}

// function that returns all posible combinations of 3 segments
int **getCombinations(int segments[], int numberOfSegments)
{
    // calculate the number of possible combinations
    int numberOfCombinations = getNumberOfCombinations(numberOfSegments);

    // create an dynamic array of combinations for triangles
    int **combinations = new int *[numberOfCombinations];
    int d = 0;
    for (int i = 0; i < numberOfSegments; i++)
    {
        for (int j = i + 1; j < numberOfSegments; j++)
        {
            for (int k = j + 1; k < numberOfSegments; k++)
            {
                combinations[d] = new int[3];
                combinations[d][0] = segments[i];
                combinations[d][1] = segments[j];
                combinations[d][2] = segments[k];
                d++;
            }
        }
    }

    return combinations;
}

void outputAreas(int **combinations, int numberOfSegments)
{
    // set output precision
    cout.precision(3);
    cout.setf(ios::fixed);

    // calculate the number of possible combinations
    int numberOfCombinations = getNumberOfCombinations(numberOfSegments);

    // loop through combinations and if it is a triangle, print the area
    for (int i = 0; i < numberOfCombinations; i++)
    {
        if (isTriangle(combinations[i]))
        {
            cout << "Valid triangle: " << combinations[i][0] << " cm, " << combinations[i][1] << " cm, " << combinations[i][2] << " cm" << endl;
            cout << "Area: " << getTriangleArea(combinations[i]) << " cm\u00B2" << endl;
            cout << endl;
        }
        else
        {
            cout << "Invalid triangle: " << combinations[i][0] << " cm, " << combinations[i][1] << " cm, " << combinations[i][2] << " cm" << endl;
            cout << endl;
        }
    }
}

// function that checks if the triangle is valid
bool isTriangle(int combination[3])
{
    if (combination[0] + combination[1] > combination[2] && combination[0] + combination[2] > combination[1] && combination[1] + combination[2] > combination[0])
    {
        return true;
    }
    else
    {
        return false;
    }
}

// function that calculates the area of the triangle
double getTriangleArea(int combination[3])
{
    double p = (combination[0] + combination[1] + combination[2]) / 2.0;
    double area = sqrt(p * (p - combination[0]) * (p - combination[1]) * (p - combination[2]));

    return area;
}

int getNumberOfCombinations(int numberOfSegments)
{
    int numberOfCombinations = numberOfSegments * (numberOfSegments - 1) * (numberOfSegments - 2) / 6;
    return numberOfCombinations;
}

// function that prints the divider
void printDivider()
{
    cout << "----------------------------------------" << endl;
    cout << endl;
}
