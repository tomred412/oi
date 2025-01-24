#include <iostream>
using namespace std;

int main() {
  string array[100];
  array[0] = "http://www.acm.org/";
  int size = 1;
  int pos = 0;
  string command;

  while (cin >> command) {
    if (command == "QUIT") return 0;

    if (command == "VISIT") {
      cin >> array[pos + 1];
      pos++;
      size = pos + 1;
      cout << array[pos] << "\n";
      continue;
    }

    if (command == "BACK") {
      if (pos == 0) {
        cout << "Ignored" << "\n";
      } else {
        pos--;
        cout << array[pos] << "\n";
      }
      continue;
    }

    if (command == "FORWARD") {
      if (pos == size - 1) {
        cout << "Ignored" << "\n";
      } else {
        pos++;
        cout << array[pos] << "\n";
      }
      continue;
    }
  }

  return 0;
}

