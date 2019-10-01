#include "Func.h"

int main() {
	setlocale(0, "");
	int menuOption;
	bool condition = 1;
	char option;
	while (condition) {
		Menu();
		menuOption = getMenuOption();
		switch (menuOption) {
		case 0: {
			cout << "Выберите тип числа, чтобы отобразить его двоичное представление в памяти ЭВМ" << endl;
			cout << "I(i) - int, S(s) - short int, U(u) - unsigned int, F(f) - float, D(d) - double: ";
			option = getOption();
			switch (option) {
			case 'I': case 'i': {
				int number = getInt();
				cout << endl << "Двоичное представление числа " << number << ":" << endl << endl;
				intInterpretation(number);
				break;
			}
			case 'S': case 's': {
				short number = getShort();
				cout << endl << "Двоичное представление числа " << number << ":" << endl << endl;
				shortInterpretation(number);
				break;
			}
			case 'U': case 'u': {
				unsigned long number = getUnsigned();
				cout << endl << "Двоичное представление числа " << number << ":" << endl << endl;
				unsignedInterpretation(number);
				break;
			}
			case 'F': case 'f': {
				float number = getFloat();
				bool digits[32];
				floatInterpretation(number, digits);
				cout << endl << "Двоичное представление числа " << number << ":" << endl << endl;
				floatOutput(digits);
				break;
			}
			case 'D': case 'd': {
				double number = getDouble();
				bool *digits = 0;
				int position = 64;
				digits = new bool[position];
				cout << endl << "Двоичное представление числа " << number << ":" << endl << endl;
				doubleInterpretation(number, digits, position);
				doubleOutput(digits);
				break;
			}
			}
			break;
		}
		case 1: {
			cout << endl << endl << "Выберите тип числа, биты которого нужно инвертировать" << endl;
			cout << "I(i) - int, S(s) - short int, U(u) - unsigned int, F(f) - float, D(d) - double: ";
			option = getOption();
			switch (option) {
			case 'I': case 'i': {
				int number = getInt();
				cout << endl << "Двоичное представление числа " << number << ":" << endl;
				intInterpretation(number);
				cout << endl << "Инверcия всех битов:" << endl << endl;
				intInterpretation(~number);
				break;
			}
			case 'S': case 's': {
				short number = getShort();
				cout << endl << "Двоичное представление числа " << number << ":" << endl;
				shortInterpretation(number);
				cout << endl << "Инверcия всех битов:" << endl << endl;
				shortInterpretation(~number);
				break;
			}
			case 'U': case 'u': {
				unsigned long number = getUnsigned();
				cout << endl << "Двоичное представление числа " << number << ":" << endl;
				unsignedInterpretation(number);
				cout << endl << "Инверcия всех битов:" << endl << endl;
				unsignedInterpretation(~number);
				break;
			}
			case 'F': case 'f': {
				float number = getFloat();
				bool digits[32];
				floatInterpretation(number, digits);
				cout << endl << "Двоичное представление числа " << number << ":" << endl;
				floatOutput(digits);
				for (int i = 0; i < 32; ++i) {
					if (digits[i] == 0)
						digits[i] = 1;
					else
						digits[i] = 0;
				}
				cout << endl << "Инверсия всех битов:" << endl << endl;
				floatOutput(digits);
				break;
			}
			case 'D': case 'd': {
				double number = getDouble();
				bool *digits = 0;
				int position = 64;
				digits = new bool[position];
				doubleInterpretation(number, digits, position);
				cout << endl << "Двоичное представление числа " << number << ":" << endl << endl;
				doubleOutput(digits);
				for (int i = 0; i < 64; ++i) {
					if (digits[i] == 0)
						digits[i] = 1;
					else
						digits[i] = 0;
				}
				cout << endl << "Инверсия всех битов:" << endl << endl;
				doubleOutput(digits);
			}
			}
			break;
		}
		case 2: {
			cout << endl;
			condition = 0;
			break;
		}
		}

	}
	system("pause");
	return 0;
}
/*Problems:
1) if in float/double input, and, of course, UNSIGNED(!!!!!!!)should limit 'em somehow;
2) Should try to make more variants.
*/
