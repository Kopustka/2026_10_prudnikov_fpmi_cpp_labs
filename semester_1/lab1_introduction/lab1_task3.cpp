#include <iostream>
#include <string>
#include <algorithm>

int main3() {
	using std::cout;
	using std::cin;
	using std::string;
	using std::reverse;

	string word;
	string rev_word;


	cout << "Enter a num: ";
	cin >> word;


	if (word.length() != 4) {
		cout << "The number must be 6 digits.";
		return 0;
	}

	rev_word = word;
	reverse(rev_word.begin(), rev_word.end());

	if (word == rev_word) {
		cout << "The string is a palindrome.";
	}
	else {
		cout << "The string is not a palindrome.";
	}

	return 0;
}