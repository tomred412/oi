/*
ID: dermotl1
LANG: C++
PROG: hamming
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<int> valid;  // store valid ones

int N;
int B;
int D;

int hamming(int a, int b) {
  int num = 0;
  for (int i = 0; i < B; i++) {
    if ((a % 2) != (b % 2)) num++;
    a = a / 2;
    b = b / 2;
  }
  return num;
}

bool works(int num) {
  for (int i = 0; i < valid.size(); i++) {
    if (hamming(valid[i], num) < D) return false;
  }
  return true;
}

int main() {
  ofstream fout("hamming.out");
  ifstream fin("hamming.in");

  fin >> N >> B >> D;

  for (int i = 0; valid.size() < N; i++) {
    if (works(i)) valid.push_back(i);
  }

  for (int i = 0; i < N; i++) {
    if (i > 0) {
      if (i % 10 == 0)
        fout << "\n";
      else
        fout << " ";
    }
    fout << valid[i];
  }
  fout << "\n";
  return 0;
}
