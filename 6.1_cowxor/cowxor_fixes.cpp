/*
ID: dermotl1
LANG: C++
PROG: cowxor
*/

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

struct Trie_Node {
  int children[2];
  int pos;
} __attribute__((packed));

Trie_Node* information;
int next_free = 1;

void insert(int num, int poss) {
  int index = 0;
  for (int i = 20; i >= 0; --i) {
    int bit = (num >> i) & 1;
    if (information[index].children[bit] == -1) {
      information[index].children[bit] = next_free;
      information[next_free].children[0] = -1;
      information[next_free].children[1] = -1;
      information[next_free].pos = -1;
      next_free++;
    }
    index = information[index].children[bit];
  }
  information[index].pos = poss;
}

pair<int, int> find(int num) {
  int index = 0;
  int max_val = 0;
  for (int i = 20; i >= 0; --i) {
    int bit = (num >> i) & 1;
    int opp_bit = 1 - bit;
    if (information[index].children[opp_bit] != -1) {
      max_val |= (1 << i);
      index = information[index].children[opp_bit];
    } else if (information[index].children[bit] != -1) {
      index = information[index].children[bit];
    } else {
      int p = information[index].pos;
      return {max_val, p};
    }
  }
  int p = information[index].pos;
  return {max_val, p};
}

int main() {
  ifstream fin("cowxor.in");
  ofstream fout("cowxor.out");

  int n;
  fin >> n;
  int max_nodes = (n + 1) * 21;
  information = new Trie_Node[max_nodes];

  information[0].children[0] = -1;
  information[0].children[1] = -1;
  information[0].pos = -1;

  vector<int> precomputation(n + 1, 0);
  int current_xor = 0;
  for (int i = 1; i <= n; ++i) {
    int temp;
    fin >> temp;
    current_xor ^= temp;
    precomputation[i] = current_xor;
  }

  insert(0, 0);

  int max_val = -1;
  int max_starting = -1;
  int max_ending = -1;

  for (int i = 1; i <= n; ++i) {
    pair<int, int> result = find(precomputation[i]);
    int temp_max = result.first;
    int temp_max_starting = result.second + 1;

    if (temp_max > max_val) {
      max_val = temp_max;
      max_starting = temp_max_starting;
      max_ending = i;
    } else if (temp_max == max_val) {
      if (i < max_ending) {
        max_starting = temp_max_starting;
        max_ending = i;
      } else if (i == max_ending && temp_max_starting > max_starting) {
        max_starting = temp_max_starting;
      }
    }
    insert(precomputation[i], i);
  }

  fout << max_val << " " << max_starting << " " << max_ending << "\n";

  delete[] information;

  return 0;
}
