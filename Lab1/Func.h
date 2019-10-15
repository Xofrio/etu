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
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 4): ";
		}
		else if (userNumber == 0 || userNumber == 1 || userNumber == 2 || userNumber == 3 || userNumber == 4) {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
		else
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 4): ";
	}
}

short getPositionNumber(char type, short needed) {
	if (needed == 1) {
		cout << endl << "Введите номер нужного бита: ";
		while (true) {
			short userNumber;
			cin >> userNumber;
			if (type == 'I' || type == 'i' || type == 'U' || type == 'u' || type == 'F' || type == 'f') {
				if (cin.fail() || userNumber < 0 || userNumber > 31) {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << endl << "Попробуйте ввести корректный номер бита (от 0 до 31): ";
				}
				else {
					cin.ignore(cin.rdbuf()->in_avail());
					return userNumber;
				}
			}
			else if (type == 'S' || type == 's') {
				if (cin.fail() || userNumber < 0 || userNumber > 15) {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << endl << "Попробуйте ввести корректный номер бита (от 0 до 15): ";
				}
				else {
					cin.ignore(cin.rdbuf()->in_avail());
					return userNumber;
				}
			}
			else {
				if (cin.fail() || userNumber < 0 || userNumber > 63) {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << endl << "Попробуйте ввести корректный номер бита (от 0 до 63): ";
				}
				else {
					cin.ignore(cin.rdbuf()->in_avail());
					return userNumber;
				}
			}
		}
	}
	else {
		for (int i = 1; i < needed + 1; ++i) {
			cout << endl << "Введите номер " << i << " бита: ";
			while (true) {
				short userNumber;
				cin >> userNumber;
				if (type == 'I' || type == 'i' || type == 'U' || type == 'u' || type == 'F' || type == 'f') {
					if (cin.fail() || userNumber < 0 || userNumber > 31) {
						cin.clear();
						cin.ignore(cin.rdbuf()->in_avail());
						cout << endl << "Попробуйте ввести корректный номер бита (от 0 до 31): ";
					}
					else {
						cin.ignore(cin.rdbuf()->in_avail());
						return userNumber;
					}
				}
				else if (type == 'S' || type == 's') {
					if (cin.fail() || userNumber < 0 || userNumber > 15) {
						cin.clear();
						cin.ignore(cin.rdbuf()->in_avail());
						cout << endl << "Попробуйте ввести корректный номер бита (от 0 до 15): ";
					}
					else {
						cin.ignore(cin.rdbuf()->in_avail());
						return userNumber;
					}
				}
				else {
					if (cin.fail() || userNumber < 0 || userNumber > 63) {
						cin.clear();
						cin.ignore(cin.rdbuf()->in_avail());
						cout << endl << "Попробуйте ввести корректный номер бита (от 0 до 63): ";
					}
					else {
						cin.ignore(cin.rdbuf()->in_avail());
						return userNumber;
					}
				}
			}
		}
	}
}

bool getByteValue() {
	cout << endl << "Введите значение бита (либо 0, либо 1): ";
	while (true) {
		bool userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректное значение бита (от 0 до 1): ";
		}
		else if (userNumber == 0 || userNumber == 1) {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}

void change(bool *A, char type, short needed) {
	short position;
	bool value;
	position = getPositionNumber(type, needed);
	value = getByteValue();
	A[position] = value;
}

void swap(bool *A, char type, short needed) {
	short position1, position2;
	while (true) {
		position1 = getPositionNumber(type, needed);
		position2 = getPositionNumber(type, needed);
		if (position1 == position2)
			cout << endl << "Необходимо ввести разные позиции битов." << endl << endl;
		else {
			bool tmp;
			tmp = A[position1];
			A[position1] = A[position2];
			A[position2] = tmp;
			break;
		}
	}

}

void inversion(bool *A, int count) {
	cout << endl << "Инверcия всех битов:" << endl << endl;
	for (int i = count - 1; i >= 0; --i)
		A[i] == 0 ? A[i] = 1 : A[i] = 0;
}

void output(char type, bool *A){
	cout << endl;
	if (type == 'I' || type == 'i' || type == 'U' || type == 'u') {
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
	for (int i = 31; i >= 0; --i)
		digits[i] = number & ((bool)1 << i);
}

void shortArray(short number, bool *digits) {
	for (int i = 15; i >= 0; --i)
		digits[i] = number & ((bool)1 << i);
}

void unsignedArray(unsigned long number, bool *digits) {
	for (int i = 31; i >= 0; --i)
		digits[i] = number & ((bool)1 << i);
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
