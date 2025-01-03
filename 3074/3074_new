#include <cstring>
#include <iostream>

using namespace std;

bool possible[9][9][9];

bool doesWork(char grid[9][9], int row, int col, int num) {
  for (int i = 0; i < 9; i++) {
    if (grid[row][i] - '0' == num || grid[i][col] - '0' == num) {
      return false;
    }
  }
  // start at top left
  int subgrid_row = (row / 3) * 3;
  int subgrid_column = (col / 3) * 3;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (grid[subgrid_row + i][subgrid_column + j] - '0' == num) {
        return false;
      }
    }
  }
  return true;
}

bool findMRV(char grid[9][9], int &row, int &col) {
  int min_options = 10;
  bool found = false;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (grid[i][j] == '.') {
        int count = 0;
        for (int num = 1; num <= 9; ++num) {
          if (possible[i][j][num - 1]) {
            ++count;
          }
        }
        if (count < min_options) {
          min_options = count;
          row = i;
          col = j;
          found = true;
        }
      }
    }
  }
  return found;
}

void update(char grid[9][9], int row, int col, int num) {
  for (int i = 0; i < 9; i++) {
    possible[row][i][num - 1] = false;
    possible[i][col][num - 1] = false;
  }
  int subgrid_row = (row / 3) * 3;
  int subgrid_column = (col / 3) * 3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      possible[subgrid_row + i][subgrid_column + j][num - 1] = false;
    }
  }
}

bool solve(char grid[9][9]) {
  int row, col;
  if (findMRV(grid, row, col) == false) return true;

  for (int num = 1; num <= 9; num++) {
    if (possible[row][col][num - 1] && doesWork(grid, row, col, num)) {
      grid[row][col] = '0' + num;

      bool backup[9][9][9];
      memcpy(backup, possible, sizeof(possible));  // make a backup

      update(grid, row, col, num);

      if (solve(grid)) return true;

      memcpy(possible, backup, sizeof(possible));
      grid[row][col] = '.';
    }
  }
  return false;
}

int main() {
  char input[82];
  while (cin >> input && input[0] != 'e') {
    char grid[9][9];
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        for (int k = 0; k < 9; k++) {
          possible[i][j][k] = true;
        }
      }
    }

    for (int i = 0; i < 81; i++) {
      grid[i / 9][i % 9] = input[i];
      if (input[i] != '.') {
        int num = input[i] - '0';
        update(grid, i / 9, i % 9, num);  // make sure the filled in are correct
      }
    }

    solve(grid);

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        cout << grid[i][j];
      }
    }
    cout << "\n";
  }
  return 0;
}

