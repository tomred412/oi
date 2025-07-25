/*
ID: dermotl1
LANG: C++
PROG: charrec
*/

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int CompareCharacterStrings(const string& a, const string& b) {
  int count = 0;
  for (int i = 0; i < 20; ++i) {
    if (a[i] != b[i]) count++;
  }
  return count;
}

int ReturnErrorRate(const vector<string>& input, int start, int length,
                    const vector<vector<string>>& font, int font_char_number) {
  if (length == 20) {
    int error = 0;
    for (int i = 0; i < 20; ++i) {
      error +=
          CompareCharacterStrings(input[start + i], font[font_char_number][i]);
    }
    return error;
  }

  if (length == 21) {
    int min_error = numeric_limits<int>::max();

    for (int i = 0; i < 20;
         ++i) {  // try all lines for duplication, i want only 20 because only
                 // 20 are correct (dupe)
      int error = 0;
      int number = 0;  // number (minus start) of actual, corrupt

      for (int j = 0; j < 20; ++j) {  // number of perfect, correct

        if (j == i) {  // at duplication
          error += min(CompareCharacterStrings(input[start + number],
                                               font[font_char_number][j]),
                       CompareCharacterStrings(
                           input[start + number + 1],
                           font[font_char_number][j]));  // find the better dupe
          number += 2;

        } else {
          error += CompareCharacterStrings(input[start + number],
                                           font[font_char_number][j]);
          number++;
        }
      }
      min_error = min(min_error, error);
    }
    return min_error;
  }

  if (length == 19) {
    int min_error = numeric_limits<int>::max();
    for (int i = 0; i < 20; ++i) {
      int error = 0;
      int number = 0;

      for (int j = 0; j < 20; ++j) {
        if (i == j) continue;  // skip it since missing
        error += CompareCharacterStrings(
            input[start + number],
            font[font_char_number][j]);  // find min error
        number++;
      }
      min_error = min(min_error, error);
    }
    return min_error;
  }
  return numeric_limits<int>::max();
}

int main() {
  ios_base::sync_with_stdio(false);

  ifstream fin("charrec.in");
  ifstream fon("font.in");
  ofstream fout("charrec.out");

  vector<vector<string>> font(27, vector<string>(20));
  int n;
  fon >> n;
  string newline;
  getline(fon, newline);

  for (int i = 0; i < 27; ++i) {
    for (int j = 0; j < 20; ++j) {
      getline(fon, font[i][j]);
    }
  }

  int n2;
  fin >> n2;
  string newline2;
  getline(fin, newline2);

  vector<string> input(n2);
  for (int i = 0; i < n2; i++) {
    getline(fin, input[i]);
  }
  /*
    string answer = "";
    int pos = 0;

    while (pos < n2) {
      int best_error = numeric_limits<int>::max();
      char best_char = '?';
      int best_length = 0;

      int lengths[3] = {20, 19, 21};
      for (auto it : lengths) {
        if ((pos + it) > n2) continue;

        for (int j = 0; j < 27; ++j) {
          int error = ReturnErrorRate(input, pos, it, font, j);

          if (error < best_error) {
            best_error = error;
            if (j == 0) {
              best_char = ' ';
            } else {
              best_char = 'a' + (j - 1);
            }
            best_length = it;
          }
        }
      }
      answer += best_char;
      pos += best_length;
    }

    fout << answer << "\n";
  */

  vector<int> min_total_error(
      n2 + 1,
      numeric_limits<int>::max());  //[i] = min_total_error for first i lines
  vector<char> characters(n2 + 1, '?');  // characters for the i array
  vector<int> lengths(n2 + 1, 0);        // lengths for the chars

  min_total_error[0] = 0;

  for (int i = 1; i <= n2; ++i) {  // find the best error rate for first i
    int lens[3] = {19, 20, 21};    // try all lengths

    for (int length : lens) {
      if (i >= length) {  // make sure i actually makes sense
        int start = i - length;
        if (min_total_error[start] == numeric_limits<int>::max()) {
          continue;  // infinity, meaning cannot have solution
        }

        int best_error_for_here = numeric_limits<int>::max();
        char best_char_for_here = '?';

        // try all
        for (int j = 0; j < 27; ++j) {
          int current_error = ReturnErrorRate(input, start, length, font, j);

          if (current_error < best_error_for_here) {
            best_error_for_here = current_error;
            if (j == 0)
              best_char_for_here = ' ';
            else
              best_char_for_here = 'a' + (j - 1);
          }
        }

        // if new is better update
        if ((min_total_error[start] + best_error_for_here) <
            min_total_error[i]) {
          min_total_error[i] =
              min_total_error[start] +
              best_error_for_here;  // ok this needs to be adding it up once we
                                    // build the char
          lengths[i] = length;
          characters[i] = best_char_for_here;
        }
      }
    }
  }

  string answer = "";
  int pos = n2;
  while (pos > 0) {
    answer += characters[pos];
    pos -= lengths[pos];
  }
  reverse(answer.begin(), answer.end());

  fout << answer << "\n";

  return 0;
}
