/*
ID: dermotl1
LANG: C++
PROG: milk3
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

bool visited[21][21][21]; //track already visited
bool possible[21]; //if a = 0, then c = (in this array)
int a_cap, b_cap, c_cap; //capacity

void pour(int a, int b, int c) { //simulation of pouring
    if (visited[a][b][c] == true) return; //already checked, return immediately
    visited[a][b][c] = true; //it's now checked
    
    if (a == 0) possible[c] = true; //it's completed

    //try all pour
    
    //A -> B
    int pour_amount = min(a, b_cap - b);
    pour(a - pour_amount, b + pour_amount, c); //call it again each time to check more and more

    // A -> C
    pour_amount = min(a, c_cap - c);
    pour(a - pour_amount, b, c + pour_amount);

    // B -> A
    pour_amount = min(b, a_cap - a);
    pour(a + pour_amount, b - pour_amount, c);

    // B -> C
    pour_amount = min(b, c_cap - c);
    pour(a, b - pour_amount, c + pour_amount);

    // C -> A
    pour_amount = min(c, a_cap - a);
    pour(a + pour_amount, b, c - pour_amount);

    // C -> B
    pour_amount = min(c, b_cap - b);
    pour(a, b + pour_amount, c - pour_amount);
}

int main() {
    ifstream fin("milk3.in");
    ofstream fout("milk3.out");

    fin >> a_cap >> b_cap >> c_cap;

    //start from the default (a and b are empty at first, but c is filled to its capacity)
    pour(0, 0, c_cap);

    bool first = true;
    for (int i = 0; i <= c_cap; i++) {
        if (possible[i] == true) {
            if (first == false) fout << " "; //there needs to be a space
            fout << i;
            first = false;
        }
    }
    fout << "\n";

    return 0;
}
