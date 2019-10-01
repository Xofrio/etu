#include <iostream>
#include <Windows.h>

using namespace std;

#ifndef FUNC_H
#define FUNC_H

HANDLE textColour = GetStdHandle(STD_OUTPUT_HANDLE);

int getInt() {
	cout << endl << "Введите число от -2147483648 до 2147483647: ";
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail() || userNumber < ~2147483647 || userNumber > 2147483647) {
			cin.clear();
			cin.ignore(cin.rdbuf() -> in_avail());
			cout << endl << "Попробуйте ввести корректное число (от -2147483648 до 2147483647): ";
		}
		else {
			cin.ignore(cin.rdbuf() -> in_avail());
			return userNumber;
		}
	}
}

short getShort() {
	cout << endl << "Введите число от -32768 до 32767: ";
	while (true) {
		short userNumber;
		cin >> userNumber;
		if (cin.fail() || userNumber < -32768 || userNumber > 32767) {
			cin.clear();
			cin.ignore(cin.rdbuf() -> in_avail());
			cout << endl << "Попробуйте ввести корректное число (от -32768 до 32767): ";
		}
		else {
			cin.ignore(cin.rdbuf() -> in_avail());
			return userNumber;
		}
	}
}

unsigned long getUnsigned() {
	cout << endl << "Введите число от 0 до 4294967295: ";
	while (true) {
		unsigned long userNumber;
		cin >> userNumber;
		if (cin.fail() || (int)userNumber < 0 || userNumber > ~(unsigned)0) {
			cout << userNumber << endl;
			cin.clear();
			cin.ignore(cin.rdbuf() -> in_avail());
			cout << endl << "Попробуйте ввести корректное число (от 0 до 4294967295): ";
		}
		else {
			cin.ignore(cin.rdbuf() -> in_avail());
			return userNumber;
		}
	}
}

float getFloat() {
	cout << endl << "Введите число от -2147483648 до 2147483647: ";
	while (true) {
		float userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf() -> in_avail());
			cout << endl << "Попробуйте ввести корректное число (от -2147483648 до 2147483647): ";
		}
		else {
			cin.ignore(cin.rdbuf() -> in_avail());
			return userNumber;
		}
	}
}

double getDouble() {
	cout << endl << "Введите число от -9223372036854775808 до 9223372036854775807: ";
	while (true) {
		double userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf() -> in_avail());
			cout << endl << "Попробуйте ввести корректное число (от -9223372036854775808 до 9223372036854775807): ";
		}
		else {
			cin.ignore(cin.rdbuf() -> in_avail());
			return userNumber;
		}
	}
}

char getOption() {
	while (true) {
		char option;
		cin >> option;
		cin.ignore(cin.rdbuf() -> in_avail());
		if (option == 'I' || option == 'i' || option == 'S' || option == 's' || option == 'U' || option == 'u' || option == 'F' || option == 'f' || option == 'D' || option == 'd')
			return option;
		else
			cout << endl << "Попробуйте ещё раз." << endl << endl << "I(i) - int, S(s) - short int, U(u) - unsigned int, F(f) - float, D(d) - double: ";
	}
}

void doubleInterpretation(double number, bool *A, int position) {
	union newType {
		double firstPart;
		char secondPart[sizeof(firstPart)];
	};
	newType unionedDouble;
	unionedDouble.firstPart = number;
	unsigned char digit;
	for (int i = sizeof(unionedDouble) - 1; i >= 0; --i) {
		digit = unionedDouble.secondPart[i];
		for (int j = 0; j < 8; ++j) {
			if (digit & (128 >> j))
				A[position - 64] = 1;//cout << 1;
			else
				A[position - 64] = 0;//cout << 0;
			position++;
		}
	}
}

void doubleOutput(bool *A) {
	for (int i = 0; i < 64; ++i) {
		if (i == 1) {
			cout << " ";
			SetConsoleTextAttribute(textColour, 5);
		}
		if (i == 12) {
			cout << " ";
			SetConsoleTextAttribute(textColour, 10);
		}
		if (i % 8 == 0 && i != 8 && i != 0)
			cout << " ";
		cout << A[i];
	}
	SetConsoleTextAttribute(textColour, 7);
	cout << endl << endl;
}

void intInterpretation(int number) {
	bool digit;
	digit = number & ((bool)1 << 31);
	cout << digit << " ";
	SetConsoleTextAttribute(textColour, 10);
	for (int n = 30; n >= 0; --n) {
		if ((31 - n) % 8 == 0)
			cout << " ";
		digit = number & ((bool)1 << n);
		cout << digit;
	}
	SetConsoleTextAttribute(textColour, 7);
	cout << endl << endl;
}

void floatInterpretation(float number, bool digits[]) {
	int *digit = reinterpret_cast<int*>(&number);
	for (int i = 31; i >= 0; --i)
		digits[i] = *digit & ((bool) 1 << i);
}

void floatOutput(bool digits[]) {
	for (int i = 31; i >= 0; --i) {
		if (i == 30) {
			SetConsoleTextAttribute(textColour, 5);
			cout << " ";
		}
		if (i == 22) {
			SetConsoleTextAttribute(textColour, 10);
			cout << " ";
		}
		if (i == 15 || i == 8)
			cout << " ";
		cout << digits[i];
	}
	SetConsoleTextAttribute(textColour, 7);
	cout << endl << endl;
}

void shortInterpretation(short number) {
	bool digit;
	digit = number & ((bool)1 << 14);
	cout << digit << " ";
	SetConsoleTextAttribute(textColour, 10);
	for (int n = 13; n >= 0; --n) {
		if ((31 - n) % 8 == 0)
			cout << " ";
		digit = number & ((bool)1 << n);
		cout << digit;
	}
	SetConsoleTextAttribute(textColour, 7);
	cout << endl << endl;
}

void unsignedInterpretation(unsigned number) {
	bool digit;
	digit = number & ((bool)1 << 31);
	cout << digit << " ";
	SetConsoleTextAttribute(textColour, 10);
	for (int n = 30; n >= 0; --n) {
		if ((31 - n) % 8 == 0)
			cout << " ";
		digit = number & ((bool)1 << n);
		cout << digit;
	}
	SetConsoleTextAttribute(textColour, 7);
	cout << endl << endl;
}

int getMenuOption() {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf() -> in_avail());
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 2): ";
		}
		else if (userNumber == 0 || userNumber == 1 || userNumber == 2) {
			cin.ignore(cin.rdbuf() -> in_avail());
			return userNumber;
		}
		else
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 2): ";
	}
}

void Menu() {
	cout << "Выберите опцию . . ." << endl;
	cout << "0. Отобразить двоичное представление числа в памяти ЭВМ" << endl;
	cout << "1. Инвертировать все биты числа" << endl;
	cout << "2. Выйти" << endl;
	cout << "Опция: ";
}

#endif
