/*
ID: dermotl1
LANG: C++
PROG: hidden
*/

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
  ifstream fin("hidden.in");
  ofstream fout("hidden.out");

  int l;
  char password[200002];
  fin >> l;

  char temp;
  int length = 0;
  while (length < l && fin >> temp) {
    password[length] = temp;
    length++;
  }

  for (int i = 0; i < l; i++) {
    password[i + l] = password[i];
  }

  int memory[200002];
  memset(memory, -1, sizeof(memory));

  int best = 0;
  for (int i = 1; i < 2 * l; ++i) {
    int challenge = memory[i - best - 1];

    while (challenge != -1 && password[i] != password[challenge + best + 1]) {
      if (password[i] < password[challenge + best + 1]) {
        best = i - challenge - 1;
      }
      challenge = memory[challenge];
    }
    if (challenge == -1 && password[best] != password[i]) {
      if (password[i] < password[best]) {
        best = i;
      }
      memory[i - best] = -1;
    } else {
      memory[i - best] = challenge + 1;
    }
  }

  fout << best % l << "\n";

  return 0;
}