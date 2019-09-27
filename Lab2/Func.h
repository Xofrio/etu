#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

#ifndef FUNC_H
#define FUNC_H

void swap(int *first, int *second) {
	*first = *first + *second;
	*second = *first - *second;
	*first = *first - *second;
}

int getValue() {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << endl << "Попробуйте ввести корректное число: ";
		}
		else {
			cin.ignore(32767, '\n');
			return userNumber;
		}
	}
}

int getIndex(int elements_count) {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail() || userNumber < 0 || userNumber >= elements_count) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << endl << "Попробуйте ввести корректный индекс (от 0 до " << elements_count - 1 << "): ";
		}
		else {
			cin.ignore(32767, '\n');
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
			cin.ignore(32767, '\n');
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 9): ";
		}
		else if (userNumber == 0 || userNumber == 1 || userNumber == 2 || userNumber == 3 || userNumber == 4 || userNumber == 5 || userNumber == 6 || userNumber == 7 || userNumber == 8 || userNumber == 9) {
			cin.ignore(32767, '\n');
			return userNumber;
		}
		else
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 9): ";
	}
}

char getMethod() {
	while (true) {
		char method;
		cin >> method;
		cin.ignore(32767, '\n');
		if (method == 'B' || method == 'b' || method == 'S' || method == 's' || method == 'C' || method == 'c' || method == 'I' || method == 'i' || method == 'Q' || method == 'q')
			return method;
		else
			cout << endl << "Попробуйте ещё раз." << endl << endl << "B(b) - Bubble, S(s) - Shaker; C(c) - Comb; I(i) - Insert; Q(q) - Quick: ";
	}
}

char getOption() {
	while (true) {
		char option;
		cin >> option;
		cin.ignore(32767, '\n');
		if (option == 'D' || option == 'd' || option == 'I' || option == 'i' || option == 'F' || option == 'f')
			return option;
		else
			cout << endl << "Попробуйте ещё раз." << endl << endl << "D(d) - удалить, I(i) - вставить, F(f) - поиск значения : ";
	}
}

void bubbleSorting(int *A, int count) {
	for (int i = 0; i < count; ++i) {
		for (int j = 0; j < count - 1; ++j) {
			if (A[j] > A[j + 1])
				swap(&A[j], &A[j + 1]);
		}
	}
}

void cocktailSorting(int *A, int count) {
	int left = 0, right = count - 1;
	bool motion = 1;
	while ((left < right) && motion == 1) {
		motion = 0;
		for (int i = left; i < right; ++i) {
			if (A[i] > A[i + 1]) {
				swap(&A[i], &A[i + 1]);
				motion = 1;
			}
		}
		--right;
		for (int i = right; i > left; --i) {
			if (A[i - 1] > A[i]) {
				swap(&A[i - 1], &A[i]);
				motion = 1;
			}
		}
		++left;
	}
}

void combSorting(int *A, int count) {
	int gap = count;
	bool motion = 1;
	while (gap != 1 || motion == 1) {
		gap = (gap * 10) / 13;
		if (gap < 1)
			gap = 1;
		motion = 0;
		for (int i = 0; i < count - gap; ++i) {
			if (A[i] > A[i + gap]) {
				swap(&A[i], &A[i + gap]);
				motion = 1;
			}
		}
	}
}

void insertionSorting(int *A, int count) {
	int i, k, j;
	for (i = 1; i < count; ++i) {
		k = A[i];
		j = i - 1;
		while (j >= 0 && A[j] > k) {
			A[j + 1] = A[j];
			--j;
		}
		A[j + 1] = k;
	}
}

void quickSorting(int *A, int start, int end) {
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
			++i;
			--j;
		}
	}
	if (start < j)
		quickSorting(A, start, j);
	if (i < end)
		quickSorting(A, i, end);
}

int search(int *A, int start, int end, int number) {
	if (end >= start) {
		int mid = start + (end - start) / 2;
		if (A[mid] == number)
			return mid;
		if (A[mid] > number)
			return search(A, start, mid - 1, number);
		if (A[mid] < number)
			return search(A, mid + 1, end, number);
	}
	return -1;
}

int back(int *A, int index, int count) {
	while (A[index] == A[index - 1]) {
		--index;
		++count;
	}
	return count;
}

int forth(int *A, int index, int count) {
	while (A[index] == A[index + 1]) {
		++index;
		++count;
	}
	return count;
}

int backIndex(int *A, int *B, int index, int count, int &index2) {
	while (A[index] == A[index - 1]) {
		B[index2] = index;
		--index;
		++count;
		++index2;
	}
	B[index2] = index;
	return count;
}

int forthIndex(int *A, int *B, int index, int count, int &index2) {
	while (A[index] == A[index + 1]) {
		B[index2] = index;
		++index;
		++count;
		++index2;
	}
	B[index2] = index;
	return count;
}

void thirdVariant(int *A, int count, int number) {
	for (int i = 0; i < count; ++i) {
		if (i % 2 == 1)
			A[i] = (A[i] - number) * (rand() % 9 + 1);
	}
}

void generateArray(int *A, int count) {
	for (int i = 0; i < count; ++i)
		A[i] = rand() % 100;
}

void showArray(int *A, int count) {
	for (int i = 0; i < count; ++i)
		cout << i << ". " << A[i] << endl;
}

void Menu() {
	cout << endl << "Выберите опцию . . ." << endl;
	cout << "0. Создать массив" << endl;
	cout << "1. Сортировать массив" << endl;
	cout << "2. Показать минимальный и максимальный элементы массива" << endl;
	cout << "3. Показать количество элементов, равных минимальному и максимальному элементам" << endl;
	cout << "4. Показать количество элементов, больших, чем заданное число" << endl;
	cout << "5. Показать количество элементов, меньших, чем заданное число" << endl;
	cout << "6. Удалить элемент, вставить элемент или найти значение" << endl;
	cout << "7. Поменять элементы местами" << endl;
	cout << "8. Уменьшить каждый нечётный элемент на число, затем умножить этот элемент на случайное число (от 1 до 9)" << endl;
	cout << "9. Выйти" << endl;
	cout << "Опция: ";
}

#endif
