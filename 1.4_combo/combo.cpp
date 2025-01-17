/*
ID: dermotl1
LANG: C++
PROG: combo
*/

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("combo.out");
  ifstream fin("combo.in");

  int n, fj1, fj2, fj3, m1, m2, m3;
  fin >> n;
  fin >> fj1 >> fj2 >> fj3;
  fin >> m1 >> m2 >> m3;

  int count = 0;

  for (int x = 1; x <= n; x++) {
    for (int y = 1; y <= n; y++) {
      for (int z = 1; z <= n; z++) {
        if (((abs(x - fj1) <= 2) || (abs(x - fj1) >= n - 2)) &&
            ((abs(y - fj2) <= 2) || (abs(y - fj2) >= n - 2)) &&
            ((abs(z - fj3) <= 2) || (abs(z - fj3) >= n - 2))) {
          count++;

        } else if (((abs(x - m1) <= 2) || (abs(x - m1) >= n - 2)) &&
                   ((abs(y - m2) <= 2) || (abs(y - m2) >= n - 2)) &&
                   ((abs(z - m3) <= 2) || (abs(z - m3) >= n - 2))) {
          count++;
        }
      }
    }
  }

  fout << count << "\n";
  return 0;
}
