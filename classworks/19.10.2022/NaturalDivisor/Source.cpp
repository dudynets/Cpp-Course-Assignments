#include <iostream>
using namespace std;

int main()
{
    // prompt user for a number
    int n;
    cout << "Please, enter your number" << endl;
    cout << "--> ";
    cin >> n;

    // output all natural divisors
    for (int i = 1; i <= n; i++) {
        if (n % i == 0)
        {
            cout << i << endl;
        }
    }

    return 0;
}
