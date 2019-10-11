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
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 14): ";
		}
		else if (userNumber == 0 || userNumber == 1 || userNumber == 2 || userNumber == 3 || userNumber == 4 || userNumber == 5 || userNumber == 6 || userNumber == 7 || userNumber == 8 || userNumber == 9 || userNumber == 10 || userNumber == 11 || userNumber == 12 || userNumber == 13 || userNumber == 14) {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
		else
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 14): ";
	}
}

int getMiniMenuOption() {
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

void orthogonal(long double **A, int order) {
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

void diagonalComposition(long double **A, int order) {
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

void sortArray(long double **A, int columns, int start, int end) {
	int k = start, i = end, j = 0;
	long double separator = A[(start + end) / 2][j], tmp;
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

void maxAtTheTop(long double **A, int order) {
	long double tmp, max = long double(~9223372036854775807);
	int maxI, maxJ;
	for (int i = 0; i < order; ++i) {
		for (int j = 0; j < order; ++j) {
			if (A[i][j] >= max) {
				max = A[i][j];
				maxI = i;
				maxJ = j;
			}
		}
	}
	for (int j = maxJ, i = 0; i < order; ++i) {
		tmp = A[i][j];
		A[i][j] = A[i][0];
		A[i][0] = tmp;
	}
	for (int i = maxI, j = 0; j < order; ++j) {
		tmp = A[i][j];
		A[i][j] = A[0][j];
		A[0][j] = tmp;
	}
}

void magicSquare(long double **A, int order) {
	int pairsCount = 0;
	bool rowsCondition = 0, columnsCondition = 0, mainDiagonalCondition = 0, secondaryDiagonalCondition = 0;
	long double sum1 = 0, sum2 = 0;
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

void minimalElement(long double **A, int order) {
	int minCount = 0;
	long double minimum = long double(9223372036854775807);
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
		cout << endl << "Минимальный элемент под побочной диагональю имеет значение: " << minimum << endl;
		cout << endl << "Таких элементов " << minCount << ", они находятся под индексами:" << endl << endl;
		for (int i = 0; i < k; ++i)
			cout << "[" << B[i] << "][" << C[i] << "]" << endl;
	}
	delete[] B;
	delete[] C;
}

void mainDiagonalSymmetry(long double **A, int order) {
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

void secondaryDiagonalSymmetry(long double **A, int order) {
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

void rowsSwap(long double **A, int order) {
	long double tmp;
	for (int i = 0; i < order / 2; ++i) {
		for (int j = 0; j < order; ++j) {
			tmp = A[i][j];
			A[i][j] = A[order - 1 - i][j];
			A[order - 1 - i][j] = tmp;
		}
	}
}

void swapClockwise(long double **A, int order) {
	long double **B = 0;
	B = new long double *[order / 2];
	for (int i = 0; i < order / 2; ++i)
		B[i] = new long double[order / 2];
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

void swapCross(long double **A, int order) {
	long double **B = 0, **C = 0;
	B = new long double *[order / 2];
	for (int i = 0; i < order / 2; ++i)
		B[i] = new long double[order / 2];
	for (int i = 0; i < order / 2; ++i) {
		for (int j = 0; j < order / 2; ++j)
			B[i][j] = A[i][j];
	}
	C = new long double *[order / 2];
	for (int i = 0; i < order / 2; ++i)
		C[i] = new long double[order / 2];
	for (int i = order / 2, k = 0; i < order; ++i, ++k) {
		for (int j = 0; j < order / 2; ++j)
			C[k][j] = A[i][j];
	}
	for (int i = 0; i < order / 2; ++i) {
		for (int j = 0; j < order / 2; ++j)
			A[i][j] = A[i + order / 2][j + order / 2];
	}
	for (int i = order / 2; i < order; ++i) {
		for (int j = 0; j < order / 2; ++j)
			A[i][j] = A[i - order / 2][j + order / 2];
	}
	for (int i = order / 2, k = 0; i < order; ++i, ++k) {
		for (int j = order / 2, n = 0; j < order; ++j, ++n)
			A[i][j] = B[k][n];
	}
	for (int i = 0; i < order / 2; ++i) {
		for (int j = order / 2, k = 0; j < order; ++j, ++k)
			A[i][j] = C[i][k];
	}
	for (int i = 0; i < order / 2; ++i)
		delete[] B[i];
	delete[] B;
	for (int i = 0; i < order / 2; ++i)
		delete[] C[i];
	delete[] C;
}

void swapUpsideDown(long double **A, int order) {
	long double **B = 0, **C = 0;
	B = new long double *[order / 2];
	for (int i = 0; i < order / 2; ++i)
		B[i] = new long double[order / 2];
	for (int i = 0; i < order / 2; ++i) {
		for (int j = 0; j < order / 2; ++j)
			B[i][j] = A[i][j];
	}
	C = new long double *[order / 2];
	for (int i = 0; i < order / 2; ++i)
		C[i] = new long double[order / 2];
	for (int i = 0; i < order / 2; ++i) {
		for (int j = order / 2, k = 0; j < order; ++j, ++k)
			C[i][k] = A[i][j];
	}
	for (int i = 0; i < order / 2; ++i) {
		for (int j = 0; j < order / 2; ++j)
			A[i][j] = A[i + order / 2][j];
	}
	for (int i = 0; i < order / 2; ++i) {
		for (int j = order / 2; j < order; ++j)
			A[i][j] = A[i + order / 2][j];
	}
	for (int i = order / 2, k = 0; i < order; ++i, ++k) {
		for (int j = 0; j < order / 2; ++j)
			A[i][j] = B[k][j];
	}
	for (int i = order / 2, k = 0; i < order; ++i, ++k) {
		for (int j = order / 2, n = 0; j < order; ++j, ++n)
			A[i][j] = C[k][n];
	}
	for (int i = 0; i < order / 2; ++i)
		delete[] B[i];
	delete[] B;
	for (int i = 0; i < order / 2; ++i)
		delete[] C[i];
	delete[] C;
}

void swapFromSideToSide(long double **A, int order) {
	long double **B = 0, **C = 0;
	B = new long double *[order / 2];
	for (int i = 0; i < order / 2; ++i)
		B[i] = new long double[order / 2];
	for (int i = 0; i < order / 2; ++i) {
		for (int j = 0; j < order / 2; ++j)
			B[i][j] = A[i][j];
	}
	C = new long double *[order / 2];
	for (int i = 0; i < order / 2; ++i)
		C[i] = new long double[order / 2];
	for (int i = order / 2, k = 0; i < order; ++i, ++k) {
		for (int j = 0; j < order / 2; ++j)
			C[k][j] = A[i][j];
	}
	for (int i = 0; i < order / 2; ++i) {
		for (int j = 0; j < order / 2; ++j)
			A[i][j] = A[i][j + order / 2];
	}
	for (int i = order / 2; i < order; ++i) {
		for (int j = 0; j < order / 2; ++j)
			A[i][j] = A[i][j + order / 2];
	}
	for (int i = order / 2, k = 0; i < order; ++i, ++k) {
		for (int j = order / 2, n = 0; j < order; ++j, ++n)
			A[i][j] = C[k][n];
	}
	for (int i = 0; i < order / 2; ++i) {
		for (int j = order / 2, k = 0; j < order; ++j, ++k)
			A[i][j] = B[i][k];
	}
	for (int i = 0; i < order / 2; ++i)
		delete[] B[i];
	delete[] B;
	for (int i = 0; i < order / 2; ++i)
		delete[] C[i];
	delete[] C;
}

void newArray(long double **A, long double **B, int order) {
	for (int j = 0; j < order; ++j) {
		long double composition = 1;
		for (int i = 0; i < order; ++i)
			composition = composition * B[j][i];
		for (int i = 0; i < order; ++i)
			A[i][j] = A[i][j] + composition;
	}
}

void serpentDownUp(long double **A, int rows, int columns) {
	int i = 0, j = 0, coils = 0;
	for (coils; coils < columns; ++coils) {
		if (coils % 2 == 0) {
			for (i, j; i < rows; ++i) {
				A[i][j] = i + 1 + j * rows;
			}
			++j;
			--i;
		}
		else {
			for (i, j; i >= 0; --i) {
				A[i][j] = rows - i + j * rows;
			}
			++j;
			++i;
		}
	}
}

void serpentSpiral(long double **A, int rows, int columns) {
	int i = 0, j = 0, n = rows, t = columns;
	if (columns <= rows) {
		for (int coils = 0; coils < rows / 2; ++coils) {
			for (i, j; j < columns - i; ++j) {
				if (j == 0)
					A[i][j] = 1;
				else
					A[i][j] = A[i][j - 1] + 1;
			}
			--j;
			++i;
			if (columns == rows) {
				for (i, j; i < j + 1; ++i)
					A[i][j] = A[i - 1][j] + 1;
			}
			else {
				for (i, j; i < n; ++i)
					A[i][j] = A[i - 1][j] + 1;
				--n;
			}
			--i;
			--j;
			if (columns == rows) {
				for (i, j; j >= columns - i - 1; --j)
					A[i][j] = A[i][j + 1] + 1;
			}
			else {
				for (i, j; j >= columns - i; --j)
					A[i][j] = A[i][j + 1] + 1;
			}
			++j;
			--i;
			for (i, j; i >= j + 1; --i)
				A[i][j] = A[i + 1][j] + 1;
			++j;
			++i;
			if (coils == rows / 2 - 1 && rows % 2 == 1 && columns == rows)
				A[i][j] = A[i][j - 1] + 1;
		}
	}
	else {
		if (rows % 2 == 1) {
			for (int coils = 0; coils < rows / 2 + 1; ++coils) {
				for (i, j; j < columns - i; ++j) {
					if (j == 0)
						A[i][j] = 1;
					else
						A[i][j] = A[i][j - 1] + 1;
				}
				if (coils == rows / 2)
					break;
				--j;
				++i;
				for (i, j; i < n; ++i)
					A[i][j] = A[i - 1][j] + 1;
				--i;
				--j;
				for (i, j; j >= columns - t; --j)
					A[i][j] = A[i][j + 1] + 1;
				++j;
				--i;
				--t;
				for (i, j; i > rows - n; --i)
					A[i][j] = A[i + 1][j] + 1;
				--n;
				++j;
				++i;
			}
		}
		else {
			for (int coils = 0; coils < rows / 2; ++coils) {
				for (i, j; j < columns - i; ++j) {
					if (j == 0)
						A[i][j] = 1;
					else
						A[i][j] = A[i][j - 1] + 1;
				}
				--j;
				++i;
				for (i, j; i < n; ++i)
					A[i][j] = A[i - 1][j] + 1;
				--i;
				--j;
				for (i, j; j >= columns - t; --j)
					A[i][j] = A[i][j + 1] + 1;
				++j;
				--i;
				--t;
				for (i, j; i > rows - n; --i)
					A[i][j] = A[i + 1][j] + 1;
				--n;
				++j;
				++i;
			}
		}
	}
}

long double maxRow(long double **A, int i, int columns)
{
	long double max = A[i][0];
	for (int j = 1; j < columns; ++j) {
		if (A[i][j] > max)
			max = A[i][j];
	}
	return max;
}

long double minRow(long double **A, int i, int columns)
{
	long double min = A[i][0];
	for (int j = 1; j < columns; ++j) {
		if (A[i][j] < min)
			min = A[i][j];
	}
	return min;
}

long double maxColumn(long double **A, int j, int rows)
{
	long double max = A[0][j];
	for (int i = 1; i < rows; ++i) {
		if (A[i][j] > max)
			max = A[i][j];
	}
	return max;
}

long double minColumn(long double **A, int j, int rows)
{
	long double min = A[0][j];
	for (int i = 1; i < rows; ++i) {
		if (A[i][j] < min)
			min = A[i][j];
	}
	return min;
}

bool saddlePointYN(long double **A, int i, int j, int rows, int columns) {
	return ((A[i][j] == maxRow(A, i, columns)) && (A[i][j] == minColumn(A, j, rows))) || ((A[i][j] == minRow(A, i, columns)) && (A[i][j] == maxColumn(A, j, rows)));
}

void saddlePoint(long double **A, int rows, int columns) {
	int count = 0;
	cout << endl;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (saddlePointYN(A, i, j, rows, columns)) {
				++count;
			}
		}
	}
	if (count == 0)
		cout << "Седловых точек не обнаружено." << endl << endl;
	else {
		cout << "Седловые точки находятся под индексами:" << endl << endl;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				if (saddlePointYN(A, i, j, rows, columns)) {
					cout << "[" << i + 1 << "][" << j + 1 << "]" << endl;
				}
			}
		}
		cout << endl << "Количество седловых точек: " << count << endl << endl;
	}
}

void memoryForArray(long double **&A, int rows, int columns) {
	A = new long double *[rows];
	for (int i = 0; i < rows; ++i)
		A[i] = new long double[columns];
}

void generateArray(long double **&A, int rows, int columns) {
	memoryForArray(A, rows, columns);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j)
			A[i][j] = rand() % 100;
	}
}

void inputArray(long double **&A, int rows, int columns) {
	memoryForArray(A, rows, columns);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			cout << "Введите значение элемента с индексами [" << i + 1 << "][" << j + 1 << "]: ";
			cin >> A[i][j];
		}
	}
	cout << endl;
}

