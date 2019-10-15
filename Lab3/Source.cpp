#include "Func.h"

int main() {
	setlocale(0, "");
	srand((unsigned)time(NULL));
	int menuOption, subMenuOption, arrayOption, rows = 1, columns = 1, rows1 = -1, columns1, miniMenuOption;
	long double **arrayOfNumbers = 0, determinant;
	bool condition = 1, created = 0, square, prerecordedA = 0, prerecordedB = 0;
	generateArray(arrayOfNumbers, rows, columns);
	while (condition) {
		cout << "Выберите опцию . . ." << endl;
		cout << "0. Создать матрицу" << endl;
		cout << "1. Упорядочить матрицу по убыванию элементов первого столбца" << endl;
		cout << "2. Определить, является ли матрица магическим квадратом" << endl;
		cout << "3. Определить, является ли матрица ортонормированной" << endl;
		cout << "4. Поменять местами квадранты" << endl;
		cout << "5. Создать матрицу, заполнив её 'змейкой'" << endl;
		cout << "6. Найти минимальный элемент под побочной диагональю" << endl;
		cout << "7. Найти седловые точки" << endl;
		cout << "8. Поменять строки по принципу: первая с последней, вторая с предпоследней и т.д." << endl;
		cout << "9. Получить новую матрицу прибавлением к элементам каждого столбца первой матрицы произведения элементов соответствующих строк второй матрицы" << endl;
		cout << "10. Переместить максимальный элемент (один из) в верхний левый угол" << endl;
		cout << "11. Определить, является ли матрица симметричной относительно главной диагонали" << endl;
		cout << "12. Определить, является ли матрица симметричной относительно побочной диагонали" << endl;
		cout << "13. Найти произведение ненулевых диагональных элементов" << endl;
		cout << "14. Найти определитель и ранг матрицы" << endl;
		cout << "15. Выйти" << endl;
		cout << "Опция: ";
		menuOption = getMenuOption();
		switch (menuOption) {
		case 0: {
			deleteArray(arrayOfNumbers, rows, columns);
			system("cls");
			arrayMenu();
			arrayOption = getArrayMenuOption();
			switch (arrayOption) {
			case 0: {
				rowsColumnsMenu(rows, columns, square);
				inputArray(arrayOfNumbers, rows, columns);
				showArray(arrayOfNumbers, rows, columns);
				created = 1;
				break;
			}
			case 1: {
				rowsColumnsMenu(rows, columns, square);
				generateArray(arrayOfNumbers, rows, columns);
				showArray(arrayOfNumbers, rows, columns);
				created = 1;
				break;
			}
			case 2: {
				inputArrayFromFile(arrayOfNumbers, rows, columns, square, created);
				if (created == 0) {
					rows = columns = 1;
					generateArray(arrayOfNumbers, rows, columns);
				}
				else {
					cout << endl;
					showArray(arrayOfNumbers, rows, columns);
				}
				break;
			}
			}
			break;
		}
		case 1: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (rows == 1 && columns == 1 || rows == 1)
				cout << endl << "Матрица уже упорядочена по убыванию элементов первого столбца, т.к. он 1 в этой матрице." << endl << endl;
			else {
				sortArray(arrayOfNumbers, columns, 0, rows - 1);
				cout << endl << "Матрица, упорядоченная по убыванию элементов первого столбца:" << endl << endl;
				showArray(arrayOfNumbers, rows, columns);
				prerecordedA = prerecordedB = 0;
			}
			break;
		}
		case 2: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка большего, либо равного 2" << endl << endl;
			else {
				magicSquare(arrayOfNumbers, rows);
				cout << endl;
			}
			break;
		}
		case 3: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка большего, либо равного 2" << endl << endl;
			else {
				orthogonal(arrayOfNumbers, rows);
				cout << endl;
			}
			break;
		}
		case 4: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1 || rows % 2 == 1)
				cout << endl << "Необходимо создать квадратную матрицу чётного порядка большего, либо равного 2" << endl << endl;
			else {
				cout << endl << "Выберите опцию . . ." << endl;
				cout << "0. Поменять квадранты местами по часовой стрелке" << endl;
				cout << "1. Поменять квадранты местами крест-накрест" << endl;
				cout << "2. Поменять квадранты местами вверх дном" << endl;
				cout << "3. Поменять квадранты местами левой и правой стороной" << endl;
				cout << "Опция: ";
				subMenuOption = getSubMenuOption();
				system("cls");
				switch (subMenuOption) {
				case 0: {
					cout << "Изначальная матрица:" << endl << endl;
					showFancyArray(arrayOfNumbers, rows, 0, 0);
					swapClockwise(arrayOfNumbers, rows);
					cout << "Матрица, квадранты которой поменялись местами по часовой стрелке:" << endl << endl;
					showFancyArray(arrayOfNumbers, rows, 1, 0);
					break;
				}
				case 1: {
					cout << "Изначальная матрица:" << endl << endl;
					showFancyArray(arrayOfNumbers, rows, 0, 1);
					swapCross(arrayOfNumbers, rows);
					cout << "Матрица, квадранты которой поменялись местами крест-накрест:" << endl << endl;
					showFancyArray(arrayOfNumbers, rows, 1, 1);
					break;
				}
				case 2: {
					cout << "Изначальная матрица:" << endl << endl;
					showFancyArray(arrayOfNumbers, rows, 0, 2);
					swapUpsideDown(arrayOfNumbers, rows);
					cout << "Матрица, квадранты которой поменялись местами кверху дном:" << endl << endl;
					showFancyArray(arrayOfNumbers, rows, 1, 2);
					break;
				}
				case 3: {
					cout << "Изначальная матрица:" << endl << endl;
					showFancyArray(arrayOfNumbers, rows, 0, 3);
					swapFromSideToSide(arrayOfNumbers, rows);
					cout << "Матрица, квадранты которой поменялись местами левой и правой стороной:" << endl << endl;
					showFancyArray(arrayOfNumbers, rows, 1, 3);
					break;
				}
				}
				prerecordedA = prerecordedB = 0;
			}
			break;
		}
		case 5: {
			deleteArray(arrayOfNumbers, rows, columns);
			rows = columns = -1;
			cout << endl << "Выберите опцию . . ." << endl;
			cout << "0. Змейка двигается по спирали по часовой стрелке" << endl;
			cout << "1. Змейка двигается сверху вниз, затем снизу вверх и т.д." << endl;
			cout << "Опция: ";
			miniMenuOption = -1;
			miniMenuOption = getMiniMenuOption();
			switch (miniMenuOption) {
			case 0: {
				system("cls");
				while (rows <= 1 || columns <= 1) {
					cout << "Введите количество строк: ";
					rows = getRowsOrColumns();
					cout << "Введите количество столбцов: ";
					columns = getRowsOrColumns();
					if (rows <= 1 || columns <= 1)
						cout << endl << "Необходимо, чтобы количество строк и столбцов было больше 1. Попробуйте ещё раз." << endl << endl;
				}
				memoryForArray(arrayOfNumbers, rows, columns);
				serpentSpiral(arrayOfNumbers, rows, columns);
				cout << endl << "Матрица, заполненная 'змейкой', двигающейся по спирали по часовой стрелке:" << endl << endl;
				showArray(arrayOfNumbers, rows, columns);
				prerecordedA = 1;
				created = 1;
				if (rows == columns)
					square = 1;
				else
					square = 0;
				break;
			}
			case 1: {
				system("cls");
				while (rows <= 1 || columns <= 1) {
					cout << "Введите количество строк: ";
					rows = getRowsOrColumns();
					cout << "Введите количество столбцов: ";
					columns = getRowsOrColumns();
					if (rows <= 1 || columns <= 1)
						cout << endl << "Необходимо, чтобы количество строк и столбцов было больше 1. Попробуйте ещё раз." << endl << endl;
				}
				memoryForArray(arrayOfNumbers, rows, columns);
				serpentDownUp(arrayOfNumbers, rows, columns);
				cout << endl << "Матрица, заполненная 'змейкой', двигающейся сверху вниз, снизу вверх и т.д.:" << endl << endl;
				showArray(arrayOfNumbers, rows, columns);
				prerecordedB = 1;
				created = 1;
				if (rows == columns)
					square = 1;
				else
					square = 0;
				break;
			}
			}
			break;
		}
		case 6: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка большего, либо равного 2" << endl << endl;
			else {
				if (prerecordedA == 1)
					cout << endl << "Минимальный элемент под побочной диагональю имеет значение " << arrayOfNumbers[1][columns - 1] << ", находится под индексами [" << 2 << "][" << columns << "]" << endl << endl;
				else if (prerecordedB == 1)
					cout << endl << "Минимальный элемент под побочной диагональю имеет значение " << arrayOfNumbers[rows - 1][1] << ", находится под индексами [" << rows << "][" << 2 << "]" << endl << endl;
				else {
					minimalElement(arrayOfNumbers, rows);
					cout << endl;
				}
			}
			break;
		}
		case 7: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (rows == 1 && columns == 1)
				cout << endl << "Необходимо создать матрицу больше, чем 1x1" << endl << endl;
			else
				saddlePoint(arrayOfNumbers, rows, columns);
			break;
		}
		case 8: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка большего, либо равного 2" << endl << endl;
			else {
				rowsSwap(arrayOfNumbers, rows);
				cout << endl << "Матрица, в которой строки переставлены следующим образом: первая с последней, вторая с предпоследней и т.д." << endl << endl;
				showArray(arrayOfNumbers, rows, columns);
				prerecordedA = prerecordedB = 0;
			}
			break;
		}
		case 9: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка большего, либо равного 2" << endl << endl;
			else {
				cout << endl << "Необходимо создать вторую матрицу того же порядка, что и существующая (" << rows << ")." << endl << endl;
				long double **arrayOfNumbers2 = 0;
				arrayMenu();
				arrayOption = -1;
				arrayOption = getArrayMenuOption();
				switch (arrayOption) {
				case 0: {
					inputArray(arrayOfNumbers2, rows, columns);
					break;
				}
				case 1: {
					generateArray(arrayOfNumbers2, rows, columns);
					break;
				}
				case 2: {
					inputArrayFromFile(arrayOfNumbers2, rows1, columns1, square, created);
					break;
				}
				}
				if (rows1 != rows && arrayOption == 2) {
					cout << endl << "В файле найдена неподходящая матрица." << endl << endl;
					created = 1;
					square = 1;
					break;
				}
				cout << endl << "Первая матрица:" << endl << endl;
				showArray(arrayOfNumbers, rows, columns);
				cout << "Вторая матрица:" << endl << endl;
				showArray(arrayOfNumbers2, rows, columns);
				newArray(arrayOfNumbers, arrayOfNumbers2, rows);
				cout << "Матрица, полученная путём прибавления к элементам каждого столбца первой матрицы произведения элементов соответствующих строк второй матрицы:" << endl << endl;
				showArray(arrayOfNumbers, rows, columns);
				prerecordedA = prerecordedB = 0;
				deleteArray(arrayOfNumbers2, rows, columns);
			}
			break;
		}
		case 10: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка большего, либо равного 2" << endl << endl;
			else {
				maxAtTheTop(arrayOfNumbers, rows);
				cout << endl << "Матрица, в которой максимальный элемент (один из) помещён в левый верхний угол путём переставления столбцов и строк:" << endl << endl;
				showArray(arrayOfNumbers, rows, columns);
				prerecordedA = prerecordedB = 0;
			}
			break;
		}
		case 11: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка большего, либо равного 2" << endl << endl;
			else {
				mainDiagonalSymmetry(arrayOfNumbers, rows);
				cout << endl;
			}
			break;
		}
		case 12: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка большего, либо равного 2" << endl << endl;
			else {
				secondaryDiagonalSymmetry(arrayOfNumbers, rows);
				cout << endl;
			}
			break;
		}
		case 13: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0 || rows == 1)
				cout << endl << "Необходимо создать квадратную матрицу порядка большего, либо равного 2" << endl << endl;
			else {
				diagonalComposition(arrayOfNumbers, rows);
				cout << endl;
			}
			break;
		}
		case 14: {
			if (created == 0)
				cout << endl << "Нет матрицы." << endl << endl;
			else if (square == 0) {
				cout << endl << "Определитель матрицы не может быть найден, поскольку матрица не квадратная." << endl;
				rankOfMatrix(arrayOfNumbers, rows, columns);
			}
			else if (rows == 1){
				cout << endl << "Определитель матрицы: " << arrayOfNumbers[0][0] << endl;
				rankOfMatrix(arrayOfNumbers, rows, columns);
			}
			else {
				determinant = determineTheDeterminant(arrayOfNumbers, rows);
				cout << endl << "Определитель матрицы: " << determinant << endl;
				rankOfMatrix(arrayOfNumbers, rows, columns);
			}
			break;
		}
		case 15: {
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
