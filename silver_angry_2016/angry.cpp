#include <algorithm>
#include <cmath>
#include <fstream>
#include <set>
#include <string>
#include <vector>
using namespace std;

vector<int> hay;
int n, k;

bool search(int find) {
  int cows = 0;
  int i = 0;
  for (int i = 0; i < n; cows++) {
    int pos = hay[i] + find;
    while (i < n && hay[i] <= pos) {
      i++;
    }
    pos = hay[i - 1] + find;
    while (i < n && hay[i] <= pos) {
      i++;
    }
    if (cows > k) return false;
  }
  return true;
}

int main() {
  ofstream fout("angry.out");
  ifstream fin("angry.in");

  fin >> n >> k;

  for (int i = 0; i < n; i++) {
    int temp;
    fin >> temp;
    hay.push_back(temp);
  }

  sort(hay.begin(), hay.end());

  int low = 0;
  int high = hay[n - 1] - hay[0];
  int a = high;

  while (low <= high) {
    int b = (low + high) / 2;
    if (search(b)) {
      a = b;
      high = b - 1;
    } else {
      low = b + 1;
    }
  }
  fout << a << "\n";

  return 0;
}
