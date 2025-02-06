/*
ID: dermotl1
LANG: C++
PROG: milk
*/

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

struct Farmer {
  int price;
  int units;
};

bool compareFarmers(Farmer i, Farmer j) { return i.price < j.price; }

int main() {
  ifstream fin("milk.in");
  ofstream fout("milk.out");

  Farmer farmers[5000];

  int milk = 0;
  int farmers_number = 0;
  int total = 0;

  fin >> milk >> farmers_number;

  for (int i = 0; i < farmers_number; i++) {
    fin >> farmers[i].price >> farmers[i].units;
  }

  sort(farmers, farmers + farmers_number, compareFarmers);

  for (int i = 0; i < farmers_number; i++) {
    if (milk == 0) break;

    int milk_to_buy = min(milk, farmers[i].units);
    total += milk_to_buy * farmers[i].price;
    milk -= milk_to_buy;
  }

  fout << total << endl;

  return 0;
}
