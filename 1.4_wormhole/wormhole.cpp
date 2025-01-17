/*
ID: dermotl1
LANG: C++
PROG: wormhole
*/

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int n = 0;
int x[12];         // x coord
int y[12];         // y coord
int pairings[12];  // pairings for every wormhole, so if it's pairings[i], then
                   // it's the number wormhole paired with it
int closest_wormhole[12];  // set it to -1 if it's not found, but if it is it's
                           // the closest wormhole on the right
int total = 0;             // number of pairings to cause infinite

bool infinite() {
  for (int i = 0; i < n; i++) {
    int pos = i;     // current position
    int amount = 0;  // check if the amount of steps is greater than n, if it
                     // is, it's infinite
    while (amount < n) {
      pos = closest_wormhole[pairings[pos]];  // pairings[pos] is the wormhole
                                              // paired, then find wormhole
      if (pos == -1) break;                   // if it's -1, then none exists
      amount++;
    }
    if (amount >= n) return true;
  }
  return false;
}

void wormholes() {
  int i = 0;
  for (i = 0; i < n; i++) {
    if (pairings[i] == -1) break;  // find first wormhole unpaired
  }

  if (i == n) {  // if everything is paired
    if (infinite() == true) total++;
    return;
  }

  for (int j = i + 1; j < n; j++) {  // one wormhole can only pair with 1 other
    if (pairings[j] == -1) {         // pair wormhole i with j
      pairings[i] = j;
      pairings[j] = i;
      wormholes();
      pairings[i] = pairings[j] = -1;  // backtrack
    }
  }
}

int main() {
  ofstream fout("wormhole.out");
  ifstream fin("wormhole.in");

  fin >> n;
  for (int i = 0; i < n; i++) {
    fin >> x[i] >> y[i];
  }

  // closest right wormhole for each wormhole
  for (int i = 0; i < n; i++) {
    closest_wormhole[i] = -1;

    for (int j = 0; j < n; j++) {
      if (y[i] == y[j] && x[j] > x[i]) {  // are they in the same row (y) and is
                                          // it to the right (x[j] > x[i])
        if (closest_wormhole[i] == -1 ||
            x[j] < x[closest_wormhole[i]]) {  // is it the closest
          closest_wormhole[i] = j;            // update it
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    pairings[i] = -1;
  }

  wormholes();

  fout << total << "\n";

  return 0;
}

