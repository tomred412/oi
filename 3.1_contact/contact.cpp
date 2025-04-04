/*
ID: dermotl1
LANG: C++
PROG: contact
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct pattern {
  int freq;
  int length;
  int value;
};

bool compare(pattern a, pattern b) {
  if (a.freq != b.freq) return a.freq > b.freq;
  if (a.length != b.length) return a.length < b.length;
  return a.value < b.value;
}

char datas[200001];
int counts[13][4096];  // first = length, second = the value in binary, it leads
pattern patterns[5000];
int pattern_count = 0;

int main() {
  ifstream fin("contact.in");
  ofstream fout("contact.out");

  int a, b, n;
  fin >> a >> b >> n;

  char c;
  int length = 0;
  while (fin >> c) {
    if (c == '0' || c == '1') {
      datas[length++] = c;
    }
  }

  for (int len = a; len <= b;
       ++len) {  // count the number of each pattern of length i
    int maxi = 1 << len;
    for (int i = 0; i <= length - len; ++i) {
      int val = 0;
      for (int j = 0; j < len; ++j) {
        val = val * 2 + (datas[i + j] - '0');
      }
      counts[len][val]++;
    }
  }

  for (int len = a; len <= b; ++len) {
    for (int val = 0; val < (1 << len); ++val) {
      if (counts[len][val] > 0) {
        patterns[pattern_count].length = len;
        patterns[pattern_count].value = val;
        patterns[pattern_count].freq = counts[len][val];
        pattern_count++;
      }
    }
  }

  sort(patterns, patterns + pattern_count, compare);

  int output_count = 0;
  int i = 0;
  while (i < pattern_count && output_count < n) {
    int current_freq = patterns[i].freq;
    fout << current_freq << "\n";
    int printed = 0;
    while (i < pattern_count && patterns[i].freq == current_freq) {
      for (int q = patterns[i].length - 1; q >= 0; --q) {
        if (patterns[i].value / (1 << q) % 2 == 1) {
          fout << '1';
        } else {
          fout << '0';
        }
      }
      printed++;
      i++;

      if (printed % 6 == 0 || i >= pattern_count ||
          patterns[i].freq != current_freq) {
        fout << "\n";
      } else {
        fout << " ";
      }
    }
    output_count++;
  }

  return 0;
}
