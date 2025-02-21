/*
ID: dermotl1
LANG: C++
PROG: runround
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool compute(int number) {
  vector<int> digits;
  int digit = 0;
  vector<bool> track(10, false);
  int num = number;

  while (num > 0) {
    digit = num % 10;
    if (!digit || track[digit]) return false;
    track[digit] = true;

    digits.push_back(digit);
    num /= 10;
  }

  reverse(digits.begin(), digits.end());

  vector<bool> saw(digits.size(), false);
  int watch = 0;      // where it is
  int digit_num = 0;  // how many numbers (it needs to be the number of digits
                      // because each is visited once)

  while (!saw[watch]) {
    saw[watch] = true;
    digit_num++;
    watch = (watch + digits[watch]) % digits.size();
  }
  if (digit_num == digits.size() && watch == 0) return true;
  return false;
}

int main() {
  ofstream fout("runround.out");
  ifstream fin("runround.in");

  int m;
  fin >> m;

  bool stop = false;
  int n = m + 1;

  while (!stop) {
    if (compute(n)) {
      stop = true;
      fout << n << "\n";
      return 0;
    }
    n++;
  }

  return 0;
}
