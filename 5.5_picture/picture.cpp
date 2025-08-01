/*
ID: dermotl1
LANG: C++
PROG: picture
*/

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct snapshot {  // a snapshot of the bottom to top scanning
  int y, x1, x2;
  bool is_top_part;  // true = top, false = bottom (start)
};

bool Compare(snapshot a, snapshot b) {
  if (a.y != b.y) return a.y < b.y;
  if (a.is_top_part == false &&
      b.is_top_part == true)  // prioritize bottom (start)
    return true;
  else
    return false;
}

int main() {
  ifstream fin("picture.in");
  ofstream fout("picture.out");

  int n;
  fin >> n;
  vector<snapshot> snapshots;
  vector<int> x_coords;  // save resources

  for (int i = 0; i < n; ++i) {
    int x1, y1, x2, y2;
    fin >> x1 >> y1 >> x2 >> y2;

    snapshot temp;
    temp.y = y1;
    temp.x1 = x1;
    temp.x2 = x2;
    temp.is_top_part = false;
    snapshots.push_back(temp);

    temp.is_top_part = true;
    temp.y = y2;
    snapshots.push_back(temp);

    x_coords.push_back(x1);
    x_coords.push_back(x2);
  }

  sort(snapshots.begin(), snapshots.end(), Compare);

  sort(x_coords.begin(), x_coords.end());  // delete duplicates
  auto last_pos = unique(x_coords.begin(), x_coords.end());
  x_coords.erase(last_pos, x_coords.end());

  if (x_coords.size() <= 1) {
    fout << "0\n";
    return 0;
  }

  vector<int> rectangles_covering_x(x_coords.size(), 0);
  int total_perimeter = 0;
  long long current_boundary = 0;  // this is the current intersections
  int current_intersections =
      0;  // how many total intersections (dont count if together)
  int last_y = snapshots[0].y;

  for (snapshot s : snapshots) {
    int gap = s.y - last_y;
    total_perimeter += 2 * current_intersections * gap;  // vertical

    auto pos1 = lower_bound(x_coords.begin(), x_coords.end(), s.x1);
    int left_x = pos1 - x_coords.begin();
    auto pos2 = lower_bound(x_coords.begin(), x_coords.end(), s.x2);
    int right_x = pos2 - x_coords.begin();

    for (int i = left_x; i < right_x; ++i) {
      if (s.is_top_part == false)
        rectangles_covering_x[i]++;
      else
        rectangles_covering_x[i]--;
    }

    long long new_boundary = 0;
    int new_intersections = 0;
    bool inside = false;

    for (int i = 0; i < x_coords.size() - 1; ++i) {  // intervals, not x
      if (rectangles_covering_x[i] > 0) {
        new_boundary += x_coords[i + 1] - x_coords[i];
        if (!inside) {
          new_intersections++;
          inside = true;
        }
      } else {
        inside = false;
      }
    }
    total_perimeter += abs(new_boundary - current_boundary);
    current_boundary = new_boundary;
    current_intersections = new_intersections;
    last_y = s.y;
  }

  fout << total_perimeter << "\n";

  return 0;
}