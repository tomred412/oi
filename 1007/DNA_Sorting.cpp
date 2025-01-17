#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int invertNumber(string s) {
  int inversions = 0;
  for (int i = 0; i < s.size() - 1; i++) {
    for (int j = i + 1; j < s.size(); j++) {
      if (s[i] > s[j]) {
        inversions++;
      }
    }
  }
  return inversions;
}

int main() {
  int n = 0;
  int m = 0;
  cin >> n >> m;

  string dna[100]; 
  int inversions[100];

  for (int i = 0; i < m; ++i) {
    cin >> dna[i];
    inversions[i] = invertNumber(dna[i]);
  }

  for (int i = 0; i < m - 1; ++i) {
    for (int j = 0; j < m - i - 1; ++j) {
      if (inversions[j] > inversions[j + 1]) {
        swap(inversions[j], inversions[j + 1]);
        swap(dna[j], dna[j + 1]); 
      }
    }
  }

  for (int i = 0; i < m; ++i) {
    cout << dna[i] << "\n";
  }

  return 0;
}
