
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <random>

const size_t MAX_LENGTH = 100'000;


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


// создает массив
void MakeArray(int* grades, int n, int normORrand, std::mt19937& gen) {
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

// удаляет минимальный элемент массива
int DeleteMin(int* grades, int n) {
	int min_el = 2'147'483'647;
	int k = 0;

	// находим минимальный элемент массива и запоминаем его индекс
	for (int i = 0; i < n; i++) {
		min_el = std::min(min_el, grades[i]);
		if (min_el == grades[i]) {
			k = i;
		}
	}

	// приравнивем его к нулю
	grades[k] = 0;

	// сдвигаем все остальные элементы массива
	for (; k < n; k++) {
		grades[k] = grades[k + 1];
	}

	return --n;

}

// удаляет максимальный элемент массива
int DeleteMax(int* grades, int n) {
	int max_el = 0;
	int k = 0;

	// находим минимальный элемент массива и запоминаем его индекс
	for (int i = 0; i < n; i++) {
		max_el = std::max(max_el, grades[i]);
		if (max_el == grades[i]) {
			k = i;
		}
	}


	// приравнивем его к нулю
	grades[k] = 0;

	// сдвигаем все остальные элементы массива
	for (; k < n; k++) {
		grades[k] = grades[k + 1];
	}


	return --n;
}

void PrintArray(int* grades, int n) {
	std::cout << "Array: ";

	for (int i = 0; i < n; i++) {
		std::cout << grades[i] << " ";
	}
	std::cout << "\n";
}

// Вывод конченого результата
void CalculateArithmeticMean(int* grades, int n) {
	float result = 0;

	// находим среднюю арифметическую
	for (int i = 0; i < n; i++) {
		result += grades[i];
	}

	result /= n;
	std::cout << "You score: " << result;
}


int main()
{
	int n;   //колличество оценок
	n = EnterN(); //ввод н
	int normORrand;
	normORrand = EnternormORrand();
	std::random_device rd;
	std::mt19937 gen(rd());

	int grades[MAX_LENGTH] = {}; //массив оценок


	MakeArray(grades, n, normORrand, gen); // создание масива 
	PrintArray(grades, n);
	n = DeleteMin(grades, n); // удаление минимального
	n = DeleteMax(grades, n); // удаление максимального 
	CalculateArithmeticMean(grades, n); // сред арифм. и подчет результата


	return 0;
}