/*
ID: dermotl1
LANG: C++
PROG: starry
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
  int x, y;  // store column for x, row for y (reversed, y, x not x, y)
};

struct Cluster {
  Point p[161];
  int size;
};

int width, height;
char grid[101][101];
bool visited[101][101];

int direction_x[8] = {-1, -1, -1, 0,
                      0,  1,  1,  1};  // use these for adjacency testing
int direction_y[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

vector<Cluster> clusters;
vector<char>
    letter_labels;  // each i in this array will also be in the clusters array,
                    // so that the a, b, c... can be stored

void FindConnectedCluster(
    int start_x, int start_y,
    Cluster& cluster) {  // construct the cluster from the starting point

  queue<Point> q;

  Point temp;
  temp.x = start_x;
  temp.y = start_y;
  q.push(temp);

  visited[start_y][start_x] = true;
  cluster.size = 0;

  while (!q.empty()) {
    Point current = q.front();
    q.pop();
    cluster.p[cluster.size++] = current;

    for (int i = 0; i < 8; ++i) {
      int new_x = current.x + direction_x[i];
      int new_y = current.y + direction_y[i];

      if (new_x >= 0 && new_y >= 0 && new_x < width && new_y < height &&
          (!visited[new_y][new_x]) && (grid[new_y][new_x] == '1')) {
        visited[new_y][new_x] = true;

        Point temp1;
        temp1.x = new_x;
        temp1.y = new_y;
        q.push(temp1);
      }
    }
  }
}

void MakeNormal(Cluster& in,
                Cluster& out) {  // so we can compare "similar" later
  int min_x = 1000;
  int min_y = 1000;
  out.size = in.size;

  for (int i = 0; i < in.size;
       ++i) {  // set it to 0, 0 because we can compare like that
    if (in.p[i].x < min_x) min_x = in.p[i].x;
    if (in.p[i].y < min_y) min_y = in.p[i].y;
  }

  for (int i = 0; i < in.size; i++) {
    out.p[i].x = in.p[i].x - min_x;
    out.p[i].y = in.p[i].y - min_y;
  }

  for (int i = 0; i < out.size - 1; i++) {
    for (int j = i + 1; j < out.size; j++) {
      if (out.p[j].y < out.p[i].y ||
          (out.p[j].y == out.p[i].y && out.p[j].x < out.p[i].x)) {
        Point temp = out.p[i];
        out.p[i] = out.p[j];
        out.p[j] = temp;
      }
    }
  }
}

void TransformCluster(Cluster& in, Cluster& out, int t) {
  out.size = in.size;
  for (int i = 0; i < in.size; i++) {
    int x = in.p[i].x;
    int y = in.p[i].y;
    int new_x = 0;
    int new_y = 0;

    if (t == 0) {  // do nothing
      new_x = x;
      new_y = y;
    } else if (t == 1) {  // rotate 90
      new_x = -y;
      new_y = x;
    } else if (t == 2) {  // rotate 180
      new_x = -x;
      new_y = -y;
    } else if (t == 3) {  // rotate 270
      new_x = y;
      new_y = -x;
    } else if (t == 4) {  // reflect vertically
      new_x = -x;
      new_y = y;
    } else if (t == 5) {  // reflect horizontally
      new_x = x;
      new_y = -y;
    } else if (t == 6) {  // reflect over diagonal (y = x)
      new_x = y;
      new_y = x;
    } else if (t == 7) {  // reflect over diagonal (y = -x)
      new_x = -y;
      new_y = -x;
    }

    out.p[i].x = new_x;
    out.p[i].y = new_y;
  }

  MakeNormal(out, out);
}

bool SameOrNot(Cluster& a, Cluster& b) {
  if (a.size != b.size) return false;

  for (int i = 0; i < a.size; ++i) {
    if (a.p[i].x != b.p[i].x || a.p[i].y != b.p[i].y) return false;
  }
  return true;
}

char FindNewOrOldClusterLabel(Cluster& cluster) {
  Cluster transform, normal;

  for (int i = 0; i < clusters.size(); ++i) {  // this is for old clusters
    for (int t = 0; t < 8; ++t) {
      TransformCluster(cluster, transform, t);
      MakeNormal(transform, normal);
      if (SameOrNot(normal, clusters[i])) return letter_labels[i];
    }
  }

  TransformCluster(cluster, transform, 0);  // this is for new clusters
  MakeNormal(transform, normal);
  clusters.push_back(normal);
  char label = 'a' + letter_labels.size();
  letter_labels.push_back(label);
  return label;
}

void PutLabelsOnGrid(Cluster& cluster, char label) {
  for (int i = 0; i < cluster.size; ++i) {
    grid[cluster.p[i].y][cluster.p[i].x] = label;
  }
}

int main() {
  ifstream fin("starry.in");
  ofstream fout("starry.out");

  fin >> width >> height;
  for (int i = 0; i < height; ++i) {
    fin >> grid[i];
  }

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      if (grid[y][x] == '1' && !visited[y][x]) {
        Cluster cluster;
        FindConnectedCluster(x, y, cluster);

        char label = FindNewOrOldClusterLabel(cluster);
        PutLabelsOnGrid(cluster, label);
      }
    }
  }

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      fout << grid[y][x];
    }
    fout << '\n';
  }

  return 0;
}