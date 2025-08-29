/*
ID: dermotl1
LANG: C++
PROG: twofive
*/

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

char temp[26];
int letters_row[6];
long long finish_ways[6][6][6][6][6];

long long countHere(char i) {
  if (i > 'Y') return 1;
  if (finish_ways[letters_row[1]][letters_row[2]][letters_row[3]]
                 [letters_row[4]][letters_row[5]] != -1)
    return finish_ways[letters_row[1]][letters_row[2]][letters_row[3]]
                      [letters_row[4]][letters_row[5]];

  long long count = 0;
  for (int j = 1; j <= 5; ++j) {
    if (letters_row[j] < letters_row[j - 1]) {
      int pos = (j - 1) * 5 + letters_row[j];

      if (temp[pos] == ' ' || temp[pos] == i) {
        letters_row[j]++;
        count += countHere(i + 1);
        letters_row[j]--;
      }
    }
  }
  finish_ways[letters_row[1]][letters_row[2]][letters_row[3]][letters_row[4]]
             [letters_row[5]] = count;
  return count;
}

void constructGrid(long long m, char constructing[26]) {
  for (int i = 0; i < 25; ++i) {
    temp[i] = ' ';
  }

  fill(letters_row, letters_row + 6, 0);
  letters_row[0] = 5;

  long long skip = 0;
  for (int i = 0; i < 25; ++i) {
    for (char j = 'A'; j <= 'Y'; ++j) {
      temp[i] = j;

      fill(letters_row, letters_row + 6, 0);
      letters_row[0] = 5;

      for (int a = 0; a < 6; ++a) {
        for (int b = 0; b < 6; ++b) {
          for (int c = 0; c < 6; ++c) {
            for (int d = 0; d < 6; ++d) {
              for (int e = 0; e < 6; ++e) {
                finish_ways[a][b][c][d][e] = -1;
              }
            }
          }
        }
      }
      finish_ways[5][5][5][5][5] = 1;

      long long count = countHere('A');
      if (skip + count < m) {
        skip += count;
      } else {
        constructing[i] = j;
        break;
      }
    }
  }
}

long long findNumber(char input[26]) {
  for (int i = 0; i < 25; ++i) {
    temp[i] = ' ';
  }

  fill(letters_row, letters_row + 6, 0);
  letters_row[0] = 5;

  long long count = 1;
  for (int i = 0; i < 25; ++i) {
    for (char j = 'A'; j < input[i]; ++j) {
      temp[i] = j;

      fill(letters_row, letters_row + 6, 0);
      letters_row[0] = 5;

      for (int a = 0; a < 6; ++a) {
        for (int b = 0; b < 6; ++b) {
          for (int c = 0; c < 6; ++c) {
            for (int d = 0; d < 6; ++d) {
              for (int e = 0; e < 6; ++e) {
                finish_ways[a][b][c][d][e] = -1;
              }
            }
          }
        }
      }
      finish_ways[5][5][5][5][5] = 1;

      count += countHere('A');
    }
    temp[i] = input[i];
  }
  return count;
}

int main() {
  ifstream fin("twofive.in");
  ofstream fout("twofive.out");

  for (int a = 0; a < 6; ++a) {
    for (int b = 0; b < 6; ++b) {
      for (int c = 0; c < 6; ++c) {
        for (int d = 0; d < 6; ++d) {
          for (int e = 0; e < 6; ++e) {
            finish_ways[a][b][c][d][e] = -1;
          }
        }
      }
    }
  }

  char type;
  fin >> type;
  if (type == 'N') {
    long long m;
    fin >> m;
    char ans[26];
    constructGrid(m, ans);
    for (int i = 0; i < 25; ++i) {
      fout << ans[i];
    }
    fout << "\n";
  } else {
    char input[26];
    fin >> input;
    fout << findNumber(input) << "\n";
  }

  return 0;
}