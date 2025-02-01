/*
ID: dermotl1
LANG: C++
PROG: ariprog
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int n = 0;
int m = 0;
int number = 0;
bool bisquares_list[125001]; //lookup if it is a bisquare
int all_bisquares[125001]; //sorted list of bisquares

void bisquares(int m) {
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m; j++) {
            int p = i * i + j * j;
            if (bisquares_list[p] == false) {
                bisquares_list[p] = true;
                all_bisquares[number] = p;
                number++;
            }
        }
    }
    sort(all_bisquares, all_bisquares + number); //sort it
}

bool valid(int a, int b) { // a is start, b is difference
    for (int i = 0; i < n; i++) {
        int num = a + i * b;
        if (bisquares_list[num] == false)
            return false;
    }
    return true;
}

int main() {
    ifstream fin("ariprog.in");
    ofstream fout("ariprog.out");

    int result_num = 0;
    int results[10000][2];

    fin >> n >> m;

    bisquares(m);

    bool found = false; //NONE

    //try all the bisquares (from number)
    for (int i = 0; i < number; i++) {
        int a = all_bisquares[i];

        //try all differences
        for (int j = i + 1; j < number; j++) {
            int b = all_bisquares[j] - a;
            if (b == 0) continue;

            //is it in the range? if not it's not
            if (a + (n - 1) * b > 125000) break;

            if (valid(a, b) == true) { //is it a sequence
                    results[result_num][0] = a;
                    results[result_num][1] = b;
                    result_num++;
                    found = true;

            }
        }
    }
    if (found == false) {
        fout << "NONE\n";
        return 0;
    }

   for (int i = 0; i < result_num; i++) {
        for (int j = i + 1; j < result_num; j++) {
            if (results[i][1] > results[j][1] || (results[i][1] == results[j][1] && results[i][0] > results[j][0])) {
                int temp_a = results[i][0]; //swap
                int temp_b = results[i][1];
                results[i][0] = results[j][0];
                results[i][1] = results[j][1];
                results[j][0] = temp_a;
                results[j][1] = temp_b;
            }
        }
   }

    for (int i = 0; i < result_num; i++) {
        fout << results[i][0] << " " << results[i][1] << "\n";
    }
    return 0;
    
}
