/*
ID: dermotl1
LANG: C++
PROG: crypt1
*/

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

// num is a lot of digits, so check if those digits are in the set, also check
// if it's 3 and 4 in the multiplying
bool works(int num, bool digit_set[], int required_length) {
  int length = 0;
  while (num > 0) {
    int digit = num % 10;
    if (!digit_set[digit]) {
      return false;
    }
    num /= 10;
    length++;
  }
  return length == required_length;
}

int main() {
  ifstream fin("crypt1.in");
  ofstream fout("crypt1.out");

  int N = 0;
  fin >> N;

  int digits[10];      // this stores intial
  bool digit_set[10];  // this stores the number so digit_set[i], and then check
                       // if i is in digits array

  for (int i = 0; i < 10; ++i) {
    digit_set[i] = false;
  }

  for (int i = 0; i < N; i++) {
    fin >> digits[i];
    digit_set[digits[i]] = true;  // make the numbers that are in the original
                                  // input true in digit_set array
  }

  int total = 0;  // solutions

  for (int i = 0; i < N; i++) {
    if (digits[i] == 0) continue;  // no leading zeroes
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        int ijk = digits[i] * 100 + digits[j] * 10 +
                  digits[k];  // how a 3 digit number is formed

        for (int a = 0; a < N; a++) {
          if (digits[a] == 0) continue;  // no leading zeroes
          for (int b = 0; b < N; b++) {
            int ab =
                digits[a] * 10 + digits[b];  // how a 2 digit number is formed
            int partial1 = ijk * (ab % 10);
            int partial2 = ijk * (ab / 10);
            int final = partial1 + 10 * partial2;

            if (works(partial1, digit_set, 3) &&
                works(partial2, digit_set, 3) && works(final, digit_set, 4))
              total++;
          }
        }
      }
    }
  }
  fout << total << "\n";
  return 0;
}
