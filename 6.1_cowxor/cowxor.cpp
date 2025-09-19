/*
ID: dermotl1
LANG: C++
PROG: cowxor
*/

// this solution uses too much memory (14/20)

#include <algorithm>
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

// precompute xor in an array, but actually it needs to be something special.
// create a struct. xor has special property: cancelling. go up from first to
// the target. too slow though. ok, create an arrray with the struct,
// "trienode". kind of like dp. build it all up, using the trienode. regularly
// it's not enough, trienode makes the time go down from n2, because 0.5 sec
// limit. idk tho, how to implement
// too much memory!!!!

struct Trie_Node {
  int children[2];
  int pos;
};

vector<Trie_Node> information(1, {{-1, -1}, -1});

void insert(int num, int poss) {
  int index = 0;
  for (int i = 20; i >= 0; --i) {
    int bit = (num >> i) & 1;
    if (information[index].children[bit] == -1) {
      information[index].children[bit] = information.size();
      information.push_back({{-1, -1}, -1});
    }
    index = information[index].children[bit];
  }
  information[index].pos = poss;
}

pair<int, int> find(int num) {
  int index = 0;
  int max = 0;
  for (int i = 20; i >= 0; --i) {
    int bit = (num >> i) & 1;
    int opp_bit = 1 - bit;
    if (information[index].children[opp_bit] != -1) {
      max = max | (1 << i);
      index = information[index].children[opp_bit];
    } else {
      index = information[index].children[bit];
    }
  }
  return {max, information[index].pos};
}

int main() {
  ifstream fin("cowxor.in");
  ofstream fout("cowxor.out");

  int n;
  fin >> n;

  vector<int> precomputation(n + 1, 0);
  int current_xor = 0;
  for (int i = 1; i <= n; ++i) {
    int temp;
    fin >> temp;
    current_xor = current_xor ^ temp;
    precomputation[i] = current_xor;
  }

  insert(0, 0);

  int max = -1;
  int max_starting = -1;
  int max_ending = -1;

  for (int i = 1; i <= n; ++i) {
    pair<int, int> result = find(precomputation[i]);
    int temp_max = result.first;
    int temp_max_starting = result.second + 1;

    if (temp_max > max) {
      max = temp_max;
      max_starting = temp_max_starting;
      max_ending = i;
    } else if (temp_max == max) {
      if (i < max_ending) {
        max_starting = temp_max_starting;
        max_ending = i;
      } else if (i == max_ending && temp_max_starting > max_starting) {
        max_starting = temp_max_starting;
      }
    }
    insert(precomputation[i], i);
  }

  fout << max << " " << max_starting << " " << max_ending << "\n";

  return 0;
}