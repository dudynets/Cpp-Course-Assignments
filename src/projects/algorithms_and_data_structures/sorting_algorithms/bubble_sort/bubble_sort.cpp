#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include <doctest/doctest.h>

using namespace std;

// Function that sorts an array of integers in ascending order using the bubble sort algorithm
// Input:
//   - array: pointer to the array of integers
//   - numberOfElements: number of elements in the array
// Output:
//   - pointer to the sorted array
int *bubbleSort(const int *array, int numberOfElements)
{
    // Create a new array to store sorted elements
    int *sortedArray = new int[numberOfElements];

    // Copy array into sortedArray
    for (int i = 0; i < numberOfElements; i++)
    {
        sortedArray[i] = array[i];
    }

    // Iterate through the all elements in the array
    for (int i = 0; i < numberOfElements - 1; i++)
    {
        // Iterate through the unsorted part of the array in each iteration
        for (int j = 0; j < numberOfElements - i - 1; j++)
        {
            // Check if elements are in the wrong order
            if (sortedArray[j] > sortedArray[j + 1])
            {
                // Swap elements
                int temp = sortedArray[j];
                sortedArray[j] = sortedArray[j + 1];
                sortedArray[j + 1] = temp;
            }
        }
    }

    // Return the sortedArray
    return sortedArray;
}

// Main function
int main()
{
    // Run tests
    doctest::Context context;
    int res = context.run();
    return res;
}

// Test cases
TEST_CASE("Sorting an array of integers with one element using bubble sort")
{
    int array[] = {1};
    int *sortedArray = bubbleSort(array, 1);
    CHECK(sortedArray != nullptr);
    CHECK(sortedArray[0] == 1);
    delete[] sortedArray;
}

TEST_CASE("Sorting an array of integers with multiple elements using bubble sort")
{
    int array[] = {4, 1, 3, 2, 5};
    int *sortedArray = bubbleSort(array, 5);
    CHECK(sortedArray != nullptr);
    CHECK(sortedArray[0] == 1);
    CHECK(sortedArray[1] == 2);
    CHECK(sortedArray[2] == 3);
    CHECK(sortedArray[3] == 4);
    CHECK(sortedArray[4] == 5);
    delete[] sortedArray;
}

TEST_CASE("Sorting a previously sorted array of integers using bubble sort")
{
    int array[] = {1, 2, 3, 4, 5};
    int *sortedArray = bubbleSort(array, 5);
    CHECK(sortedArray != nullptr);
    CHECK(sortedArray[0] == 1);
    CHECK(sortedArray[1] == 2);
    CHECK(sortedArray[2] == 3);
    CHECK(sortedArray[3] == 4);
    CHECK(sortedArray[4] == 5);
    delete[] sortedArray;
}

TEST_CASE("Sorting an array of integers with negative numbers using bubble sort")
{
    int array[] = {-4, -5, -3, -2, 1, 4, -1, 2, 3, 0};
    int *sortedArray = bubbleSort(array, 10);
    CHECK(sortedArray != nullptr);
    CHECK(sortedArray[0] == -5);
    CHECK(sortedArray[1] == -4);
    CHECK(sortedArray[2] == -3);
    CHECK(sortedArray[3] == -2);
    CHECK(sortedArray[4] == -1);
    CHECK(sortedArray[5] == 0);
    CHECK(sortedArray[6] == 1);
    CHECK(sortedArray[7] == 2);
    CHECK(sortedArray[8] == 3);
    CHECK(sortedArray[9] == 4);
    delete[] sortedArray;
}
