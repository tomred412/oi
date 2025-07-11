/*
ID: dermotl1
LANG: C++
PROG: snail
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
bool visited[121][121];
bool barriers[121][121];
int n;
int b;

int dx[4] = {-1, 0, 1, 0};  // x  is row, y is column (opposite sometimes)
int dy[4] = {0, 1, 0, -1};

int TraverseGrid(int direction, int x, int y,
                 int turns) {  // direction = 0 for north, 1 for east, 2 for
                               // south, 3 for west
  visited[x][y] = true;
  int new_x, new_y;
  int steps = 1;

  new_x = x + dx[direction];
  new_y = y + dy[direction];

  if (new_x >= 0 && new_y < n && new_x < n && new_y >= 0) {
    if (!barriers[new_x][new_y] && !visited[new_x][new_y])
      steps = 1 + TraverseGrid(direction, new_x, new_y, 0);

    else if (barriers[new_x][new_y]) {
      if (turns == 0) {
        turns++;
        steps = max(TraverseGrid(((direction + 1) % 4), x, y, turns),
                    TraverseGrid(((direction + 3) % 4), x, y, turns));
      }
    }
  } else if (turns == 0) {
    turns++;
    steps = max(TraverseGrid(((direction + 1) % 4), x, y, turns),
                TraverseGrid(((direction + 3) % 4), x, y, turns));
  }
  visited[x][y] = false;
  return steps;
}

int main() {
  ifstream fin("snail.in");
  ofstream fout("snail.out");

  fin >> n >> b;
  for (int i = 0; i < b; ++i) {
    char temp1;
    int temp2;
    fin >> temp1 >> temp2;
    barriers[temp1 - 'A'][temp2 - 1] = true;
  }

  int answer = max(TraverseGrid(2, 0, 0, 0), TraverseGrid(1, 0, 0, 0));

  fout << answer << "\n";

  return 0;
}