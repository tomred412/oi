/*
ID: dermotl1
LANG: C++
PROG: castle
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct wall {  // best wall removal's row, column, and direction
  int row, col;
  int dir;
};

int col;                 // m
int row;                 // n
int castle[50][50];      // original, wall info
int room_label[50][50];  // which room does each square belong to?
bool room_visited[50][50];
int largest_room = 0;
int wall_room = 0;  // room formed by removing a wall
int room_size[2500];
wall best_wall;

bool isWall(int row, int col, int dir) {  // 0: w, 1: n, 2: e, 3: s
  return castle[row][col] & (1 << dir);
}

int delta_row[4] = {0, -1, 0, 1};
int delta_col[4] = {-1, 0, 1, 0};
int num = 0;

void visit(int row, int col) {
  if (room_visited[row][col]) return;
  room_visited[row][col] = true;
  room_label[row][col] = num;
  room_size[num]++;
  for (int i = 0; i < 4; i++) {
    if (!isWall(row, col, i)) visit(row + delta_row[i], col + delta_col[i]);
  }
}

void chooseWall(int i, int j, int n_i, int n_j,
                int dir) {  // n_variable = adjacent wall (new)
  if (n_i >= 0 && n_i < row && n_j >= 0 && n_j < col &&
      room_label[i][j] != room_label[n_i][n_j]) {
    int new_size =
        room_size[room_label[i][j]] + room_size[room_label[n_i][n_j]];
    if (new_size > wall_room ||
        (new_size == wall_room &&
         (j < best_wall.col || (j < best_wall.col && i > best_wall.row))) ||
        (new_size == wall_room && j == best_wall.col && i == best_wall.row &&
         dir < best_wall.dir)) {
      wall_room = new_size;
      best_wall.row = i;
      best_wall.col = j;
      best_wall.dir = dir;
    }
  }
}

int main() {
  ofstream fout("castle.out");
  ifstream fin("castle.in");

  fin >> col >> row;

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      fin >> castle[i][j];
    }
  }

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (!room_visited[i][j]) {
        visit(i, j);
        num++;
      }
    }
  }

  largest_room = 0;
  for (int i = 0; i < num; i++) {
    if (room_size[i] > largest_room) {
      largest_room = room_size[i];
    }
  }

  for (int j = 0; j < col; j++) {
    for (int i = row - 1; i >= 0; i--) {
      if (isWall(i, j, 1))
        chooseWall(i, j, i - 1, j,
                   1);  // check only north and east b/c it's already going to
                        // be checked when iterating
      if (isWall(i, j, 2)) chooseWall(i, j, i, j + 1, 2);
    }
  }

  fout << num << "\n"
       << largest_room << "\n"
       << wall_room << "\n"
       << best_wall.row + 1 << " " << best_wall.col + 1 << " ";
  if (best_wall.dir == 0) fout << "W\n";
  if (best_wall.dir == 1) fout << "N\n";
  if (best_wall.dir == 2) fout << "E\n";
  if (best_wall.dir == 3) fout << "S\n";
  return 0;
}
