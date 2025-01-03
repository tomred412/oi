/*
ID: dermotl1
LANG: C++
PROG: transform
*/

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool equality(char a[10][10], char b[10][10], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (a[i][j] != b[i][j]) {
        return false;
        // stop at inequal value
      }
    }
  }
  return true;
}

void rotation(char a[10][10], int n) {
  char b[10][10];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      b[j][n - i - 1] = a[i][j];
    }
  }
  // make another array equal to the changed array

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a[i][j] = b[i][j];
      // make that array equal to original array and output nothing
    }
  }
}

void reflection(char a[10][10], int n) {
  char b[10][10];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      b[i][j] = a[i][n - j - 1];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a[i][j] = b[i][j];
    }
  }
}
// same thing

int main() {
  ofstream fout("transform.out");
  ifstream fin("transform.in");

  int n;
  fin >> n;
  // take in pattern size

  char before[10][10];
  char after[10][10];
  // initalize arrays

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fin >> before[i][j];
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fin >> after[i][j];
    }
  }

  // rotation, but first temp so no damage
  char temp[10][10];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      temp[i][j] = before[i][j];
    }
  }
  rotation(temp, n);
  if (equality(temp, after, n)) {
    fout << 1 << "\n";
    return 0;
  }
  // temp again (so no damage)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      temp[i][j] = before[i][j];
    }
  }
  // rotate 180
  rotation(temp, n);
  rotation(temp, n);
  if (equality(temp, after, n)) {
    fout << 2 << "\n";
    return 0;
  }
  // temp
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      temp[i][j] = before[i][j];
    }
  }
  // rotate 270
  rotation(temp, n);
  rotation(temp, n);
  rotation(temp, n);
  if (equality(temp, after, n)) {
    fout << 3 << "\n";
    return 0;
  }

  // reflection, but temp first
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      temp[i][j] = before[i][j];
    }
  }
  reflection(temp, n);
  if (equality(temp, after, n)) {
    fout << 4 << "\n";
    return 0;
  }

  // reflection followed by rotation (combo), temp first
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      temp[i][j] = before[i][j];
    }
  }
  reflection(temp, n);
  rotation(temp, n);

  if (equality(temp, after, n)) {
    fout << 5 << "\n";
    return 0;
  }
  // temp
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      temp[i][j] = before[i][j];
    }
  }
  // combo (180)
  reflection(temp, n);
  rotation(temp, n);
  rotation(temp, n);

  if (equality(temp, after, n)) {
    fout << 5 << "\n";
    return 0;
  }
  // temp
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      temp[i][j] = before[i][j];
    }
  }
  // combo (270)
  reflection(temp, n);
  rotation(temp, n);
  rotation(temp, n);
  rotation(temp, n);
  if (equality(temp, after, n)) {
    fout << 5 << endl;
    return 0;
  }

  // no change
  if (equality(before, after, n) == true) {
    fout << 6 << "\n";
    return 0;
  }

  // invalid if nothing applies
  fout << 7 << endl;

  return 0;
}

