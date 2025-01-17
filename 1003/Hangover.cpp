#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
double n = 0;
double y = 0;

    while (cin >> n) {
        if (n == 0.00) break;
        
        y = 0;
        int cards = 0;
        
        for (int i = 2; i < 400; i++) {
            y = y + (1.00 / i);
            cards++;
            
            if (y >= n) {
                cout << cards << " card(s)" << endl;
                break;
                
            }
            
        }
    }

    return 0;
}
