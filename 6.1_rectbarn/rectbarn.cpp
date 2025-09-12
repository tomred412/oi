/*
ID: dermotl1
LANG: C++
PROG: rectbarn
*/

#include <algorithm>
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
#include <utility>
#include <vector>

using namespace std;

int main() {
  ifstream fin("rectbarn.in");
  ofstream fout("rectbarn.out");
  int r, c, p;
  fin >> r >> c >> p;

  // 1 based
  vector<vector<int>> damaged(r + 1);
  for (int i = 0; i < p; ++i) {
    int x, y;
    fin >> x >> y;
    damaged[x].push_back(y);
  }

  vector<int> height(c + 2, 0);
  vector<int> position;
  int best = 0;

  for (int a = 1; a <= r; ++a) {
    for (int b = 1; b <= c; ++b) {
      height[b] += 1;
    }
    for (int i = 0; i < damaged[a].size(); ++i) {
      height[damaged[a][i]] = 0;
    }

    position.clear();
    height[c + 1] = 0;
    for (int b = 1; b <= c + 1; ++b) {
      int h = height[b];

      while (!position.empty() && height[position.back()] > h) {
        int position_here = position.back();
        position.pop_back();
        int height_testing_rectangle = height[position_here];
        int left;
        if (position.empty())
          left = 1;
        else
          left = position.back() + 1;
        int right = b - 1;
        int width = right - left + 1;
        int area = width * height_testing_rectangle;
        if (area > best) best = area;
      }
      position.push_back(b);
    }
  }
  fout << best << "\n";
  return 0;
}