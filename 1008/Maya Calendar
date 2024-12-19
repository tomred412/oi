#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
	vector<string> haab_months;
	haab_months.push_back("pop");
	haab_months.push_back("no");
	haab_months.push_back("zip");
	haab_months.push_back("zotz");
	haab_months.push_back("tzec");
	haab_months.push_back("xul");
	haab_months.push_back("yoxkin");
	haab_months.push_back("mol");
	haab_months.push_back("chen");
	haab_months.push_back("yax");
	haab_months.push_back("zac");
	haab_months.push_back("ceh");
	haab_months.push_back("mac");
	haab_months.push_back("kankin");
	haab_months.push_back("muan");
	haab_months.push_back("pax");
	haab_months.push_back("koyab");
	haab_months.push_back("cumhu");
	haab_months.push_back("uayet");

	vector<string> tzolkin_day_names;
	tzolkin_day_names.push_back("imix");
	tzolkin_day_names.push_back("ik");
	tzolkin_day_names.push_back("akbal");
	tzolkin_day_names.push_back("kan");
	tzolkin_day_names.push_back("chicchan");
	tzolkin_day_names.push_back("cimi");
	tzolkin_day_names.push_back("manik");
	tzolkin_day_names.push_back("lamat");
	tzolkin_day_names.push_back("muluk");
	tzolkin_day_names.push_back("ok");
	tzolkin_day_names.push_back("chuen");
	tzolkin_day_names.push_back("eb");
	tzolkin_day_names.push_back("ben");
	tzolkin_day_names.push_back("ix");
	tzolkin_day_names.push_back("mem");
	tzolkin_day_names.push_back("cib");
	tzolkin_day_names.push_back("caban");
	tzolkin_day_names.push_back("eznab");
	tzolkin_day_names.push_back("canac");
	tzolkin_day_names.push_back("ahau");

	int n = 0;
	cin >> n;
	cout << n << "\n";
	for (int i = 0; i < n; i++) {
		int haab_day, haab_year;
		string haab_month;
		char dot;

		cin >> haab_day >> dot >> haab_month >> haab_year;

		int month_number = 0;
		for (int j = 0; j < haab_months.size(); j++) {
			if (haab_months[j] == haab_month) {
				month_number = j;
				break;
			}
		}
		int day = (haab_year * 365) + (month_number * 20) + haab_day;
		int tzolkin_day_name_number = day % 20;
		int tzolkin_day_number = day % 13 + 1;
		int tzolkin_year = day/260;

		string tzolkin_day_name;

		for (int k = 0; k < tzolkin_day_names.size(); k++) {
			if (k == tzolkin_day_name_number) {
				tzolkin_day_name = tzolkin_day_names[k];
				break;
			}
		}
		cout << tzolkin_day_number << " " << tzolkin_day_name << " " << tzolkin_year << "\n";
	}

	return 0;
}
