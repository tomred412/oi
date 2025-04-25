/*
ID: dermotl1
LANG: C++
PROG: spin
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct wedge {
  int start;
  int extent;
};

struct wheel {
  int speed;
  int wedge_number;
  vector<wedge> wheel_wedges;
};

bool time_align(wheel wheels[5],
                int x) {  // check if it's aligned at time x
  vector<bool> degrees(360, true);
  bool temp[360];  // which degrees
  int i, j, p, q;
  for (i = 0; i < 5; ++i) {
    for (q = 0; q < 360; ++q) {
      temp[q] = false;
    }
    for (j = 0; j < wheels[i].wedge_number; ++j) {
      int wedge_start =
          (wheels[i].wheel_wedges[j].start + wheels[i].speed * x) % 360;
      int wedge_extent = wheels[i].wheel_wedges[j].extent;
      for (p = 0; p <= wedge_extent; ++p) {
        int degree = (wedge_start + p) % 360;
        temp[degree] = true;
      }
    }
    for (q = 0; q < 360; ++q) {
      if (degrees[q] && temp[q])
        degrees[q] = true;
      else
        degrees[q] = false;
    }
  }
  for (q = 0; q < 360; ++q) {
    if (degrees[q]) return true;
  }
  return false;
}

int main() {
  ifstream fin("spin.in");
  ofstream fout("spin.out");

  wheel wheels[5];
  int i, j;

  for (i = 0; i < 5; ++i) {
    fin >> wheels[i].speed >> wheels[i].wedge_number;
    for (j = 0; j < wheels[i].wedge_number; ++j) {
      wedge w;
      fin >> w.start >> w.extent;
      wheels[i].wheel_wedges.push_back(w);
    }
  }

  for (int x = 0; x < 360; ++x) {
    if (time_align(wheels, x)) {
      fout << x << "\n";
      return 0;
    }
  }
  fout << "none\n";
  return 0;
}
