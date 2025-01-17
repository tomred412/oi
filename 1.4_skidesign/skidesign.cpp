/*
ID: dermotl1
LANG: C++
PROG: skidesign
*/

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
  ifstream fin("skidesign.in");
  ofstream fout("skidesign.out");

  int n = 0;

  fin >> n;
  int array[1000];

  for (int i = 0; i < n; i++) {
    fin >> array[i];
  }
  sort(array, array + n);

  int answer = 2147483647;
  int result = 0;
  int total = 0;
  int max = 0;

  for (int min = 0; min < array[n - 1]; min++) {
    max = min + 17;
    total = 0;
    result = 0;

    for (int j = 0; j < n; j++) {
      if (array[j] > max) {
        result = (array[j] - max) * (array[j] - max);
        total += result;
      }
      if (array[j] < min) {
        result = (min - array[j]) * (min - array[j]);
        total += result;
      }
    }
    if (total < answer) answer = total;
  }
  fout << answer << "\n";
  return 0;
}

