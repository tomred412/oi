#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> array(n);
  for (int i = 0; i < n; i++) {
    cin >> array[i];
  }

  vector<int> num(n + 1, 0);
  for (int i = 0; i < array.size(); i++) {
    if (array[i] <= n) {  // no need for >n
      num[array[i]]++;
    }
  }
  int miss = 0;
  int extra = 0;

  for (int i = 0; i <= n; i++) {
    cout << max(num[i], miss) << "\n";
    if (num[i] == 0) miss++;
  }

  return 0;
}
