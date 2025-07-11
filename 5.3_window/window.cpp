/*
ID: dermotl1
LANG: C++
PROG: window
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

struct window {
  int x1, x2, y1,
      y2;  // x1 and y1 are top left, 2 are bottom right (0, 0 at bottom left)
  char identifier;
};

vector<window> interface;

int FindVisibleArea(int x1, int x2, int y1, int y2, int pos) {
  if (x1 >= x2 || y1 >= y2) {  // stop it immediately
    return 0;
  }

  while (pos < interface.size()) {
    window& temp = interface[pos];
    int temp_x1 = min(temp.x1, temp.x2);
    int temp_y1 = min(temp.y1, temp.y2);
    int temp_x2 = max(temp.x1, temp.x2);
    int temp_y2 = max(temp.y1, temp.y2);
    // ensure it maintains order in top left and bottom right

    if (x1 >= temp_x2 || x2 <= temp_x1 || y1 >= temp_y2 ||
        y2 <= temp_y1) {  // there is no overlap
      pos++;
      continue;
    }
    int answer = 0;  // to find the answer, split the rectangle (cut off) until
                     // it reaches the end of the function to return
    answer += FindVisibleArea(x1, min(x2, temp_x1), y1, y2,
                              pos + 1);  // right side (only direct)
    answer += FindVisibleArea(max(x1, temp_x2), x2, y1, y2, pos + 1);  // right
    answer += FindVisibleArea(max(x1, temp_x1), min(x2, temp_x2),
                              max(y1, temp_y2), y2, pos + 1);  // top
    answer += FindVisibleArea(max(x1, temp_x1), min(x2, temp_x2), y1,
                              min(y2, temp_y1), pos + 1);  // bottom
    return answer;
  }
  return (x2 - x1) * (y2 - y1);
}

int main() {
  ifstream fin("window.in");
  ofstream fout("window.out");

  char in;
  while (fin >> in) {
    if (in == 'w') {
      int x1, x2, y1, y2;
      char paren1, paren2, comma, id;
      fin >> paren1 >> id >> comma >> x1 >> comma >> y1 >> comma >> x2 >>
          comma >> y2 >> paren2;
      window temp;
      temp.identifier = id;
      temp.x1 = min(x1, x2);  // ensure its top left and stuff
      temp.x2 = max(x1, x2);
      temp.y1 = min(y1, y2);
      temp.y2 = max(y1, y2);

      interface.push_back(temp);
    }
    if (in == 't') {
      char id;
      char paren1, paren2;
      fin >> paren1 >> id >> paren2;
      for (int i = 0; i < interface.size(); ++i) {
        if (interface[i].identifier == id) {
          window temp = interface[i];
          interface.erase(interface.begin() + i);
          interface.push_back(temp);
          break;
        }
      }
    }
    if (in == 'b') {
      char id;
      char paren1, paren2;
      fin >> paren1 >> id >> paren2;
      for (int i = 0; i < interface.size(); ++i) {
        if (interface[i].identifier == id) {
          window temp = interface[i];
          interface.erase(interface.begin() + i);
          interface.insert(interface.begin(), temp);
          break;
        }
      }
    }
    if (in == 'd') {
      char id;
      char paren1, paren2;
      fin >> paren1 >> id >> paren2;
      for (int i = 0; i < interface.size(); ++i) {
        if (interface[i].identifier == id) {
          interface.erase(interface.begin() + i);
          break;
        }
      }
    }
    if (in == 's') {
      char id;
      char paren1, paren2;
      fin >> paren1 >> id >> paren2;
      int pos = -1;
      for (int i = 0; i < interface.size(); ++i) {
        if (interface[i].identifier == id) pos = i;
      }

      window temp = interface[pos];
      int x1 = min(temp.x1, temp.x2);
      int x2 = max(temp.x1, temp.x2);
      int y1 = min(temp.y1, temp.y2);
      int y2 =
          max(temp.y1, temp.y2);  // ensure correct top left and bottom right

      int total_area = (x2 - x1) * (y2 - y1);
      int visible_area = FindVisibleArea(x1, x2, y1, y2, pos + 1);
      double percent = (100.0 * visible_area) / total_area;
      fout << fixed << setprecision(3) << percent << '\n';
    }
  }

  return 0;
}