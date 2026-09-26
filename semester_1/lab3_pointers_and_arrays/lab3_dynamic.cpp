#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>


void PrintArray(int* grades, int n) {
	std::cout << "Array";

	for (int i = 0; i < n; i++) {
		std::cout << grades[i] << " ";
	}
	std::cout << "\n";
}

// создает массив
void MakeArray(int* grades, int n) {

	for (int i = 0; i < n; i++) {
		std::cin >> grades[i];
	}
}

// удаляет минимальный элемент массива
int DeleteMin(int* grades, int n) {

	int min_el = grades[0];
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
	int max_el = grades[0];
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
	std::cout << "Enter count of elements(count must be greater than 2): ";

	if (!(std::cin >> n) || n <= 2) {
		std::cout << "You must enter a positive number or n < 2!\n";
		std::exit(-1);
	}
	int* grades = new int[n] {}; //массив оценок

	std::cout << "Enter marks : ";


	MakeArray(grades, n);
	n = DeleteMin(grades, n);
	n = DeleteMax(grades, n);
	CalculateArithmeticMean(grades, n);



	delete[] grades;
	//grades = nullptr;

	return 0;
}