/*
ID: dermotl1
LANG: C++
PROG: pprime
*/

#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

int storage[1000000];
int total = 2;  // there will be 2 terms already, 5 and 7
int a;
int b;

bool prime(int n) {
  if (n < 2) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  int limit = sqrt(n);
  for (int i = 3; i <= limit; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

void store(int i) {
  if (i >= a && i <= b && prime(i)) {
    storage[total] = i;
    total++;
  }
}

void two() {
  for (int d1 = 1; d1 <= 9; d1++) {
    int i = d1 * 10 + d1;
    if (i > b) return;
    store(i);
  }
}

void three() {
  for (int d1 = 1; d1 <= 9; d1++) {
    for (int d2 = 0; d2 <= 9; d2++) {
      int i = d1 * 100 + d2 * 10 + d1;
      if (i > b) return;
      store(i);
    }
  }
}

void four() {
  for (int d1 = 1; d1 <= 9; d1++) {
    for (int d2 = 0; d2 <= 9; d2++) {
      int i = d1 * 1000 + d2 * 100 + d2 * 10 + d1;
      if (i > b) return;
      store(i);
    }
  }
}

void five() {
  for (int d1 = 1; d1 <= 9; d1++) {
    for (int d2 = 0; d2 <= 9; d2++) {
      for (int d3 = 0; d3 <= 9; d3++) {
        int i = d1 * 10000 + d2 * 1000 + d3 * 100 + d2 * 10 + d1;
        if (i > b) return;
        store(i);
      }
    }
  }
}

void six() {
  for (int d1 = 1; d1 <= 9; d1++) {
    for (int d2 = 0; d2 <= 9; d2++) {
      for (int d3 = 0; d3 <= 9; d3++) {
        int i = d1 * 100000 + d2 * 10000 + d3 * 1000 + d3 * 100 + d2 * 10 + d1;
        if (i > b) return;
        store(i);
      }
    }
  }
}

void seven() {
  for (int d1 = 1; d1 <= 9; d1++) {
    for (int d2 = 0; d2 <= 9; d2++) {
      for (int d3 = 0; d3 <= 9; d3++) {
        for (int d4 = 0; d4 <= 9; d4++) {
          int i = d1 * 1000000 + d2 * 100000 + d3 * 10000 + d4 * 1000 +
                  d3 * 100 + d2 * 10 + d1;
          if (i > b) return;
          store(i);
        }
      }
    }
  }
}

void eight() {
  for (int d1 = 1; d1 <= 9; d1++) {
    for (int d2 = 0; d2 <= 9; d2++) {
      for (int d3 = 0; d3 <= 9; d3++) {
        for (int d4 = 0; d4 <= 9; d4++) {
          int i = d1 * 100000000 + d2 * 1000000 + d3 * 100000 + d4 * 10000 +
                  d4 * 1000 + d3 * 100 + d2 * 10 + d1;
          if (i > b) return;
          store(i);
        }
      }
    }
  }
}

int main() {
  ifstream fin("pprime.in");
  ofstream fout("pprime.out");

  storage[0] = 5;
  storage[1] = 7;

  fin >> a >> b;

  two();
  three();
  four();
  five();
  six();
  seven();
  eight();

  if (a == 5) {
    for (int i = 0; i < total; i++) {
      fout << storage[i] << "\n";
    }
  }

  if (a > 5 && a <= 7) {
    for (int i = 1; i < total; i++) {
      fout << storage[i] << "\n";
    }
  }

  if (a > 7) {
    for (int i = 2; i < total; i++) {
      fout << storage[i] << "\n";
    }
  }
  return 0;
}
