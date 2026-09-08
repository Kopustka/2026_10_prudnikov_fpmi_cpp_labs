#include <iostream>


int main2()
{
    using std::cout;
    using std::cin;

    int N;
    cout << "Enter two integers N: ";
    cin >> N;

    if (N <= 0) {
        cout << "Integers must be positive.";
    }

    cout << "Answer: " << N * N << " ";
  


    return 0;
}
