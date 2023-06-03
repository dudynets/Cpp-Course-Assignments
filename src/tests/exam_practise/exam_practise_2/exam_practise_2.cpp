#include <iostream>
#include <utility>
#include <vector>
#include <fstream>

using namespace std;

struct Date {
  int day;
  int month;
  int year;

  Date(int _day, int _month, int _year) : day(_day), month(_month), year(_year) {};

  friend ostream &operator<<(ostream &os, const Date &date) {
    os << date.day << "/" << date.month << "/" << date.year;
    return os;
  }
};

class Action {
 private:
  string title;
  long durationInSeconds;

 public:
  Action(string _title, long _durationInSeconds) : title(std::move(_title)), durationInSeconds(_durationInSeconds) {};

  string getTitle() {
    return title;
  }

  [[nodiscard]] long getDuration() const {
    return durationInSeconds;
  }

  friend ostream &operator<<(ostream &os, const Action &action) {
    os << "        Action:\n";
    os << "          Title: " << action.title << "\n";
    os << "          Duration: " << action.durationInSeconds << " sec.\n";

    return os;
  }
};

class DailyAgenda {
 private:
  Date date;
  vector<Action> actions;

 public:
  DailyAgenda(Date _date, vector<Action> _actions) : date(_date), actions(std::move(_actions)) {};

  long getTotalDurationByTitle(const string &title) {
    long duration = 0;

    for (auto action : actions) {
      if (action.getTitle() == title) {
        duration += action.getDuration();
      }
    }

    return duration;
  }

  vector<Action> getActions() {
    return actions;
  }

  friend ostream &operator<<(ostream &os, const DailyAgenda &dailyAgenda) {
    os << "    Daily agenda:\n";
    os << "      Date: " << dailyAgenda.date << "\n";
    os << "      Actions:\n";

    for (const auto &action : dailyAgenda.actions) {
      os << action << "\n";
    }

    return os;
  }
};

class WeeklyAgenda {
 private:
  string ownerName;
  vector<DailyAgenda> dailyAgendas;

 public:
  WeeklyAgenda(string _ownerName, vector<DailyAgenda> _dailyAgendas)
      : ownerName(std::move(_ownerName)), dailyAgendas(std::move(_dailyAgendas)) {};

  string getOwnerName() {
    return ownerName;
  }

  void addDailyAgenda(const DailyAgenda &dailyAgenda) {
    dailyAgendas.push_back(dailyAgenda);
  }

  long getTotalDurationByTitle(const string &title) {
    long duration = 0;

    for (auto dailyAgenda : dailyAgendas) {
      duration += dailyAgenda.getTotalDurationByTitle(title);
    }

    return duration;
  }

  vector<DailyAgenda> getDailyAgendas() {
    return dailyAgendas;
  }

  friend ostream &operator<<(ostream &os, const WeeklyAgenda &weeklyAgenda) {
    os << "Weekly agenda:\n";
    os << "  Owner name: " << weeklyAgenda.ownerName << "\n";
    os << "  Days:\n";

    for (const auto &dailyAgenda : weeklyAgenda.dailyAgendas) {
      os << dailyAgenda << "\n";
    }

    return os;
  }
};

vector<string> split(const string &str, const string &delimiter) {
  vector<string> tokens;
  size_t start = 0, end;
  while ((end = str.find(delimiter, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delimiter.length();
  }
  tokens.push_back(str.substr(start));
  return tokens;
}

void printAllAgendas(const vector<WeeklyAgenda> &weeklyAgendas) {
  cout << "==================\n";
  cout << "ALL WEEKLY AGENDAS\n";
  cout << "==================\n\n";

  for (const auto &weeklyAgenda : weeklyAgendas) {
    cout << weeklyAgenda << endl;
  }
}

void printMaxActionsAgenda(vector<WeeklyAgenda> weeklyAgendas) {
  int maxActionsWeeklyAgendaIndex = 0;
  int maxActionsDailyAgendaIndex = 0;

  for (int i = 0; i < weeklyAgendas.size(); i++) {
    WeeklyAgenda weeklyAgenda = weeklyAgendas.at(i);
    unsigned long maxNumberOfActions = 0;

    for (int j = 0; j < weeklyAgenda.getDailyAgendas().size(); j++) {
      DailyAgenda dailyAgenda = weeklyAgenda.getDailyAgendas().at(j);

      if (dailyAgenda.getActions().size() > maxNumberOfActions) {
        maxNumberOfActions = dailyAgenda.getActions().size();
        maxActionsWeeklyAgendaIndex = i;
        maxActionsDailyAgendaIndex = j;
      }
    }
  }

  WeeklyAgenda maxActionsWeeklyAgenda = weeklyAgendas.at(maxActionsWeeklyAgendaIndex);
  string maxActionsOwner = maxActionsWeeklyAgenda.getOwnerName();
  DailyAgenda maxActionsDailyAgenda = maxActionsWeeklyAgenda.getDailyAgendas().at(maxActionsDailyAgendaIndex);

  cout << "==================\n";
  cout << "MAX ACTIONS AGENDA\n";
  cout << "==================\n\n";

  cout << "Owner name: " << maxActionsOwner << endl;
  cout << maxActionsDailyAgenda << endl;
}

void printWalkTotalDurationToFile(const vector<WeeklyAgenda> &weeklyAgendas, const string &title) {
  ofstream output("../src/tests/exam_practise/exam_practise_2/report.txt");
  if (!output.is_open()) {
    throw runtime_error("file not found");
  }

  output << "\"" << title << "\" action total duration:\n";

  for (auto weeklyAgenda : weeklyAgendas) {
    output << "  " << weeklyAgenda.getOwnerName() << ": " << weeklyAgenda.getTotalDurationByTitle(title) << " sec.\n";
  }

  output.close();

  cout << "Total duration of \"" << title << "\" action has been successfully written to file.\n";
}

int main() {
  try {
    vector<WeeklyAgenda> weeklyAgendas;

    ifstream input("../src/tests/exam_practise/exam_practise_2/people.txt");
    if (!input.is_open()) {
      throw runtime_error("file not found");
    }

    string line;
    while (getline(input, line)) {
      vector<string> tokens = split(line, " ");

      string owner = tokens[0];
      int day = stoi(tokens[1]);
      int month = stoi(tokens[2]);
      int year = stoi(tokens[3]);

      Date date(day, month, year);

      vector<Action> actions;

      for (int i = 4; i < tokens.size(); i += 2) {
        string title = tokens[i];
        long durationInSeconds = stoi(tokens[i + 1]);

        actions.emplace_back(title, durationInSeconds);
      }

      DailyAgenda dailyAgenda(date, actions);

      bool ownerExists = false;
      for (auto &weeklyAgenda : weeklyAgendas) {
        if (weeklyAgenda.getOwnerName() != owner) {
          continue;
        }

        weeklyAgenda.addDailyAgenda(dailyAgenda);
        ownerExists = true;
      }

      if (!ownerExists) {
        WeeklyAgenda weeklyAgenda(owner, {dailyAgenda});
        weeklyAgendas.push_back(weeklyAgenda);
      }
    }

    input.close();

    printAllAgendas(weeklyAgendas);
    printMaxActionsAgenda(weeklyAgendas);
    printWalkTotalDurationToFile(weeklyAgendas, "Walking");
  }
  catch (runtime_error &error) {
    cout << "Error: " << error.what();
  }
  catch (...) {
    cout << "Unknown error";
  }

  return 0;
}
