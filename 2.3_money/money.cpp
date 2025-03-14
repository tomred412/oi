/*
ID: dermotl1
LANG: C++
PROG: money
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

long long arr[10001];
int coins[25];

int main() {
  ifstream fin("money.in");
  ofstream fout("money.out");

  int v, n;
  fin >> v >> n;

  for (int i = 0; i < v; i++) {
    fin >> coins[i];
  }
  arr[0] = 1;

  for (int i = 0; i < v; i++) {
    int a = coins[i];
    for (int j = a; j <= n; j++) {
      arr[j] = arr[j - a] + arr[j];
    }
  }
  fout << arr[n] << "\n";
  return 0;
}
