/*
ID: dermotl1
LANG: C++
PROG: zerosum
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n;
int signs[9];  // 1 = +, -1 = -, 0 = ' '
ifstream fin("zerosum.in");
ofstream fout("zerosum.out");

bool solve() {
  int sum = 0;
  int num = 1;
  int sign = 1;
  for (int i = 2; i <= n; i++) {
    if (signs[i - 2] == 0) {
      num = num * 10 + i;
    } else {
      sum = sign * num + sum;
      num = i;
      sign = signs[i - 2];
    }
  }
  sum = sign * num + sum;
  if (sum == 0)
    return true;
  else
    return false;
}

void generate(int a) {
  if (a == n - 1) {
    if (solve()) {
      fout << "1";
      for (int i = 2; i <= n; i++) {
        if (signs[i - 2] == 1) fout << "+";
        if (signs[i - 2] == -1) fout << "-";
        if (signs[i - 2] == 0) fout << " ";
        fout << i;
      }
      fout << "\n";
    }
    return;
  }
  signs[a] = 0;
  generate(a + 1);

  signs[a] = 1;
  generate(a + 1);

  signs[a] = -1;
  generate(a + 1);
}

int main() {
  fin >> n;

  generate(0);
  return 0;
}
