
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>

const size_t MAX_LENGTH = 100'000;

// создает массив
void MakeArray(int* grades, int n) {

	for (int i = 0; i < n; i++) {
		std::cin >> grades[i];
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
	int grades[MAX_LENGTH] = {}; //массив оценок

	std::cout << "Enter count of elements: ";

	if (!(std::cin >> n) || n <= 0) {
		std::cout << "You must enter a positive number!\n";
		std::exit(-1);
	}

	std::cout << "Enter marks : ";

	MakeArray(grades, n);
	n = DeleteMin(grades, n);
	n = DeleteMax(grades, n);
	CalculateArithmeticMean(grades, n);


	return 0;
}