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
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 2): ";
		}
		else if (userNumber == 0 || userNumber == 1 || userNumber == 2) {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
		else
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 2): ";
	}
}

bool getSubMenuOption() {
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

void orthogonal(double **A, int order) {
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
		cout << "Матрица ортонормированная" << endl;
	else
		cout << "Матрица не ортонормированная" << endl;
}

void generateArray(double **&A, int rows, int columns) {
	A = new double *[rows];
	for (int i = 0; i < rows; ++i)
		A[i] = new double[columns];
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j)
			A[i][j] = rand() % 100;
	}
}

void inputArray(double **&A, int rows, int columns) {
	A = new double *[rows];
	for (int i = 0; i < rows; ++i)
		A[i] = new double[columns];
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			cout << "Введите значение элемента с индексами [" << i + 1 << "][" << j + 1 << "]: ";
			cin >> A[i][j];
		}
	}
}

void showArray(double **A, int rows, int columns) {
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

void deleteArray(double **A, int rows, int columns) {
	for (int i = 0; i < rows; ++i)
		delete[] A[i];
	delete[] A;
	A = 0;
}

void Menu() {
	cout << "Выберите опцию . . ." << endl;
	cout << "0. Создать матрицу" << endl;
	cout << "1. Определить, является ли матрица ортонормированной" << endl;
	cout << "2. Выйти" << endl;
	cout << "Опция: ";
}

#endif
