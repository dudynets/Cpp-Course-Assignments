#include <iostream>
#include <string>
using namespace std;

string getSpaces(int number);

int main()
{
    // initialize matrix dimensions variables
    int n, m;

    // prompt user for matrix dimensions
    cout << "Enter the number of rows: " << endl;
    cout << "--> ";
    cin >> n;
    cout << endl;

    cout << "Enter the number of columns: " << endl;
    cout << "--> ";
    cin >> m;

    cout << endl
         << "-------------------------------------" << endl;

    // get the matrix from the user
    int matrix[30][30];
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            cout << endl
                 << "Enter the element at position (" << row + 1 << ", " << col + 1 << "): " << endl;
            cout << "--> ";
            cin >> matrix[row][col];
        }
        cout << endl
             << "------------------" << endl;
        cout << "Row " << row + 1 << " is finished." << endl;
        cout << "------------------" << endl;
    }

    cout << endl
         << "--------" << endl;
    cout << "RESULTS:" << endl;
    cout << "--------" << endl;

    cout << endl
         << "-------------------------------------" << endl;

    // print the matrix
    cout << endl
         << "MATRIX:"
         << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << getSpaces(matrix[i][j]) << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl
         << "-------------------------------------";

    // print all columns with uneven numbers
    cout << endl
         << endl
         << "COLUMNS WITH UNEVEN NUMBERS:"
         << endl;

    bool hasResult = false;
    for (int col = 0; col < m; col++)
    {
        bool hasUneven = true;
        for (int row = 0; row < n; row++)
        {
            if (matrix[row][col] % 2 == 0)
            {
                hasUneven = false;
                break;
            }
        }

        if (hasUneven)
        {
            hasResult = true;
            cout << endl;
            cout << "- Column " << col + 1 << ": " << endl;
            for (int row = 0; row < n; row++)
            {
                cout << getSpaces(matrix[row][col]) << matrix[row][col] << " " << endl;
            }
        }
    }

    if (!hasResult)
    {
        cout << endl
             << "- No columns with uneven numbers found." << endl;
    }

    cout << endl
         << "-------------------------------------" << endl;

    // print only diagonal elements
    cout << endl
         << "DIAGONAL ELEMENTS:"
         << endl;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            if (row == col || row + col == n - 1)
            {
                cout << getSpaces(matrix[row][col]) << matrix[row][col] << " ";
            }
            else
            {
                cout << getSpaces(matrix[row][col]);
                string numberString = to_string(matrix[row][col]);
                for (int i = 0; i < numberString.length(); i++)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    cout << endl
         << "-------------------------------------";

    // print only the smallest element in each row
    cout << endl
         << endl
         << "SMALLEST ELEMENT IN EACH ROW:"
         << endl;

    for (int row = 0; row < n; row++)
    {
        int smallest = matrix[row][0];
        for (int col = 1; col < m; col++)
        {
            if (matrix[row][col] < smallest)
            {
                smallest = matrix[row][col];
            }
        }

        for (int col = 0; col < m; col++)
        {
            if (matrix[row][col] == smallest)
            {
                cout << getSpaces(matrix[row][col]) << matrix[row][col] << " ";
            }
            else
            {
                cout << getSpaces(matrix[row][col]);
                string numberString = to_string(matrix[row][col]);
                for (int i = 0; i < numberString.length(); i++)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    cout << endl
         << "-------------------------------------";

    // print only the biggest element in each row
    cout << endl
         << endl
         << "BIGGEST ELEMENT IN EACH ROW:"
         << endl;

    for (int row = 0; row < n; row++)
    {
        int biggest = matrix[row][0];
        for (int col = 1; col < m; col++)
        {
            if (matrix[row][col] > biggest)
            {
                biggest = matrix[row][col];
            }
        }

        for (int col = 0; col < m; col++)
        {
            if (matrix[row][col] == biggest)
            {
                cout << getSpaces(matrix[row][col]) << matrix[row][col] << " ";
            }
            else
            {
                cout << getSpaces(matrix[row][col]);
                string numberString = to_string(matrix[row][col]);
                for (int i = 0; i < numberString.length(); i++)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    cout << endl
         << "-------------------------------------";

    // prompt user for k and l row numbers
    int k, l;
    cout << endl
         << endl
         << "Enter the first row index to swap: " << endl;
    cout << "--> ";
    cin >> k;

    cout << endl
         << "Enter the second row index to swap: " << endl;
    cout << "--> ";
    cin >> l;

    // check if k and l are valid
    bool isValid = k > 0 && k <= n && l > 0 && l <= n;
    if (isValid)
    {
        // copy the matrix
        int matrixCopy[30][30];
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < m; col++)
            {
                matrixCopy[row][col] = matrix[row][col];
            }
        }

        // swap the k and l rows
        for (int col = 0; col < m; col++)
        {
            int temp = matrixCopy[k - 1][col];
            matrixCopy[k - 1][col] = matrixCopy[l - 1][col];
            matrixCopy[l - 1][col] = temp;
        }

        // print the swapped matrix
        cout << endl
             << "MATRIX WITH SWAPPED ROWS:"
             << endl;

        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < m; col++)
            {
                cout << getSpaces(matrixCopy[row][col]) << matrixCopy[row][col] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << endl
             << "Invalid row indexes." << endl;
    }

    cout << endl
         << "-------------------------------------";

    // calculate number of columns where elements are descending
    int descendingColumns = 0;
    for (int col = 0; col < m; col++)
    {
        bool isDescending = true;
        for (int row = 1; row < n; row++)
        {
            if (matrix[row][col] >= matrix[row - 1][col])
            {
                isDescending = false;
                break;
            }
        }

        if (isDescending)
        {
            descendingColumns++;
        }
    }
    cout << endl
         << endl
         << "Number of columns where elements are descending: " << descendingColumns << endl;

    return 0;
}

// function that gets spaces for numbers
string getSpaces(int number)
{
    string numberString = to_string(number);
    string spaces = " ";
    for (int i = 0; i < 3 - numberString.length(); i++)
    {
        spaces += " ";
    }
    return spaces;
}
