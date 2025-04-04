/*
ID: dermotl1
LANG: C++
PROG: comehome
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int convert(char a) {
  if ('a' <= a && a <= 'z')
    return a - 'a';  // lowercase = 0-25, uppercase = 26-51
  else
    return a - 'A' + 26;
}
int dist[52][52];

int main() {
  ifstream fin("comehome.in");
  ofstream fout("comehome.out");

  int n, a1, b1, temp;
  char a, b;
  fin >> n;
  for (int i = 0; i < n; i++) {
    fin >> a >> b;
    a1 = convert(a);
    b1 = convert(b);
    fin >> temp;
    if (dist[a1][b1] == 0 || dist[a1][b1] > temp) {
      dist[a1][b1] = temp;
      dist[b1][a1] = temp;
    }
  }
  for (int k = 0; k < 52; k++) {
    for (int i = 0; i < 52; i++) {
      for (int j = 0; j < 52; j++) {
        if (dist[i][k] != 0 && dist[k][j] != 0) {
          if (dist[i][j] == 0 || dist[i][k] + dist[k][j] < dist[i][j]) {
            dist[i][j] = dist[i][k] + dist[k][j];
          }
        }
      }
    }
  }
  int ans = 1000000;
  int answ = 0;
  for (int i = 26; i < 51; i++) {
    if (dist[i][51] != 0 && dist[i][51] < ans) {
      ans = dist[i][51];
      answ = i;
    }
  }
  char answe = 'A' + (answ - 26);
  fout << answe << " " << ans << "\n";

  return 0;
}
