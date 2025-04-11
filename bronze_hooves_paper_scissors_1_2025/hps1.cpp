#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
// #include <bits/stdc++.h>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<char> > interact(n, vector<char>(n, ' '));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i; ++j) {
      if (j == i) {
        char temp;
        cin >> temp;
        interact[i][j] = 'D';
      } else {
        char temp;
        cin >> temp;
        interact[i][j] = temp;
        if (temp == 'W') {
          interact[j][i] = 'L';
        }
        if (temp == 'D') {
          interact[j][i] = 'D';
        }
        if (temp == 'L') {
          interact[j][i] = 'W';
        }
      }
    }
  }

  vector<int> results(m);

  for (int i = 0; i < m; ++i) {
    int s1;
    int s2;
    cin >> s1 >> s2;
    s1--;
    s2--;

    int answer = 0;

    for (int l = 0; l < n; l++) {
      if (interact[l][s1] == 'W' && interact[l][s2] == 'W') answer++;
    }

    int count = 0;

    for (int r = 0; r < n; r++) {
      if (interact[r][s1] == 'W' && interact[r][s2] == 'W') {
        count += n;
      } else {
        count += answer;
      }
    }
    results[i] = count;
  }
  for (int i = 0; i < results.size(); ++i) {
    cout << results[i] << "\n";
  }
  return 0;
}
