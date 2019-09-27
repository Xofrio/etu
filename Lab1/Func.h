#include <iostream>
#include <Windows.h>

using namespace std;

#ifndef FUNC_H
#define FUNC_H

int getInt() {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << endl << "Попробуйте ввести корректное число (от  -2147483648 до 2147483647): ";
		}
		else {
			cin.ignore(32767, '\n');
			return userNumber;
		}
	}
}

short getShort() {
	while (true) {
		short userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << endl << "Попробуйте ввести корректное число (от -32768 до 32767): ";
		}
		else {
			cin.ignore(32767, '\n');
			return userNumber;
		}
	}
}

unsigned getUnsigned() {
	while (true) {
		unsigned userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << endl << "Попробуйте ввести корректное число (от 0 до 4294967295): ";
		}
		else {
			cin.ignore(32767, '\n');
			return userNumber;
		}
	}
}

float getFloat() {
	while (true) {
		float userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << endl << "Попробуйте ввести корректное число (от 1.175494351e-38 до 3.402823466e+38): ";
		}
		else {
			cin.ignore(32767, '\n');
			return userNumber;
		}
	}
}

double getDouble() {
	while (true) {
		double userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << endl << "Попробуйте ввести корректное число (от -2.2250738585072014e-308 до 1.7976931348623158e+308): ";
		}
		else {
			cin.ignore(32767, '\n');
			return userNumber;
		}
	}
}

char getOption() {
	while (true) {
		char option;
		cin >> option;
		cin.ignore(32767, '\n');
		if (option == 'I' || option == 'i' || option == 'S' || option == 's' || option == 'U' || option == 'u' || option == 'F' || option == 'f' || option == 'D' || option == 'd')
			return option;
		else
			cout << endl << "Попробуйте ещё раз." << endl << endl << "I(i) - int, S(s) - short int, U(u) - unsigned int, F(f) - float, D(d) - double: ";
	}
}

void intInterpretation(int number) {
	bool razryad;
	razryad = number & ((unsigned)1 << 31);
	cout << razryad << " ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	for (int n = 30; n >= 0; --n) {
		razryad = number & ((unsigned)1 << n);
		cout << razryad;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void shortInterpretation(short number) {
	bool razryad;
	razryad = number & ((unsigned)1 << 14);
	cout << razryad << " ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	for (int n = 13; n >= 0; --n) {
		razryad = number & ((unsigned)1 << n);
		cout << razryad;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void unsignedInterpretation(unsigned number) {
	bool razryad;
	razryad = number & ((unsigned)1 << 31);
	cout << razryad << " ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	for (int n = 30; n >= 0; --n) {
		razryad = number & ((unsigned)1 << n);
		cout << razryad;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
#endif
