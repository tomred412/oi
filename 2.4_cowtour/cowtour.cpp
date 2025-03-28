/*
ID: dermotl1
LANG: C++
PROG: cowtour
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct point {
  int x, y;
};

double dist[150][150];
point pasture[150];
int n;
double limit = numeric_limits<double>::max();

double distanceCalc(int i, int j) {
  double new_x = pasture[i].x - pasture[j].x;
  double new_y = pasture[i].y - pasture[j].y;
  return sqrt(new_x * new_x + new_y * new_y);
}

void algorithm() {
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dist[i][k] < limit && dist[k][j] < limit)
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
}

void fieldFinder(vector<vector<int> > &fields) {
  vector<bool> visited(n, false);
  for (int i = 0; i < n; i++) {
    if (visited[i] == false) {
      vector<int> field;
      vector<int> stack;
      stack.push_back(i);
      visited[i] = true;

      while (stack.empty() == false) {
        int add = stack.back();
        stack.pop_back();
        field.push_back(add);

        for (int j = 0; j < n; j++) {
          if (visited[j] == false && dist[add][j] < limit) {
            visited[j] = true;
            stack.push_back(j);
          }
        }
      }
      fields.push_back(field);
    }
  }
}

double diameter(vector<int> field) {
  double maxi = 0.0;
  for (int i = 0; i < field.size(); i++) {
    for (int j = 0; j < field.size(); j++) {
      if (field[i] != field[j]) maxi = max(maxi, dist[field[i]][field[j]]);
    }
  }
  return maxi;
}

int main() {
  ifstream fin("cowtour.in");
  ofstream fout("cowtour.out");

  fin >> n;
  for (int i = 0; i < n; i++) {
    fin >> pasture[i].x >> pasture[i].y;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      char c;
      fin >> c;
      if (i == j) {
        dist[i][j] = 0;
      } else if (c == '1') {
        dist[i][j] = distanceCalc(i, j);
      } else {
        dist[i][j] = limit;
      }
    }
  }
  algorithm();

  vector<vector<int> > fields;
  fieldFinder(fields);

  vector<double> diameters;
  for (int i = 0; i < fields.size(); i++) {
    double field_diameter = diameter(fields[i]);
    diameters.push_back(field_diameter);
  }
  vector<double> max_field_dist(n, 0.0);
  for (int i = 0; i < fields.size(); i++) {
    for (int j = 0; j < fields[i].size(); j++) {
      int a = fields[i][j];

      for (int k = 0; k < fields[i].size(); k++) {
        int b = fields[i][k];
        if (dist[a][b] < limit) {
          max_field_dist[a] = max(max_field_dist[a], dist[a][b]);
        }
      }
    }
  }

  double min_diameter = limit;

  for (int i = 0; i < fields.size(); i++) {
    for (int j = i + 1; j < fields.size(); j++) {
      for (int k = 0; k < fields[i].size(); k++) {
        int a = fields[i][k];
        for (int p = 0; p < fields[j].size(); p++) {
          int b = fields[j][p];

          double new_distance = distanceCalc(a, b);
          double new_diameter =
              max(max(diameters[i], diameters[j]),
                  max_field_dist[a] + max_field_dist[b] + new_distance);
          min_diameter = min(min_diameter, new_diameter);
        }
      }
    }
  }
  fout << fixed << setprecision(6) << min_diameter << "\n";
}
