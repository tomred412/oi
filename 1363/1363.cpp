#include <iostream>

using namespace std;

int main() {
  int n;
  while (cin >> n && n != 0) {
    while (true) {
      int final[1000];  // final order
      cin >> final[0];

      if (final[0] == 0) break;  // stop this one

      for (int i = 1; i < n; i++) {
        cin >> final[i];  // read the cars
      }

      int station[1000];  // a stack for the station
      int pos = -1;       // stack tracker
      int coach = 1;      // Incoming train coaches (1 to n)
      bool possible = true;

      for (int i = 0; i < n; i++) {
        while (coach <= n && coach <= final[i]) {
          pos++;
          station[pos] = coach;  // put it on the stack
          coach++;
        }

        if (pos >= 0 &&
            station[pos] == final[i]) {  // check if it matches the requirements
          pos--;                         // then, delete it from stack
        } else {
          possible = false;  // if not, set it to false
          break;
        }
      }

      if (possible) {
        cout << "Yes\n";
      } else {
        cout << "No\n";
      }
    }
    cout << "\n";
  }
  return 0;
}

