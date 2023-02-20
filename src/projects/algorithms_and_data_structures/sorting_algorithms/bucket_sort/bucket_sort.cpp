#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include <doctest/doctest.h>

using namespace std;

// Function that gets the maximum value in an array of integers
// Input:
//   - array: pointer to the array of integers
//   - numberOfElements: number of elements in the array
// Output:
//   - maximum value in the array
int getMaxValue(const int *array, int numberOfElements) {
    int maxVal = array[0];
    for (int i = 1; i < numberOfElements; i++) {
        if (array[i] > maxVal) {
            maxVal = array[i];
        }
    }
    return maxVal;
}

// Function that gets the minimum value in an array of integers
// Input:
//   - array: pointer to the array of integers
//   - numberOfElements: number of elements in the array
// Output:
//   - minimum value in the array
int getMinValue(const int *array, int numberOfElements) {
    int minVal = array[0];
    for (int i = 1; i < numberOfElements; i++) {
        if (array[i] < minVal) {
            minVal = array[i];
        }
    }
    return minVal;
}

// Function that creates an array of buckets and initializes them to 0
// Input:
//   - range: range of values in the array
// Output:
//   - pointer to the array of buckets
int* createBuckets(int range) {
    int *buckets = new int[range];
    for (int i = 0; i < range; i++) {
        buckets[i] = 0;
    }
    return buckets;
}

// Function that distributes the elements in the array into the buckets
// Input:
//   - array: pointer to the array of integers
//   - numberOfElements: number of elements in the array
//   - buckets: pointer to the array of buckets
//   - minValue: minimum value in the array
// Output:
//   - none
void distributeElements(const int *array, int numberOfElements, int *buckets, int minValue) {
    for (int i = 0; i < numberOfElements; i++) {
        buckets[array[i] - minValue]++;
    }
}

// Function that sorts an array of integers in ascending order using the bucket sort algorithm
// Input:
//   - array: pointer to the array of integers
//   - numberOfElements: number of elements in the array
// Output:
//   - pointer to the sorted array
int* bucketSort(const int *array, int numberOfElements) {
    // Create a new array to store sorted elements
    int *sortedArray = new int[numberOfElements];

    // Copy array into sortedArray
    for (int i = 0; i < numberOfElements; i++) {
        sortedArray[i] = array[i];
    }

    // Find minimum and maximum values in the array
    int minValue = getMinValue(sortedArray, numberOfElements);
    int maxValue = getMaxValue(sortedArray, numberOfElements);

    // Calculate the range of values
    int range = maxValue - minValue + 1;

    // Create an array of buckets
    int *buckets = createBuckets(range);

    // Place each element in the appropriate bucket
    distributeElements(sortedArray, numberOfElements, buckets, minValue);

    // Update the array with the sorted elements
    int index = 0;
    for (int i = 0; i < range; i++) {
        for (int j = 0; j < buckets[i]; j++) {
            sortedArray[index++] = i + minValue;
        }
    }

    // Free the memory used by the buckets array
    delete [] buckets;

    // Return the sorted array
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
TEST_CASE("Sorting an array of integers with one element using bucket sort")
{
    int array[] = {1};
    int *sortedArray = bucketSort(array, 1);
    CHECK(sortedArray != nullptr);
    CHECK(sortedArray[0] == 1);
    delete[] sortedArray;
}

TEST_CASE("Sorting an array of integers with multiple elements using bucket sort")
{
    int array[] = {4, 1, 3, 2, 5};
    int *sortedArray = bucketSort(array, 5);
    CHECK(sortedArray != nullptr);
    CHECK(sortedArray[0] == 1);
    CHECK(sortedArray[1] == 2);
    CHECK(sortedArray[2] == 3);
    CHECK(sortedArray[3] == 4);
    CHECK(sortedArray[4] == 5);
    delete[] sortedArray;
}

TEST_CASE("Sorting a previously sorted array of integers using bucket sort")
{
    int array[] = {1, 2, 3, 4, 5};
    int *sortedArray = bucketSort(array, 5);
    CHECK(sortedArray != nullptr);
    CHECK(sortedArray[0] == 1);
    CHECK(sortedArray[1] == 2);
    CHECK(sortedArray[2] == 3);
    CHECK(sortedArray[3] == 4);
    CHECK(sortedArray[4] == 5);
    delete[] sortedArray;
}

TEST_CASE("Sorting an array of integers with negative numbers using bucket sort")
{
    int array[] = {-4, -5, -3, -2, 1, 4, -1, 2, 3, 0};
    int *sortedArray = bucketSort(array, 10);
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
