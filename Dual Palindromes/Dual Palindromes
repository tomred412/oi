/*
ID: dermotl1
LANG: C++
PROG: dualpal
*/

#include <string.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void convert(int n, int B, char* result) {
  int l = 0;

  while (n > 0) {
    int remainder = n % B;
    n /= B;

    if (remainder < 10) {
      result[l++] = '0' + remainder;
    } else {
      result[l++] = 'A' + (remainder - 10);
    }
  }

  for (int i = 0; i < l / 2; i++) {
    swap(result[i], result[l - 1 - i]);
  }

  result[l] = '\0';
}

bool palindromeCheck(char* check) {
  int length = strlen(check);

  for (int i = 0; i < length / 2; i++) {
    if (check[i] != check[length - 1 - i]) return false;
  }

  return true;
}

int main() {
  ofstream fout("dualpal.out");
  ifstream fin("dualpal.in");

  int N, S;
  fin >> N >> S;

  int found_numbers = 0;
  int check = S + 1;

  while (found_numbers < N) {
    int number_of_bases = 0;
    char result_in_base[100];

    for (int i = 2; i <= 10; i++) {
      convert(check, i, result_in_base);

      if (palindromeCheck(result_in_base) == true) {
        number_of_bases++;
      }

      if (number_of_bases >= 2) {
        fout << check << "\n";
        found_numbers++;
        break;
      }
    }
    check++;
  }

  return 0;
}
