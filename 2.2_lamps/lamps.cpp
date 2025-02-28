/*
ID: dermotl1
LANG: C++
PROG: lamps
*/
#include <fstream>
#include <set>
#include <vector>
using namespace std;

void buttonPress(vector<int>& lamps, int button) {
  if (button == 1) {
    for (int i = 0; i < 6; i++) {  // all
      lamps[i] = 1 - lamps[i];
    }
  }
  if (button == 2) {
    for (int i = 0; i < 6; i = i + 2) {  // odd
      lamps[i] = 1 - lamps[i];
    }
  }
  if (button == 3) {
    for (int i = 1; i < 6; i += 2) {
      lamps[i] = 1 - lamps[i];  // even
    }
  }
  if (button == 4) {
    for (int i = 0; i < 6; i = i + 3) {
      lamps[i] = 1 - lamps[i];  // 1 mod 3
    }
  }
}
bool check(vector<int> lamps, vector<int> on_array, vector<int> off_array) {
  for (int i = 0; i < on_array.size(); i++) {
    if (lamps[on_array[i] % 6] != 1) return false;
  }
  for (int i = 0; i < off_array.size(); i++) {
    if (lamps[off_array[i] % 6] != 0) return false;
  }
  return true;
}
int main() {
  ofstream fout("lamps.out");
  ifstream fin("lamps.in");
  int n, c, temp;
  vector<int> on_array;
  vector<int> off_array;

  fin >> n >> c;
  while (true) {
    fin >> temp;
    if (temp == -1) break;
    on_array.push_back(temp - 1);
  }
  while (true) {
    fin >> temp;
    if (temp == -1) break;
    off_array.push_back(temp - 1);
  }
  set<vector<int> > result;
  for (int i = 0; i < 16;
       i++) {  // 2^4, possibilities; code like in the castle, 0000 = 0, 0001 =
               // 1, 0010 = 2, 0100 = 3, 1000 = 4
    vector<int> lamps(6, 1);
    int num = 0;
    if (i % 2 != 0) {
      buttonPress(lamps, 1);
      num++;
    }
    if ((i / 2) % 2 != 0) {
      buttonPress(lamps, 2);
      num++;
    }
    if ((i / 4) % 2 != 0) {
      buttonPress(lamps, 3);
      num++;
    }
    if ((i / 8) % 2 != 0) {
      buttonPress(lamps, 4);
      num++;
    }
    if (num > c) continue;
    if (check(lamps, on_array, off_array)) {
      vector<int> temporary;
      for (int i = 0; i < n; i++) {
        temporary.push_back(lamps[i % 6]);
      }
      result.insert(temporary);
    }
  }
  if (result.empty()) fout << "IMPOSSIBLE\n";
  for (const auto& item : result) {
    for (const auto& thing : item) {
      fout << thing;
    }
    fout << "\n";
  }
  return 0;
}
