#include "Func.h"

int main() {
	setlocale(0, "");
	int menuOption, numberI;
	short numberS;
	unsigned long numberU;
	float numberF;
	double numberD;
	bool condition = 1, *digits = 0, created = 0;
	char option;
	while (condition) {
		cout << "Выберите опцию . . ." << endl;
		cout << "0. Отобразить двоичное представление числа в памяти ЭВМ" << endl;
		cout << "1. Инвертировать все биты числа" << endl;
		cout << "2. Выйти" << endl;
		cout << "Опция: ";
		menuOption = getMenuOption();
		switch (menuOption) {
		case 0: {
			system("cls");
			created = 1;
			cout << "Выберите тип числа, чтобы отобразить его двоичное представление в памяти ЭВМ" << endl;
			cout << "I(i) - int, S(s) - short, U(u) - unsigned, F(f) - float, D(d) - double: ";
			option = getOption();
			switch (option) {
			case 'I': case 'i': {
				numberI = getInt();
				digits = new bool[32];
				cout << endl << "Двоичное представление числа " << numberI << ":" << endl << endl;
				intArray(numberI, digits);
				Output(option, digits);
				break;
			}
			case 'S': case 's': {
				numberS = getShort();
				digits = new bool[16];
				cout << endl << "Двоичное представление числа " << numberS << ":" << endl << endl;
				shortArray(numberS, digits);
				Output(option, digits);
				break;
			}
			case 'U': case 'u': {
				numberU = getUnsigned();
				digits = new bool[32];
				cout << endl << "Двоичное представление числа " << numberU << ":" << endl << endl;
				unsignedArray(numberU, digits);
				Output(option, digits);
				break;
			}
			case 'F': case 'f': {
				numberF = getFloat();
				digits = new bool[32];
				floatArray(numberF, digits);
				cout << endl << "Двоичное представление числа " << numberF << ":" << endl << endl;
				Output(option, digits);
				break;
			}
			case 'D': case 'd': {
				numberD = getDouble();
				digits = new bool[64];
				cout << endl << "Двоичное представление числа " << numberD << ":" << endl << endl;
				doubleArray(numberD, digits, 64);
				Output(option, digits);
				break;
			}
			}
			break;
		}
		case 1: {
			if (created == 0) {
				cout << endl << "Сначала необходимо ввести число." << endl << endl;
				break;
			}
			else {
				switch (option) {
				cout << endl << "Инверcия всех битов:" << endl << endl;
				case 'I': case 'i': {
					inversion(digits, 31);
					cout << endl;
					Output(option, digits);
					break;
				}
				case 'S': case 's': {
					inversion(digits, 15);
					cout << endl;
					Output(option, digits);
					break;
				}
				case 'U': case 'u': {
					inversion(digits, 31);
					cout << endl;
					Output(option, digits);
					break;
				}
				case 'F': case 'f': {
					inversion(digits, 31);
					cout << endl;
					Output(option, digits);
					break;
				}
				case 'D': case 'd': {
					inversion(digits, 63);
					cout << endl;
					Output(option, digits);
					break;
				}
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
	delete[] digits;
	system("pause");
	return 0;
}
/*Problems:
1) if in float/double input, and, of course, UNSIGNED(!!!!!!!)should limit 'em somehow;
2) Should try to make more variants.
*/
