#include <bits/stdc++.h>

using namespace std;

int main() {
  int array[7];
  for (int i = 0; i < 7; i++) {
    cin >> array[i];
  }
  sort(array, array + 7);
  int a = array[0];
  int b = array[1];
  int c = array[6] - a - b;

  cout << a << " " << b << " " << c << "\n";
}
