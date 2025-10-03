/*
ID: dermotl1
LANG: C++
PROG: packrec
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
  int w, h;
};

vector<rectangle> recs(4);
set<pair<int, int>> answer;
int min_area = numeric_limits<int>::max();

bool sortRectangle(const rectangle& a, const rectangle& b) {
  if (a.w != b.w) return a.w < b.w;
  return a.h < b.h;
}

void checkSolution(int width, int height) {
  int area = width * height;

  if (area < min_area) {
    min_area = area;
    answer.clear();

    pair<int, int> temp;
    temp.first = min(width, height);
    temp.second = max(width, height);
    answer.insert(temp);
  } else if (area == min_area) {
    pair<int, int> temp;
    temp.first = min(width, height);
    temp.second = max(width, height);
    answer.insert(temp);
  }
}

void enumerateCases(vector<rectangle> recs) {
  // 1 basic layout (side by side)
  checkSolution(recs[0].w + recs[1].w + recs[2].w + recs[3].w,
                max({recs[0].h, recs[1].h, recs[2].h, recs[3].h}));

  // 2 basic layout (3 on bottom 1 on top)
  checkSolution(max(recs[0].w, (recs[1].w + recs[2].w + recs[3].w)),
                (max({recs[1].h, recs[2].h, recs[3].h}) + recs[0].h));

  // 3 basic layout (1 on top of 2, with another on the side)
  checkSolution((max(recs[1].w + recs[2].w, recs[0].w) + recs[3].w),
                max((max(recs[1].h, recs[2].h) + recs[0].h), recs[3].h));

  // 4 and 5 basic layout (1 over another, next to 2)
  checkSolution((max(recs[0].w, recs[1].w) + recs[2].w + recs[3].w),
                (max(max(recs[0].h + recs[1].h, recs[2].h), recs[3].h)));

  // 6 very complicated L (cutout) thing
  int temp_w = max(recs[0].w + recs[1].w, max(recs[2].w, recs[3].w));
  int temp_h = max(recs[0].h + recs[2].h, recs[1].h + recs[3].h);

  if (recs[0].h > recs[1].h) {
    temp_w = max(temp_w, recs[0].w + recs[3].w);

    if (recs[0].h - recs[1].h < recs[3].h) {
      temp_w = max(temp_w, recs[2].w + recs[3].w);
    }
  } else {
    temp_w = max(temp_w, recs[1].w + recs[2].w);
    if (recs[1].h - recs[0].h < recs[2].h) {
      temp_w = max(temp_w, recs[2].w + recs[3].w);
    }
  }
  checkSolution(temp_w, temp_h);
}

int main() {
  ifstream fin("packrec.in");
  ofstream fout("packrec.out");

  for (int i = 0; i < 4; ++i) {
    fin >> recs[i].w >> recs[i].h;
  }

  vector<rectangle> permuations = recs;
  sort(permuations.begin(), permuations.end(), sortRectangle);

  // first
  for (int i1 = 0; i1 < 2; ++i1) {
    for (int i2 = 0; i2 < 2; ++i2) {
      for (int i3 = 0; i3 < 2; ++i3) {
        for (int i4 = 0; i4 < 2; ++i4) {
          vector<rectangle> temp = permuations;
          if (i1) {
            int x = temp[0].w;
            temp[0].w = temp[0].h;
            temp[0].h = x;
          }
          if (i2) {
            int x = temp[1].w;
            temp[1].w = temp[1].h;
            temp[1].h = x;
          }
          if (i3) {
            int x = temp[2].w;
            temp[2].w = temp[2].h;
            temp[2].h = x;
          }
          if (i4) {
            int x = temp[3].w;
            temp[3].w = temp[3].h;
            temp[3].h = x;
          }
          enumerateCases(temp);
        }
      }
    }
  }

  // next
  // probably use do while actually...
  while (
      next_permutation(permuations.begin(), permuations.end(), sortRectangle)) {
    for (int i1 = 0; i1 < 2; ++i1) {
      for (int i2 = 0; i2 < 2; ++i2) {
        for (int i3 = 0; i3 < 2; ++i3) {
          for (int i4 = 0; i4 < 2; ++i4) {
            vector<rectangle> temp = permuations;
            if (i1) {
              int x = temp[0].w;
              temp[0].w = temp[0].h;
              temp[0].h = x;
            }
            if (i2) {
              int x = temp[1].w;
              temp[1].w = temp[1].h;
              temp[1].h = x;
            }
            if (i3) {
              int x = temp[2].w;
              temp[2].w = temp[2].h;
              temp[2].h = x;
            }
            if (i4) {
              int x = temp[3].w;
              temp[3].w = temp[3].h;
              temp[3].h = x;
            }
            enumerateCases(temp);
          }
        }
      }
    }
  }

  fout << min_area << "\n";
  for (auto it : answer) {
    fout << it.first << " " << it.second << "\n";
  }

  return 0;
}