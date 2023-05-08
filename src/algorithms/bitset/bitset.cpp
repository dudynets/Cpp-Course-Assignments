#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include "doctest/doctest.h"

using namespace std;

// Number of bits in an unsigned long long
const int BITS_PER_LONG = 8 * sizeof(unsigned long long);

// Class that implements a bitset with a fixed number of bits.
class Bitset {
 private:
  unsigned long long *bits;
  int size;

 public:
  // Constructor that creates a bitset with n bits
  explicit Bitset(int n) {
    // Define the number of unsigned long longs needed to store n bits
    size = (n + BITS_PER_LONG - 1) / BITS_PER_LONG;

    // Allocate the array of unsigned long longs
    bits = new unsigned long long[size];

    // Initialize all bits to 0
    for (int i = 0; i < size; i++) {
      bits[i] = 0;
    }
  }

  // Copy constructor
  Bitset(const Bitset &other) {
    // Copy the size
    size = other.size;

    // Allocate the array of unsigned long longs
    bits = new unsigned long long[size];

    // Copy the bits
    for (int i = 0; i < size; i++) {
      bits[i] = other.bits[i];
    }
  }

  // Destructor
  ~Bitset() {
    delete[] bits;
  }

  // Method that set the i-th bit to 1
  void set(int i) {
    // Compute the index of the unsigned long long that contains the i-th bit
    int index = i / BITS_PER_LONG;

    // Compute the offset of the i-th bit inside the unsigned long long
    int offset = i % BITS_PER_LONG;

    // Set the i-th bit to 1
    bits[index] |= (1ULL << offset);
  }

  // Method that set the i-th bit to 0
  void reset(int i) {
    // Compute the index of the unsigned long long that contains the i-th bit
    int index = i / BITS_PER_LONG;

    // Compute the offset of the i-th bit inside the unsigned long long
    int offset = i % BITS_PER_LONG;

    // Set the i-th bit to 0
    bits[index] &= ~(1ULL << offset);
  }

  // Method that returns the value of the i-th bit
  [[nodiscard]] bool test(int i) const {
    // Compute the index of the unsigned long long that contains the i-th bit
    int index = i / BITS_PER_LONG;

    // Compute the offset of the i-th bit inside the unsigned long long
    int offset = i % BITS_PER_LONG;

    // Return the value of the i-th bit
    return (bits[index] & (1ULL << offset)) != 0;
  }

  // Method that returns the number of bits set to 1
  [[nodiscard]] int count() const {
    // Initialize the result
    int result = 0;

    // Count the number of bits set to 1
    for (int i = 0; i < size; i++) {
      result += __builtin_popcountll(bits[i]);
    }

    // Return the result
    return result;
  }

  // Overload of the operator &
  Bitset operator&(const Bitset &other) const {
    // Create a new bitset
    Bitset result(size * BITS_PER_LONG);

    // Compute the bitwise AND between the two bitsets
    for (int i = 0; i < size; i++) {
      result.bits[i] = bits[i] & other.bits[i];
    }

    // Return the result
    return result;
  }

  // Overload of the operator &=
  Bitset &operator&=(const Bitset &other) {
    // Compute the bitwise AND between the two bitsets
    for (int i = 0; i < size; i++) {
      bits[i] &= other.bits[i];
    }

    // Return the result
    return *this;
  }

  // Overload of the operator |
  Bitset operator|(const Bitset &other) const {
    // Create a new bitset
    Bitset result(size * BITS_PER_LONG);

    // Compute the bitwise OR between the two bitsets
    for (int i = 0; i < size; i++) {
      result.bits[i] = bits[i] | other.bits[i];
    }

    // Return the result
    return result;
  }

  // Overload of the operator |=
  Bitset &operator|=(const Bitset &other) {
    // Compute the bitwise OR between the two bitsets
    for (int i = 0; i < size; i++) {
      bits[i] |= other.bits[i];
    }

    // Return the result
    return *this;
  }

  // Overload of the operator ^
  Bitset operator^(const Bitset &other) const {
    // Create a new bitset
    Bitset result(size * BITS_PER_LONG);

    // Compute the bitwise XOR between the two bitsets
    for (int i = 0; i < size; i++) {
      result.bits[i] = bits[i] ^ other.bits[i];
    }

    // Return the result
    return result;
  }

