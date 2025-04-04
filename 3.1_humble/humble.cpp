/*
ID: dermotl1
LANG: C++
PROG: humble
*/

#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
  ifstream fin("humble.in");
  ofstream fout("humble.out");

  int k, n;
  fin >> k >> n;

  vector<int> primes(k);
  for (int i = 0; i < k; ++i) {
    fin >> primes[i];
  }
  vector<long long> humble(n + 1);
  humble[0] = 1;

  vector<int> index(k, 0);

  for (int i = 1; i <= n; ++i) {
    long long next = LONG_MAX;

    for (int j = 0; j < k; ++j) {
      long long possible = (long long)primes[j] * humble[index[j]];
      if (possible < next) {
        next = possible;
      }
    }
    humble[i] = next;

    for (int j = 0; j < k; ++j) {
      if ((long long)primes[j] * humble[index[j]] == next) {
        index[j]++;
      }
    }
  }
  fout << humble[n] << "\n";
  return 0;
}
