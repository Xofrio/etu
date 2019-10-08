#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

HANDLE textColour = GetStdHandle(STD_OUTPUT_HANDLE);

#ifndef FUNC_H
#define FUNC_H

int getRowsOrColumns() {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail() || userNumber <= 0) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректное число: ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}

int getMenuOption() {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 10): ";
		}
		else if (userNumber == 0 || userNumber == 1 || userNumber == 2 || userNumber == 3 || userNumber == 4 || userNumber == 5 || userNumber == 6 || userNumber == 7 || userNumber == 8 || userNumber == 9 || userNumber == 10) {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
		else
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 10): ";
	}
}

bool getArrayMenuOption() {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 1): ";
		}
		else if (userNumber == 0 || userNumber == 1) {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
		else
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 1): ";
	}
}

int getSubMenuOption() {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 3): ";
		}
		else if (userNumber == 0 || userNumber == 1 || userNumber == 2 || userNumber == 3) {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
		else
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 3): ";
	}
}

void orthogonal(int **A, int order) {
	int scalarPairs = 0, scalarSelf = 0;
	for (int i = 0; i < order - 1; ++i) {
		for (int k = i + 1; k < order; ++k) {
			double scalarPairsValue = 0;
			for (int j = 0; j < order; ++j)
				scalarPairsValue = scalarPairsValue + A[i][j] * A[k][j];
			if (scalarPairsValue == 0)
				++scalarPairs;
		}
	}
	for (int i = 0; i < order; ++i) {
		double scalarSelfValue = 0;
		for (int j = 0; j < order; ++j)
			scalarSelfValue = scalarSelfValue + A[i][j] * A[i][j];
		if (scalarSelfValue == 1)
			++scalarSelf;
	}
	if (scalarPairs == (order * (order - 1) / 2) && scalarSelf == order)
		cout << endl << "Матрица ортонормированная" << endl;
	else
		cout << endl << "Матрица не ортонормированная" << endl;
}

void diagonalComposition(int **A, int order) {
	double composition = 1;
	int mid, countZero = 0;
	if (order % 2 != 0)
		mid = order / 2;
	else
		mid = -1;
	for (int i = 0; i < order; ++i) {
		for (int j = 0; j < order; ++j) {
			if (i == j) {
				if (A[i][j] != 0)
					composition = composition * A[i][j];
				else
					++countZero;
			}
		}
	}
	for (int i = order - 1; i >= 0; --i) {
		for (int j = order - 1; j >= 0; --j) {
			if (i + j == order - 1) {
				if (A[i][j] != 0 && i != mid)
					composition = composition * A[i][j];
				else
					++countZero;
			}
		}
	}
	if (order % 2 == 0 && countZero == order * 2)
		cout << endl << "Все диагональные элементы равны нулю." << endl;
	else if (order % 2 != 0 && countZero == order * 2)
		cout << endl << "Все диагональные элементы равны нулю." << endl;
	else
		cout << endl << "Произведение ненулевых диагональных элементов: " << composition << endl;
}

void quickSortingForTwoArrays(int *A, int *B, int start, int end) {
	int i = start, j = end, tmp;
	int separator = A[(start + end) / 2];
	while (i <= j) {
		while (A[i] < separator)
			++i;
		while (A[j] > separator)
			--j;
		if (i <= j) {
			tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
			tmp = B[i];
			B[i] = B[j];
			B[j] = tmp;
			++i;
			--j;
		}
	}
	if (start < j)
		quickSortingForTwoArrays(A, B, start, j);
	if (i < end)
		quickSortingForTwoArrays(A, B, i, end);
}

void sortArray(int **A, int columns, int start, int end) {
	int k = start, i = end, j = 0, tmp, separator = A[(start + end) / 2][j];
	while (k <= i) {
		while (A[k][j] > separator)
			++k;
		while (A[i][j] < separator)
			--i;
		if (k <= i) {
			for (int n = 0; n < columns; ++n) {
				tmp = A[k][n];
				A[k][n] = A[i][n];
				A[i][n] = tmp;
			}
			++k;
			--i;
		}
	}
	if (start < i)
		sortArray(A, columns, start, i);
	if (k < end)
		sortArray(A, columns, k, end);
}

