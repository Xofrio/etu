#include "Func.h"

int main() {
	setlocale(0, "");
	srand((unsigned)time(NULL));
	int **arrayOfNumbers = 0, menuOption, rows = 1, columns = 1;
	bool condition = 1, created = 0, square, manual, prerecordedA = 0, prerecordedB = 0; //prerecorded is located here for secondaryDiagonal search if v.no.5 is executed, so v.no.6 is not full, till v.no.5 is done
	generateArray(arrayOfNumbers, rows, columns);
	while (condition) {
		Menu();
		menuOption = getMenuOption();
		switch (menuOption) {
		case 0: {
			deleteArray(arrayOfNumbers, rows, columns);
			system("cls");
			arrayMenu();
			manual = getArrayMenuOption();
			cout << endl << "Введите количество строк: ";
			rows = getRowsOrColumns();
			cout << "Введите количество столбцов: ";
			columns = getRowsOrColumns();
			if (rows == columns)
				square = 1;
			else
				square = 0;
			created = 1;
			cout << endl;
			switch (manual) {
			case 0: {
				inputArray(arrayOfNumbers, rows, columns);
				showArray(arrayOfNumbers, rows, columns);
				break;
			}
			case 1: {
				generateArray(arrayOfNumbers, rows, columns);
				showArray(arrayOfNumbers, rows, columns);
				break;
			}
			}
			break;
		}
		case 1: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка N, где N>=2" << endl << endl;
			else {
				orthogonal(arrayOfNumbers, rows);
				cout << endl;
			}
			break;
		}
		case 2: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка N, где N>=2" << endl << endl;
			else {
				diagonalComposition(arrayOfNumbers, rows);
				cout << endl;
			}
			break;
		}
		case 3: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка N, где N>=2" << endl << endl;
			else {
				minimalElement(arrayOfNumbers, rows);
				cout << endl;
			}
			break;
		}
		case 4: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка N, где N>=2" << endl << endl;
			else {
				magicSquare(arrayOfNumbers, rows);
				cout << endl;
			}
			break;
		}
		case 5: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка N, где N>=2" << endl << endl;
			else {
				mainDiagonalSymmetry(arrayOfNumbers, rows);
				cout << endl;
			}
			break;
		}
		case 6: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка N, где N>=2" << endl << endl;
			else {
				secondaryDiagonalSymmetry(arrayOfNumbers, rows);
				cout << endl;
			}
			break;
		}
		case 7: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (rows == 1 && columns == 1 || rows == 1)
				cout << endl << "Матрица уже отсортирована по убыванию элементов первого столбца, т.к. он 1 в этой матрице." << endl << endl;
			else {
				sortArray(arrayOfNumbers, columns, 0, rows - 1);
				cout << endl << "Матрица, отсортированная по убыванию элементов первого столбца:" << endl << endl;
				showArray(arrayOfNumbers, rows, columns);
			}
			break;
		}
		case 8: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка N, где N>=2" << endl << endl;
			else {
				rowsSwap(arrayOfNumbers, rows);
				cout << endl << "Матрица, в которой строки переставлены следующим образом: первая с последней, вторая с предпоследней и т.д." << endl << endl;
				showArray(arrayOfNumbers, rows, columns);
			}
			break;
		}
		case 9: {
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
