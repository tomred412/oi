        #include <iostream>
        #include <string>
        #include <algorithm>
        #include <vector>
        #include <math.h>
        #include <stdlib.h>
        #include <sstream>
        
        using namespace std;
        
        int sti(string x) {
            int result = 0;
            for (int i = 0; i < x.size(); i++) {
                result = result * 10 + (x[i] - '0');
            }
            return result;
        }
        
        string multi(string num, int factor) {
        	string result;
        	int carry = 0;
        
        	for (int i = num.size() - 1; i >= 0; i--) {
        		int digit = num[i] - '0';
        		int product = digit * factor + carry;
        		result = char((product % 10) + '0') + result;
        		carry = product / 10;
        	}
        
        	while (carry != 0) {
        		result = char((carry % 10) + '0') + result;
        		carry = carry / 10;
        	}
        	return result;
        }
        
        string exponent(string base, int power) {
        	int decimal = 0; //to the right, like 1.23 so it's 23, so that's 2
        
        	for (int i = 0; i < base.size(); i++) {
        		if (base[i] == '.') {
        			decimal = base.size() - i - 1;
        			base.erase(base.begin() + i);
        			break;
        		}
        	}
        
        	string result = "1";
        
        	for (int i = 0; i < power; i++) {
        		result = multi(result, sti(base));
        	}
        
        	decimal = decimal * power;
        	if (decimal > 0) {
        		while (result.size() <= decimal) {
        			result = '0' + result;
        		}
        		result.insert(result.end() - decimal, '.');
        	}
        
        	while (result.size() > 1 && result[0] == '0' && result[1] != '.') {
        		result.erase(result.begin());
        	}
        
        	while (!result.empty() && result[result.size() - 1] == '0' && result.find('.') != string::npos) {
        		result.erase (result.size()-1);
        	}
        	if (!result.empty() && result[result.size() - 1] == '.') {
        		result.erase (result.size()-1);
        	}
        
        	return result;
        }
        
        int main() {
        	string s;
        	int n;
        	string result;
        
        	while (cin >> s >> n) {
        		result = exponent(s, n);
                
                if (result.size() > 1 && result[0] == '0' && result[1] == '.') {
                
                result.erase(0, 1);
                }
        		cout << result << endl;
        	}
        
        	return 0;
        }
        
