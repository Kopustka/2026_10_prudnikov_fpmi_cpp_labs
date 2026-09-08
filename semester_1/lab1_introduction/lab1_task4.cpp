#include <iostream>
#include <string>
#include <algorithm>

int main4()
{
	using std::cout;
	using std::cin;
	using std::string;

	string word_num;

	cout << "Enter a num: ";
	cin >> word_num;

	if (word_num.length() != 6) {
		cout << "The number must be 6 digits.";
		return 0;
	}

	string left_str = word_num.substr(0, 3);
	string right_str = word_num.substr(3, 3);

	if (left_str == right_str) {
		cout << "The number is lucky.";
	}
	else {
		cout << "The number is not lucky.";
	}


	return 0;
}