void showArray(long double **A, int rows, int columns) {
	cout << " ";
	SetConsoleTextAttribute(textColour, 5);
	for (int i = 0; i < columns; ++i) {
		cout.width(15);
		cout.fill(' ');
		cout << i + 1;
	}
	SetConsoleTextAttribute(textColour, 7);
	cout << endl << endl;
	for (int i = 0; i < rows; ++i) {
		SetConsoleTextAttribute(textColour, 5);
		cout << i + 1;
		SetConsoleTextAttribute(textColour, 7);
		for (int j = 0; j < columns; ++j) {
			if (i >= 9 && i < 99 && j == 0)
				cout.width(14);
			else if (i >= 99 && j == 0)
				cout.width(13);
			else
				cout.width(15);
			cout.fill(' ');
			cout << A[i][j];
		}
		cout << endl << endl;
	}
}

void showFancyArray(long double **A, int order, bool condition, int method) {
	cout << " ";
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
	for (int i = 0; i < order; ++i) {
		cout.width(15);
		cout.fill(' ');
		cout << i + 1;
	}
	SetConsoleTextAttribute(textColour, 7);
	cout << endl << endl;
	for (int i = 0; i < order; ++i) {
		SetConsoleTextAttribute(textColour, 5);
		cout << i + 1;
		SetConsoleTextAttribute(textColour, 7);
		for (int j = 0; j < order; ++j) {
			if (i >= 0 && i < order / 2 && j >= 0 && j < order / 2)
				SetConsoleTextAttribute(textColour, part1);
			else if (i >= 0 && i < order / 2 && j >= order / 2 && j < order)
				SetConsoleTextAttribute(textColour, part2);
			else if (i >= order / 2 && i < order && j >= 0 && j < order / 2)
				SetConsoleTextAttribute(textColour, part3);
			else if (i >= order / 2 && i < order && j >= order / 2 && j < order)
				SetConsoleTextAttribute(textColour, part4);
			{
				if (i >= 9 && i < 99 && j == 0)
					cout.width(14);
				else if (i >= 99 && j == 0)
					cout.width(13);
				else
					cout.width(15);
				cout.fill(' ');
				cout << A[i][j];
			}
		}
		SetConsoleTextAttribute(textColour, 7);
		cout << endl << endl;
	}
}

void deleteArray(long double **A, int rows, int columns) {
	for (int i = 0; i < rows; ++i)
		delete[] A[i];
	delete[] A;
	A = 0;
}

void arrayMenu() {
	cout << "Выберите опцию . . ." << endl;
	cout << "0. Заполнить матрицу вручную" << endl;
	cout << "1. Заполнить матрицу автоматически" << endl;
	cout << "Опция: ";
}

#endif