  // Overload of the operator ^=
  Bitset &operator^=(const Bitset &other) {
    // Compute the bitwise XOR between the two bitsets
    for (int i = 0; i < size; i++) {
      bits[i] ^= other.bits[i];
    }

    // Return the result
    return *this;
  }

  // Overload of the operator ~
  Bitset operator~() const {
    // Create a new bitset
    Bitset result(size * BITS_PER_LONG);

    // Compute the bitwise NOT of the bitset
    for (int i = 0; i < size; i++) {
      result.bits[i] = ~bits[i];
    }

    // Return the result
    return result;
  }

  // Overload of the operator ~=
  Bitset &operator~() {
    // Compute the bitwise NOT of the bitset
    for (int i = 0; i < size; i++) {
      bits[i] = ~bits[i];
    }

    // Return the result
    return *this;
  }

  // Overload of the operator ==
  bool operator==(const Bitset &other) const {
    // Check if the two bitsets have the same size
    if (size != other.size) {
      return false;
    }

    // Check if the two bitsets have the same bits
    for (int i = 0; i < size; i++) {
      // Check if the i-th unsigned long long is equal
      if (bits[i] != other.bits[i]) {
        // The two bitsets are different
        return false;
      }
    }

    // The two bitsets are equal
    return true;
  }

