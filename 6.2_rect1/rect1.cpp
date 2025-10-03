/*
ID: dermotl1
LANG: C++
PROG: rect1
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
#include <utility>
#include <vector>

using namespace std;

struct rectangle {
  int x1, y1, x2, y2;  // lower left + upper right
  int color;
};

bool overlaps(rectangle a, rectangle b) {
  if ((max(a.x1, b.x1) < min(a.x2, b.x2)) && max(a.y1, b.y1) < min(a.y2, b.y2))
    return true;

  return false;
}

int main() {
  ifstream fin("rect1.in");
  ofstream fout("rect1.out");

  int a, b, n;
  fin >> a >> b >> n;

  vector<rectangle> visible;
  visible.push_back({0, 0, a, b, 1});

  for (int i = 0; i < n; ++i) {
    rectangle temp;
    fin >> temp.x1 >> temp.y1 >> temp.x2 >> temp.y2 >> temp.color;

    vector<rectangle> next;

    for (auto it : visible) {
      if (!overlaps(it, temp)) {
        next.push_back(it);
        continue;
      }

      int overlap_left_x = max(it.x1, temp.x1);
      int overlap_right_x = min(it.x2, temp.x2);
      int overlap_bottom_y = max(it.y1, temp.y1);
      int overlap_top_y = min(it.y2, temp.y2);

      if (it.x1 < overlap_left_x)
        next.push_back({it.x1, it.y1, overlap_left_x, it.y2, it.color});
      if (overlap_right_x < it.x2)
        next.push_back({overlap_right_x, it.y1, it.x2, it.y2, it.color});
      if (it.y1 < overlap_bottom_y)
        next.push_back({overlap_left_x, it.y1, overlap_right_x,
                        overlap_bottom_y, it.color});
      if (overlap_top_y < it.y2)
        next.push_back(
            {overlap_left_x, overlap_top_y, overlap_right_x, it.y2, it.color});
    }
    next.push_back(temp);
    visible.swap(next);
  }

  vector<long long> area(2502, 0);
  for (auto it : visible) {
    long long w = (long long)it.x2 - it.x1;
    long long h = (long long)it.y2 - it.y1;
    if (w > 0 && h > 0) area[it.color] += w * h;
  }

  for (int i = 1; i <= 2500; ++i) {
    if (area[i] > 0) fout << i << " " << area[i] << "\n";
  }

  return 0;
}