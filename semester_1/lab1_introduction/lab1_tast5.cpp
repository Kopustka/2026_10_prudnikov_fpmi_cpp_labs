#include <iostream>

int main5()
{

	using std::cout;
	using std::cin;

	int n;
	int fib_0 = 0;
	int fib_1 = 1;


	cout << "Enter count of Fibonachi numbers:" ;
	cin >> n;
	cout << "Fibonachi numbers:";
	cout << fib_0 << ' ';


	
	for (int i = 0; i <= n; ++i) {
		cout << fib_1 << ' ';
		int fib_intermediate = fib_1;
		fib_1 = fib_1 + fib_0;
		fib_0 = fib_intermediate;
		

	}
	return 0;
}