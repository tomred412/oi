/*
ID: dermotl1
LANG: C++
PROG: ttwo
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

char arr[10][10];

struct thing {
  int x, y;
  char direction;  // N, E, W, S
};

int convert_x(char direction) {
  if (direction == 'N') return -1;
  if (direction == 'S') return 1;
  return 0;
}

int convert_y(char direction) {
  if (direction == 'W') return -1;
  if (direction == 'E') return 1;
  return 0;
}

char convert_dir(char direction) {
  if (direction == 'N') return 'E';
  if (direction == 'E') return 'S';
  if (direction == 'S') return 'W';
  return 'N';
}

thing cows, farmer;

void move(thing &thing) {
  int new_x = thing.x + convert_x(thing.direction);
  int new_y = thing.y + convert_y(thing.direction);
  if (new_x < 0 || new_y < 0 || new_x >= 10 || new_y >= 10 ||
      arr[new_x][new_y] == '*') {
    thing.direction = convert_dir(thing.direction);
  } else {
    thing.x = new_x;
    thing.y = new_y;
  }
}

int convert_int(char direction) {
  if (direction == 'N') return 0;
  if (direction == 'E') return 1;
  if (direction == 'S') return 2;
  return 3;
}

int main() {
  ifstream fin("ttwo.in");
  ofstream fout("ttwo.out");

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fin >> arr[i][j];
      if (arr[i][j] == 'F') {
        farmer.x = i;
        farmer.y = j;
        farmer.direction = 'N';
      }
      if (arr[i][j] == 'C') {
        cows.x = i;
        cows.y = j;
        cows.direction = 'N';
      }
    }
  }
  int minutes = 0;
  while (true) {
    if (farmer.x == cows.x && farmer.y == cows.y) {
      fout << minutes << "\n";
      return 0;
    }
    if (minutes > 160000) {
      fout << "0\n";
      return 0;
    }
    move(farmer);
    move(cows);
    minutes++;
  }

  return 0;
}
