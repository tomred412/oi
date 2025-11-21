/*
ID: dermotl1
LANG: C++
PROG: prime3
*/

#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int target_sum;
int first_digit;
int grid[5][5];

bool good_prefix[6][100000];
bool good_rev_prefix[6][100000];
bool is_prime[100000];

int row_val[5] = {0};
int col_val[5] = {0};
int diag_val = 0;
int anti_diag_val = 0;

int row_sum[5] = {0};
int col_sum[5] = {0};
int diag_sum = 0;
int anti_diag_sum = 0;

vector<string> solutions;

bool isPrime(int n) {
  if (n <= 1) return false;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) return false;
  }
  return true;
}

int getDigitSum(int n) {
  int sum = 0;
  while (n > 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}

void precomputeAll() {
  for (int i = 2; i < 100000; ++i) {
    is_prime[i] = isPrime(i);
  }
  for (int i = 10000; i < 100000; ++i) {
    if (is_prime[i] && getDigitSum(i) == target_sum) {
      int temp = i;
      good_prefix[5][temp] = true;
      temp /= 10;
      good_prefix[4][temp] = true;
      temp /= 10;
      good_prefix[3][temp] = true;
      temp /= 10;
      good_prefix[2][temp] = true;
      temp /= 10;
      good_prefix[1][temp] = true;

      temp = i;
      int rev = 0;
      for (int k = 0; k < 5; ++k) {
        rev = rev * 10 + temp % 10;
        temp /= 10;
      }
      temp = rev;
      good_rev_prefix[5][temp] = true;
      temp /= 10;
      good_rev_prefix[4][temp] = true;
      temp /= 10;
      good_rev_prefix[3][temp] = true;
      temp /= 10;
      good_rev_prefix[2][temp] = true;
      temp /= 10;
      good_rev_prefix[1][temp] = true;
    }
  }
}

void store() {
  string s = "";
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      s += to_string(grid[i][j]);
    }
  }
  solutions.push_back(s);
}

void solve(int x, int y) {
  if (x == 5) {
    store();
    return;
  }

  int next_x = x;
  int next_y = y + 1;
  if (next_y == 5) {
    next_x = x + 1;
    next_y = 0;
  }

  int start_d = 0, end_d = 9;

  if (x == 0 && y == 0) {
    start_d = first_digit;
    end_d = first_digit;
  } else {
    int correct = -1;
    if (y == 4) {
      correct = target_sum - row_sum[x];
      if (correct < 0 || correct > 9) return;
    }

    if (x == 4) {
      int temp = target_sum - col_sum[y];
      if (temp < 0 || temp > 9) return;
      if (correct != -1 && correct != temp) return;
      correct = temp;
    }

    if (x == 4 && y == 4) {
      int temp = target_sum - diag_sum;
      if (temp < 0 || temp > 9) return;
      if (correct != -1 && correct != temp) return;
      correct = temp;
    }

    if (x == 4 && y == 0) {
      int temp = target_sum - anti_diag_sum;
      if (temp < 0 || temp > 9) return;
      if (correct != -1 && correct != temp) return;
      correct = temp;
    }

    if (correct != -1) {
      start_d = correct;
      end_d = correct;
    }
  }

  for (int i = start_d; i <= end_d; ++i) {
    int r_curr = row_val[x] * 10 + i;

    if (!good_prefix[y + 1][r_curr]) continue;

    int c_curr = col_val[y] * 10 + i;

    if (!good_prefix[x + 1][c_curr]) continue;

    int d_curr = diag_val;
    if (x == y) {
      d_curr = diag_val * 10 + i;
      if (!good_prefix[x + 1][d_curr]) continue;
    }

    int ad_curr = anti_diag_val;
    if (x + y == 4) {
      ad_curr = anti_diag_val * 10 + i;
      if (!good_rev_prefix[x + 1][ad_curr]) continue;
    }

    grid[x][y] = i;
    row_val[x] = r_curr;
    col_val[y] = c_curr;

    row_sum[x] += i;
    col_sum[y] += i;

    if (x == y) {
      diag_val = d_curr;
      diag_sum += i;
    }

    if (x + y == 4) {
      anti_diag_val = ad_curr;
      anti_diag_sum += i;
    }

    solve(next_x, next_y);

    row_val[x] /= 10;
    col_val[y] /= 10;

    row_sum[x] -= i;
    col_sum[y] -= i;

    if (x == y) {
      diag_val /= 10;
      diag_sum -= i;
    }

    if (x + y == 4) {
      anti_diag_val /= 10;
      anti_diag_sum -= i;
    }
  }
}

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);

  ifstream fin("prime3.in");
  ofstream fout("prime3.out");

  fin >> target_sum >> first_digit;

  precomputeAll();
  solve(0, 0);

  if (solutions.empty()) {
    fout << "NONE\n";
  } else {
    sort(solutions.begin(), solutions.end());

    for (int i = 0; i < solutions.size(); ++i) {
      if (i > 0) fout << "\n";
      for (int j = 0; j < 25; ++j) {
        fout << solutions[i][j];
        if ((j + 1) % 5 == 0) fout << "\n";
      }
    }
  }
  return 0;
}