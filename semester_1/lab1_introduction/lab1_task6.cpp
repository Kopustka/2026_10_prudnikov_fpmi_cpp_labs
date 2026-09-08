#include <iostream>

int main()
{
    using std::cout;
    using std::cin;


    int a, b, d;

    cout << "Enter a, b, d: ";
    cin >> a >> b >> d;

    while (a <= b) {
        if (a % 3 == 0) {
            cout << a << " ";
        }
        a += d;
    }

    return 0;
}