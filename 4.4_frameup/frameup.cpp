/*
ID: dermotl1
LANG: C++
PROG: frameup
*/

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int height, width;
char grid[31][31];
bool letters[27];
int top[27], bottom[27], lefts[27],
    rights[27];  // top, bottom = rows (for sides); left, right = columns (for
                 // sides)
bool is_below_graph[27][27];  // i is below j? if true
int covering_number[27];      // how many frames above this frame? (i)

char result[27];
vector<string> final_results;

bool visited[27];
int frame_count = 0;

void FindBorders() {
  for (int i = 0; i < 27; ++i) {
    top[i] = 30;
    bottom[i] = -1;
    lefts[i] = 30;
    rights[i] = -1;
  }
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      char temp = grid[i][j];
      if (temp >= 'A' && temp <= 'Z') {
        int number = temp - 'A';
        letters[number] = true;

        top[number] = min(top[number], i);
        bottom[number] = max(bottom[number], i);
        lefts[number] = min(lefts[number], j);
        rights[number] = max(rights[number], j);
      }
    }
  }
  for (int i = 0; i < 26; ++i) {
    if (letters[i]) frame_count++;
  }
}

void GetOrder() {
  for (int i = 0; i < 26; ++i) {
    if (!letters[i]) continue;

    int row = top[i];  // check the top border
    for (int j = lefts[i]; j <= rights[i]; ++j) {
      char temp = grid[row][j];
      if (temp >= 'A' && temp <= 'Z' && temp - 'A' != i)
        is_below_graph[i][temp - 'A'] = true;
    }

    row = bottom[i];  // check bottom
    for (int j = lefts[i]; j <= rights[i]; ++j) {
      char temp = grid[row][j];
      if (temp >= 'A' && temp <= 'Z' && temp - 'A' != i)
        is_below_graph[i][temp - 'A'] = true;
    }

    int column = lefts[i];  // check left
    for (int j = top[i]; j <= bottom[i]; ++j) {
      char temp = grid[j][column];
      if (temp >= 'A' && temp <= 'Z' && temp - 'A' != i)
        is_below_graph[i][temp - 'A'] = true;
    }

    column = rights[i];  // check right
    for (int j = top[i]; j <= bottom[i]; ++j) {
      char temp = grid[j][column];
      if (temp >= 'A' && temp <= 'Z' && temp - 'A' != i)
        is_below_graph[i][temp - 'A'] = true;
    }
  }
  for (int i = 0; i < 26; ++i) {
    for (int j = 0; j < 26; ++j) {
      if (is_below_graph[i][j]) covering_number[j]++;
    }
  }
}

void ObtainSolutions(int counts) {
  if (counts == frame_count) {
    result[counts] = '\0';
    final_results.push_back(string(result));
    return;
  }

  for (int i = 0; i < 26; ++i) {
    if (letters[i] && !visited[i] && covering_number[i] == 0) {
      visited[i] = true;
      for (int j = 0; j < 26; ++j) {
        if (is_below_graph[i][j]) covering_number[j]--;
      }
      result[counts] = 'A' + i;
      ObtainSolutions(counts + 1);

      visited[i] = false;  // go back, redo
      for (int j = 0; j < 26; ++j) {
        if (is_below_graph[i][j]) covering_number[j]++;
      }
    }
  }
}

int main() {
  ifstream fin("frameup.in");
  ofstream fout("frameup.out");

  fin >> height >> width;
  for (int i = 0; i < height; ++i) {
    fin >> grid[i];
  }

  FindBorders();
  GetOrder();
  ObtainSolutions(0);

  sort(final_results.begin(), final_results.end());
  for (auto it : final_results) {
    fout << it << "\n";
  }

  return 0;
}
