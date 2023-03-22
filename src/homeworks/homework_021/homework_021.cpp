#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Constants
const bool USE_DEFAULT_VALUES = false;

// Define transport types
const string WATER = "WATER";
const string LAND = "LAND";
const string AMPHIBIAN = "AMPHIBIAN";

// Class that represents a transport
class Transport {
 private:
  string name;
  int engineVolume;
  string type;
 public:
  // Constructor
  Transport(string name, int engineVolume, string type) {
    this->name = std::move(name);
    this->engineVolume = engineVolume;
    this->type = std::move(type);
  }

  // Getters
  [[nodiscard]] virtual string getName() const {
    return name;
  }

  [[nodiscard]] virtual int getEngineVolume() const {
    return engineVolume;
  }

  [[nodiscard]] string getType() const {
    return type;
  }

  // Overloaded operators
  friend ostream &operator<<(ostream &os, const Transport &transport) {
    os << transport.getType() + " TRANSPORT:" << endl;
    os << "    - GENERAL INFO: " << endl;
    os << "        - Name: " << transport.getName() << endl;
    os << "        - Engine volume: " << transport.getEngineVolume() << endl;
    return os;
  }

  virtual bool operator<(Transport &transport) {
    return name < transport.name;
  }
};

// Class that represents a water transport
class WaterTransport : public virtual Transport {
 private:
  string typeOfWater;
  int maxSpeedInWater;
 public:
  // Constructor
  WaterTransport(string name, int engineVolume, string typeOfWater, int maxSpeedInWater) :
      Transport(std::move(name), engineVolume, WATER) {
    this->typeOfWater = std::move(typeOfWater);
    this->maxSpeedInWater = maxSpeedInWater;
  }

  // Getters
  [[nodiscard]] string getTypeOfWater() const {
    return typeOfWater;
  }

  [[nodiscard]] int getMaxSpeedInWater() const {
    return maxSpeedInWater;
  }

  // Overloaded operators
  friend ostream &operator<<(ostream &os, const WaterTransport &water_transport) {
    os << static_cast<Transport>(water_transport);
    os << "    - WATER SPECIFIC INFO: " << endl;
    os << "        - Type of water: " << water_transport.getTypeOfWater() << endl;
    os << "        - Max speed in water: " << water_transport.getMaxSpeedInWater() << endl;
    return os;
  }
};

// Class that represents a land transport
class LandTransport : public virtual Transport {
 private:
  int maxSpeedOnLand;
  int numberOfSeats;
 public:
  // Constructor
  LandTransport(string name, int engineVolume, int maxSpeedOnLand, int numberOfSeats) :
      Transport(std::move(name), engineVolume, LAND) {
    this->maxSpeedOnLand = maxSpeedOnLand;
    this->numberOfSeats = numberOfSeats;
  }

  // Getters
  [[nodiscard]] int getMaxSpeedOnLand() const {
    return maxSpeedOnLand;
  }

  [[nodiscard]] int getNumberOfSeats() const {
    return numberOfSeats;
  }

  // Overloaded operators
  friend ostream &operator<<(ostream &os, const LandTransport &land_transport) {
    os << static_cast<Transport>(land_transport);
    os << "    - LAND SPECIFIC INFO: " << endl;
    os << "        - Max speed on land: " << land_transport.getMaxSpeedOnLand() << endl;
    os << "        - Number of seats: " << land_transport.getNumberOfSeats() << endl;
    return os;
  }
};

// Class that represents an amphibian transport
class AmphibianTransport : public WaterTransport, public LandTransport {
 private:
  int maxHoursInWater;
  int maxHoursOnLand;
 public:
  // Constructor
  AmphibianTransport(
      const string &name,
      int engineVolume,
      string typeOfWater,
      int maxSpeedInWater,
      int maxSpeed,
      int numberOfSeats,
      int maxHoursInWater,
      int maxHoursOnLand) :
      Transport(name, engineVolume, AMPHIBIAN),
      WaterTransport(name, engineVolume, std::move(typeOfWater), maxSpeedInWater),
      LandTransport(name, engineVolume, maxSpeed, numberOfSeats) {
    this->maxHoursInWater = maxHoursInWater;
    this->maxHoursOnLand = maxHoursOnLand;
  }

