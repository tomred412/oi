/*
ID: dermotl1
LANG: C++
PROG: numtri
*/

#include <algorithm>
#include <fstream>

using namespace std;

int triangle[1000][1000];  // the data
int done[1000][1000];      // done already
int r = 0;                 // the rows #

int find(int i, int j) {  // i is row, j is column
  if (i == r - 1)
    return triangle[i][j];  // the sum is itself, it's already at the bottom
  if (done[i][j] != -1) return done[i][j];  // it's done

  int left = find(i + 1, j);
  int right = find(i + 1, j + 1);

  done[i][j] =
      triangle[i][j] + max(left, right);  // add the end to the rest of the sum
  return done[i][j];
}

int main() {
  ofstream fout("numtri.out");
  ifstream fin("numtri.in");

  fin >> r;

  for (int i = 0; i < r; i++) {
    for (int j = 0; j <= i; j++) {
      fin >> triangle[i][j];
      done[i][j] = -1;
    }
  }

  int total_sum = find(0, 0);
  fout << total_sum << "\n";

  return 0;
}
