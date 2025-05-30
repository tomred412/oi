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

int main() {
  int answer = 0;
  int n, q;
  cin >> n >> q;

  vector<int> bricks(3 * n * n, n);  // when it reaches 0, no brick left
  vector<vector<vector<bool>>> carved(
      n, vector<vector<bool>>(
             n, vector<bool>(n, false)));  // if i j k has been carved

  for (int x = 0; x < q; ++x) {
    int i, j, k;
    cin >> i >> j >> k;
    carved[i][j][k] = true;

    int affected[3];
    affected[0] = j * n + k;              // i brick
    affected[1] = n * n + i * n + k;      // j brick
    affected[2] = 2 * n * n + i * n + j;  // k brick

    for (int y = 0; y < 3; ++y) {
      bricks[affected[y]]--;
      if (bricks[affected[y]] == 0) answer++;
    }
    cout << answer << "\n";
  }
  return 0;
}