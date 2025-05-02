/*
ID: dermotl1
LANG: C++
PROG: shopping
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

struct offer {
  int code[5];  // product code
  int counts[5];
  int price;
  int amount;  // amount of diff products
};

int s, b;           // s = special offers, b = to buy
offer offers[100];  // store the offers
int need[5];        // how many of each to buy
int price[5];       // regular price of each
int item_code[5];   // item codes
int min_price = numeric_limits<int>::max();
int solving[6][6][6][6][6];
int offer_count;

int index_return(int x) {
  for (int i = 0; i < 5; ++i) {
    if (item_code[i] == x) return i;
  }
  return -1;
}

int main() {
  ifstream fin("shopping.in");
  ofstream fout("shopping.out");
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      for (int p = 0; p < 6; ++p) {
        for (int q = 0; q < 6; ++q) {
          for (int r = 0; r < 6; ++r) {
            solving[i][j][p][q][r] = numeric_limits<int>::max();
          }
        }
      }
    }
  }

  fin >> offer_count;
  for (int i = 0; i < offer_count; ++i) {
    offer offering;
    fin >> offering.amount;
    for (int j = 0; j < 5; ++j) {
      offering.code[j] = 0;
      offering.counts[j] = 0;
    }
    for (int j = 0; j < offering.amount; ++j) {
      int c, k;
      fin >> c >> k;
      int index = index_return(c);
      if (index == -1) {
        for (int p = 0; p < 5; ++p) {
          if (item_code[p] == 0) {
            item_code[p] = c;
            index = p;
            break;
          }
        }
      }
      offering.code[index] = c;
      offering.counts[index] = k;
    }
    fin >> offering.price;
    offers[i] = offering;
  }
  for (int i = 0; i < 5; ++i) {
    need[i] = 0;
    price[i] = 0;
  }

  int buy_count;
  fin >> buy_count;
  for (int i = 0; i < buy_count; ++i) {
    int c, k, p;
    fin >> c >> k >> p;
    int index = index_return(c);
    if (index == -1) {
      for (int j = 0; j < 5; ++j) {
        if (item_code[j] == 0) {
          item_code[j] = c;
          index = j;
          break;
        }
      }
    }
    need[index] = k;
    price[index] = p;
  }

  for (int a = 0; a <= need[0]; ++a) {
    for (int b = 0; b <= need[1]; ++b) {
      for (int c = 0; c <= need[2]; ++c) {
        for (int d = 0; d <= need[3]; ++d) {
          for (int e = 0; e <= need[4]; ++e) {
            int cost = a * price[0] + b * price[1] + c * price[2] +
                       d * price[3] + e * price[4];
            for (int i = 0; i < offer_count; ++i) {
              offer offering = offers[i];
              int new_a = a - offering.counts[0];
              int new_b = b - offering.counts[1];
              int new_c = c - offering.counts[2];
              int new_d = d - offering.counts[3];
              int new_e = e - offering.counts[4];
              if (new_a >= 0 && new_b >= 0 && new_c >= 0 && new_d >= 0 &&
                  new_e >= 0) {
                cost = min(cost, solving[new_a][new_b][new_c][new_d][new_e] +
                                     offering.price);
              }
            }
            solving[a][b][c][d][e] = cost;
          }
        }
      }
    }
  }
  fout << solving[need[0]][need[1]][need[2]][need[3]][need[4]] << "\n";
  return 0;
}
