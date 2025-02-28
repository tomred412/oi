/*
ID: dermotl1
LANG: C++
PROG: prefix
*/

#include <fstream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream fin("prefix.in");
  ofstream fout("prefix.out");

  vector<vector<char> > primitives;
  vector<char> s;
  bool tracker[200000] = {};
  tracker[0] = true;
  char temp[11];

  while (fin >> temp) {
    if (temp[0] == '.') break;
    vector<char> temp_array;
    for (int i = 0; temp[i] != '\0'; i++) {
      temp_array.push_back(temp[i]);
    }
    primitives.push_back(temp_array);
  }

  char a;

  while (fin >> a) {
    s.push_back(a);
  }

  int max = 0;

  for (int i = 0; i < s.size(); i++) {
    if (!tracker[i]) continue;

    for (int j = 0; j < primitives.size(); j++) {
      int length = primitives[j].size();
      if (i + length > s.size()) continue;
      bool works = true;
      for (int k = 0; k < length; k++) {
        if (s[i + k] != primitives[j][k]) {
          works = false;
          break;
        }
      }
      if (works) {
        tracker[i + length] = true;
        if (max < i + length) max = i + length;
      }
    }
  }
  fout << max << "\n";
  return 0;
}
