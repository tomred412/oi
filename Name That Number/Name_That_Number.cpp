/*
ID: dermotl1
LANG: C++
PROG: namenum
*/

#include <algorithm>
#include <fstream>

using namespace std;

int main() {
  ofstream fout("namenum.out");
  ifstream fin("namenum.in");
  ifstream dict("dict.txt");

  string line;
  string number;

  fin >> number;
  int output = 0;

  while (dict >> line) {
    string line2 = line;

    int map[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6,
                   6, 6, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0};

    for (int i = 0; i < line.size(); i++) {
      char c = line[i];
      line[i] = map[c - 'A'] + '0';
    }
    if (number == line) {
	output = 1;
	fout << line2 << "\n";
      
      
    }
  }
if (output == 0) fout << "NONE\n";

return 0;
}
