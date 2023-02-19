#include <iostream>
using namespace std;

int main()
{
    // prompt user for number of elements in first array
    cout << "Enter the number of elements in first array: ";
    int n1;
    cin >> n1;
    cout << "---" << endl;

    // initialize first array
    int *a = new int[n1];
    for (int i = 0; i < n1; i++)
    {
        cout << "Enter the element " << i + 1 << " of the first array: ";
        cin >> a[i];
    }

    cout << endl;

    // prompt user for number of elements in second array
    cout << "Enter the number of elements in second array: ";
    int n2;
    cin >> n2;
    cout << "---" << endl;

    // initialize second array
    int *b = new int[n2];
    for (int i = 0; i < n2; i++)
    {
        cout << "Enter the element " << i + 1 << " of the second array: ";
        cin >> b[i];
    }

    // merge two arrays
    int *c = new int[n1 + n2];
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2)
    {
        if (a[i] < b[j])
        {
            c[k] = a[i];
            i++;
        }
        else
        {
            c[k] = b[j];
            j++;
        }
        k++;
    }

    // copy the remaining elements of a, if there are any
    while (i < n1)
    {
        c[k] = a[i];
        i++;
        k++;
    }

    // copy the remaining elements of b, if there are any
    while (j < n2)
    {
        c[k] = b[j];
        j++;
        k++;
    }

    // output the result
    cout << endl;
    cout << "Merged array: ";
    for (int i = 0; i < n1 + n2; i++)
    {
        cout << c[i] << " ";
    }

    return 0;
}
