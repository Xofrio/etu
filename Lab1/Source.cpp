#include "Func.h"

int main() {
	char option;
	setlocale(0, "");
	cout << "1, 2. Какое число нужно представить в двоичной системе? " << endl << endl;
	cout << "I(i) - int, S(s) - short int, U(u) - unsigned int, F(f) - float, D(d) - double: ";
	option = getOption();
	switch (option) {
	case 'I': case 'i': {
		int number;
		cout << endl << "Введите число от -2147483648 до 2147483647: ";
		number = getInt();
		cout << endl << "Двоичное представление числа " << number << ":" << endl << endl;
		intInterpretation(number);
		break;
	}
	case 'S': case 's': {
		short number;
		cout << endl << "Введите число от -32768 до 32767: ";
		number = getShort();
		cout << endl << "Двоичное представление числа " << number << ":" << endl << endl;
		shortInterpretation(number);
		break;
	}
	case 'U': case 'u': {
		unsigned number;
		cout << endl << "Введите число от 0 до 4294967295: ";
		number = getUnsigned();
		cout << endl << "Двоичное представление числа " << number << ":" << endl << endl;
		unsignedInterpretation(number);
		break;
	}
	case 'F': case 'f': {
		float number;
		cout << endl << "Введите число от 1.175494351e-38 до 3.402823466e+38: ";
		number = getFloat();
		cout << endl << "Двоичное представление числа " << number << ":" << endl << endl;
		break;
	}
	case 'D': case 'd': {
		double number;
		cout << endl << "Введите число от -2.2250738585072014e-308 до 1.7976931348623158e+308: ";
		number = getDouble();
		cout << endl << "Двоичное представление числа " << number << ":" << endl << endl;

		break;
	}
	}
	cout << endl << endl << "3. Какое число нужно представить в двоичной системе и затем инвертировать?" << endl << endl;
	cout << "I(i) - int, S(s) - short int, U(u) - unsigned int, F(f) - float, D(d) - double: ";
	option = getOption();
	switch (option) {
	case 'I': case 'i': {
		int number;
		cout << endl << "Введите число от -2147483648 до 2147483647: ";
		number = getInt();
		cout << endl << "Инвертированное число " << number << ", представленное в двоичной системе (" << ~ number << "):" << endl << endl;
		intInterpretation(~ number);
		break;
	}
	case 'S': case 's': {
		short number;
		cout << endl << "Введите число от -32768 до 32767: ";
		number = getShort();
		cout << endl << "Инвертированное число " << number << ", представленное в двоичной системе (" << ~number << "):" << endl << endl;
		shortInterpretation(~ number);
		break;
	}
	case 'U': case 'u': {
		unsigned number;
		cout << endl << "Введите число от 0 до 4294967295: ";
		number = getUnsigned();
		cout << endl << "Инвертированное число " << number << ", представленное в двоичной системе (" << ~number << "):" << endl << endl;
		unsignedInterpretation(~ number);
		break;
	}
	case 'F': case 'f': {
		float number;
		cout << endl << "Введите число от 1.175494351e-38 до 3.402823466e+38: ";

		break;
	}
	case 'D': case 'd': {
		double number;
		cout << endl << "Введите число от -2.2250738585072014e-308 до 1.7976931348623158e+308: ";

		break;
	}
	}
	cout << endl << endl;
	system("pause");
	return 0;
}
/*float, double. При выводе необходимо визуально обозначить знаковый разряд мантиссы, знаковый разряд порядка (если есть),мантиссу и порядок;
setprecision, чтобы установить сколько знаков вы хотите вывести. */
