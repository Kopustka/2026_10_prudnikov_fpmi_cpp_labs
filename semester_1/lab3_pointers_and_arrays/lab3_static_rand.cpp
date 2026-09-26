
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <random>


const size_t MAX_LENGTH = 100'000;

// ввод количества элементов
int EnterN() {
	int n = 0;
	std::cout << "Enter count of elements(count must be greater than 2): ";

	if (!(std::cin >> n) || n <= 2) {
		std::cout << "You must enter a positive number or n < 2!\n";
		std::exit(-1);

	}
	return n;
}

// ввод левого предела
int EnterA() {
	int a = 0;

	if (!(std::cin >> a) || a <= 0) {
		std::cout << "You must enter a positive a!\n";
		std::exit(-1);
	}
	return a;
}


// ввыод правого предела
int EnterB() {
	int b = 0;

	if (!(std::cin >> b) || b <= 0) {
		std::cout << "You must enter a positive b!\n";
		std::exit(-1);
	}
	return b;
}

// вывод списка
void PrintArray(int* grades, int n) {
	std::cout << "Array";

	for (int i = 0; i < n; i++) {
		std::cout << grades[i] << " ";
	}
	std::cout << "\n";
}


// создает массив
void MakeRandArray(int* grades, int n, int a, int b) {

	std::mt19937 gen(45218965);

	std::uniform_int_distribution<int> dist(a, b);


	for (int i = 0; i < n; i++) {
		int x = dist(gen);
		grades[i] = x;
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
	int n = EnterN(); //колличество оценок
	int grades[MAX_LENGTH] = {}; //массив оценок

	std::cout << "Enter interval boundaries: ";
	int a = EnterA();  // левая граница
	int b = EnterB(); // правая граница

	if (a >= b) {
		std::cout << "A must be less B!\n";
		std::exit(-1);
	}

	MakeRandArray(grades, n, a, b); // создание рандомного массива
	n = DeleteMin(grades, n); // удаление минимального
	n = DeleteMax(grades, n); // удаление максимального
	CalculateArithmeticMean(grades, n); // водсчет и вывод конечного


	return 0;
}