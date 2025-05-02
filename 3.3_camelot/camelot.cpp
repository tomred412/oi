/*
ID: dermotl1
LANG: C++
PROG: camelot
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

struct piece {
  int row;
  int col;
};

int r, c;
piece king;
piece knights[225];
int knight_count = 0;
int knight_distance[30][26][30][26];  // from [x][y] to [x1][y1]
int king_distance[30][26];            // from start to [x][y]

int direction_row[8] = {-2, -1, 1, 2, 2, 1, -1, -2};  // how knights move
int direction_col[8] = {1, 2, 2, 1, -1, -2, -2, -1};

void solve_knight() {  // solve the knight's distance from this to that
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      // Initialize knight distances
      for (int p = 0; p < r; ++p) {
        for (int q = 0; q < c; ++q) {
          knight_distance[i][j][p][q] = numeric_limits<int>::max();
        }
      }
      queue<piece> qu;
      knight_distance[i][j][i][j] = 0;
      qu.push((piece){i, j});

      while (!qu.empty()) {
        piece current = qu.front();
        qu.pop();
        int current_row = current.row;
        int current_col = current.col;
        int current_dist = knight_distance[i][j][current_row][current_col];

        for (int k = 0; k < 8; ++k) {
          int new_row = current_row + direction_row[k];
          int new_col = current_col + direction_col[k];

          if (new_row >= 0 && new_row < r && new_col >= 0 && new_col < c) {
            if (knight_distance[i][j][new_row][new_col] ==
                numeric_limits<int>::max()) {
              knight_distance[i][j][new_row][new_col] = current_dist + 1;
              qu.push((piece){new_row, new_col});
            }
          }
        }
      }
    }
  }
}

void solve_king() {  // solve the kings distance from start to this
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      int difference_row = king.row - i;
      if (difference_row < 0) difference_row = -difference_row;
      int difference_column = king.col - j;
      if (difference_column < 0) difference_column = -difference_column;
      if (difference_column > difference_row)
        king_distance[i][j] = difference_column;
      else
        king_distance[i][j] = difference_row;
    }
  }
}

int main() {
  ifstream fin("camelot.in");
  ofstream fout("camelot.out");

  fin >> r >> c;

  char king_row, king_col;
  fin >> king_col >> king_row;

  king.row = king_row - '1';
  king.col = king_col - 'A';

  char knight_row, knight_col;
  while (fin >> knight_col >> knight_row) {
    knights[knight_count].row = knight_row - '1';
    knights[knight_count].col = knight_col - 'A';
    knight_count++;
  }

  solve_knight();
  solve_king();

  int best = numeric_limits<int>::max();
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      int total_cost = 0;
      bool go = true;
      for (int p = 0; p < knight_count; ++p) {
        int knight_start_col = knights[p].col;
        int knight_start_row = knights[p].row;
        int steps = knight_distance[knight_start_row][knight_start_col][i][j];
        if (steps == numeric_limits<int>::max()) {
          go = false;
          break;
        }
        total_cost += steps;
      }
      if (!go) continue;

      int best_king = king_distance[i][j];

      for (int p = king.row - 2; p <= king.row + 2;
           ++p) {  // check 25, 2 radius
        for (int q = king.col - 2; q <= king.col + 2; ++q) {
          if (p < 0 || p >= r || q < 0 || q >= c) continue;
          int king_steps = king_distance[p][q];

          for (int u = 0; u < knight_count; ++u) {
            int knight_start_row = knights[u].row;
            int knight_start_col = knights[u].col;

            int knight_to_king =
                knight_distance[knight_start_row][knight_start_col][p][q];
            int knight_king_to_meet = knight_distance[p][q][i][j];
            int knight_original =
                knight_distance[knight_start_row][knight_start_col][i][j];

            if (knight_to_king == numeric_limits<int>::max() ||
                knight_king_to_meet == numeric_limits<int>::max())
              continue;
            int extra = knight_to_king + knight_king_to_meet + king_steps -
                        knight_original;
            if (extra < best_king) best_king = extra;
          }
        }
      }
      int total = total_cost + best_king;
      if (total < best) best = total;
    }
  }

  fout << best << "\n";
  return 0;
}
