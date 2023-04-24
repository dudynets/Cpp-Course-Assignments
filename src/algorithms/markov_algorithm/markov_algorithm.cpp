#define DOCTEST_CONFIG_IMPLEMENT

#include <map>
#include <string>
#include <utility>
#include "doctest/doctest.h"

using namespace std;

// Class that implements the Markov Algorithm
class MarkovAlgorithm {
 private:
  string input;
  map<string, string> rules;
  int maxIterations;
 public:
  // Constructor
  MarkovAlgorithm(string _input, const map<string, string> &_rules, int _maxIterations) :
      input(std::move(_input)), rules(_rules), maxIterations(_maxIterations) {}

  // Method that runs the algorithm
  [[nodiscard]] string run() const {
    // Define the output string and assign the input string to it
    string output = input;

    // Define a boolean variable that indicates if the output string has changed
    bool hasChanged = true;

    // Define an integer variable that counts the number of iterations
    int iterationIndex = 0;

    // While the output string has changed and the number of iterations is less than the maximum number of iterations
    while (hasChanged && iterationIndex < maxIterations) {
      // Set the changed variable to false
      hasChanged = false;

      // For each rule
      for (auto &rule : rules) {
        // Set the position to 0
        size_t position = 0;

        // While the rule is found in the output string
        while ((position = output.find(rule.first, position)) != string::npos) {
          // Replace the rule with the corresponding string
          output.replace(position, rule.first.length(), rule.second);

          // Update the position
          position += rule.second.length();

          // Set the changed variable to true
          hasChanged = true;
        }
      }
      // Update the number of iterations
      iterationIndex++;
    }

    // Return the output string
    return output;
  }
};

// Main function
int main() {

  // Run tests
  doctest::Context context;
  int res = context.run();
  return res;
}

// Tests
TEST_CASE("Use one rule") {
  string input = "a";
  map<string, string> rules = {{"a", "b"}};
  int maxIterations = 99999;
  MarkovAlgorithm ma(input, rules, maxIterations);
  CHECK(ma.run() == "b");
}

TEST_CASE("Use non-existent rule") {
  string input = "a";
  map<string, string> rules = {{"b", "c"}};
  int maxIterations = 99999;
  MarkovAlgorithm ma(input, rules, maxIterations);
  CHECK(ma.run() == "a");
}

TEST_CASE("Use recursive rules") {
  string input = "a";
  map<string, string> rules = {{"a", "b"}, {"b", "c"}, {"c", "a"}};
  int maxIterations = 99999;
  MarkovAlgorithm ma(input, rules, maxIterations);
  CHECK(ma.run() == "a");
}