  // Getters
  [[nodiscard]] int getMaxHoursInWater() const {
    return maxHoursInWater;
  }

  [[nodiscard]] int getMaxHoursOnLand() const {
    return maxHoursOnLand;
  }

  // Overloaded operators
  friend ostream &operator<<(ostream &os, const AmphibianTransport &amphibian_transport) {
    os << static_cast<Transport>(amphibian_transport);
    os << "    - WATER SPECIFIC INFO: " << endl;
    os << "        - Type of water: " << amphibian_transport.getTypeOfWater() << endl;
    os << "        - Max speed in water: " << amphibian_transport.getMaxSpeedInWater() << endl;
    os << "    - LAND SPECIFIC INFO: " << endl;
    os << "        - Max speed on land: " << amphibian_transport.getMaxSpeedOnLand() << endl;
    os << "        - Number of seats: " << amphibian_transport.getNumberOfSeats() << endl;
    os << "    - AMPHIBIAN SPECIFIC INFO: " << endl;
    os << "        - Max hours in water: " << amphibian_transport.getMaxHoursInWater() << endl;
    os << "        - Max hours on land: " << amphibian_transport.getMaxHoursOnLand() << endl;
    return os;
  }
};

// Function declarations
Transport *promptForTransportItem();

// Main function
int main() {
  // Create a vector of transport items
  vector<Transport *> transports;

  // Check if the user wants to use default values
  if (USE_DEFAULT_VALUES) {
    // Add 10 transport items to the vector
    transports = {
        new WaterTransport("Boat", 100, "Ocean", 100),
        new WaterTransport("Submarine", 200, "Ocean", 200),
        new LandTransport("Truck", 300, 300, 3),
        new LandTransport("All-terrain vehicle", 400, 400, 4),
        new AmphibianTransport("Amphibian", 500, "Ocean", 500, 500, 5, 5, 5),
        new LandTransport("Bus", 600, 600, 6),
        new WaterTransport("Yacht", 700, "Ocean", 700),
        new WaterTransport("Sailboat", 800, "Ocean", 800),
        new LandTransport("Car", 900, 900, 9),
        new LandTransport("Motorcycle", 1000, 1000, 1)
    };
  } else {
    // Prompt for 10 transport items
    const int TRANSPORT_ITEMS_COUNT = 10;
    for (int i = 0; i < TRANSPORT_ITEMS_COUNT; i++) {
      cout << "=============================\n";
      cout << "Adding transport item " << i + 1 << " of " << TRANSPORT_ITEMS_COUNT << "\n";
      cout << "=============================\n\n";

      // Add transport item to vector
      transports.push_back(promptForTransportItem());

      cout << "\n\n\n";
    }
  }

  // Sort transport items by name
  sort(transports.begin(), transports.end(), [](const Transport *a, const Transport *b) {
    // Cast to Transport* to use < operator
    auto *aCasted = const_cast<Transport *>(a);
    auto *bCasted = const_cast<Transport *>(b);

    // Compare names
    return *aCasted < *bCasted;
  });

  // Print all transports
  cout << "=================\n";
  cout << "SORTED TRANSPORT:\n";
  cout << "=================\n\n";
  for (const auto &transport : transports) {
    // Check if transport is an AmphibianTransport, WaterTransport or LandTransport
    if (const auto *amphibianTransport = dynamic_cast<AmphibianTransport *>(transport)) {
      cout << *amphibianTransport << endl;
    } else if (const auto *waterTransport = dynamic_cast<WaterTransport *>(transport)) {
      cout << *waterTransport << endl;
    } else if (const auto *landTransport = dynamic_cast<LandTransport *>(transport)) {
      cout << *landTransport << endl;
    }
  }
  cout << "\n\n";

  // Find the transport with the largest engine volume
  auto maxEngineVolume = max_element(transports.begin(), transports.end(), [](const Transport *a, const Transport *b) {
    return a->getEngineVolume() < b->getEngineVolume();
  });

  cout << "===============\n";
  cout << "LARGEST ENGINE:\n";
  cout << "===============\n\n";
  cout << **maxEngineVolume << endl;
  cout << "\n\n";

  // Find the transport with the smallest engine volume
  auto minEngineVolume = min_element(transports.begin(), transports.end(), [](const Transport *a, const Transport *b) {
    return a->getEngineVolume() < b->getEngineVolume();
  });

  cout << "================\n";
  cout << "SMALLEST ENGINE:\n";
  cout << "================\n\n";
  cout << **minEngineVolume << endl;
  cout << "\n\n";

  // Print only water transport
  cout << "================\n";
  cout << "WATER TRANSPORT:\n";
  cout << "================\n\n";
  bool hasWaterTransport = false;
  for (const auto &transport : transports) {
    // Check if transport is not amphibian
    if (dynamic_cast<AmphibianTransport *>(transport)) {
      continue;
    }

    // Check if transport is water transport
    if (const auto *waterTransport = dynamic_cast<WaterTransport *>(transport)) {
      cout << *waterTransport << endl;
      hasWaterTransport = true;
    }
  }
  if (!hasWaterTransport) {
    cout << "    No water transport found!\n";
  }
  cout << "\n\n";

  // Print only amphibian transport
  cout << "====================\n";
  cout << "AMPHIBIAN TRANSPORT:\n";
  cout << "====================\n\n";
  bool hasAmphibianTransport = false;
  for (const auto &transport : transports) {
    // Check if transport is amphibian
    if (const auto *amphibianTransport = dynamic_cast<AmphibianTransport *>(transport)) {
      cout << *amphibianTransport << endl;
      hasAmphibianTransport = true;
    }
  }
  if (!hasAmphibianTransport) {
    cout << "    No amphibian transport found!\n";
  }

  return 0;
}

