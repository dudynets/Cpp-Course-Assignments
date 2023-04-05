#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

// Function to tabulate
ostringstream tabulate(double(*f)(double), double a, double b, int n) {
  // Initialize output stream
  ostringstream oss;

  // Calculate step
  double h = (b - a) / n;

  // Print table header
  oss << setw(9) << "x" << setw(16) << "y" << endl;
  oss << "----------------------------\n";

  // Print table body
  for (int i = 0; i <= n; i++) {
    oss << "|  " << setw(6) << a + i * h << "  | " << setw(12) << f(a + i * h) << "  |" << endl;
  }

  // Print table footer
  oss << "----------------------------\n\n";

  // Return output stream
  return oss;
}

double f(double x) {
//  return x ^ 3 + x ^ 2 + 8x + 9
  return pow(x, 3) + pow(x, 2) + 8 * x + 9;
}

// Main function
int main() {
  // Open file to write
  ofstream ofs("../src/classworks/30_03_2023/function_tabulation/output.txt");

  // Check if file is opens
  if (!ofs.is_open()) {
    cout << "Error opening file" << endl;
    return 1;
  }

  // Write to file
  ofs << "sin(x) from 0 to 1:\n";
  ofs << tabulate(sin, 0, 1, 10).str();

  ofs << "cos(x) from 0 to 1:\n";
  ofs << tabulate(cos, 0, 1, 10).str();

  ofs << "tan(x) from 0 to 1:\n";
  ofs << tabulate(tan, 0, 1, 10).str();

  ofs << "ctg(x) from 0 to 1:\n";
  ofs << tabulate([](double x) { return 1 / tan(x); }, 0, 1, 10).str();

  ofs << "exp(x) from 0 to 1:\n";
  ofs << tabulate(exp, 0, 1, 10).str();

  ofs << "x^3 + x^2 + 8x + 9 from 0 to 1:\n";
  ofs << tabulate(f, 0, 1, 10).str();

  ofs << "sin x + 8tan x - 24 x^2 from 0 to 1:\n";
  ofs << tabulate([](double x) { return sin(x) + 8 * tan(x) - 24 * pow(x, 2); }, 0, 1, 10).str();

  // Close file
  ofs.close();

  return 0;
}
