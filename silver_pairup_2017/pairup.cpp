// #include <bits/stdc++.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct cows {
  vector<int> output;
  vector<int> counts;
};

int main() {
  ofstream fout("pairup.out");
  ifstream fin("pairup.in");

  cows cow;

  int n;
  fin >> n;

  for (int i = 0; i < n; i++) {
    int temp1, temp2;
    fin >> temp1 >> temp2;
    cow.counts.push_back(temp1);
    cow.output.push_back(temp2);
  }
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (cow.output[j] > cow.output[j + 1]) {
        swap(cow.output[j], cow.output[j + 1]);
        swap(cow.counts[j], cow.counts[j + 1]);
      }
    }
  }
  int maxi = 0;

  for (int i = 0, j = n - 1; i <= j;) {
    int pairing = min(cow.counts[i], cow.counts[j]);
    if (i == j) pairing = pairing / 2;

    maxi = max(maxi, cow.output[i] + cow.output[j]);

    cow.counts[i] = cow.counts[i] - pairing;
    cow.counts[j] = cow.counts[j] - pairing;

    if (cow.counts[i] == 0) i++;
    if (cow.counts[j] == 0) j--;
  }
  fout << maxi << "\n";
  return 0;
}
