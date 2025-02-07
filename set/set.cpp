#include <iostream>
#include <set>

using namespace std;

set<int> s;

void insert(int data) { s.insert(data); }

void print();
// prints the data in the tree, in order

void print(int node) {
  for (auto i = s.begin(); i != s.end(); i++) {
    cout << *i << " ";
  }
}

bool find(int data) { return s.count(data); }

int main() {
  cout << "Please enter the list, then a period, then m numbers to find in the "
          "set.\n";

  int n;
  while (cin >> n) {
    insert(n);
    if (cin.peek() == '.') break;
  }

  char period;
  cin >> period;

  if (period != '.') {
    cout << "There should be a period.\n";
    return 0;
  }

  int m;
  cin >> m;

  int p = 0;

  for (int i = 0; i < m; i++) {
    cin >> p;
    if (find(p) == true) cout << p << ": yes\n";
    if (find(p) == false) cout << p << ": no\n";
  }
  cout << "Sorted tree:\n";
  print(0);

  return 0;
}
