/*
ID: dermotl1
LANG: C++
PROG: sprime
*/

#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

int n;
int results[10000];
int total = 0;

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

void generate(int num,
              int length) {  // length = current length, num = current num
  if (length == n) {
    results[total] = num;
    total++;
    return;
  }

  int digits[4] = {1, 3, 7, 9};  // odd, prime ending digits (ex. 31, 23, 17,
                                 // 29)
  for (int i = 0; i < 4; i++) {
    int new_num = num * 10 + digits[i];
    if (prime(new_num) == true) generate(new_num, length + 1);
  }
}

int main() {
  ifstream fin("sprime.in");
  ofstream fout("sprime.out");

  fin >> n;

  int start[4] = {2, 3, 5, 7};  // prime starting digits
  for (int i = 0; i < 4; i++) {
    generate(start[i], 1);
  }

  for (int i = 0; i < total; i++) {
    fout << results[i] << "\n";
  }

  return 0;
}
