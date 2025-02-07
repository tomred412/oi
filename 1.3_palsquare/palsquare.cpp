/*
ID: dermotl1
LANG: C++
PROG: palsquare
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
  ofstream fout("palsquare.out");
  ifstream fin("palsquare.in");

  int B = 0;
  fin >> B;

  for (int i = 1; i <= 300; i++) {
    int square = i * i;
    char result[100];
    char squareInB[100];

    convert(i, B, result);
    convert(square, B, squareInB);

    if (palindromeCheck(squareInB) == true)
      fout << result << " " << squareInB << "\n";
  }
  return 0;
}
