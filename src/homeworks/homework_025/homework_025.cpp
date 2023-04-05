#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

// Define a vector of languages
vector<string> languages = {"Ukrainian", "English", "Polish", "German", "French", "Spanish", "Italian", "Chinese", "Japanese", "Korean", "Hebrew", "Arabic"};

// Greeting function
string getGreeting(string name, string(*f)(string)) {
  return f(std::move(name));
}

// Ukrainian greeting
string ukrainianGreeting(string name) {
  return "З Днем народження, " + name + "!";
}

// English greeting
string englishGreeting(string name) {
  return "Happy birthday, " + name + "!";
}

// Polish greeting
string polishGreeting(string name) {
  return "Wszystkiego najlepszego z okazji urodzin, " + name + "!";
}

// German greeting
string germanGreeting(string name) {
  return "Alles Gute zum Geburtstag, " + name + "!";
}

// French greeting
string frenchGreeting(string name) {
  return "Joyeux anniversaire, " + name + "!";
}

// Spanish greeting
string spanishGreeting(string name) {
  return "Feliz cumpleaños, " + name + "!";
}

// Italian greeting
string italianGreeting(string name) {
  return "Auguri di buon compleanno, " + name + "!";
}

// Chinese greeting
string chineseGreeting(string name) {
  return "生日快乐, " + name + "!";
}

// Japanese greeting
string japaneseGreeting(string name) {
  return "お誕生日おめでとう, " + name + "!";
}

// Korean greeting
string koreanGreeting(string name) {
  return "생일 축하합니다, " + name + "!";
}

// Hebrew greeting
string hebrewGreeting(string name) {
  return "חג יום הולדת שמח, " + name + "!";
}

// Arabic greeting
string arabicGreeting(string name) {
  return "عيد ميلاد سعيد, " + name + "!";
}

// All languages greeting
string allLanguagesGreeting(string name) {
  // Define a greeting string
  string greeting;

  // Append all languages greetings
  greeting += "Ukrainian: " + ukrainianGreeting(name) + "\n";
  greeting += "English: " + englishGreeting(name) + "\n";
  greeting += "Polish: " + polishGreeting(name) + "\n";
  greeting += "German: " + germanGreeting(name) + "\n";
  greeting += "French: " + frenchGreeting(name) + "\n";
  greeting += "Spanish: " + spanishGreeting(name) + "\n";
  greeting += "Italian: " + italianGreeting(name) + "\n";
  greeting += "Chinese: " + chineseGreeting(name) + "\n";
  greeting += "Japanese: " + japaneseGreeting(name) + "\n";
  greeting += "Korean: " + koreanGreeting(name) + "\n";
  greeting += "Hebrew: " + hebrewGreeting(name) + "\n";
  greeting += "Arabic: " + arabicGreeting(name);

  // Return greeting
  return greeting;
}

// Main function
int main() {
  // Define a file stream and open a file
  ofstream ofs("../src/homeworks/homework_025/output.txt");

  // Check if the file is open
  if (!ofs.is_open()) {
    cout << "Error opening file" << endl;
    return 1;
  }

  // Ask user for a name
  cout << "Enter name for greeting:\n";
  cout << "--> ";
  string name;
  cin >> name;

  // Ask user for a language
  cout << "\nChoose a language for greeting:\n";
  for (int i = 0; i < languages.size(); i++) {
    cout << "  " << i + 1 << ". " << languages[i] << "\n";
  }
  cout << "  " << languages.size() + 1 << ". All languages\n";
  cout << "\nYour choice:\n";
  cout << "--> ";
  int choice;
  cin >> choice;

  // Check if choice is valid
  if (choice < 1 || choice > languages.size() + 1) {
    cout << "\nInvalid choice! Exiting...\n";
    return 0;
  }

  // Define a greeting string
  string greeting;

  // If choice is "All languages" (last option), then get a greeting for each language
  if (choice == languages.size() + 1) {
    greeting = getGreeting(name, allLanguagesGreeting);
  } else {
    // Otherwise get a greeting for selected language
    switch (choice) {
      case 1:
        greeting = getGreeting(name, ukrainianGreeting);
        break;
      case 2:
        greeting = getGreeting(name, englishGreeting);
        break;
      case 3:
        greeting = getGreeting(name, polishGreeting);
        break;
      case 4:
        greeting = getGreeting(name, germanGreeting);
        break;
      case 5:
        greeting = getGreeting(name, frenchGreeting);
        break;
      case 6:
        greeting = getGreeting(name, spanishGreeting);
        break;
      case 7:
        greeting = getGreeting(name, italianGreeting);
        break;
      case 8:
        greeting = getGreeting(name, chineseGreeting);
        break;
      case 9:
        greeting = getGreeting(name, japaneseGreeting);
        break;
      case 10:
        greeting = getGreeting(name, koreanGreeting);
        break;
      case 11:
        greeting = getGreeting(name, hebrewGreeting);
        break;
      case 12:
        greeting = getGreeting(name, arabicGreeting);
        break;
      default:
        cout << "\nInvalid choice! Exiting...\n";
        return 0;
    }
  }

  // Write greeting to file
  ofs << greeting << endl;

  // Print success message
  cout << "\nGreeting successfully written to file!\nCheck \"output.txt\".\n";

  // Close file
  ofs.close();

  return 0;
}
