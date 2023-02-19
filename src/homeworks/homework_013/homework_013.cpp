#include <iostream>
using namespace std;

int getRowSum(int **matrix, int row, int columns);
int **sortRows(int **matrix, int rows, int columns);

int main()
{
    // prompt user for number of rows and columns
    int rows, columns;
    cout << "Enter number of rows: " << endl;
    cout << "-> ";
    cin >> rows;
    cout << endl;

    cout << "Enter number of columns: " << endl;
    cout << "-> ";
    cin >> columns;
    cout << endl;

    cout << "----------------\n\n";

    // initialize 2D matrix array
    int **unsortedMatrix = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        unsortedMatrix[i] = new int[columns];
    }

    // prompt user for matrix elements
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << "Enter element [" << i << "][" << j << "]: " << endl;
            cout << "-> ";
            cin >> unsortedMatrix[i][j];
            cout << endl;
        }
    }

    cout << "----------------\n";

    // bubble sort matrix rows
    int **sortedMatrix = sortRows(unsortedMatrix, rows, columns);

    // print unsorted matrix
    cout << endl
         << "Unsorted matrix: " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << unsortedMatrix[i][j] << "  ";
        }
        cout << endl;
    }

    // print sorted matrix
    cout << endl
         << "Sorted matrix: " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << sortedMatrix[i][j] << "  ";
        }
        cout << endl;
    }

    return 0;
}

// function that gets the sum of elements in a matrix row
int getRowSum(int **matrix, int row, int columns)
{
    int sum = 0;
    for (int i = 0; i < columns; i++)
    {
        sum += matrix[row][i];
    }
    return sum;
}

// function that sorts the matrix rows by row sum descendingly
int **sortRows(int **matrix, int rows, int columns)
{
    // create a new matrix to store sorted matrix
    int **sortedMatrix = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        sortedMatrix[i] = new int[columns];
    }

    // copy matrix into sortedMatrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            sortedMatrix[i][j] = matrix[i][j];
        }
    }

    // sort rows by row sum descendingly
    for (int i = 0; i < rows; i++)
    {
        for (int j = i + 1; j < rows; j++)
        {
            if (getRowSum(sortedMatrix, i, columns) < getRowSum(sortedMatrix, j, columns))
            {
                int *temp = sortedMatrix[i];
                sortedMatrix[i] = sortedMatrix[j];
                sortedMatrix[j] = temp;
            }
        }
    }

    return sortedMatrix;
}
