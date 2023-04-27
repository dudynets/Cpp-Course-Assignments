#include <iostream>
#include <list>
#include <regex>
using namespace std;
#define C char
#define L list<C>
#define S string
#define E const
#define O cout
#define r return
#define G for
L a() {
  L l;
  S s;
  O << "|e|";
  getline(cin, s);
  G (C i : s) {
    l.push_back(i);
  }
  r l;
}
L b(L &l) {
  L x;
  regex p("[^a-zA-Z0-9]");
  for (C i : l) {
    S str(1, i);
    if (regex_search(str, p)) {
      x.push_back(i);
    }
  }
  r x;
}
L c(E L &l) {
  L s = l;
  s.sort();
  s.unique();
  r s;
}
int main() {
  L l = a();
  L f = b(l);
  L s = c(f);
  O << "|f|";
  G (auto &i : f) {
    O << i;
  }
  O << "|s|";
  G (auto &i : s) {
    O << i;
  }
}