// Function that prompts the user to add a new transport item
Transport *promptForTransportItem() {
  int choice;
  string name;
  int engineVolume;
  string typeOfWater;
  int maxSpeedInWater;
  int maxSpeedOnLand;
  int numberOfSeats;
  int maxHoursInWater;
  int maxHoursOnLand;

  cout << "    Choose the type of transport you want to add:\n\n";
  cout << "    1. Water transport\n";
  cout << "    2. Land transport\n";
  cout << "    3. Amphibian transport\n\n";
  cout << "    Your choice:\n    ==> ";
  cin >> choice;

  cout << "\n    Enter the name of the transport:\n    ==> ";
  cin >> name;

  cout << "\n    Enter the engine volume of the transport:\n    ==> ";
  cin >> engineVolume;

  switch (choice) {
    case 1:cout << "\n    Enter the type of water:\n    ==> ";
      cin >> typeOfWater;

      cout << "\n    Enter the max speed in water:\n    ==> ";
      cin >> maxSpeedInWater;

      return new WaterTransport(name, engineVolume, typeOfWater, maxSpeedInWater);
    case 2:cout << "\n    Enter the max speed on land:\n    ==> ";
      cin >> maxSpeedOnLand;

      cout << "\n    Enter the number of seats:\n    ==> ";
      cin >> numberOfSeats;

      return new LandTransport(name, engineVolume, maxSpeedOnLand, numberOfSeats);
    case 3:cout << "\n    Enter the type of water:\n    ==> ";
      cin >> typeOfWater;

      cout << "\n    Enter the max speed in water:\n    ==> ";
      cin >> maxSpeedInWater;

      cout << "\n    Enter the max speed on land:\n    ==> ";
      cin >> maxSpeedOnLand;

      cout << "\n    Enter the number of seats:\n    ==> ";
      cin >> numberOfSeats;

      cout << "\n    Enter the max hours in water:\n    ==> ";
      cin >> maxHoursInWater;

      cout << "\n    Enter the max hours on land:\n    ==> ";
      cin >> maxHoursOnLand;

      return new AmphibianTransport(
          name,
          engineVolume,
          typeOfWater,
          maxSpeedInWater,
          maxSpeedOnLand,
          numberOfSeats,
          maxHoursInWater,
          maxHoursOnLand
      );
    default:return nullptr;
  }
}