void magicSquare(int **A, int order) {
	int sum1 = 0, pairsCount = 0, sum2 = 0;
	bool rowsCondition = 0, columnsCondition = 0, mainDiagonalCondition = 0, secondaryDiagonalCondition = 0;
	for (int j = 0, i = 0; j < order; ++j)
			sum1 = sum1 + A[i][j];
	for (int i = 1; i < order; ++i) {
		for (int j = 0; j < order; ++j)
			sum2 = sum2 + A[i][j];
		if (sum2 == sum1)
			++pairsCount;
		sum2 = 0;
	}
	if (pairsCount == order - 1)
		rowsCondition = 1;
	pairsCount = 0;
	for (int j = 0; j < order; ++j) {
		for (int i = 0; i < order; ++i)
			sum2 = sum2 + A[i][j];
		if (sum2 == sum1)
			++pairsCount;
		sum2 = 0;
	}
	if (pairsCount == order)
		columnsCondition = 1;
	for (int i = 0; i < order; ++i) {
		for (int j = 0; j < order; ++j) {
			if (i == j)
				sum2 = sum2 + A[i][j];
		}
	}
	if (sum2 == sum1)
		mainDiagonalCondition = 1;
	sum2 = 0;
	for (int i = order - 1; i >= 0; --i) {
		for (int j = order - 1; j >= 0; --j) {
			if (i + j == order - 1)
				sum2 = sum2 + A[i][j];
		}
	}
	if (sum2 == sum1)
		secondaryDiagonalCondition = 1;
	if (rowsCondition == 1 && columnsCondition == 1 && mainDiagonalCondition == 1 && secondaryDiagonalCondition == 1)
		cout << endl << "Матрица является магическим квадратом." << endl;
	else
		cout << endl << "Матрица не является магическим квадратом." << endl;
}

void minimalElement(int **A, int order) {
	int minimum = 2147483647, minCount = 0;
	for (int i = order - 1; i >= 1; --i) {
		for (int j = order - 1; j >= 1; --j)
			if (i + j >= order && A[i][j] <= minimum)
				minimum = A[i][j];
	}
	for (int i = order - 1; i >= 1; --i) {
		for (int j = order - 1; j >= 1; --j) {
			if (i + j >= order && A[i][j] == minimum)
				++minCount;
		}
	}
	int k = 0, *B = 0, *C = 0;
	B = new int[minCount];
	C = new int[minCount];
	for (int i = order - 1; i >= 1; --i) {
		for (int j = order - 1; j >= 1; --j) {
			if (i + j >= order && A[i][j] == minimum) {
				B[k] = i + 1;
				C[k] = j + 1;
				++k;
			}
		}
	}
	if (minCount == 1)
		cout << endl << "Минимальный элемент под побочной диагональю имеет значение " << minimum << ", находится под индексами [" << B[0] << "][" << C[0] << "]" << endl << endl;
	else {
		quickSortingForTwoArrays(B, C, 0, k - 1);
		cout << endl << "Минимальный элемент под побочной диагональю имеет значение" << minimum << endl;
		cout << "Таких элементов несколько, они находятся под индексами:" << endl << endl;
		for (int i = 0; i < k; ++i)
			cout << "[" << B[i] << "][" << C[i] << "]" << endl;
	}
	delete[] B;
	delete[] C;
}

void mainDiagonalSymmetry(int **A, int order) {
	int pairs = 0;
	for (int i = 0; i < order / 2; ++i) {
		for (int j = 0; j < order / 2; ++j) {
			if (i == j && A[i][j] == A[order - 1 - i][order - 1 - j])
				++pairs;
		}
	}
	if (pairs == order / 2)
		cout << endl << "Матрица симметрична относительно главной диагонали." << endl;
	else
		cout << endl << "Матрица не симметрична относительно главной диагонали." << endl;
}

void secondaryDiagonalSymmetry(int **A, int order) {
	int pairs = 0;
	for (int i = order - 1; i >= order / 2; --i) {
		for (int j = 0; j < order / 2; ++j) {
			if (i + j == order - 1 && A[i][j] == A[j][i])
				++pairs;
		}
	}
	if (pairs == order / 2)
		cout << endl << "Матрица симметрична относительно побочной диагонали." << endl;
	else
		cout << endl << "Матрица не симметрична относительно побочной диагонали." << endl;
}

void rowsSwap(int **A, int order) {
	int tmp;
	for (int i = 0; i < order / 2; ++i) {
		for (int j = 0; j < order; ++j) {
			tmp = A[i][j];
			A[i][j] = A[order - 1 - i][j];
			A[order - 1 - i][j] = tmp;
		}
	}
}

void swapClockwise(int **A, int order) {
	int **B = 0;
	B = new int *[order / 2];
	for (int i = 0; i < order / 2; ++i)
		B[i] = new int[order / 2];
	for (int i = 0; i < order / 2; ++i) {
		for (int j = 0; j < order / 2; ++j)
			B[i][j] = A[i][j];
	}
	for (int i = 0; i < order / 2; ++i) {
		for (int j = 0; j < order / 2; ++j)
			A[i][j] = A[i + order / 2][j];
	}
	for (int i = order / 2; i < order; ++i) {
		for (int j = 0; j < order / 2; ++j)
			A[i][j] = A[i][j + order / 2];
	}
	for (int i = order / 2; i < order; ++i) {
		for (int j = order / 2; j < order; ++j)
			A[i][j] = A[i - order / 2][j];
	}
	for (int i = 0; i < order / 2; ++i) {
		for (int j = order / 2, k = 0; j < order; ++j, ++k)
			A[i][j] = B[i][k];
	}
	for (int i = 0; i < order / 2; ++i)
		delete[] B[i];
	delete[] B;
}

