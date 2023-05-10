#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// Class that represents attendance report
class AttendanceReport {
  string inputFilePath;
  map<unsigned int, map<unsigned int, unsigned int>> attendance;

  // Method that returns day name by day number
  static string getDayName(unsigned int day) {
    // Map week days to names
    vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    // Return day name
    return days[day - 1];
  }

  // Method that returns time string by hour number
  static string getTimeString(unsigned int hour) {
    // Convert hour number to string
    stringstream ss;
    ss << hour;
    string hourString = ss.str();

    // Add leading zero if needed
    if (hourString.length() == 1) {
      hourString = "0" + hourString;
    }

    // Add minutes
    hourString += ":00";

    // Return time string
    return hourString;
  }

  // Method that parses the input file
  void parseFile() {
    // Open file and check if it's open
    ifstream file(inputFilePath);
    if (!file.is_open()) {
      throw invalid_argument("File not found");
    }

    // Read file line by line
    string line;
    while (getline(file, line)) {
      // Parse line
      unsigned int day, hour, visitors;
      istringstream iss(line);
      iss >> day >> hour >> visitors;

      // Add attendance of that day to the map
      attendance[day][hour] = visitors;
    }
  }

 public:
  // Constructor
  explicit AttendanceReport(string _inputFilePath) : inputFilePath(std::move(_inputFilePath)) {
    parseFile();
  }

  // Method that generates report of days with minimum visitors
  void generateMinVisitorsReport(const string &outputFilePath) {
    // Create output file and check if it's open
    ofstream file(outputFilePath);
    if (!file.is_open()) {
      throw invalid_argument("Something went wrong while creating the report file");
    }

    // Iterate over days
    for (auto &[dayNumber, day] : attendance) {
      // Output day name
      file << getDayName(dayNumber) << ":" << endl;

      // Find minimum visitors
      unsigned int minVisitors = INT_MAX;
      unsigned int minHour;
      for (auto &[hour, hourAttendance] : day) {
        if (hourAttendance < minVisitors) {
          minVisitors = hourAttendance;
          minHour = hour;
        }
      }

      // Output minimum visitors and time
      file << "  Time: " << getTimeString(minHour) << "\n";
      file << "  Visitors: " << minVisitors << " visitors\n\n";
    }
  }

  // Method that generates report of day with most visitors
  void mostVisitorsReport(const string &outputFilePath) {
    // Create output file and check if it's open
    ofstream file(outputFilePath);
    if (!file.is_open()) {
      throw invalid_argument("Something went wrong while creating the report file");
    }

    // Find day with most visitors
    unsigned int maxVisitors = 0;
    unsigned int maxDay;
    for (auto &[dayNumber, day] : attendance) {
      unsigned int totalDayVisitors = 0;
      for (auto &[hour, hourAttendance] : day) {
        totalDayVisitors += hourAttendance;
      }
      if (totalDayVisitors > maxVisitors) {
        maxVisitors = totalDayVisitors;
        maxDay = dayNumber;
      }
    }

    // Output day name and total visitors
    file << "Day: " << getDayName(maxDay) << "\n";
    file << "Total visitors: " << maxVisitors << " visitors\n";
  }
};

// Main function
int main() {
  AttendanceReport report("../src/classworks/04_05_2023/associative_containers/input.txt");
  report.generateMinVisitorsReport("../src/classworks/04_05_2023/associative_containers/output1.txt");
  report.mostVisitorsReport("../src/classworks/04_05_2023/associative_containers/output2.txt");
}
