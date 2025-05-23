/*
ID: dermotl1
LANG: C++
PROG: job
*/

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main() {
  ifstream fin("job.in");
  ofstream fout("job.out");
  int n, m1, m2;
  fin >> n >> m1 >> m2;

  vector<int> a_times(m1);
  vector<int> b_times(m2);

  for (int i = 0; i < m1; ++i) {
    fin >> a_times[i];
  }

  for (int i = 0; i < m2; ++i) {
    fin >> b_times[i];
  }

  vector<int> a_free_time(m1);  // at which time machine a becomes free again
  for (int i = 0; i < m1; ++i) {
    a_free_time[i] = a_times[i];
  }
  vector<int> a_store_finished;  // when each job finished using machine a

  for (int i = 0; i < n; ++i) {
    int best_a = 0;
    for (int j = 0; j < m1; ++j) {
      if (a_free_time[j] < a_free_time[best_a]) best_a = j;
    }

    a_store_finished.push_back(a_free_time[best_a]);
    a_free_time[best_a] += a_times[best_a];
  }

  int final_a_time =
      *max_element(a_store_finished.begin(), a_store_finished.end());

  sort(a_store_finished.begin(), a_store_finished.end());
  vector<int> b_free_time(m2);

  for (int i = 0; i < m2; ++i) {
    b_free_time[i] = b_times[i];
  }

  vector<int> b_store_finished(n);

  for (int i = n - 1; i >= 0; --i) {
    int best_b = 0;
    for (int j = 0; j < m2; ++j) {
      if (b_free_time[j] < b_free_time[best_b]) best_b = j;
    }
    b_store_finished[i] = a_store_finished[i] + b_free_time[best_b];
    b_free_time[best_b] += b_times[best_b];
  }

  int final_b_time =
      *max_element(b_store_finished.begin(), b_store_finished.end());

  fout << final_a_time << " " << final_b_time << "\n";

  return 0;
}