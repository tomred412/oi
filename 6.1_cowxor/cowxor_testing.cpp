/*
ID: dermotl1
LANG: C++
PROG: cowxor
*/

#include <algorithm>
#include <bitset>
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
#include <utility>
#include <vector>

using namespace std;

const int depth = 21;
const int leaf_start = 1 << depth;
const int max_nodes =
    1 << (depth + 1);  // explicity make array of full 21 size binary tree

bitset<max_nodes> node_exists;  // which ones exist in tree
int leaf_array[1 << depth];     // track pos (final)

void insert(int num, int i) {
  int node = 1;
  for (int j = 20; j >= 0; --j) {
    int bit = (num >> j) & 1;
    node = node * 2 + bit;
    node_exists.set(node);
  }
  int index = node - leaf_start;
  if (i > leaf_array[index]) {
    leaf_array[index] = i;
  }
}

int find(int num) {
  int node = 1;
  for (int j = 20; j >= 0; --j) {
    int bit = (num >> j) & 1;
    int desired = 1 - bit;
    int next_node = node * 2 + desired;
    if (node_exists.test(next_node)) {
      node = next_node;
    } else {
      node = node * 2 + bit;
    }
  }
  return leaf_array[node - leaf_start];
}

int main() {
  ifstream fin("cowxor.in");
  ofstream fout("cowxor.out");

  fill(leaf_array, leaf_array + (1 << depth), -1);
  node_exists.reset();

  int n;
  fin >> n;
  vector<int> precomputation(n + 1, 0);
  insert(0, 0);

  int best_xor = -1;
  int best_start = -1;
  int best_end = -1;

  for (int i = 1; i <= n; i++) {
    int a;
    fin >> a;
    precomputation[i] = precomputation[i - 1] ^ a;

    int j = find(precomputation[i]);
    int xor_val = precomputation[i] ^ precomputation[j];
    int start = j + 1;
    int end = i;

    if (xor_val > best_xor) {
      best_xor = xor_val;
      best_start = start;
      best_end = end;
    } else if (xor_val == best_xor) {
      if (i < best_end) {
        best_end = end;
        best_start = start;
      } else if (i == best_end && start > best_start) {
        best_start = start;
      }
    }

    insert(precomputation[i], i);
  }

  fout << best_xor << " " << best_start << " " << best_end << endl;

  return 0;
}