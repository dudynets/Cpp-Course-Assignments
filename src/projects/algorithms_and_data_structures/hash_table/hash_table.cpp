#define DOCTEST_CONFIG_IMPLEMENT

#include <vector>
#include <exception>
#include <doctest/doctest.h>

using namespace std;

// This class is a custom exception that is thrown when a key is not found in the hash table.
class KeyNotFoundException : public exception {
 public:
  KeyNotFoundException() = default;

  [[nodiscard]] const char *what() const noexcept override {
    return "KeyNotFoundException: key not found";
  }
};

// This class is a custom implementation of a hash table data structure.
class HashTable {
 private:
  // Create a vector of vectors (buckets) of pairs, where each pair contains an int and a string.
  vector<vector<pair<int, string>>> data;
  int numberOfBuckets = 0;

 public:
  // Constructor
  explicit HashTable(int _numberOfBuckets) : numberOfBuckets(_numberOfBuckets) {
    // Resize the data vector to the number of buckets
    data.resize(numberOfBuckets);
  }

  // This function sets the value of the key in the hash table to the value passed in.
  // If the key doesn't exist, it is added to the hash table.
  void set(const int &key, const string &value) {
    // Get the hash of the key
    int hash = getHash(key);

    // Loop through the data vector
    for (auto &i : data[hash]) {
      // If we find the bucket with hash we're looking for
      if (i.first == key) {
        // Set the value
        i.second = value;
        // If we didn't find the bucket with hash, we need to add a new pair
        return;
      }
    }
    // Add a new pair to the bucket
    data[hash].emplace_back(key, value);
  }

  // Delete an element from the hash table by its key.
  // The code loops through all the elements of the bucket, and if it finds the element we're looking for, it erases it.
  void deleteByKey(const int &key) {
    // Get the hash of the key
    int hash = getHash(key);

    // Loop through all the elements in the bucket.
    for (auto i = data[hash].begin(); i != data[hash].end(); i++) {
      // If we find the element we're looking for, erase it and return.
      if (i->first == key) {
        data[hash].erase(i);
        return;
      }
    }

    // If we didn't find the element, throw an error.
    throw KeyNotFoundException();
  }

  // Return a value associated with the given key.
  // If the key does not exist, throw an error.
  string get(const int &key) {
    // Get the hash of the key
    int hash = getHash(key);

    // Iterate through the bucket
    for (auto &i : data[hash]) {
      // Check if the key is equal to the key of the current item
      if (i.first == key) {
        // Return the value
        return i.second;
      }
    }
    // Throw an error if the key is not found
    throw KeyNotFoundException();
  }

  // Function that returns the hash of the key.
  [[nodiscard]] int getHash(const int &key) const {
    return key % numberOfBuckets;
  }
};

int main() {
  // Run tests
  doctest::Context context;
  int res = context.run();
  return res;
}

TEST_CASE("Setting and getting values in a hash table") {
  HashTable hashTable(16);

  hashTable.set(1, "apple");
  hashTable.set(2, "banana");
  hashTable.set(3, "orange");
  CHECK(hashTable.get(1) == "apple");
  CHECK(hashTable.get(2) == "banana");
  CHECK(hashTable.get(3) == "orange");

  hashTable.set(4, "pear");
  CHECK(hashTable.get(4) == "pear");

  hashTable.set(16, "grape");
  hashTable.set(32, "strawberry");
  CHECK(hashTable.get(16) == "grape");
  CHECK(hashTable.get(32) == "strawberry");
}

TEST_CASE("Setting and getting values in a hash table with same key") {
  HashTable hashTable(16);

  hashTable.set(1, "apple");
  hashTable.set(2, "banana");
  hashTable.set(3, "orange");
  CHECK(hashTable.get(1) == "apple");
  CHECK(hashTable.get(2) == "banana");
  CHECK(hashTable.get(3) == "orange");

  hashTable.set(1, "pear");
  CHECK(hashTable.get(1) == "pear");
}

TEST_CASE("Delete existing item") {
  HashTable hashTable(16);

  hashTable.set(1, "apple");
  hashTable.set(2, "banana");
  hashTable.set(3, "orange");
  CHECK_EQ(hashTable.get(1), "apple");
  CHECK_EQ(hashTable.get(2), "banana");
  CHECK_EQ(hashTable.get(3), "orange");

  hashTable.deleteByKey(2);
  CHECK_EQ(hashTable.get(1), "apple");
  CHECK_THROWS(hashTable.get(2));
  CHECK_EQ(hashTable.get(3), "orange");
}

TEST_CASE("Delete non-existent item") {
  HashTable hashTable(16);

  hashTable.set(1, "apple");
  CHECK_THROWS(hashTable.deleteByKey(2));
}
