/*
ID: dermotl1
LANG: C++
PROG: cryptcow
*/

#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

string original = "Begin the Escape execution at the Break of Dawn";
int answer = -1;

bool checkStartEnd(const string& check) {
  int n = check.size();
  int firstC = check.find('C');
  int firstO = check.find('O');
  int firstW = check.find('W');
  int lastO = check.rfind('O');
  int lastW = check.rfind('W');

  if (firstC == string::npos || lastW == string::npos) return false;

  if ((firstO != string::npos && firstC > firstO) ||
      (firstW != string::npos && firstC > firstW))
    return false;

  if (lastO != string::npos && lastW < lastO) return false;

  if (firstC > 0 && check.compare(0, firstC, original, 0, firstC) != 0)
    return false;

  int after = n - lastW - 1;
  if (after > 0 && check.compare(n - after, after, original,
                                 original.size() - after, after) != 0)
    return false;

  return true;
}

bool checkFragments(const string& check) {
  string temp;

  for (int i = 0; i < check.size(); ++i) {
    if (check[i] == 'C' || check[i] == 'O' || check[i] == 'W') {
      if (!temp.empty()) {
        if (original.find(temp) == string::npos) return false;
        temp.clear();
      }

    } else
      temp += check[i];
  }

  if (!temp.empty() && original.find(temp) == string::npos) return false;
  return true;
}

bool dfs(const string& check, int encryptions) {
  if (check == original) {
    answer = encryptions;
    return true;
  }

  if (check.size() < original.size()) return false;

  if (check.find('C') == string::npos || check.find('O') == string::npos ||
      check.find('W') == string::npos)
    return false;

  if (!checkStartEnd(check) || !checkFragments(check)) return false;

  vector<int> c, o, w;

  for (int i = 0; i < check.size(); ++i) {
    if (check[i] == 'C')
      c.push_back(i);
    else if (check[i] == 'O')
      o.push_back(i);
    else if (check[i] == 'W')
      w.push_back(i);
  }

  for (int ci = 0; ci < (int)c.size(); ci++) {
    for (int oj = 0; oj < (int)o.size(); oj++) {
      int c_pos = c[ci];
      int o_pos = o[oj];
      if (!(c_pos < o_pos)) continue;

      for (int wk = (int)w.size() - 1; wk >= 0; wk--) {
        int w_pos = w[wk];
        if (!(o_pos < w_pos)) continue;

        string t;
        t.reserve(check.size() - 3);
        t.append(check, 0, c_pos);                             // left
        t.append(check, o_pos + 1, w_pos - o_pos - 1);         // mid2
        t.append(check, c_pos + 1, o_pos - c_pos - 1);         // mid1
        t.append(check, w_pos + 1, check.size() - w_pos - 1);  // right

        if (dfs(t, encryptions + 1)) return true;
      }
    }
  }
  return false;
}

int main() {
  ifstream fin("cryptcow.in");
  ofstream fout("cryptcow.out");

  string check;
  getline(fin, check);

  int n = check.size();
  int c_count = 0;
  int o_count = 0;
  int w_count = 0;
  int first[256] = {0};
  int target[256] = {0};

  for (auto it : check) {
    if (it == 'C')
      ++c_count;
    else if (it == 'O')
      ++o_count;
    else if (it == 'W')
      ++w_count;
    else
      ++first[it];
  }

  for (auto it : original) {
    ++target[it];
  }

  if (c_count != o_count || o_count != c_count ||
      n - 3 * c_count != original.size()) {
    fout << "0 0\n";
    return 0;
  }

  for (int i = 0; i < 256; ++i) {
    if (i == 'C' || i == 'O' || i == 'W') continue;
    if (first[i] != target[i]) {
      fout << "0 0\n";
      return 0;
    }
  }

  if (c_count == 0) {
    fout << (check == original ? "1 0\n" : "0 0\n");
    return 0;
  }

  if (dfs(check, 0)) {
    fout << "1 " << answer << "\n";
  } else {
    fout << "0 0\n";
  }

  return 0;
}