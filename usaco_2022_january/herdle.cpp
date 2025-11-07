#include <algorithm>
#include <bitset>
#include <cctype>
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
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int frequency_answer[26];
int frequency_guess[26];

int main() {
  string answer[3];
  string guess[3];

  for (int i = 0; i < 3; ++i) {
    cin >> answer[i];
  }
  for (int i = 0; i < 3; ++i) {
    cin >> guess[i];
  }
  int green = 0;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (answer[i][j] == guess[i][j]) {
        ++green;
      } else {
        ++frequency_answer[answer[i][j] - 'A'];
        ++frequency_guess[guess[i][j] - 'A'];
      }
    }
  }
  int yellow = 0;
  for (int i = 0; i < 26; i++) {
    yellow += min(frequency_answer[i], frequency_guess[i]);
  }

  cout << green << "\n" << yellow << "\n";
  return 0;
}