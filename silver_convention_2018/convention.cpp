#include <bits/stdc++.h>

#include <fstream>
#include <set>
#include <string>
#include <vector>
using namespace std;

vector<int> cows;
int n, m, c;

bool search(int find) {
  int bus = 1;
  int first = cows[0];
  int pos = 0;
  for (int i = 1; i < n; i++) {
    if (i - pos >= c || cows[i] - first > find) {
      bus++;
      first = cows[i];
      pos = i;
    }
    if (bus > m) return false;
  }
  return true;
}

int main() {
  ofstream fout("convention.out");
  ifstream fin("convention.in");

  fin >> n >> m >> c;

  for (int i = 0; i < n; i++) {
    int temp;
    fin >> temp;
    cows.push_back(temp);
  }

  sort(cows.begin(), cows.end());
  int low = 0;
  int high = 1000000000;
  int a = high;

  while (low <= high) {
    int b = (low + high) / 2;
    if (search(b)) {
      a = b;
      high = b - 1;
    } else {
      low = b + 1;
    }
  }
  fout << a << "\n";

  return 0;
}
