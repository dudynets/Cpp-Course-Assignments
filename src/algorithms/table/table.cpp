#define DOCTEST_CONFIG_IMPLEMENT

#include <vector>
#include <exception>
#include "doctest/doctest.h"

using namespace std;

// This class is a custom exception that is thrown when a key is not found in the table.
class KeyNotFoundException : public exception {
 public:
  KeyNotFoundException() = default;

  [[nodiscard]] const char *what() const noexcept override {
    return "KeyNotFoundException: key not found";
  }
};

// This class is a custom implementation of a table data structure.
class Table {
 private:
  // Create a vector of pairs, where each pair contains an int and a string.
  vector<pair<int, string>> data;

 public:
  // This function sets the value of the key in the table to the value passed in.
  // If the key doesn't exist, it is added to the table.
  void set(const int &key, string value) {
    // Loop through the data vector
    for (auto &i : data) {
      // If we find the key we're looking for
      if (i.first == key) {
        // Set the value
        i.second = value;
        // If we didn't find the key, we need to add a new pair
        return;
      }
    }
    // Add a new pair to the vector
    data.emplace_back(key, value);
  }

  // Delete an element from the table by its key.
  // The code loops through all the elements in the vector, and if it finds the element we're looking for, it erases it.
  void deleteByKey(const int &key) {
    // Loop through all the elements in the vector.
    for (auto i = data.begin(); i != data.end(); i++) {
      // If we find the element we're looking for, erase it and return.
      if (i->first == key) {
        data.erase(i);
        return;
      }
    }

    // If we didn't find the element, throw an error.
    throw KeyNotFoundException();
  }

  // Return a value associated with the given key.
  // If the key does not exist, return -1.
  string get(const int &key) {
    // Iterate through the data vector
    for (auto &i : data) {
      // Check if the key is equal to the key of the current item
      if (i.first == key) {
        // Return the value
        return i.second;
      }
    }
    // Throw an error if the key is not found
    throw KeyNotFoundException();
  }
};

int main() {
  // Run tests
  doctest::Context context;
  int res = context.run();
  return res;
}

TEST_CASE("Setting and getting values in a table") {
  Table table;
  table.set(1, "apple");
  table.set(2, "banana");
  table.set(3, "orange");
  CHECK(table.get(1) == "apple");
  CHECK(table.get(2) == "banana");
  CHECK(table.get(3) == "orange");
  table.set(4, "pear");
  CHECK(table.get(4) == "pear");
}

TEST_CASE("Setting and getting values in a table with same key") {
  Table table;
  table.set(1, "apple");
  table.set(2, "banana");
  table.set(3, "orange");
  CHECK(table.get(1) == "apple");
  CHECK(table.get(2) == "banana");
  CHECK(table.get(3) == "orange");
  table.set(1, "pear");
  CHECK(table.get(1) == "pear");
}

TEST_CASE("Delete existing item") {
  Table table;
  table.set(1, "apple");
  table.set(2, "banana");
  table.set(3, "orange");
  CHECK_EQ(table.get(1), "apple");
  CHECK_EQ(table.get(2), "banana");
  CHECK_EQ(table.get(3), "orange");
  table.deleteByKey(2);
  CHECK_EQ(table.get(1), "apple");
  CHECK_THROWS(table.get(2));
  CHECK_EQ(table.get(3), "orange");
}

TEST_CASE("Delete non-existent item") {
  Table table;
  table.set(1, "apple");
  CHECK_THROWS(table.deleteByKey(2));
}
