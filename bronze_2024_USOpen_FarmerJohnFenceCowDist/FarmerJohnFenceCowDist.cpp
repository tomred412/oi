
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// i need to make functions to find the grid distance, then use that to
// determine the points on the fence. also, perimeter can add it up in main for
// each cow using the simple functions

struct point {
  int x, y;
};

struct fence_segment {
  point start, end;
  int length;
  int perimeter_before;
};

int grid[1001][1001];

int FindDistance(point a, point b) { return abs(a.x - b.x) + abs(a.y - b.y); }

bool DeterminePointOnSegment(point p1, fence_segment f) {
  if (f.start.x == f.end.x) {  // vertical fence
    if (p1.x == f.start.x && ((p1.y >= f.start.y && p1.y <= f.end.y) ||
                              (p1.y <= f.start.y && p1.y >= f.end.y)))
      return true;
    else
      return false;
  } else {  // horizontal fence
    if (p1.y == f.start.y && ((p1.x >= f.start.x && p1.x <= f.end.x) ||
                              (p1.x <= f.start.x && p1.x >= f.end.x)))
      return true;
    else
      return false;
  }
}

int FindFenceToPointDistance(point p1) {
  return grid[p1.x][p1.y];
}  // this is too slow, i need to change it by making it already done

int main() {
  int n, p;
  cin >> n >> p;

  vector<point> fence_posts(p);
  for (int i = 0; i < p; ++i) {
    cin >> fence_posts[i].x >> fence_posts[i].y;
  }

  // make fence segments (circle), then keep calculating perimeter (each and
  // total)
  vector<fence_segment> fence_segments;
  int total_length = 0;
  for (int i = 0; i < p; ++i) {
    point a = fence_posts[i];
    point b = fence_posts[(i + 1) % p];  // circle

    int length = FindDistance(a, b);

    fence_segment temp;
    temp.start = a;
    temp.end = b;
    temp.length = length;
    temp.perimeter_before = total_length;

    fence_segments.push_back(temp);

    if (a.x == b.x) {
      int y1 = min(a.y, b.y);
      int y2 = max(a.y, b.y);

      for (int y = y1; y <= y2; ++y) {
        grid[a.x][y] = total_length + abs(y - a.y);  // make nonnegative
      }
    } else {
      int x1 = min(a.x, b.x);
      int x2 = max(a.x, b.x);

      for (int x = x1; x <= x2; ++x) {
        grid[x][a.y] = total_length + abs(x - a.x);
      }
    }

    total_length += length;
  }

  // calculate each cow
  for (int i = 0; i < n; ++i) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    point start;  // start and end of the cow
    start.x = x1;
    start.y = y1;

    point end;
    end.x = x2;
    end.y = y2;

    int distance1 =
        FindFenceToPointDistance(start);  // where exactly on the fence
    int distance2 = FindFenceToPointDistance(end);

    int clockwise = abs(distance2 - distance1);  // calculate 2
    int counter = total_length - clockwise;
    cout << min(clockwise, counter) << "\n";
  }

  return 0;
}