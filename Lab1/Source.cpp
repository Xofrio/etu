#include "Func.h"

int main() {
	setlocale(0, "");
	int menuOption, numberI, count;
	short numberS;
	unsigned numberU;
	float numberF;
	double numberD;
	bool condition = 1, *digits = 0, created = 0;
	char option;
	while (condition) {
		cout << "Выберите опцию . . ." << endl;
		cout << "0. Отобразить двоичное представление числа в памяти ЭВМ" << endl;
		cout << "1. Инвертировать все биты числа" << endl;
		cout << "2. Поменять значение произвольного бита" << endl;
		cout << "3. Поменять местами значения двух битов" << endl;
		cout << "4. Выйти" << endl;
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
				count = 32;
				digits = new bool[count];
				cout << endl << "Двоичное представление числа " << numberI << ":" << endl;
				intArray(numberI, digits);
				output(option, digits);
				break;
			}
			case 'S': case 's': {
				numberS = getShort();
				count = 16;
				digits = new bool[count];
				cout << endl << "Двоичное представление числа " << numberS << ":" << endl;
				shortArray(numberS, digits);
				output(option, digits);
				break;
			}
			case 'U': case 'u': {
				numberU = getUnsigned();
				digits = new bool[32];
				cout << endl << "Двоичное представление числа " << numberU << ":" << endl;
				unsignedArray(numberU, digits);
				output(option, digits);
				break;
			}
			case 'F': case 'f': {
				numberF = getFloat();
				count = 32;
				digits = new bool[count];
				floatArray(numberF, digits);
				cout << endl << "Двоичное представление числа " << numberF << ":" << endl;
				output(option, digits);
				break;
			}
			case 'D': case 'd': {
				numberD = getDouble();
				count = 64;
				digits = new bool[count];
				cout << endl << "Двоичное представление числа " << numberD << ":" << endl;
				doubleArray(numberD, digits, 64);
				output(option, digits);
				break;
			}
			}
			break;
		}
		case 1: {
			if (created == 0)
				cout << endl << "Сначала необходимо ввести число." << endl << endl;
			else {
				inversion(digits, count);
				output(option, digits);
			}
			break;
		}
		case 2: {
			if (created == 0)
				cout << endl << "Сначала необходимо ввести число." << endl << endl;
			else {
				change(digits, option, 1);
				output(option, digits);
			}
			break;
		}
		case 3: {
			if (created == 0)
				cout << endl << "Сначала необходимо ввести число." << endl << endl;
			else {
				swap(digits, option, 2);
				output(option, digits);
			}
			break;
		}
		case 4: {
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
1) if in float/double input.
2) Should try to make more variants.
*/