void generateArray(int **&A, int rows, int columns) {
	A = new int *[rows];
	for (int i = 0; i < rows; ++i)
		A[i] = new int[columns];
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j)
			A[i][j] = rand() % 100;
	}
}


void inputArray(int **&A, int rows, int columns) {
	A = new int *[rows];
	for (int i = 0; i < rows; ++i)
		A[i] = new int[columns];
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			cout << "Введите значение элемента с индексами [" << i + 1 << "][" << j + 1 << "]: ";
			cin >> A[i][j];
		}
	}
	cout << endl;
}


void showArray(int **A, int rows, int columns) {
	cout << '\t';
	SetConsoleTextAttribute(textColour, 5);
	for (int i = 0; i < columns; ++i)
		cout << i + 1 << '\t';
	SetConsoleTextAttribute(textColour, 7);
	cout << endl << endl;
	for (int i = 0; i < rows; ++i) {
		SetConsoleTextAttribute(textColour, 5);
		cout << i + 1 << '\t';
		SetConsoleTextAttribute(textColour, 7);
		for (int j = 0; j < columns; ++j)
			cout << A[i][j] << '\t';
		cout << endl << endl;
	}
}

void showFancyArray(int **A, int order, bool condition, int method) {
	cout << '\t';
	int part1 = 0, part2 = 0, part3 = 0, part4 = 0;
	if (condition == 0) {
			part1 = 3;
			part2 = 4;
			part3 = 9;
			part4 = 10;
	}
	else if (method == 0) {
		part1 = 9;
		part2 = 3;
		part3 = 10;
		part4 = 4;
	}
	else if (method == 1) {
		part1 = 10;
		part2 = 9;
		part3 = 4;
		part4 = 3;
	}
	else if (method == 2) {
		part1 = 9;
		part2 = 10;
		part3 = 3;
		part4 = 4;
	}
	else if (method == 3) {
		part1 = 4;
		part2 = 3;
		part3 = 10;
		part4 = 9;
	}
	SetConsoleTextAttribute(textColour, 5);
	for (int i = 0; i < order; ++i)
		cout << i + 1 << '\t';
	SetConsoleTextAttribute(textColour, 7);
	cout << endl << endl;
	for (int i = 0; i < order; ++i) {
		SetConsoleTextAttribute(textColour, 5);
		cout << i + 1 << '\t';
		SetConsoleTextAttribute(textColour, 7);
		for (int j = 0; j < order; ++j) {
			if (i >= 0 && i < order /2 && j >= 0 && j < order /2)
				SetConsoleTextAttribute(textColour, part1);
			else if (i >= 0 && i < order / 2 && j >= order / 2 && j < order)
				SetConsoleTextAttribute(textColour, part2);
			else if (i >= order / 2 && i < order && j >= 0 && j < order /2)
				SetConsoleTextAttribute(textColour, part3);
			else if (i >= order / 2 && i < order && j >= order / 2 && j < order)
				SetConsoleTextAttribute(textColour, part4);
			cout << A[i][j] << '\t';
		}
		SetConsoleTextAttribute(textColour, 7);
		cout << endl << endl;
	}
}

void deleteArray(int **A, int rows, int columns) {
	for (int i = 0; i < rows; ++i)
		delete[] A[i];
	delete[] A;
	A = 0;
}

void Menu() {
	cout << "Выберите опцию . . ." << endl;
	cout << "0. Создать матрицу" << endl;
	cout << "1. Определить, является ли матрица ортонормированной" << endl;
	cout << "2. Найти произведение ненулевых диагональных элементов" << endl;
	cout << "3. Найти минимальный элемент под побочной диагональю" << endl;
	cout << "4. Определить, является ли матрица магическим квадратом" << endl;
	cout << "5. Определить, является ли матрица симметричной относительно главной диагонали" << endl;
	cout << "6. Определить, является ли матрица симметричной относительно побочной диагонали" << endl;
	cout << "7. Отсортировать матрицу по убыванию элементов первого столбца" << endl;
	cout << "8. Поменять строки по принципу: первая с последней, вторая с предпоследней и т.д." << endl;
	cout << "9. Поменять местами квадранты" << endl;
	cout << "10. Выйти" << endl;
	cout << "Опция: ";
}

void arrayMenu() {
	cout << "Выберите опцию . . ." << endl;
	cout << "0. Заполнить матрицу вручную" << endl;
	cout << "1. Заполнить матрицу автоматически" << endl;
	cout << "Опция: ";
}

void swapMenu() {
	cout << "Выберите опцию . . ." << endl;
	cout << "0. Поменять квадранты местами по часовой стрелке" << endl;
	cout << "1. Поменять квадранты местами крест-накрест" << endl;
	cout << "2. Поменять квадранты местами вверх дном" << endl;
	cout << "3. Поменять квадранты местами левой и правой стороной" << endl;
	cout << "Опция: ";
}

#endif
