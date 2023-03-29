#include <iostream>
#include <chrono>
#include <vector>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

// Function that converts a date string in the format dd/mm/yyyy to a time_point
chrono::system_clock::time_point parseDateString(const string &date) {
  // Create a tm struct
  tm time = {};

  // Parse the date string
  istringstream ss(date);

  // Set the date format
  ss >> get_time(&time, "%d/%m/%Y");

  // Check if the parsing was successful
  if (ss.fail()) {
    // Throw an exception if the parsing was not successful
    throw invalid_argument("Invalid date");
  }

  // Convert the tm struct to a time_point
  auto duration = chrono::system_clock::from_time_t(mktime(&time));

  // Return the time_point
  return {duration};
}

// Function that converts a time_point to a date string in the format dd/mm/yyyy
string parseDateTimePoint(chrono::system_clock::time_point date) {
  // Convert the time_point to a time_t
  time_t t = chrono::system_clock::to_time_t(date);

  // Convert the time_t to a date string
  stringstream ss;

  // Set the date format
  ss << put_time(localtime(&t), "%d/%m/%Y");

  // Return the date string
  return ss.str();
}

// Class that represents a product
template<typename T>
class Product {
 private:
  T data;
  chrono::system_clock::time_point productionDate;
  int expirationDays = 0;
 public:
  // Constructors
  Product() = default;
  Product(T _data, chrono::system_clock::time_point _productionDate, int _expirationDays)
      : data(_data), productionDate(_productionDate), expirationDays(_expirationDays) {}

  // Overload the << operator
  friend ostream &operator<<(ostream &os, const Product &product) {
    // Print product data
    os << "Product data:\n  - " << product.data << "\n";

    // Print product expiration data header
    os << "Expiration data:\n";

    // Check if product is expired
    const bool isExpired = product.getExpirationDate() < chrono::system_clock::now();
    if (isExpired) {
      os << "  (!) Product is expired (!)\n";
    } else {
      os << "  (!) Product is not expired (!)\n";
    }

    // Print product expiration data
    os << "  - Production date: " << parseDateTimePoint(product.productionDate) << "\n";
    os << "  - Expiration date: " << parseDateTimePoint(product.getExpirationDate()) << "\n";
    os << "  - Expiration period: " << product.expirationDays << " days\n";

    return os;
  }

  // Overload the >> operator
  friend istream &operator>>(istream &is, Product &product) {
    // Prompt user to enter product data
    cout << "  Enter data: ";
    is >> product.data;

    // Prompt user to enter product production date
    cout << "  Enter production date (format: DD/MM/YYYY): ";
    string dateString;
    is >> dateString;
    product.productionDate = parseDateString(dateString);

    // Prompt user to enter product expiration period
    cout << "  Enter expiration period (in days): ";
    is >> product.expirationDays;
    return is;
  }

  // Getter for the expiration date
  [[nodiscard]] chrono::system_clock::time_point getExpirationDate() const {
    return productionDate + chrono::hours(24 * expirationDays);
  }
};

// Structure that represents a milk product
struct Milk {
  string name;
  int fatContent = 0;

  // Overload the << operator
  friend ostream &operator<<(ostream &os, const Milk &milk) {
    // Print milk name
    os << "Name: " << milk.name << "\n";

    // Print milk fat content
    os << "  - Fat content: " << milk.fatContent << "%";

    return os;
  }

  // Overload the >> operator
  friend istream &operator>>(istream &is, Milk &milk) {
    cout << "\n";

    // Prompt user to enter milk name
    cout << "    - Enter name: ";
    is >> milk.name;

    // Prompt user to enter milk fat content
    cout << "    - Enter fat content (in %): ";
    is >> milk.fatContent;

    return is;
  }
};

// Main function
int main() {
  // Print header
  cout << "================\n";
  cout << "STRING PRODUCTS:\n";
  cout << "================\n\n";

  // Define string products
  vector<Product<string>> stringProducts;

  // Prompt for number of string products
  int numberOfStringProducts;
  cout << "Enter number of string products:\n";
  cout << "--> ";
  cin >> numberOfStringProducts;
  cout << "\n";

  // Prompt for string products data
  for (int i = 0; i < numberOfStringProducts; i++) {
    cout << "Enter data for product #" << i + 1 << ":\n";
    Product<string> product;
    cin >> product;
    stringProducts.push_back(product);

    cout << "\n";
  }

  // Print milk products header
  cout << "==============\n";
  cout << "MILK PRODUCTS:\n";
  cout << "==============\n\n";

  // Define milk products
  vector<Product<Milk>> milkProducts;

  // Prompt for number of milk products
  int numberOfMilkProducts;
  cout << "Enter number of milk products:\n";
  cout << "--> ";
  cin >> numberOfMilkProducts;
  cout << "\n";

  // Prompt for milk products data
  for (int i = 0; i < numberOfMilkProducts; i++) {
    cout << "Enter data for product #" << i + 1 << ":\n";
    Product<Milk> product;
    cin >> product;
    milkProducts.push_back(product);

    cout << "\n";
  }

  // Print products header
  cout << "=========\n";
  cout << "PRODUCTS:\n";
  cout << "=========\n\n";

  // Print string products
  for (const auto &product : stringProducts) {
    cout << product << "\n\n";
  }

  // Print milk products
  for (const auto &product : milkProducts) {
    cout << product << "\n\n";
  }

  return 0;
}
