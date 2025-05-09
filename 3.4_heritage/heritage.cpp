/*
ID: dermotl1
LANG: C++
PROG: heritage
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

char in[27];
int in_length = 0;
char pre[27];
int pre_length = 0;
char post[27];
int post_tracker = 0;

void solve(int in_first, int in_last, int pre_first,
           int pre_last) {  // declare ranges

  if (in_first > in_last) return;

  char root = pre[pre_first];
  int root_tracker;

  for (int i = in_first; i <= in_last; ++i) {
    if (in[i] == root) {
      root_tracker = i;
      break;
    }
  }
  int left_nodes = root_tracker - in_first;

  solve(in_first, root_tracker - 1, pre_first + 1,
        pre_first + left_nodes);  // left branch
  solve(root_tracker + 1, in_last, pre_first + left_nodes + 1,
        pre_last);  // right branch

  post[post_tracker] = root;
  post_tracker++;
}
int main() {
  ifstream fin("heritage.in");
  ofstream fout("heritage.out");

  char temp;
  while (fin.get(temp) && temp != '\n') {
    in[in_length] = temp;
    in_length++;
  }
  while (fin.get(temp) && temp != '\n') {
    pre[pre_length] = temp;
    pre_length++;
  }

  solve(0, in_length - 1, 0, pre_length - 1);

  for (int i = 0; i < post_tracker; i++) {
    fout << post[i];
  }
  fout << "\n";

  return 0;
}