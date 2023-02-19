#include <iostream>
using namespace std;

int *bubbleSort(int *array, int n);

int main()
{
    // prompt user for number of elements in array
    int n;
    cout << "Enter number of elements in array: " << endl;
    cout << "-> ";
    cin >> n;
    cout << endl;

    cout << "----------------\n\n";

    // prompt user for array elements
    int *unsortedArray = new int[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter element " << i + 1 << ": " << endl;
        cout << "-> ";
        cin >> unsortedArray[i];
        cout << endl;
    }

    cout << "----------------\n";

    // bubble sort array
    int *sortedArray = bubbleSort(unsortedArray, n);

    // print unsorted array
    cout << endl
         << "Unsorted array:    ";
    for (int i = 0; i < n; i++)
    {
        cout << unsortedArray[i] << " ";
    }

    // print sorted array
    cout << endl
         << "Sorted array:      ";
    for (int i = 0; i < n; i++)
    {
        cout << sortedArray[i] << " ";
    }

    return 0;
}

// function that bubble sorts the array
int *bubbleSort(int *array, int n)
{
    // create a new array to store sorted array
    int *sortedArray = new int[n];

    // copy array into sortedArray
    for (int i = 0; i < n; i++)
    {
        sortedArray[i] = array[i];
    }

    // bubble sort sortedArray
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (sortedArray[j] > sortedArray[j + 1])
            {
                int temp = sortedArray[j];
                sortedArray[j] = sortedArray[j + 1];
                sortedArray[j + 1] = temp;
            }
        }
    }

    return sortedArray;
}
