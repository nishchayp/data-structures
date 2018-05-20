#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<string> phone_book(10000000, "");
	int n;
	cin >> n;
	string type;
	string name;
	long long number;
	for (int i = 0; i < n; i++) {
		cin >> type;
		cin >> number;
		if (type == "add") {
			cin >> name;
			phone_book[number] = name;
		} else if (type == "find") {
			if (phone_book[number] != "")
				cout << phone_book[number] << endl;
			else
				cout << "not found" << endl;
		} else {
			phone_book[number] = "";
		}
	}
}