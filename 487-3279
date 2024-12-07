#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
	int n;
	cin >> n;


	vector<string> numbers(n);

	for (int i = 0; i < n; i++) {
		cin >> numbers[i];

		for (int j = 0; j < numbers[i].size(); j++) {
			if (isalpha(numbers[i][j])) {
				if (numbers[i][j] >= 'A' && numbers[i][j] <= 'C') {
					numbers[i][j] = '2';
				} else if (numbers[i][j] >= 'D' && numbers[i][j] <= 'F') {
					numbers[i][j] = '3';
				} else if (numbers[i][j] >= 'G' && numbers[i][j] <= 'I') {
					numbers[i][j] = '4';
				} else if (numbers[i][j] >= 'J' && numbers[i][j] <= 'L') {
					numbers[i][j] = '5';
				} else if (numbers[i][j] >= 'M' && numbers[i][j] <= 'O') {
					numbers[i][j] = '6';
				} else if (numbers[i][j] >= 'P' && numbers[i][j] <= 'S') {
					numbers[i][j] = '7';
				} else if (numbers[i][j] >= 'T' && numbers[i][j] <= 'V') {
					numbers[i][j] = '8';
				} else if (numbers[i][j] >= 'W' && numbers[i][j] <= 'Y') {
					numbers[i][j] = '9';
				}
			} else if (numbers[i][j] == '-') {
				numbers[i].erase(j, 1);
				j = j - 1;

			}
		}
	}

	sort(numbers.begin(), numbers.end());

	int count = 1;

	bool duplicate = false;


	for (int i = 1; i <= n; ++i) {
		if (i < n && numbers[i] == numbers[i - 1]) {
			count = count + 1;
		} else {
			if (count > 1) {
				duplicate = true;
				cout << numbers[i - 1].substr(0, 3) << "-" << numbers[i - 1].substr(3) << " " << count << endl;
			}

			count = 1;
		}
	}


	if (duplicate == false) {
		cout << "No duplicates." << endl;
	}

	return 0;
}

