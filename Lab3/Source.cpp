#include "Func.h"

int main() {
	setlocale(0, "");
	srand((unsigned)time(NULL));
	int menuOption, rows = 1, columns = 1;
	double **arrayOfNumbers = 0;
	bool condition = 1, created = 0, square = 0, manual;
	generateArray(arrayOfNumbers, rows, columns);
	while (condition) {
		Menu();
		menuOption = getMenuOption();
		switch (menuOption) {
		case 0: {
			deleteArray(arrayOfNumbers, rows, columns);
			system("cls");
			cout << "Выберите опцию . . ." << endl;
			cout << "0. Заполнить матрицу вручную" << endl;
			cout << "1. Заполнить матрицу автоматически" << endl;
			cout << "Опция: ";
			manual = getSubMenuOption();
			cout << "Введите количество строк: ";
			rows = getRowsOrColumns();
			cout << "Введите количество столбцов: ";
			columns = getRowsOrColumns();
			if (rows == columns)
				square = 1;
			created = 1;
			cout << endl;
			switch (manual) {
			case 0: {
				inputArray(arrayOfNumbers, rows, columns);
				showArray(arrayOfNumbers, rows, columns);
				cout << endl;
				break;
			}
			case 1: {
				generateArray(arrayOfNumbers, rows, columns);
				showArray(arrayOfNumbers, rows, columns);
				cout << endl;
				break;
			}
			}
			break;
		}
		case 1: {
			if (created == 0)
				cout << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << "Необходимо создать квадратную матрицу порядка N, где N>=2" << endl << endl;
			else {
				orthogonal(arrayOfNumbers, rows);
				cout << endl;
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
	deleteArray(arrayOfNumbers, rows, columns);
	system("pause");
	return 0;
}
/* 1. Input from file
   2. More variants
*/
