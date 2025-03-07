#include <bits/stdc++.h>

#include <fstream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
  ofstream fout("herding.out");
  ifstream fin("herding.in");

  int array[3];
  fin >> array[0] >> array[1] >> array[2];

  sort(array, array + 3);

  if (array[2] - array[1] == 1 && array[1] - array[0] == 1) {
    fout << "0\n0\n";
    return 0;
  }

  if (array[1] - array[0] == 2 || array[2] - array[1] == 2)
    fout << "1\n";
  else
    fout << "2\n";

  int something = max(array[1] - array[0], array[2] - array[1]);
  fout << something - 1 << "\n";
}