  // Overload of the operator !=
  bool operator!=(const Bitset &other) const {
    // Check if the two bitsets are different
    return !(*this == other);
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
TEST_CASE("Default constructor creates a bitset with all bits set to zero") {
  Bitset bitset(16);
  for (int i = 0; i < 16; i++) {
    CHECK(bitset.test(i) == false);
  }
}

TEST_CASE("Setting and resetting individual bits") {
  Bitset bitset(16);
  bitset.set(1);
  bitset.set(3);
  bitset.set(6);

  CHECK(bitset.test(0) == false);
  CHECK(bitset.test(1) == true);
  CHECK(bitset.test(2) == false);
  CHECK(bitset.test(3) == true);
  CHECK(bitset.test(4) == false);
  CHECK(bitset.test(5) == false);
  CHECK(bitset.test(6) == true);
  CHECK(bitset.test(7) == false);

  bitset.reset(3);
  CHECK(bitset.test(3) == false);

  bitset.reset(6);
  CHECK(bitset.test(6) == false);

  bitset.set(6);
  CHECK(bitset.test(6) == true);

  bitset.reset(1);
  CHECK(bitset.test(1) == false);

  bitset.set(1);
  CHECK(bitset.test(1) == true);
}

TEST_CASE("Bitwise AND operator") {
  Bitset bitset1(16);
  bitset1.set(1);
  bitset1.set(3);
  bitset1.set(6);

  Bitset bitset2(16);
  bitset2.set(1);
  bitset2.set(2);
  bitset2.set(3);
  bitset2.set(4);
  bitset2.set(6);

  Bitset bitset3 = bitset1 & bitset2;

  CHECK(bitset3.test(0) == false);
  CHECK(bitset3.test(1) == true);
  CHECK(bitset3.test(2) == false);
  CHECK(bitset3.test(3) == true);
  CHECK(bitset3.test(4) == false);
  CHECK(bitset3.test(5) == false);
  CHECK(bitset3.test(6) == true);
  CHECK(bitset3.test(7) == false);
}

TEST_CASE("Bitwise OR operator") {
  Bitset bitset1(16);
  bitset1.set(1);
  bitset1.set(3);
  bitset1.set(6);

  Bitset bitset2(16);
  bitset2.set(1);
  bitset2.set(2);
  bitset2.set(3);
  bitset2.set(4);
  bitset2.set(6);

  Bitset bitset3 = bitset1 | bitset2;

  CHECK(bitset3.test(0) == false);
  CHECK(bitset3.test(1) == true);
  CHECK(bitset3.test(2) == true);
  CHECK(bitset3.test(3) == true);
  CHECK(bitset3.test(4) == true);
  CHECK(bitset3.test(5) == false);
  CHECK(bitset3.test(6) == true);
  CHECK(bitset3.test(7) == false);
}

TEST_CASE("Bitwise XOR operator") {
  Bitset bitset1(16);
  bitset1.set(1);
  bitset1.set(3);
  bitset1.set(6);

  Bitset bitset2(16);
  bitset2.set(1);
  bitset2.set(2);
  bitset2.set(3);
  bitset2.set(4);
  bitset2.set(6);

  Bitset bitset3 = bitset1 ^ bitset2;

  CHECK(bitset3.test(0) == false);
  CHECK(bitset3.test(1) == false);
  CHECK(bitset3.test(2) == true);
  CHECK(bitset3.test(3) == false);
  CHECK(bitset3.test(4) == true);
  CHECK(bitset3.test(5) == false);
  CHECK(bitset3.test(6) == false);
  CHECK(bitset3.test(7) == false);
}

TEST_CASE("Bitwise NOT operator") {
  Bitset bitset1(16);
  bitset1.set(1);
  bitset1.set(3);
  bitset1.set(6);

  Bitset bitset2 = ~bitset1;

  CHECK(bitset2.test(0) == true);
  CHECK(bitset2.test(1) == false);
  CHECK(bitset2.test(2) == true);
  CHECK(bitset2.test(3) == false);
  CHECK(bitset2.test(4) == true);
  CHECK(bitset2.test(5) == true);
  CHECK(bitset2.test(6) == false);
  CHECK(bitset2.test(7) == true);
}

TEST_CASE("Equality and inequality operators") {
  Bitset bitset1(16);
  bitset1.set(1);
  bitset1.set(3);
  bitset1.set(6);

  Bitset bitset2(16);
  bitset2.set(1);
  bitset2.set(3);
  bitset2.set(6);

  Bitset bitset3(16);
  bitset3.set(1);
  bitset3.set(3);
  bitset3.set(6);
  bitset3.set(7);

  CHECK(bitset1 == bitset2);
  CHECK(bitset1 != bitset3);
  CHECK(bitset2 != bitset3);
}

TEST_CASE("Bitwise AND assignment operator") {
  Bitset bitset1(16);
  bitset1.set(1);
  bitset1.set(3);
  bitset1.set(6);

  Bitset bitset2(16);
  bitset2.set(1);
  bitset2.set(2);
  bitset2.set(3);
  bitset2.set(4);
  bitset2.set(6);

  bitset1 &= bitset2;

  CHECK(bitset1.test(0) == false);
  CHECK(bitset1.test(1) == true);
  CHECK(bitset1.test(2) == false);
  CHECK(bitset1.test(3) == true);
  CHECK(bitset1.test(4) == false);
  CHECK(bitset1.test(5) == false);
  CHECK(bitset1.test(6) == true);
  CHECK(bitset1.test(7) == false);
}

TEST_CASE("Bitwise OR assignment operator") {
  Bitset bitset1(16);
  bitset1.set(1);
  bitset1.set(3);
  bitset1.set(6);

  Bitset bitset2(16);
  bitset2.set(1);
  bitset2.set(2);
  bitset2.set(3);
  bitset2.set(4);
  bitset2.set(6);

  bitset1 |= bitset2;

  CHECK(bitset1.test(0) == false);
  CHECK(bitset1.test(1) == true);
  CHECK(bitset1.test(2) == true);
  CHECK(bitset1.test(3) == true);
  CHECK(bitset1.test(4) == true);
  CHECK(bitset1.test(5) == false);
  CHECK(bitset1.test(6) == true);
  CHECK(bitset1.test(7) == false);
}

TEST_CASE("Bitwise XOR assignment operator") {
  Bitset bitset1(16);
  bitset1.set(1);
  bitset1.set(3);
  bitset1.set(6);

  Bitset bitset2(16);
  bitset2.set(1);
  bitset2.set(2);
  bitset2.set(3);
  bitset2.set(4);
  bitset2.set(6);

  bitset1 ^= bitset2;

  CHECK(bitset1.test(0) == false);
  CHECK(bitset1.test(1) == false);
  CHECK(bitset1.test(2) == true);
  CHECK(bitset1.test(3) == false);
  CHECK(bitset1.test(4) == true);
  CHECK(bitset1.test(5) == false);
  CHECK(bitset1.test(6) == false);
  CHECK(bitset1.test(7) == false);
}
