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

    // sort an array
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // find the smallest positive integer
    int smallestPositiveInteger = -1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > 0)
        {
            smallestPositiveInteger = arr[i];
            break;
        }
    }

    // output the result
    if (smallestPositiveInteger == -1)
    {
        cout << endl << "There is no positive integer in the array" << endl;
    } else
    {
        cout << endl << "The smallest positive integer is " << smallestPositiveInteger << endl;

    }

    return 0;
}
