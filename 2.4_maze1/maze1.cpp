/*
ID: dermotl1
LANG: C++
PROG: maze1
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int w, h;

struct exits {
  int x, y;
};

char maze[205][81];
int dista[205][81];
exits one;
exits two;

void find(exits &one, exits &two) {
  int count = 0;
  for (int i = 1; i < h * 2; i = i + 2) {
    if (maze[i][0] == ' ') {
      if (count == 0) {
        one.x = i;
        one.y = 1;
        count++;
      } else {
        two.x = i;
        two.y = 1;
        count++;
      }
    }
    if (maze[i][2 * w] == ' ') {
      if (count == 0) {
        one.x = i;
        one.y = 2 * w - 1;
        count++;
      } else {
        two.x = i;
        two.y = 2 * w - 1;
        count++;
      }
    }
  }
  for (int j = 1; j < w * 2; j = j + 2) {
    if (maze[0][j] == ' ') {
      if (count == 0) {
        one.x = 1;
        one.y = j;
        count++;
      } else {
        two.x = 1;
        two.y = j;
        count++;
      }
    }
    if (maze[2 * h][j] == ' ') {
      if (count == 0) {
        one.x = 2 * h - 1;
        one.y = j;
        count++;
      } else {
        two.x = 2 * h - 1;
        two.y = j;
        count++;
      }
    }
  }
}

void search(int x, int y, int now) {
  if (x < 0 || y < 0 || x > 2 * h || y > 2 * w ||
      dista[x][y] && now >= dista[x][y])
    return;
  if (dista[x][y] == 0 || now < dista[x][y]) dista[x][y] = now;

  if (maze[x - 1][y] == ' ') search(x - 2, y, now + 1);
  if (maze[x + 1][y] == ' ') search(x + 2, y, now + 1);
  if (maze[x][y - 1] == ' ') search(x, y - 2, now + 1);
  if (maze[x][y + 1] == ' ') search(x, y + 2, now + 1);
}

int main() {
  ifstream fin("maze1.in");
  ofstream fout("maze1.out");

  fin >> w >> h;
  fin.ignore();

  char a;

  for (int i = 0; i < 2 * h + 1; i++) {
    for (int j = 0; j < 2 * w + 1; j++) {
      fin.get(maze[i][j]);
    }
    fin.ignore();
  }

  find(one, two);
  search(one.x, one.y, 1);
  search(two.x, two.y, 1);

  int answer = 0;
  for (int i = 1; i < 2 * h + 1; i = i + 2) {
    for (int j = 1; j < 2 * w + 1; j = j + 2) {
      answer = max(answer, dista[i][j]);
    }
  }
  fout << answer << "\n";
}
