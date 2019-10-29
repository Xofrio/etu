#include "Func.h"

int main() {
	setlocale(LC_ALL, "");
	int menuOption, length = 0;
	string userInput;
	bool condition = 1, created = 0;
	while (condition) {
		cout << "Выберите опцию . . ." << endl;
		cout << "0. Ввести последовательность символов" << endl;
		cout << "1. Вывести слова последовательности, не содержащие цифр" << endl;
		cout << "2. Выйти" << endl;
		cout << "Опция: ";
		menuOption = getMenuOption();
		switch (menuOption) {
		case 0: {
			userInput = getSequence(length);
			userInput = correction(userInput, length);
			cout << "Исправленная последовательность (удалены лишние пробелы, знаки препинания, изменён регистр):" << endl << endl << userInput << endl << endl;
			created = 1;
			break;
		}
		case 1: {
			if (created == 0)
				cout << endl << "Не введена последовательность символов." << endl << endl;
			else
				wordsWithoutNumbers(userInput, length);
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
