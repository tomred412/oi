#include <iostream>

using namespace std;

bool doesWork(char large_grid[9][9], int row, int column, char test_num) {
  for (int i = 0; i < 9; i++) {
    if (large_grid[row][i] == test_num || large_grid[i][column] == test_num)
      return false;
  }

  // start at top left
  int subgrid_row = (row / 3) * 3;
  int subgrid_column = (column / 3) * 3;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (large_grid[subgrid_row + i][subgrid_column + j] == test_num)
        return false;
    }
  }
  return true;
}

bool findMRV(char large_grid[9][9], int& row, int& column) {
  int min_options = 100;
  bool found = false;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (large_grid[i][j] == '.') {
        int options = 0;

        for (int n = 1; n <= 9; n++) {
          char num = n + '0';
          if (doesWork(large_grid, i, j, num)) {
            options++;
          }
        }

        if (options < min_options) {
          min_options = options;
          row = i;
          column = j;
          found = true;
        }

        if (min_options == 1) {
          return true;
        }
      }
    }
  }
  return found;
}

bool solve(char large_grid[9][9]) {
  int row, column;

  if (findMRV(large_grid, row, column) == false) return true;

  for (int n = 1; n <= 9; n++) {
    char num = n + '0';
    if (doesWork(large_grid, row, column, num)) {
      large_grid[row][column] = num;

      if (solve(large_grid)) {
        return true;
      }

      large_grid[row][column] = '.';  // redo
    }
  }

  return false;  // redo
}

int main() {
  char initial[82];
  char large_grid[9][9];

  while (true) {
    cin >> initial;
    if (initial[0] == 'e') break;

    for (int i = 0; i < 81; i++) {
      large_grid[i / 9][i % 9] = initial[i];
    }
    solve(large_grid);

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        cout << large_grid[i][j];
      }
    }
    cout << "\n";
  }

  return 0;
}

