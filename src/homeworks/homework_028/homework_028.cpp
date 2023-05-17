#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <utility>

using namespace std;

// Input and output files
const string INPUT_FILE = "../src/homeworks/homework_028/input.txt";
const string OUTPUT_FILE = "../src/homeworks/homework_028/output.txt";
const string MATERIALS_FILE = "../src/homeworks/homework_028/materials.txt";

// Structure that implements a foreman
struct ForemanInfo {
  string name;
  string surname;
  string email;
  string phone;

  // Overload the cout operator
  friend ostream &operator<<(ostream &os, const ForemanInfo &fi) {
    os << "  Name: " << fi.name << "\n";
    os << "  Surname: " << fi.surname << "\n";
    os << "  Email: " << fi.email << "\n";
    os << "  Phone: " << fi.phone;
    return os;
  }
};

// Structure that implements a material
struct Material {
  string date;
  string name;
  int volume;
  int cost;

  // Overload the << operator
  friend ostream &operator<<(ostream &os, const Material &m) {
    os << "  Name: " << m.name << "\n";
    os << "  Date: " << m.date << "\n";
    os << "  Volume: " << m.volume << "\n";
    os << "  Cost: " << m.cost;
    return os;
  }

  // Overload the == operator for unordered_set
  bool operator==(const Material &other) const {
    return name == other.name;
  }
};

// Structure that implements the hash function for unordered_set
template<>
struct hash<Material> {
  size_t operator()(const Material &m) const {
    return hash<string>()(m.name);
  }
};

// Class that implements a brigade
class Brigade {
 private:
  int id;
  ForemanInfo foreman;
  list<Material> materials;

 public:
  // Constructor
  Brigade(int _id, ForemanInfo _foreman, list<Material> _materials)
      : id(_id), foreman(std::move(_foreman)), materials(std::move(_materials)) {}

  // Overload the << operator
  friend ostream &operator<<(ostream &os, const Brigade &b) {
    os << "Brigade ID: " << b.id << "\n";
    os << "Foreman:\n" << b.foreman << "\n";
    os << "Materials:\n";
    for (const auto &material : b.materials) {
      os << material << "\n";
    }
    return os;
  }

  // Get the total volume of materials used by the brigade
  [[nodiscard]] int getTotalVolume() const {
    int total = 0;
    for (const auto &material : materials) {
      total += material.volume;
    }
    return total;
  }

  // Get the total cost of materials used by the brigade
  [[nodiscard]] int getTotalCost() const {
    int total = 0;
    for (const auto &material : materials) {
      total += material.cost;
    }
    return total;
  }

  // Get a list of all the materials used by the brigade
  [[nodiscard]] list<Material> getAllMaterials() const {
    return materials;
  }

  // Getters
  [[nodiscard]] int getId() const {
    return id;
  }

  [[nodiscard]] list<Material> getMaterials() const {
    return materials;
  }
};

// Class that implements a brigade manager
class BrigadeManager {
 private:
  list<Brigade> brigades;

 public:
  // Function that parses the input file
  void parseFile(const string &filename) {
    ifstream infile(filename);
    if (!infile) {
      throw runtime_error("Failed to open file");
    }

    string line;
    while (getline(infile, line)) {
      istringstream iss(line);
      int id;
      string name, surname, email, phone, date, material;
      int volume, cost;

      if (!(iss >> id >> name >> surname >> email >> phone >> date >> material >> volume >> cost)) {
        continue;
      }

      ForemanInfo foreman = {name, surname, email, phone};
      Material mat = {date, material, volume, cost};

      auto it = find_if(brigades.begin(), brigades.end(), [id](const Brigade &b) {
        return b.getId() == id;
      });

      if (it == brigades.end()) {
        list<Material> materials = {mat};
        brigades.emplace_back(id, foreman, materials);
      } else {
        it->getMaterials().push_back(mat);
      }
    }

    infile.close();
  }

  // Function that writes the brigades to the output file
  static void writeToFile(string filename, const list<Brigade> &brigades) {
    ofstream outfile(filename);
    if (!outfile) {
      throw runtime_error("Failed to open file");
    }

    for (const auto &b : brigades) {
      outfile << b << "\n";
    }

    outfile.close();
  }

  // Function that displays the brigades
  void displayBrigades() {
    brigades.sort([](const Brigade &b1, const Brigade &b2) {
      return b1.getId() < b2.getId();
    });

    writeToFile(OUTPUT_FILE, brigades);

    for (const auto &b : brigades) {
      cout << b << "\n";
    }
  }

  // Function that displays the materials
  void displayMaterials() {
    unordered_set<Material> uniqueMaterials;
    for (const auto &b : brigades) {
      for (const auto &m : b.getAllMaterials()) {
        uniqueMaterials.insert(m);
      }
    }

    ofstream outfile(MATERIALS_FILE);
    if (!outfile) {
      throw runtime_error("Failed to open file");
    }

    for (const auto &m : uniqueMaterials) {
      outfile << "Name: " << m.name << "\n";
      outfile << "Volume: " << m.volume << "\n";
      outfile << "Cost: " << m.cost << "\n\n";
    }

    outfile.close();
  }
};

// Main function
int main() {
  BrigadeManager manager;

  try {
    manager.parseFile(INPUT_FILE);
    manager.displayBrigades();
    manager.displayMaterials();
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
