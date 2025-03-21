/*
ID: dermotl1
LANG: C++
PROG: fracdec
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ifstream fin("fracdec.in");
  ofstream fout("fracdec.out");

  int n, d;
  fin >> n >> d;

  vector<int> decimal_digit;         // stores each individual decimal digit
  vector<int> remainder_pos(d, -1);  // stores the position of the remainder

  int integer = n / d;
  fout << integer;
  int remainder = n % d;

  int count = to_string(integer).length();

  if (remainder == 0) {
    fout << ".0\n";
    return 0;
  }
  fout << ".";
  count++;

  int repeat_start = -1;
  for (int i = 0; remainder != 0; i++) {
    if (remainder_pos[remainder] != -1) {
      repeat_start = remainder_pos[remainder];
      break;
    }
    remainder_pos[remainder] = i;
    remainder *= 10;
    decimal_digit.push_back(remainder / d);
    remainder %= d;
  }

  for (int i = 0; i < decimal_digit.size(); i++) {
    if (i == repeat_start) {
      fout << "(";
      count++;
    }
    fout << decimal_digit[i];
    count++;
    if (count == 76) {
      fout << "\n";
      count = 0;  // Reset the counter after each line break
    }
  }

  if (repeat_start != -1) fout << ")";
  fout << "\n";
  return 0;
}
