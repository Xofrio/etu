#include "Func.h"

int main() {
	setlocale(0, "");
	srand((unsigned)time(NULL));
	dLL *list = 0;
	long int arraySpeed, listSpeed, addArraySpeed = -1, searchArraySpeed = -1, eraseArraySpeed = -1, addListSpeed = -1, searchListSpeed = -1, eraseListSpeed = -1;
	int *array = 0, amountArray = 0, amountList = 0, startAmountArray, startAmountList;
	short arrayMethod, listMethod;
	bool condition = 1;
	while (condition) {
		short option = menu();
		switch (option) {
		case 0: {
			array = createArray(array, amountArray, arraySpeed, arrayMethod, startAmountArray);
			break;
		}
		case 1: {
			creationSpeed(array, list, startAmountArray, startAmountList, arraySpeed, listSpeed, arrayMethod, listMethod, 0);
			break;
		}
		case 2: {
			array = arrayAddFindErase(array, amountArray, addArraySpeed, searchArraySpeed, eraseArraySpeed);
			break;
		}
		case 3: {
			addFindEraseSpeed(array, list, addArraySpeed, searchArraySpeed, eraseArraySpeed, addListSpeed, searchListSpeed, eraseListSpeed, 0);
			break;
		}
		case 4: {
			createList(list, amountList, listSpeed, listMethod, startAmountList);
			break;
		}
		case 5: {
			creationSpeed(array, list, startAmountArray, startAmountList, arraySpeed, listSpeed, arrayMethod, listMethod, 1);
			break;
		}
		case 6: {
			/*add/search/delete*/
			break;
		}
		case 7: {
			addFindEraseSpeed(array, list, addArraySpeed, searchArraySpeed, eraseArraySpeed, addListSpeed, searchListSpeed, eraseListSpeed, 1);
			break;
		}
		case 8: {
			oddEven(array, list, amountArray, amountList);
			break;
		}
		case 9: {
			condition = 0;
			break;
		}
		}
	}
	delete[] array;
	return 0;
}

/*
6) Создание списка (вручную, с файла)!! (Почему так долго?)
7) Вставка, удаление и получение элемента двусвязного списка. Удаление и получение элемента необходимо реализовать по индексу и по значению.
9) Почему массив быстрее?
*/