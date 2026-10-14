#include<iostream>
#include<cmath>
#include<random>

int EnterN() {
	int n = 0;
	std::cout << "Write down the side length of the square matrix.(count must be greater than 2): ";

	if (!(std::cin >> n) || n < 2) {
		std::cout << "You must enter a positive number or n >= 2!\n";
		std::exit(-1);
	}

	return n;
}

// создает массив
void MakeMatrix(int**& matrix, int n) {

	matrix = new int* [n];

	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
	}



	std::cout << "Enter cut (a b): ";

	int a;
	std::cin >> a;

	int b;
	std::cin >> b;

	std::mt19937 gen(45218965);
	std::uniform_int_distribution<int> dist(a, b);


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = dist(gen);
		}
	}

}

// выывести массив
void PrintMatrix(int** matrix, int n) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}


// повернуть массив на 90 градусов
// сначала меняем элементы местами относительно главной диагонали
// записываем элементы в списке в обратном порядке
void matrix_rotation(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			std::swap(matrix[i][j], matrix[j][i]);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n / 2; j++) {
			std::swap(matrix[i][j], matrix[i][n - 1 - j]);
		}
	}
}

void DeleteMemory(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}


int main()
{
	int n;
	n = EnterN();
	int** matrix = nullptr;


	MakeMatrix(matrix, n);


	std::cout << "90 grad" << "\n";
	matrix_rotation(matrix, n);
	PrintMatrix(matrix, n);

	std::cout << "180 grad" << "\n";
	matrix_rotation(matrix, n);
	PrintMatrix(matrix, n);

	std::cout << "270 grad" << "\n";
	matrix_rotation(matrix, n);
	PrintMatrix(matrix, n);


	DeleteMemory(matrix, n);


}