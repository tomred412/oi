#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
    
int cases = 1;
int p, e, i, d;
	while (cin >> p >> e >> i >> d) {
		int day = d + 1;
        if (p == -1 && e == -1 && i == -1 && d == -1) break;
        
		while ((day - p) % 23 != 0 || (day - e) % 28 != 0 || (day - i) % 33 != 0) {
		    day = day + 1;


		}
		cout << "Case " << cases << ": the next triple peak occurs in " << day - d << " days." << endl; 
		cases = cases + 1;
	}
	return 0;
}
