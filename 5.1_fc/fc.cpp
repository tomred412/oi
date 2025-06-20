/*
ID: dermotl1
LANG: C++
PROG: fc
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

struct Point {
  double x, y;
};

Point center;

bool CompareAngles(Point a, Point b) {
  double angle_1 = atan2(a.y - center.y, a.x - center.x);
  double angle_2 = atan2(b.y - center.y, b.x - center.x);

  if (angle_1 == angle_2) {
    double dist1 = (a.x - center.x) * (a.x - center.x) +
                   (a.y - center.y) * (a.y - center.y);
    double dist2 = (b.x - center.x) * (b.x - center.x) +
                   (b.y - center.y) * (b.y - center.y);
    return dist1 < dist2;
  }

  return angle_1 < angle_2;
}

double ZCrossProduct(Point O, Point A, Point B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

int main() {
  ifstream fin("fc.in");
  ofstream fout("fc.out");

  int n;
  fin >> n;

  if (n < 2) {
    fout << "0.00\n";
    return 0;
  } else if (n == 2) {
    double x1, y1, x2, y2;
    fin >> x1 >> y1 >> x2 >> y2;
    double dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    fout << fixed << setprecision(2) << 2.0 * dist << "\n";
    return 0;
  }

  vector<Point> points(n);
  center.x = 0;
  center.y = 0;

  double temp1 = 0.0;
  double temp2 = 0.0;
  for (int i = 0; i < n; ++i) {
    fin >> points[i].x >> points[i].y;
    temp1 += points[i].x;
    temp2 += points[i].y;
  }

  center.x = temp1 / n;
  center.y = temp2 / n;

  sort(points.begin(), points.end(), CompareAngles);

  vector<Point> hull;
  hull.push_back(points[0]);
  hull.push_back(points[1]);

  for (int i = 2; i < n; ++i) {
    while (hull.size() >= 2 &&
           ZCrossProduct(hull[hull.size() - 2], hull[hull.size() - 1],
                         points[i]) <= 0) {
      hull.pop_back();
    }
    hull.push_back(points[i]);
  }

  while (hull.size() >= 3) {
    bool flag = false;

    if (ZCrossProduct(hull[hull.size() - 2], hull.back(), hull[0]) <= 0) {
      hull.pop_back();
      flag = true;
    }

    if (hull.size() >= 3 && ZCrossProduct(hull.back(), hull[0], hull[1]) <= 0) {
      hull.erase(hull.begin());
      flag = true;
    }
    if (!flag) break;
  }

  double perimeter = 0.0;

  for (int i = 0; i < hull.size() - 1; ++i) {
    Point p1 = hull[i];
    Point p2 = hull[i + 1];
    perimeter +=
        sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)));
  }

  Point last_point = hull.back();
  Point first_point = hull.front();
  perimeter +=
      sqrt(((last_point.x - first_point.x) * (last_point.x - first_point.x)) +
           ((last_point.y - first_point.y) * (last_point.y - first_point.y)));

  fout << fixed << setprecision(2) << perimeter << "\n";

  return 0;
}
