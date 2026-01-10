/*
ID: dermotl1
LANG: C++
PROG: fence4
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

struct point {
  double x, y;
};

struct segment {
  point p1, p2;
  int pos1, pos2;
  int id;
};

int n;
point observer;
vector<point> corners;
vector<segment> fences;
vector<bool> is_fence_visible;

bool isBetween(double test, double a, double b) {
  return test >= min(a, b) - 1e-9 && test <= max(a, b) + 1e-9;
}

bool isPointOnSegment(point p, segment s) {
  return isBetween(p.x, s.p1.x, s.p2.x) && isBetween(p.y, s.p1.y, s.p2.y);
}

bool isEndpoint(point p, segment s) {
  double d1 =
      sqrt((p.x - s.p1.x) * (p.x - s.p1.x) + (p.y - s.p1.y) * (p.y - s.p1.y));
  double d2 =
      sqrt((p.x - s.p2.x) * (p.x - s.p2.x) + (p.y - s.p2.y) * (p.y - s.p2.y));
  return (d1 < 1e-9 || d2 < 1e-9);
}

bool doesIntersection(segment s1, segment s2, bool check_fence) {
  bool is_vertical1 = abs(s1.p1.x - s1.p2.x) < 1e-9;
  bool is_vertical2 = abs(s2.p1.x - s2.p2.x) < 1e-9;

  double x_intersect, y_intersect;

  if (is_vertical1 && is_vertical2) {
    return false;

  } else if (is_vertical1) {
    x_intersect = s1.p1.x;
    double slope2 = (s2.p2.y - s2.p1.y) / (s2.p2.x - s2.p1.x);
    double b2 = s2.p1.y - slope2 * s2.p1.x;
    y_intersect = slope2 * x_intersect + b2;

  } else if (is_vertical2) {
    x_intersect = s2.p1.x;
    double slope1 = (s1.p2.y - s1.p1.y) / (s1.p2.x - s1.p1.x);
    double b1 = s1.p1.y - slope1 * s1.p1.x;
    y_intersect = slope1 * x_intersect + b1;

  } else {
    double slope1 = (s1.p2.y - s1.p1.y) / (s1.p2.x - s1.p1.x);
    double b1 = s1.p1.y - slope1 * s1.p1.x;

    double slope2 = (s2.p2.y - s2.p1.y) / (s2.p2.x - s2.p1.x);
    double b2 = s2.p1.y - slope2 * s2.p1.x;

    if (abs(slope1 - slope2) < 1e-9) return false;

    x_intersect = (b2 - b1) / (slope1 - slope2);
    y_intersect = slope1 * x_intersect + b1;
  }

  point intersection;
  intersection.x = x_intersect;
  intersection.y = y_intersect;

  if (isPointOnSegment(intersection, s1) &&
      isPointOnSegment(intersection, s2)) {
    if (check_fence) {
      if (isEndpoint(intersection, s1) || isEndpoint(intersection, s2))
        return false;
    }
    return true;
  }
  return false;
}

point calculateIntersection(segment s1, segment s2) {
  bool is_vertical1 = abs(s1.p1.x - s1.p2.x) < 1e-9;
  bool is_vertical2 = abs(s2.p1.x - s2.p2.x) < 1e-9;

  double x_intersect, y_intersect;

  if (is_vertical1) {
    x_intersect = s1.p1.x;
    double slope2 = (s2.p2.y - s2.p1.y) / (s2.p2.x - s2.p1.x);
    double b2 = s2.p1.y - slope2 * s2.p1.x;
    y_intersect = slope2 * x_intersect + b2;

  } else if (is_vertical2) {
    x_intersect = s2.p1.x;
    double slope1 = (s1.p2.y - s1.p1.y) / (s1.p2.x - s1.p1.x);
    double b1 = s1.p1.y - slope1 * s1.p1.x;
    y_intersect = slope1 * x_intersect + b1;

  } else {
    double slope1 = (s1.p2.y - s1.p1.y) / (s1.p2.x - s1.p1.x);
    double b1 = s1.p1.y - slope1 * s1.p1.x;

    double slope2 = (s2.p2.y - s2.p1.y) / (s2.p2.x - s2.p1.x);
    double b2 = s2.p1.y - slope2 * s2.p1.x;

    x_intersect = (b2 - b1) / (slope1 - slope2);
    y_intersect = slope1 * x_intersect + b1;
  }
  point answer;
  answer.x = x_intersect;
  answer.y = y_intersect;

  return answer;
}

bool isUpperHalf(point p) {
  if (p.y > observer.y) return true;
  if (p.y < observer.y) return false;
  return p.x > observer.x;
}

bool compare(point a, point b) {
  bool upper_a = isUpperHalf(a);
  bool upper_b = isUpperHalf(b);

  if (upper_a != upper_b) return upper_a;

  double dx1 = a.x - observer.x;
  double dy1 = a.y - observer.y;
  double dx2 = b.x - observer.x;
  double dy2 = b.y - observer.y;

  return (dx1 * dy2 - dy1 * dx2) > 0;
}

int main() {
  ifstream fin("fence4.in");
  ofstream fout("fence4.out");

  fin >> n;
  fin >> observer.x >> observer.y;
  for (int i = 0; i < n; ++i) {
    point temp;
    fin >> temp.x >> temp.y;
    corners.push_back(temp);
  }

  for (int i = 0; i < n; ++i) {
    int next = (i + 1) % n;
    segment temp;
    temp.p1 = corners[i];
    temp.p2 = corners[next];
    temp.pos1 = i + 1;
    temp.pos2 = next + 1;
    fences.push_back(temp);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i + 2; j < n; ++j) {
      if (i == 0 && j == n - 1) continue;
      if (doesIntersection(fences[i], fences[j], true)) {
        fout << "NOFENCE\n";
        return 0;
      }
    }
  }

  is_fence_visible.resize(n);
  vector<point> sorted = corners;

  sort(sorted.begin(), sorted.end(), compare);

  for (int i = 0; i < sorted.size(); ++i) {
    point p1 = sorted[i];
    point p2 = sorted[(i + 1) % sorted.size()];

    if (abs((p1.x - observer.x) * (p2.y - observer.y) -
            (p1.y - observer.y) * (p2.x - observer.x)) < 1e-9 &&
        ((p1.x - observer.x) * (p2.x - observer.x) +
         (p1.y - observer.y) * (p2.y - observer.y)) > 0)
      continue;

    double mid_dx = (p1.x - observer.x) + (p2.x - observer.x);
    double mid_dy = (p1.y - observer.y) + (p2.y - observer.y);

    point far_point;
    far_point.x = observer.x + mid_dx * 200000.0;
    far_point.y = observer.y + mid_dy * 200000.0;

    segment ray;
    ray.p1 = observer;
    ray.p2 = far_point;
    ray.pos1 = -1;
    ray.pos2 = -1;
    ray.id = -1;

    double min_dist = numeric_limits<double>::max();
    int closest_fence_id = -1;

    for (int j = 0; j < n; ++j) {
      if (doesIntersection(ray, fences[j], false)) {
        point hit = calculateIntersection(ray, fences[j]);
        double dist = sqrt((hit.x - observer.x) * (hit.x - observer.x) +
                           (hit.y - observer.y) * (hit.y - observer.y));
        if (dist < min_dist) {
          min_dist = dist;
          closest_fence_id = j;
        }
      }
    }
    if (closest_fence_id != -1) is_fence_visible[closest_fence_id] = true;
  }

  vector<segment> output;
  for (int i = 0; i < n; i++) {
    if (is_fence_visible[i]) {
      segment out = fences[i];

      if (out.pos1 > out.pos2) {
        swap(out.pos1, out.pos2);
        swap(out.p1, out.p2);
      }
      output.push_back(out);
    }
  }

  sort(output.begin(), output.end(), [](segment a, segment b) {
    if (a.pos2 != b.pos2) return a.pos2 < b.pos2;
    return a.pos1 < b.pos1;
  });

  fout << output.size() << "\n";
  for (auto it : output) {
    fout << it.p1.x << " " << it.p1.y << " " << it.p2.x << " " << it.p2.y
         << "\n";
  }

  return 0;
}