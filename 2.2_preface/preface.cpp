/*
ID: dermotl1
LANG: C++
PROG: preface
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<char> total;  // all i need is the number of times it occurs

void convert(int num) {  // convert it and store it immediately
  while (num >= 1000) {
    total.push_back('M');
    num -= 1000;
  }
  if (num >= 900) {
    total.push_back('C');
    total.push_back('M');
    num -= 900;
  }
  if (num >= 500) {
    total.push_back('D');
    num -= 500;
  }
  if (num >= 400) {
    total.push_back('C');
    total.push_back('D');
    num -= 400;
  }

  while (num >= 100) {
    total.push_back('C');
    num -= 100;
  }
  if (num >= 90) {
    total.push_back('X');
    total.push_back('C');
    num -= 90;
  }
  if (num >= 50) {
    total.push_back('L');
    num -= 50;
  }
  if (num >= 40) {
    total.push_back('X');
    total.push_back('L');
    num -= 40;
  }

  while (num >= 10) {
    total.push_back('X');
    num -= 10;
  }
  if (num >= 9) {
    total.push_back('I');
    total.push_back('X');
    num -= 9;
  }
  if (num >= 5) {
    total.push_back('V');
    num -= 5;
  }
  if (num >= 4) {
    total.push_back('I');
    total.push_back('V');
    num -= 4;
  }

  while (num >= 1) {
    total.push_back('I');
    num -= 1;
  }
}

int main() {
  ofstream fout("preface.out");
  ifstream fin("preface.in");

  int count[256] = {0};  // ascii
  int n;
  fin >> n;

  for (int i = 1; i <= n; i++) {
    convert(i);
  }

  for (int i = 0; i < total.size(); i++) {
    count[total[i]]++;
  }

  if (count['I'] != 0) fout << "I " << count['I'] << "\n";
  if (count['V'] != 0) fout << "V " << count['V'] << "\n";
  if (count['X'] != 0) fout << "X " << count['X'] << "\n";
  if (count['L'] != 0) fout << "L " << count['L'] << "\n";
  if (count['C'] != 0) fout << "C " << count['C'] << "\n";
  if (count['D'] != 0) fout << "D " << count['D'] << "\n";
  if (count['M'] != 0) fout << "M " << count['M'] << "\n";

  return 0;
}
