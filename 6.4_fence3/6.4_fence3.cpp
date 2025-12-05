/*
ID: dermotl1
LANG: C++
PROG: fence3
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

struct fence {
  double x1, y1, x2, y2;
  double min_x, min_y;
  double max_x, max_y;
};

int f;
fence fences[155];

double distanceToFence(double x, double y, const fence &e) {
  double nx = x;
  double ny = y;
  if (nx < e.min_x) nx = e.min_x;
  if (nx > e.max_x) nx = e.max_x;

  if (ny < e.min_y) ny = e.min_y;
  if (ny > e.max_y) ny = e.max_y;

  double dx = x - nx;
  double dy = y - ny;

  return sqrt(dx * dx + dy * dy);
}

double totalDistance(double x, double y) {
  double answer = 0.0;
  for (int i = 0; i < f; ++i) {
    answer += distanceToFence(x, y, fences[i]);
  }
  return answer;
}

int main() {
  ifstream fin("fence3.in");
  ofstream fout("fence3.out");

  fin >> f;

  double minimum_x = numeric_limits<double>::infinity();
  double minimum_y = minimum_x;
  double maximum_x = -numeric_limits<double>::infinity();
  double maximum_y = maximum_x;

  for (int i = 0; i < f; ++i) {
    fin >> fences[i].x1 >> fences[i].y1 >> fences[i].x2 >> fences[i].y2;

    fences[i].min_x = min(fences[i].x1, fences[i].x2);
    fences[i].max_x = max(fences[i].x1, fences[i].x2);
    fences[i].min_y = min(fences[i].y1, fences[i].y2);
    fences[i].max_y = max(fences[i].y1, fences[i].y2);

    if (fences[i].min_x < minimum_x) minimum_x = fences[i].min_x;
    if (fences[i].max_x > maximum_x) maximum_x = fences[i].max_x;
    if (fences[i].min_y < minimum_y) minimum_y = fences[i].min_y;
    if (fences[i].max_y > maximum_y) maximum_y = fences[i].max_y;
  }

  if (minimum_x < 0) minimum_x = 0;
  if (minimum_y < 0) minimum_y = 0;
  if (maximum_x > 100) maximum_x = 100;
  if (maximum_y > 100) maximum_y = 100;

  double best_x = (minimum_x + maximum_x) * 0.5;
  double best_y = (minimum_y + maximum_y) * 0.5;
  double best_value = totalDistance(best_x, best_y);

  double width = max(maximum_x - minimum_x, maximum_y - minimum_y);
  if (width == 0) width = 100.0;

  int grid = 5;
  for (int x = 0; x < grid; ++x) {  // descent
    for (int y = 0; y < grid; ++y) {
      double start_x = minimum_x + (maximum_x - minimum_x) * (x + 0.5) /
                                       grid;  // center of each division
      double start_y = minimum_y + (maximum_y - minimum_y) * (y + 0.5) / grid;

      double current_x = start_x;
      double current_y = start_y;
      double current_value = totalDistance(current_x, current_y);
      double descent = width;

      while (descent > 0.001) {
        bool better = false;

        for (int dx = -1; dx <= 1; dx++) {
          for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;

            double nx = current_x + dx * descent;
            double ny = current_y + dy * descent;

            if (nx < minimum_x) nx = minimum_x;
            if (nx > maximum_x) nx = maximum_x;
            if (ny < minimum_y) ny = minimum_y;
            if (ny > maximum_y) ny = maximum_y;

            double val = totalDistance(nx, ny);
            if (val + 1e-9 < current_value) {
              current_value = val;
              current_x = nx;
              current_y = ny;
              better = true;
            }
          }
        }
        if (!better) descent *= 0.5;
      }
      if (current_value < best_value) {
        best_value = current_value;
        best_x = current_x;
        best_y = current_y;
      }
    }
  }
  fout << fixed << setprecision(1) << best_x << " " << best_y << " "
       << best_value << "\n";

  return 0;
}