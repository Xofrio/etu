#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include <chrono>

using namespace std;

HANDLE textColour = GetStdHandle(STD_OUTPUT_HANDLE);

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
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректное число: ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}

int getArrayValue() {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректное число: ";
		}
		else if (userNumber >= 0 || userNumber <= 99) {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
		else {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректное число: ";
		}
	}
}

void output(bool *A) {
	for (int i = 31; i >= 0; --i) {
		if ((31 - i) % 8 == 0 && i != 31)
			cout << " ";
		cout << A[i];
		if (i == 31) {
			cout << " ";
			SetConsoleTextAttribute(textColour, 10);
		}
	}
	SetConsoleTextAttribute(textColour, 7);
}

void charArray(char litera, bool *digits) {
	for (int i = 31; i >= 0; --i)
		digits[i] = int(litera) & ((bool)1 << i);
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

void intArray(int number, bool *digits) {
	for (int i = 31; i >= 0; --i)
		digits[i] = number & ((bool)1 << i);
}

void inputArray(int *&A, int elements) {
	for (int i = 0; i < elements; ++i) {
		cout << "Введите значение элемента с индексами [" << i << "] (от 0 до 99): ";
		A[i] = getArrayValue();
	}
	cout << endl;
}

void generateArray(int *A, int count) {
	for (int i = 0; i < count; ++i)
		A[i] = rand() % 100;
}

void inputArrayFromFile(int *&A, int &elements, bool &created) {
	elements = 0;
	ifstream in("array.txt");
	if (in.is_open()) {
		int temp;
		while (!in.eof()) {
			in >> temp;
			++elements;
		}
		in.seekg(0, ios::beg);
		in.clear();
		A = new int[elements];
		int i = 0;
		while (!in.eof()) {
			in >> A[i];
			++i;
		}
		if (elements > 0)
			created = 1;
		else
			created = 0;
		in.close();
	}
	else {
		cout << "Файл с именем 'array.txt' не найден." << endl << endl;
	}
}

void showArray(int *A, int count) {
	for (int i = 0; i < count; ++i)
		cout << i << ". " << A[i] << endl;
	cout << endl;
}

void draw(string str) {
	SetConsoleTextAttribute(textColour, 2);
	cout << str << endl;
	SetConsoleTextAttribute(textColour, 7);
}

int mainMenu() {
	int key = 0;
	int code = 0;
	do {
		system("cls");
		key = (key + 6) % 6;
		if (key == 0)
			draw(">Регистрация/вход");
		else
			cout << " Регистрация/вход" << endl;
		if (key == 1)
			draw(">Приветствие");
		else
			cout << " Приветствие" << endl;
		if (key == 2)
			draw(">Создать массив");
		else
			cout << " Создать массив" << endl;
		if (key == 3)
			draw(">Указать метод сортировки и получить некоторые данные о массиве");
		else
			cout << " Указать метод сортировки и получить некоторые данные о массиве" << endl;
		if (key == 4)
			draw(">Посмотреть флаги двух стран");
		else
			cout << " Посмотреть флаги двух стран" << endl;
		if (key == 5)
			draw(">Выйти");
		else
			cout << " Выйти" << endl;
		code = _getch();
		if (code != 13) {
			code = _getch();
			if (code == 80 || code == 251)
				++key;
			if (code == 72 || code == 246)
				--key;
		}
	} while (code != 13);
	system("cls");
	return key;
}

int userMenu() {
	int key = 0;
	int code = 0;
	do {
		system("cls");
		key = (key + 3) % 3;
		if (key == 0)
			draw(">Регистрация");
		else
			cout << " Регистрация" << endl;
		if (key == 1)
			draw(">Авторизация");
		else
			cout << " Авторизация" << endl;
		if (key == 2)
			draw(">Назад");
		else
			cout << " Назад" << endl;
		code = _getch();
		if (code != 13) {
			code = _getch();
			if (code == 80 || code == 251)
				++key;
			if (code == 72 || code == 246)
				--key;
		}
	} while (code != 13);
	system("cls");
	return key;
}

int fallBack() {
	int key = 0;
	int code = 0;
	do {
		key = (key + 1) % 1;
		if (key == 0){
			cout << endl;
			draw(">Назад");
		}
		code = _getch();
	} while (code != 13);
	return key;
}

int anonymousMenu() {
	int key = 0;
	int code = 0;
	do {
		system("cls");
		key = (key + 3) % 3;
		cout << "Обнаружен неавторизованный пользователь! Хотите авторизоваться?" << endl;
		if (key == 0)
			draw(">Авторизация");
		else
			cout << " Авторизация" << endl;
		if (key == 1)
			draw(">Я аноним");
		else
			cout << " Я аноним" << endl;
		if (key == 2)
			draw(">Назад");
		else
			cout << " Назад" << endl;

		code = _getch();
		if (code != 13) {
			code = _getch();
			if (code == 80 || code == 251)
				++key;
			if (code == 72 || code == 246)
				--key;
		}
	} while (code != 13);
	return key;
}

int arrayMenu() {
	int key = 0;
	int code = 0;
	do {
		system("cls");
		key = (key + 4) % 4;
		if (key == 0)
			draw(">Заполнить массив вручную");
		else
			cout << " Заполнить массив вручную" << endl;
		if (key == 1)
			draw(">Заполнить массив автоматически");
		else
			cout << " Заполнить массив автоматически" << endl;
		if (key == 2)
			draw(">Считать массив из файла");
		else
			cout << " Считать массив из файла" << endl;
		if (key == 3)
			draw(">Назад");
		else
			cout << " Назад" << endl;
		code = _getch();
		if (code != 13) {
			code = _getch();
			if (code == 80 || code == 251)
				++key;
			if (code == 72 || code == 246)
				--key;
		}
	} while (code != 13);
	system("cls");
	return key;
}


int methodMenu() {
	int key = 0;
	int code = 0;
	do {
		system("cls");
		key = (key + 6) % 6;
		if (key == 0)
			draw(">Bubble");
		else
			cout << " Bubble" << endl;
		if (key == 1)
			draw(">Shaker");
		else
			cout << " Shaker" << endl;
		if (key == 2)
			draw(">Comb");
		else
			cout << " Comb" << endl;
		if (key == 3)
			draw(">Insert");
		else
			cout << " Insert" << endl;
		if (key == 4)
			draw(">Quick");
		else
			cout << " Quick" << endl;
		if (key == 5)
			draw(">Назад");
		else
			cout << " Назад" << endl;
		code = _getch();
		if (code != 13) {
			code = _getch();
			if (code == 80 || code == 251)
				++key;
			if (code == 72 || code == 246)
				--key;
		}
	} while (code != 13);
	system("cls");
	return key;
}

#endif