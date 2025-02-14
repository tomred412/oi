/*
ID: dermotl1
LANG: C++
PROG: frac1
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct fraction {
  int numerator;
  int denominator;
};

bool compare(fraction a, fraction b) {
  return (double)a.numerator / a.denominator <
         (double)b.numerator / b.denominator;
}

int gcd(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

int main() {
  ofstream fout("frac1.out");
  ifstream fin("frac1.in");

  int n = 0;
  fin >> n;

  vector<fraction> fractions;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      if (gcd(j, i) == 1) {  // it must be reduced
        fraction p;
        p.numerator = j;
        p.denominator = i;
        fractions.push_back(p);
      }
    }
  }

  sort(fractions.begin(), fractions.end(), compare);

  for (int i = 0; i < fractions.size(); i++) {
    fout << fractions[i].numerator << "/" << fractions[i].denominator << "\n";
  }

  return 0;
}
