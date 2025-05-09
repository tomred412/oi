/*
ID: dermotl1
LANG: C++
PROG: fence9
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int gcd(int a, int b) {
  while (b != 0) {
    int r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int main() {
  ifstream fin("fence9.in");
  ofstream fout("fence9.out");

  int n, m, p;
  fin >> n >> m >> p;

  int double_area = p * m;

  int boundary_1 = gcd(n, m);
  int boundary_2 = gcd(abs(p - n), m);
  int boundary_3 = p;
  int total_boundary = boundary_1 + boundary_2 + boundary_3;

  int interior = (double_area - total_boundary + 2) / 2;

  fout << interior << "\n";
}