#include <iostream>


int main1()
{
    using std::cout;
    using std::cin;

    int n, m;
	cout << "Enter two integers n, m: ";
	cin >> n >> m;

    if ((n <= 0) || (m <= 0)) {
        cout << "Integers must be positive.";
    }
    
	int min = std::min(n, m);
    cout << "Common dividers:" << 1 << ' ';
    for (int i = 2; i <= min; ++i) {
		if ((n % i == 0) && (m % i == 0)) {
			cout << i << ' ';
		}
    }


    return 0;   
}
