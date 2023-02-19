#include <iostream>
using namespace std;

int main()
{
    // get an array of numbers from user
    int n;
    cout << "Please, enter the number of elements in your array" << endl;
    cout << "--> ";
    cin >> n;
    cout << endl;

    int arr[9999];
    for (int i = 0; i < n; i++)
    {
        cout << "Please, enter the " << i + 1 << " element of your array" << endl;
        cout << "--> ";
        cin >> arr[i];
    }

    // check if the array is sorted
    bool isSorted = true;
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            isSorted = false;
            break;
        }
    }

    // output the result
    if (isSorted)
    {
        cout << endl << "The array is sorted" << endl;
    }
    else
    {
        cout << endl << "The array is not sorted" << endl;
    }

    return 0;
}
