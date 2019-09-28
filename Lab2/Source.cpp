#include "Func.h"

int main() {
	setlocale(0, "");
	srand((unsigned)time(NULL));
	int *arrayOfNumbers = 0, elementsCount, menuOption, desiredIndex, comparison, userNumber, userNumber2, cnt2, cnt3, cnt4, cnt5, cnt6, cnt7, cnt8, cnt9;
	char method;
	bool condition = 1, sorted = 0, created = 0;
	cnt2 = cnt3 = cnt4 = cnt5 = cnt6 = cnt7 = cnt8 = cnt9 = comparison = 0;
	while (condition) {
		Menu();
		menuOption = getMenuOption();
		switch (menuOption) {
		case 0: {
			delete[] arrayOfNumbers;
			system("cls");
			cout << "Введите размерность массива: ";
			elementsCount = getValue();
			created = 1;
			cout << endl;
			arrayOfNumbers = new int[elementsCount];
			generateArray(arrayOfNumbers, elementsCount);
			showArray(arrayOfNumbers, elementsCount);
			for (int i = 0; i < elementsCount - 1; ++i) {
				if (arrayOfNumbers[i] <= arrayOfNumbers[i + 1])
					++comparison;
			}
			if (comparison == elementsCount - 1)
					sorted = 1;
			comparison = 0;
			break;
			}
		case 1: {
			if (created == 0 || elementsCount == 0) {
				cout << "Нет массива." << endl << endl;
			}
			else {
				cout << endl << "2. Укажите, каким методом сортировать." << endl << endl << "B(b) - Bubble, S(s) - Shaker; C(c) - Comb; I(i) - Insert; Q(q) - Quick: ";
				method = getMethod();
				switch (method) {
				case 'B': case 'b': bubbleSorting(arrayOfNumbers, elementsCount);
					cout << endl << "Отсортированный массив (метод сортировки - Bubble):" << endl << endl;
					break;
				case 'S': case 's': cocktailSorting(arrayOfNumbers, elementsCount);
					cout << endl << "Отсортированный массив (метод сортировки - Shaker):" << endl << endl;
					break;
				case 'C': case 'c': combSorting(arrayOfNumbers, elementsCount);
					cout << endl << "Отсортированный массив (метод сортировки - Comb):" << endl << endl;
					break;
				case 'I': case 'i': insertionSorting(arrayOfNumbers, elementsCount);
					cout << endl << "Отсортированный массив (метод сортировки - Insert):" << endl << endl;
					break;
				case 'Q': case 'q': quickSorting(arrayOfNumbers, 0, elementsCount - 1);
					cout << endl << "Отсортированный массив (метод сортировки - Quick):" << endl << endl;
					break;
				}
				showArray(arrayOfNumbers, elementsCount);
				sorted = 1;
			}
			break;
		}
		case 2: {
			if (created == 0 || elementsCount == 0) {
				cout << "Нет массива." << endl << endl;
			}
			else if (sorted == 0) {
				int min = 2147483647, max = ~min;
				searchMinMax(arrayOfNumbers, elementsCount, min, max);
				cout << endl <<"Минимальный элемент: " << min << " Максимальный элемент: " << max << endl << endl;
			}
			else {
				cout << endl << "Минимальный элемент: " << arrayOfNumbers[0] << " Максимальный элемент: " << arrayOfNumbers[elementsCount - 1] << endl << endl;
			}
			break;
		}
		case 3: {
			if (created == 0 || elementsCount == 0) {
				cout << "Нет массива." << endl << endl;
			}
			else if (sorted == 0) {
				int min = 2147483647, max = ~min, count = 0;
				searchMinMax(arrayOfNumbers, elementsCount, min, max);
				for (int i = 0; i < elementsCount; ++i) {
					if (arrayOfNumbers[i] == (max + min) / 2)
						++count;
				}
				if (count == 0)
					cout << endl << "Нет элементов, равных среднему минимального и максимального (" << (max + min) / 2 << ")" << endl << endl;
				else
					cout << endl << "Количество элементов в массиве, равных среднему минимального и максимального (" << (max + min) / 2 << "): " << count << endl << endl;
			}
			else {
				desiredIndex = search(arrayOfNumbers, 0, elementsCount - 1, (arrayOfNumbers[0] + arrayOfNumbers[elementsCount - 1]) / 2);
				if (desiredIndex == -1)
					cout << endl << "Нет элементов, равных среднему минимального и максимального (" << (arrayOfNumbers[0] + arrayOfNumbers[elementsCount - 1]) / 2 << ")" << endl << endl;
				else if (desiredIndex != -1) {
					int count = 0;
					if (arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex + 1] && arrayOfNumbers[desiredIndex] != arrayOfNumbers[desiredIndex - 1]) {
						count = forth(arrayOfNumbers, desiredIndex, count);
						++count;
					}
					else if (arrayOfNumbers[desiredIndex] != arrayOfNumbers[desiredIndex + 1] && arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex - 1]) {
						count = back(arrayOfNumbers, desiredIndex, count);
						++count;
					}
					else if (arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex + 1] && arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex - 1]) {
						int desiredIndex2 = desiredIndex;
						count = back(arrayOfNumbers, desiredIndex2, count) + forth(arrayOfNumbers, desiredIndex, count);
						++count;
					}
					else
						++count;
					cout << endl << "Количество элементов, равных среднему минимального и максимального(" << (arrayOfNumbers[0] + arrayOfNumbers[elementsCount - 1]) / 2 << "): " << count << endl << endl;
				}
			}
			break;
		}
		case 4: {
			if (created == 0 || elementsCount == 0) {
				cout << "Нет массива." << endl << endl;
			}
			else {
				cout << endl << "Введите число, чтобы показать количество элементов, больших, чем это число: ";
				userNumber = getValue();
				if (sorted == 0) {
					int count = 0;
					for (int i = 0; i < elementsCount; ++i) {
						if (arrayOfNumbers[i] > userNumber)
							++count;
					}
					if (count == 0)
						cout << endl << "Нет элементов, больших, чем " << userNumber << endl << endl;
					else
						cout << endl << "Количество элементов, больших, чем " << userNumber << ": " << count << endl << endl;
				}
				else {
					desiredIndex = search(arrayOfNumbers, 0, elementsCount - 1, userNumber);
					userNumber2 = userNumber;
					while (desiredIndex == -1 && userNumber < 99) {
						++userNumber;
						desiredIndex = search(arrayOfNumbers, 0, elementsCount - 1, userNumber);
					}
					if (desiredIndex >= 0 && userNumber != userNumber2) {
						while (arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex - 1])
							--desiredIndex;
						cout << endl << "Количество элементов, больших, чем " << userNumber2 << ": " << elementsCount - desiredIndex << endl;
					}
					else if (desiredIndex >= 0 && userNumber == userNumber2) {
						while (arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex + 1])
							++desiredIndex;
						if (desiredIndex == elementsCount - 1)
							cout << endl << "Нет таких элементов." << endl << endl;
						else
							cout << endl << "Количество элементов, больших, чем " << userNumber2 << ": " << elementsCount - 1 - desiredIndex << endl << endl;
					}
					else
						cout << endl << "Нет таких элементов." << endl << endl;
				}
			}
			break;
		}
		case 5: {
			if (created == 0 || elementsCount == 0) {
				cout << "Нет массива." << endl << endl;
			}
			else {
				cout << endl << "Введите число, чтобы показать количество элементов, меньших, чем это число: ";
				userNumber = getValue();
				if (sorted == 0) {
					int count = 0;
					for (int i = 0; i < elementsCount; ++i) {
						if (arrayOfNumbers[i] < userNumber)
							++count;
					}
					if (count == 0)
						cout << endl << "Нет элементов, меньших, чем " << userNumber << endl << endl;
					else
						cout << endl << "Количество элементов, больших, чем " << userNumber << ": " << count << endl << endl;

				}
				else {
					desiredIndex = search(arrayOfNumbers, 0, elementsCount - 1, userNumber);
					userNumber2 = userNumber;
					while (desiredIndex == -1 && userNumber > 0) {
						--userNumber;
						desiredIndex = search(arrayOfNumbers, 0, elementsCount - 1, userNumber);
					}
					if (desiredIndex >= 0 && userNumber != userNumber2) {
						while (arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex + 1])
							++desiredIndex;
						cout << endl << "Количество элементов, меньших, чем " << userNumber2 << ": " << desiredIndex + 1 << endl << endl;
					}
					else if (desiredIndex >= 0 && userNumber == userNumber2) {
						while (arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex - 1])
							--desiredIndex;
						if (desiredIndex == 0)
							cout << endl << "Нет таких элементов." << endl << endl;
						else
							cout << endl << "Количество элементов, меньших, чем " << userNumber2 << ": " << desiredIndex << endl << endl;
					}
					else
						cout << endl << "Нет таких элементов." << endl << endl;
				}
			}
			break;
		}
		case 6: {
			if (created == 0 || elementsCount == 0) {
				cout << "Нет массива." << endl << endl;
			}
			else {
				cout << endl << "Удалить элемент, вставить элемент или найти значение?" << endl << endl << "D(d) - удалить, I(i) - вставить, F(f) - поиск значения: ";
				method = getOption();
				switch (method) {
				case 'D': case 'd': {
						cout << endl << "Введите номер элемента, который требуется удалить: ";
						userNumber = getIndex(elementsCount);
						int *arrayOfNumbers3 = new int[elementsCount - 1];
						auto begin = chrono::steady_clock::now();
						for (int i = 0; i < userNumber; ++i)
							arrayOfNumbers3[i] = arrayOfNumbers[i];
						for (int i = userNumber; i < elementsCount - 1; ++i)
							arrayOfNumbers3[i] = arrayOfNumbers[i + 1];
						auto end = chrono::steady_clock::now();
						--elementsCount;
						for (int i = 0; i < elementsCount; ++i)
							arrayOfNumbers[i] = arrayOfNumbers3[i];
						cout << endl << "Изменённый массив:" << endl << endl;
						showArray(arrayOfNumbers, elementsCount);
						cout << endl << "Время, затраченное на удаление: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl << endl;
						delete[] arrayOfNumbers3;
						break;
				}
				case 'I': case 'i': {
					cout << endl << "Введите номер элемента, на место которого нужно вставить новый элемент: ";
					userNumber = getIndex(elementsCount);
					cout << endl << "Введите значение нового элемента: ";
					userNumber2 = getValue();
					int *arrayOfNumbers3 = new int[elementsCount + 1];
					auto begin = chrono::steady_clock::now();
					arrayOfNumbers3[userNumber] = userNumber2;
					for (int i = userNumber + 1; i < elementsCount + 1; ++i)
						arrayOfNumbers3[i] = arrayOfNumbers[i - 1];
					for (int i = userNumber - 1; i >= 0; i--)
						arrayOfNumbers3[i] = arrayOfNumbers[i];
					auto end = chrono::steady_clock::now();
					++elementsCount;
					for (int i = 0; i < elementsCount; ++i)
						arrayOfNumbers[i] = arrayOfNumbers3[i];
					cout << endl << "Изменённый массив:" << endl << endl;
					showArray(arrayOfNumbers, elementsCount);
					cout << endl << "Время, затраченное на вставку: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl << endl;
					if (sorted = 1 && ((userNumber2 >= arrayOfNumbers[userNumber - 1] && userNumber2 <= arrayOfNumbers[userNumber + 1]) || (userNumber == 0 && userNumber2 <= arrayOfNumbers[userNumber + 1])))
						sorted = 1;
					else
						sorted = 0;
					delete[] arrayOfNumbers3;
					break;
				}
				case 'F': case 'f': {
						int *arrayOfNumbers2 = new int[elementsCount];
						for (int i = 0; i < elementsCount; ++i)
							arrayOfNumbers2[i] = 0;
						cout << endl << "Введите искомое число: ";
						userNumber = getValue();
						if (sorted == 0) {
							int count = 0, index2 = 0;
							auto begin = chrono::steady_clock::now();
							for (int i = 0; i < elementsCount; ++i) {
								if (arrayOfNumbers[i] == userNumber) {
									++count;
									arrayOfNumbers2[index2] = i;
									++index2;
								}
							}
							auto end = chrono::steady_clock::now();
							if (count == 0)
								cout << endl << "Нет таких элементов." << endl << endl;
							else if (count == 1)
								cout << endl << "Искомое число находится под индексом: " << arrayOfNumbers2[0] << endl << endl;
							else {
								cout << endl << "В массиве несколько элементов со значением " << userNumber << ", их количество равно: " << count << endl;
								cout << endl << "Они находятся под индексами: " << endl;
								showArray(arrayOfNumbers2, count);
								delete[] arrayOfNumbers2;
								cout << endl;
							}
							cout << endl << "Время, затраченное на поиск: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl;
						}
						else {
							auto begin = chrono::steady_clock::now();
							desiredIndex = search(arrayOfNumbers, 0, elementsCount - 1, userNumber);
							auto end = chrono::steady_clock::now();
							if (desiredIndex >= 0 && arrayOfNumbers[desiredIndex] != arrayOfNumbers[desiredIndex + 1] && arrayOfNumbers[desiredIndex] != arrayOfNumbers[desiredIndex - 1]) {
								cout << endl << "Искомое число находится под индексом: " << desiredIndex << endl << endl;
							}
							else if (desiredIndex >= 0 && arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex + 1] && arrayOfNumbers[desiredIndex] != arrayOfNumbers[desiredIndex - 1]) {
								int count = 0, index = 0;
								count = forthIndex(arrayOfNumbers, arrayOfNumbers2, desiredIndex, count, index);
								++count;
								int *arrayOfNumbers3 = new int[count];
								for (int i = 0; i < count; ++i)
									arrayOfNumbers3[i] = arrayOfNumbers2[i];
								delete[] arrayOfNumbers2;
								quickSorting(arrayOfNumbers3, 0, count - 1);
								cout << endl << "В массиве несколько элементов со значением " << userNumber << ", их количество равно: " << count << endl;
								cout << endl << "Они находятся под индексами:" << endl;
								showArray(arrayOfNumbers3, count);
								delete[] arrayOfNumbers3;
								cout << endl;
							}
							else if (desiredIndex >= 0 && arrayOfNumbers[desiredIndex] != arrayOfNumbers[desiredIndex + 1] && arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex - 1]) {
								int count = 0, index = 0;
								count = backIndex(arrayOfNumbers, arrayOfNumbers2, desiredIndex, count, index);
								++count;
								int *arrayOfNumbers3 = new int[count];
								for (int i = 0; i < count; ++i)
									arrayOfNumbers3[i] = arrayOfNumbers2[i];
								delete[] arrayOfNumbers2;
								quickSorting(arrayOfNumbers3, 0, count - 1);
								cout << endl << "В массиве обнаружено несколько элементов со значением " << userNumber << ", их количество равно: " << count << endl;
								cout << endl << "Они находятся под индексами: " << endl;
								showArray(arrayOfNumbers3, count);
								delete[] arrayOfNumbers3;
								cout << endl;
							}
							else if (desiredIndex >= 0 && arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex + 1] && arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex - 1]) {
								int count = 0, desiredIndex2 = desiredIndex, index = 0;
								count = backIndex(arrayOfNumbers, arrayOfNumbers2, desiredIndex, count, index);
								for (int i = 0; i < index + 1; ++i)
									arrayOfNumbers2[i] = arrayOfNumbers2[i + 1];
								count = forthIndex(arrayOfNumbers, arrayOfNumbers2, desiredIndex2, count, index);
								++count;
								int *arrayOfNumbers3 = new int[count];
								for (int i = 0; i < count; ++i)
									arrayOfNumbers3[i] = arrayOfNumbers2[i];
								delete[] arrayOfNumbers2;
								quickSorting(arrayOfNumbers3, 0, count - 1);
								cout << endl << "В массиве обнаружено несколько элементов со значением " << userNumber << ", их количество равно: " << count << endl;
								cout << endl << "Они находятся под индексами: " << endl;
								showArray(arrayOfNumbers3, count);
								delete[] arrayOfNumbers3;
								cout << endl;
							}
							else
								cout << endl << "Такого числа в массиве нет." << endl << endl;
							cout << endl << "Время, затраченное на поиск: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl;
						}
					break;
					}
				}
			}
			break;
		}
			case 7: {
				if (created == 0 || elementsCount == 0) {
					cout << "Нет массива." << endl << endl;
				}
				else if (elementsCount == 1) {
					cout << endl << "В массиве всего 1 элемент, замена бессмысленна." << endl << endl;
				}
				else {
					cout << endl << "Введите номера элементов, которые следует поменять местами." << endl;
					while (true) {
						cout << endl << "Введите номер первого элемента: ";
						userNumber = getIndex(elementsCount);
						cout << endl << "Введите номер второго элемента: ";
						userNumber2 = getIndex(elementsCount);
						if (userNumber == userNumber2)
							cout << endl << "Индексы не могут совпадать. Попробуйте ещё раз." << endl << endl;
						else
							break;
					}
					auto begin = chrono::steady_clock::now();
					swap(&arrayOfNumbers[userNumber], &arrayOfNumbers[userNumber2]);
					auto end = chrono::steady_clock::now();
					cout << endl << "Изменённый массив:" << endl << endl;
					showArray(arrayOfNumbers, elementsCount);
					cout << endl << "Время, затраченное на обмен элементов массива: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl << endl;
				}
				break;
			}
			case 8: {
				if (created == 0 || elementsCount == 0) {
					cout << "Нет массива." << endl << endl;
				}
				else {
					cout << endl << "Введите число, на которое уменьшится каждый нечётный элемент: ";
					userNumber = getValue();
					thirdVariant(arrayOfNumbers, elementsCount, userNumber);
					cout << endl << "Массив, где каждый нечётный элемент уменьшен на " << userNumber << " и умножен на случайное число от 1 до 9:" << endl << endl;
					showArray(arrayOfNumbers, elementsCount);
					for (int i = 0; i < elementsCount; ++i) {
						if (arrayOfNumbers[i] % 2 == 0) ++cnt2;
						if (arrayOfNumbers[i] % 3 == 0) ++cnt3;
						if (arrayOfNumbers[i] % 4 == 0) ++cnt4;
						if (arrayOfNumbers[i] % 5 == 0) ++cnt5;
						if (arrayOfNumbers[i] % 6 == 0) ++cnt6;
						if (arrayOfNumbers[i] % 7 == 0) ++cnt7;
						if (arrayOfNumbers[i] % 8 == 0) ++cnt8;
						if (arrayOfNumbers[i] % 9 == 0) ++cnt9;
					}
					cout << endl << "Количество элементов, делящихся на 1: " << elementsCount << endl;
					cout << "Количество элементов, делящихся на 2: " << cnt2 << endl;
					cout << "Количество элементов, делящихся на 3: " << cnt3 << endl;
					cout << "Количество элементов, делящихся на 4: " << cnt4 << endl;
					cout << "Количество элементов, делящихся на 5: " << cnt5 << endl;
					cout << "Количество элементов, делящихся на 6: " << cnt6 << endl;
					cout << "Количество элементов, делящихся на 7: " << cnt7 << endl;
					cout << "Количество элементов, делящихся на 8: " << cnt8 << endl;
					cout << "Количество элементов, делящихся на 9: " << cnt9 << endl << endl;
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
	delete[] arrayOfNumbers;
	system("pause");
	return 0;
}
/*
So-called problems:
1. User cin. Should try rdbuf()->in.avail();
2. Arrays in 6. Should try to transport indexes to two variables (your number is in range (x-y)), if array is sorted;
*/
