/*
ID: dermotl1
LANG: C++
PROG: stamps
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ifstream fin("stamps.in");
  ofstream fout("stamps.out");

  int infinity = numeric_limits<int>::max();

  int k, n;
  fin >> k >> n;

  vector<int> number_of_stamps(2000000, infinity);  // for each amount of cents
  int stamps[50];
  number_of_stamps[0] = 0;

  for (int i = 0; i < n; ++i) {
    fin >> stamps[i];
  }
  int i;
  for (i = 1; i <= 2000000; ++i) {
    for (int j = 0; j < n; ++j) {
      int a = stamps[j];
      if (i - a >= 0 && number_of_stamps[i - a] + 1 < number_of_stamps[i]) {
        number_of_stamps[i] = number_of_stamps[i - a] + 1;
      }
    }
    if (number_of_stamps[i] > k) break;
  }
  fout << i - 1 << "\n";
  return 0;
}
