/*
ID: dermotl1
LANG: C++
PROG: ratios
*/

#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
  ifstream fin("ratios.in");
  ofstream fout("ratios.out");

  int goal[3];        // goal ratio
  int mixture[3][3];  // ratios, //1st = the mixture number, 2nd = mixture type

  fin >> goal[0] >> goal[1] >> goal[2];

  for (int i = 0; i < 3; ++i) {
    fin >> mixture[i][0] >> mixture[i][1] >> mixture[i][2];
  }

  int best_1, best_2, best_3, best_multiple = 0;
  int min_sum = numeric_limits<int>::max();

  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      for (int p = 0; p < 100; ++p) {
        if (i + j + p == 0) continue;
        int sum[3];  // calculate total of each part
        sum[0] = i * mixture[0][0] + j * mixture[1][0] + p * mixture[2][0];
        sum[1] = i * mixture[0][1] + j * mixture[1][1] + p * mixture[2][1];
        sum[2] = i * mixture[0][2] + j * mixture[1][2] + p * mixture[2][2];

        int multiply = -1;
        bool correct = true;

        for (int q = 0; q < 3; ++q) {
          if (goal[q] == 0) {
            if (sum[q] != 0) correct = false;
            continue;
          } else {
            if (sum[q] % goal[q] != 0)
              correct = false;
            else {
              int new_multiply = sum[q] / goal[q];
              if (multiply == -1)
                multiply = new_multiply;
              else if (multiply != new_multiply)
                correct = false;
            }
          }
        }
        if (correct && multiply > 0 && ((i + j + p) < min_sum)) {
          min_sum = i + j + p;
          best_1 = i;
          best_2 = j;
          best_3 = p;
          best_multiple = multiply;
        }
      }
    }
  }

  if (min_sum == numeric_limits<int>::max()) {
    fout << "NONE\n";
  } else {
    fout << best_1 << " " << best_2 << " " << best_3 << " " << best_multiple
         << "\n";
  }

  return 0;
}
