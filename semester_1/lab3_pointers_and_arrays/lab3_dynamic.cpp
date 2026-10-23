#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <random>

//ввод н
int EnterN() {
	int n = 0;
	std::cout << "Enter count of elements(count must be greater than 2): ";

	if (!(std::cin >> n) || n <= 2) {
		std::cout << "You must enter a positive number or n > 2!\n";
		std::exit(-1);
	}

	return n;
}
int EnternormORrand() {
	int normORrand;

	std::cout << "Enter 1 if norm arr, enter 0 if rand arr: ";
	if (!(std::cin >> normORrand) || normORrand < 0 || normORrand > 1) {
		std::cout << "You must enter 0 or 1!\n";
		std::exit(-1);
	}

	return normORrand;
}


void PrintArray(double* grades, int n) {
	std::cout << "Array: ";

	for (int i = 0; i < n; i++) {
		std::cout << grades[i] << " ";
	}
	std::cout << "\n";
}

// создает массив
void MakeArray(double* grades, int n, int normORrand, std::mt19937& gen) {
	if (normORrand == 1) {
		for (int i = 0; i < n; i++) {
			std::cout << "Enter marks : ";
			std::cin >> grades[i];
		}
	}
	else if (normORrand == 0) {
		int a, b;
		std::cout << "Enter a and b: ";
		std::cin >> a >> b;
		std::uniform_int_distribution<int> dist(a, b);
		for (int i = 0; i < n; i++) {
			grades[i] = dist(gen);
		}
	}
}



int calculating(double* arr, int n) {
	int b_index = 0;
	double min_diff = INT_MAX;

	for (int i = 0; i < n; i++) {
		double sum1 = 0;
		double sum2 = 0;

		for (int j = 0; j < i; j++) {
			sum1 += arr[j];
		}
		for (int j = i; j < n; j++) {
			sum2 += arr[j];
		}

		double current_diff = std::abs(sum2 - sum1);
		if (current_diff < min_diff) {
			min_diff = current_diff;
			b_index = i;
		}
	}
	return b_index;
}


void DelArr(double* arr) {
	delete[] arr;
	//grades = nullptr;
}


int main()
{
	int n;   //колличество оценок
	n = EnterN(); //ввод н
	int normORrand;
	normORrand = EnternormORrand();
	std::random_device rd;
	std::mt19937 gen(rd());

	double* arr = new double[n] {}; //массив оценок

	MakeArray(arr, n, normORrand, gen);  // создание массива
	PrintArray(arr, n);
	int index = calculating(arr, n);

	std::cout << "Your index: " << index;
	DelArr(arr);

	return 0;
}