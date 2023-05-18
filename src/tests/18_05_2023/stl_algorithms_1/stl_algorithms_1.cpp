#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>

using namespace std;

// Function that splits a string into tokens
vector<string> split(const string &line, const string &delimiter) {
  vector<string> tokens;
  size_t start = 0, end = 0;

  while ((end = line.find(delimiter, start)) != string::npos) {
    tokens.push_back(line.substr(start, end - start));
    start = end + delimiter.length();
  }

  tokens.push_back(line.substr(start));

  vector<string> result(tokens.size());
  copy(tokens.begin(), tokens.end(), result.begin());

  return result;
}

// Function that gets the dot product of two vectors
int getDotProduct(const vector<int> &vector1, const vector<int> &vector2) {
  if (vector1.size() != vector2.size()) {
    return -1;
  }

  // Create a temporary vector to hold the products of corresponding elements
  vector<int> temp(vector1.size());
  transform(vector1.begin(), vector1.end(), vector2.begin(), temp.begin(), multiplies<>());

  // Compute the sum of the products
  int sum = accumulate(temp.begin(), temp.end(), 0);

  return sum;
}

// Function that parses a file and returns two vectors
pair<vector<int>, vector<int>> parseFile(const string &inputFilePath) {
  vector<int> vector1;
  vector<int> vector2;

  ifstream inputFile(inputFilePath);

  if (!inputFile.is_open()) {
    throw runtime_error("File not found");
  }

  string line;
  int lineNumber = 0;
  while (getline(inputFile, line) && lineNumber < 2) {
    vector<string> parts = split(line, " ");

    for (auto &part : parts) {
      int number = stoi(part);

      switch (lineNumber) {
        case 0:vector1.push_back(number);
          break;
        case 1:vector2.push_back(number);
          break;
        default:break;
      }
    }

    lineNumber++;
  }

  inputFile.close();

  return make_pair(vector1, vector2);
}

// Main function
int main() {
  pair<vector<int>, vector<int>> vectors = parseFile("../src/tests/18_05_2023/stl_algorithms_1/input.txt");
  vector<int> vector1 = vectors.first;
  vector<int> vector2 = vectors.second;

  int dotProduct = getDotProduct(vector1, vector2);

  vector<int> *maxVector = &vector1;
  if (*max_element(vector2.begin(), vector2.end()) > *max_element(vector1.begin(), vector1.end())) {
    maxVector = &vector2;
  }
  reverse(maxVector->begin(), maxVector->end());

  cout << "Vector 1: ";
  for (auto &i : vector1) {
    cout << i << " ";
  }

  cout << "\n";

  cout << "Vector 2: ";
  for (auto &i : vector2) {
    cout << i << " ";
  }

  cout << "\n";

  cout << "Dot product: " << dotProduct << "\n";

  cout << "Reversed vector with max element: ";
  for (auto &i : *maxVector) {
    cout << i << " ";
  }

  return 0;
}
