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

cows cow;

bool compare(int a, int b) { return cow.output[a] < cow.output[b]; }

int main() {
  ofstream fout("pairup.out");
  ifstream fin("pairup.in");

  int n;
  fin >> n;

  for (int i = 0; i < n; i++) {
    int temp1, temp2;
    fin >> temp1 >> temp2;
    cow.counts.push_back(temp1);
    cow.output.push_back(temp2);
  }

  vector<int> temp(n);
  for (int i = 0; i < n; i++) {
    temp[i] = i;
  }
  sort(temp.begin(), temp.end(), compare);

  vector<int> sorted_o(n), sorted_c(n);
  for (int i = 0; i < n; i++) {
    sorted_o[i] = cow.output[temp[i]];
    sorted_c[i] = cow.counts[temp[i]];
  }

  cow.output = sorted_o;
  cow.counts = sorted_c;

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
