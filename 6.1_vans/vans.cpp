/*
ID: dermotl1
LANG: C++
PROG: vans
*/

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

struct Big {
  vector<int> digits;
};

Big createNumber(int num = 0) {
  Big result;
  if (num == 0) {
    result.digits.push_back(0);
  } else {
    while (num > 0) {
      result.digits.push_back(num % 10);
      num /= 10;
    }
  }
  return result;
}

Big addNumbers(const Big& a, const Big& b) {
  Big result;
  result.digits.clear();

  int carry = 0;
  int minimum = max(a.digits.size(), b.digits.size());

  for (int i = 0; i < minimum || carry > 0; ++i) {
    int sum = carry;
    if (i < a.digits.size()) sum += a.digits[i];
    if (i < b.digits.size()) sum += b.digits[i];

    result.digits.push_back(sum % 10);
    carry = sum / 10;
  }

  return result;
}

Big multiplyNumbers(const Big& a, int multiply) {
  Big result;

  int carry = 0;
  for (int i = 0; i < a.digits.size() || carry > 0; ++i) {
    int product = carry;
    if (i < a.digits.size()) product += a.digits[i] * multiply;

    result.digits.push_back(product % 10);
    carry = product / 10;
  }

  return result;
}

Big subtractNumbers(const Big& a, const Big& b) {
  Big result;

  int borrow = 0;
  for (int i = 0; i < a.digits.size(); ++i) {
    int difference = a.digits[i] - borrow;
    if (i < b.digits.size()) difference -= b.digits[i];

    if (difference < 0) {
      difference += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }

    result.digits.push_back(difference);
  }

  while (result.digits.size() > 1 && result.digits.back() == 0) {
    result.digits.pop_back();
  }

  return result;
}

int main() {
  ifstream fin("vans.in");
  ofstream fout("vans.out");

  int n;
  fin >> n;

  vector<Big> incomplete(max((n + 1), 4));
  vector<Big> complete(max((n + 1), 4));

  incomplete[1] = createNumber(2);
  incomplete[2] = createNumber(2);
  incomplete[3] = createNumber(8);
  complete[1] = createNumber(0);
  complete[2] = createNumber(2);
  complete[3] = createNumber(4);

  for (int i = 4; i <= n; ++i) {
    Big temp1 = multiplyNumbers(complete[i - 1], 2);
    Big temp2 = addNumbers(temp1, incomplete[i - 1]);
    Big temp3 = addNumbers(temp2, incomplete[i - 2]);
    incomplete[i] = subtractNumbers(temp3, incomplete[i - 3]);

    complete[i] = addNumbers(complete[i - 1], incomplete[i - 1]);
  }

  for (int i = complete[n].digits.size() - 1; i >= 0; --i) {
    fout << complete[n].digits[i];
  }

  fout << "\n";

  return 0;
}