#include <bits/stdc++.h>
using namespace std;

int main() {
  ofstream fout("diamond.out");
  ifstream fin("diamond.in");

  int n, k;
  vector<int> array;
  fin >> n >> k;

  for (int i = 0; i < n; i++) {
    int temp;
    fin >> temp;
    array.push_back(temp);
  }
  sort(array.begin(), array.end());

  int maxi = 0;

  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (array[j] - array[i] <= k) {
        maxi = max(maxi, j - i + 1);
      }
    }
  }

  fout << maxi << "\n";
  return 0;
}
