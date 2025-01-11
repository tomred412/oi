/*
ID: dermotl1
LANG: C++
PROG: milk
*/

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

// this array stores the first one, farmer's price
int farmer_price[5000];

// this array stores the second, units of milk
int farmer_units[5000];

bool compareFarmers(int i, int j) { return farmer_price[i] < farmer_price[j]; }

int main() {
  ifstream fin("milk.in");
  ofstream fout("milk.out");

  int milk = 0;
  int farmers_number = 0;
  int total = 0;

  fin >> milk >> farmers_number;

  // this array stores the original order of the farmer's price before the sort
  int original[farmers_number];

  for (int i = 0; i < farmers_number; i++) {
    fin >> farmer_price[i] >> farmer_units[i];
  }

  for (int i = 0; i < farmers_number; i++) {
    original[i] = i;
  }

  sort(original, original + farmers_number, compareFarmers);

  for (int i = 0; i < farmers_number; i++) {
    if (milk == 0) break;

    int farmer_number_in_original = original[i];
    int milk_to_buy = min(milk, farmer_units[farmer_number_in_original]);
    total += milk_to_buy * farmer_price[farmer_number_in_original];
    milk -= milk_to_buy;
  }

  fout << total << endl;

  return 0;
}

