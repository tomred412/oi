/*
ID: dermotl1
LANG: C++
PROG: shuttle
*/

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct State {
  int board[25];
  int hole;           // pos
  vector<int> moves;  // store prev move
};

int n, total;

bool IsGoal(int* board) {
  if (board[n] != 0) return false;
  for (int i = 0; i < n; ++i) {
    if (board[i] != 2) return false;
  }
  return true;
}

int ConvertBoard(int* board) {
  int converted = 0;
  for (int i = 0; i < total; ++i) {
    converted = converted * 3 + board[i];
  }
  return converted;
}

int main() {
  ifstream fin("shuttle.in");
  ofstream fout("shuttle.out");

  fin >> n;
  total = 2 * n + 1;

  State initial;
  for (int i = 0; i < n; ++i) {
    initial.board[i] = 1;
  }
  initial.board[n] = 0;
  for (int i = n + 1; i < total; ++i) {
    initial.board[i] = 2;
  }
  initial.hole = n;
  initial.moves.clear();

  queue<State> discover;
  set<int> seen;
  discover.push(initial);
  seen.insert(ConvertBoard(initial.board));

  while (!discover.empty()) {
    State front = discover.front();
    discover.pop();

    if (IsGoal(front.board)) {
      for (int i = 0; i < front.moves.size(); ++i) {
        if (i > 0) {
          if (i % 20 == 0)
            fout << "\n";
          else
            fout << " ";
        }
        fout << front.moves[i];
      }
      fout << "\n";
      return 0;
    }
    int save = front.hole;
    for (int j = -2; j <= 2; ++j) {
      if (j == 0) continue;
      int begin = j + save;
      if (begin < 0 || begin >= total) continue;

      if (j == 1 || j == -1) {
        if (!((front.board[begin] == 1 && begin < save) ||
              (front.board[begin] == 2 && begin > save)))
          continue;

      } else {
        int over = save + j / 2;
        if (!((front.board[begin] == 1 && front.board[over] == 2 &&
               begin < save) ||
              (front.board[begin] == 2 && front.board[over] == 1 &&
               begin > save)))
          continue;
      }
      State next = front;
      next.board[save] = next.board[begin];
      next.board[begin] = 0;
      next.hole = begin;
      next.moves.push_back(begin + 1);

      int converted = ConvertBoard(next.board);
      if (seen.find(converted) == seen.end()) {
        seen.insert(converted);
        discover.push(next);
      }
    }
  }

  return 0;
}
