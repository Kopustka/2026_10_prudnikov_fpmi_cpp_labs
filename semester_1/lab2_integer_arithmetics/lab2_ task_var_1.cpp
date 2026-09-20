
#include <iostream>



long DeleteDoubleNums(long long n) {

    long long k = n;
    int buffer = 9;
    int i = 1;
    long long rank = 1;

    // цикл для нахождения мин числа 
    for (;n != 0;) {
        if ((n % 10) <= buffer) {
            buffer = n % 10;
        }
        n /= 10;
        i++;
    }

    // цикл который проходиться по первоначальному числу и отсеивает мин число
    for (;i != 1;) {
        if ((k % 10) != buffer) {
            n += rank * (k % 10);
            rank *= 10;
        }
        k /= 10;
        i--;
    }

    return n;
}


int main()
{
    long long n;

    std::cout << "Enter natural number: ";

    if (!(std::cin >> n) || n <= 0) {
        std::cout << "You must enter a positive number!\n";
        std::exit(-1);
    }

    std::cout << "Its your answer:" << DeleteDoubleNums(n);

    return 0;
}



