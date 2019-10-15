#include <iostream>
#include <Windows.h>
#undef min
#undef max

using namespace std;

#ifndef FUNC_H
#define FUNC_H

HANDLE textColour = GetStdHandle(STD_OUTPUT_HANDLE);

int getInt() {
	cout << endl << "Введите число от " << numeric_limits<int>::min() << " до " << numeric_limits<int>::max() << ": ";
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail() || userNumber < numeric_limits<int>::min() || userNumber > numeric_limits<int>::max()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректное число (от " << numeric_limits<int>::min() << " до " << numeric_limits<int>::max() << "): ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}

short getShort() {
	cout << endl << "Введите число от " << numeric_limits<short>::min() << " до " << numeric_limits<short>::max() << ": ";
	while (true) {
		short userNumber;
		cin >> userNumber;
		if (cin.fail() || userNumber < numeric_limits<short>::min() || userNumber > numeric_limits<short>::max()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректное число (от " << numeric_limits<short>::min() << " до " << numeric_limits<short>::max() << "): ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}

unsigned getUnsigned() {
	cout << endl << "Введите число от " << numeric_limits<unsigned>::min() << " до " << numeric_limits<unsigned>::max() << ": ";
	while (true) {
		unsigned userNumber;
		cin >> userNumber;
		if (cin.fail() || (int)userNumber < 0 || userNumber > numeric_limits<unsigned>::max()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректное число (от " << numeric_limits<unsigned>::min() << " до " << numeric_limits<unsigned>::max() << "): ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}

float getFloat() {
	cout << endl << "Введите число от " << numeric_limits<float>::min() << " до " << numeric_limits<float>::max() << ": ";
	while (true) {
		float userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректное число (от " << numeric_limits<float>::min() << " до " << numeric_limits<float>::max() << "): ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}

double getDouble() {
	cout << endl << "Введите число от " << numeric_limits<double>::min() << " до " << numeric_limits<double>::max() << ": ";
	while (true) {
		double userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректное число (от " << numeric_limits<double>::min() << " до " << numeric_limits<double>::max() << "): ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}

char getOption() {
	while (true) {
		char option;
		cin >> option;
		cin.ignore(cin.rdbuf()->in_avail());
		if (option == 'I' || option == 'i' || option == 'S' || option == 's' || option == 'U' || option == 'u' || option == 'F' || option == 'f' || option == 'D' || option == 'd')
			return option;
		else
			cout << endl << "Попробуйте ещё раз." << endl << endl << "I(i) - int, S(s) - short int, U(u) - unsigned int, F(f) - float, D(d) - double: ";
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

void inversion(bool *A, int count) {
	cout << endl << "Инверcия всех битов:" << endl << endl;
	for (int i = count; i >= 0; --i)
		A[i] == 0 ? A[i] = 1 : A[i] = 0;
}

void Output(char type, bool *A){
	if (type == 'I' || type == 'i') {
		for (int i = 31; i >= 0; --i) {
			if ((31 - i) % 8 == 0 && i != 31)
				cout << " ";
			cout << A[i];
			if (i == 31) {
				cout << " ";
				SetConsoleTextAttribute(textColour, 10);
			}
		}
	}
	else if (type == 'S' || type == 's') {
		for (int i = 15; i >= 0; --i) {
			if ((31 - i) % 8 == 0 && i != 15)
				cout << " ";
			cout << A[i];
			if (i == 15) {
				cout << " ";
				SetConsoleTextAttribute(textColour, 10);
			}
		}
	}
	else if (type == 'U' || type == 'u') {
		for (int n = 31; n >= 0; --n) {
			if ((31 - n) % 8 == 0 && n != 31)
				cout << " ";
			cout << A[n];
			if (n == 31) {
				cout << " ";
				SetConsoleTextAttribute(textColour, 10);
			}
		}
	}
	else if (type == 'F' || type == 'f') {
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
			cout << A[i];
		}
	}
	else if (type == 'D' || type == 'd') {
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
	}
	SetConsoleTextAttribute(textColour, 7);
	cout << endl << endl;
}

void intArray(int number, bool *digits) {
	for (int i = 31; i >= 0; --i) {
		digits[i] = number & ((bool)1 << i);
	}
}

void shortArray(short number, bool *digits) {
	for (int i = 15; i >= 0; --i) {
		digits[i] = number & ((bool)1 << i);
	}
}

void unsignedArray(unsigned long number, bool *digits) {
	for (int i = 31; i >= 0; --i) {
		digits[i] = number & ((bool)1 << i);
	}
}

void floatArray(float number, bool *digits) {
	int *digit = reinterpret_cast<int*>(&number);
	for (int i = 31; i >= 0; --i)
		digits[i] = *digit & ((bool)1 << i);
}

void doubleArray(double number, bool *A, int position) {
	union newType {
		double firstPart;
		char secondPart[sizeof(firstPart)];
	} unionedDouble;
	unionedDouble.firstPart = number;
	unsigned char digit;
	for (int i = sizeof(unionedDouble) - 1; i >= 0; --i) {
		digit = unionedDouble.secondPart[i];
		for (int j = 0; j < 8; ++j) {
			digit & (128 >> j) ? A[position - 64] = 1 : A[position - 64] = 0;
			position++;
		}
	}
}

#endif
