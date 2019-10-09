#include "Func.h"

int main() {
	setlocale(0, "");
	srand((unsigned)time(NULL));
	int *arrayOfNumbers = 0, elementsCount, menuOption, desiredIndex, comparison = 0, userNumber, userNumber2;
	char method;
	bool condition = 1, sorted = 0, created = 0;
	while (condition) {
		cout << "Выберите опцию . . ." << endl;
		cout << "0. Создать массив" << endl;
		cout << "1. Отсортировать массив" << endl;
		cout << "2. Показать минимум и максимум" << endl;
		cout << "3. Показать количество элементов, равных среднему минимума и максимума" << endl;
		cout << "4. Показать количество элементов, больших, чем заданное число" << endl;
		cout << "5. Показать количество элементов, меньших, чем заданное число" << endl;
		cout << "6. Удалить элемент, вставить элемент или найти значение" << endl;
		cout << "7. Поменять элементы местами" << endl;
		cout << "8. Задание по вариантам" << endl;
		cout << "9. Выйти" << endl;
		cout << "Опция: ";
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
				cout << endl << "Нет массива." << endl << endl;
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
				cout << endl << "Нет массива." << endl << endl;
			}
			else if (sorted == 0) {
				int min = 2147483647, max = ~min;
				searchMinMax(arrayOfNumbers, elementsCount, min, max);
				cout << endl << "Минимум: " << min << " Максимум: " << max << endl << endl;
			}
			else {
				cout << endl << "Минимум: " << arrayOfNumbers[0] << " Максимум: " << arrayOfNumbers[elementsCount - 1] << endl << endl;
			}
			break;
		}
		case 3: {
			if (created == 0 || elementsCount == 0) {
				cout << endl << "Нет массива." << endl << endl;
			}
			else if (sorted == 0) {
				int min = 2147483647, max = ~min, count = 0;
				searchMinMax(arrayOfNumbers, elementsCount, min, max);
				for (int i = 0; i < elementsCount; ++i) {
					if (arrayOfNumbers[i] == (max + min) / 2)
						++count;
				}
				if (count == 0)
					cout << endl << "Нет элементов, равных среднему минимума и максимума (" << (max + min) / 2 << ")" << endl << endl;
				else
					cout << endl << "Количество элементов в массиве, равных среднему минимума и максимума (" << (max + min) / 2 << "): " << count << endl << endl;
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
				cout << endl << "Нет массива." << endl << endl;
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
				cout << endl << "Нет массива." << endl << endl;
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
				cout << endl << "Нет массива." << endl << endl;
			}
			else {
				cout << endl << "Удалить элемент, вставить элемент или найти значение?" << endl << endl;
				cout << "D(d) - удалить, I(i) - вставить, F(f) - поиск значения: ";
				method = getOption();
				switch (method) {
				case 'D': case 'd': {
					cout << endl << "Введите номер элемента, который требуется удалить: ";
					userNumber = getIndex(elementsCount);
					int *arrayOfNumbers2 = new int[elementsCount - 1];
					auto begin = chrono::steady_clock::now();
					for (int i = 0; i < userNumber; ++i)
						arrayOfNumbers2[i] = arrayOfNumbers[i];
					for (int i = userNumber; i < elementsCount - 1; ++i)
						arrayOfNumbers2[i] = arrayOfNumbers[i + 1];
					auto end = chrono::steady_clock::now();
					--elementsCount;
					for (int i = 0; i < elementsCount; ++i)
						arrayOfNumbers[i] = arrayOfNumbers2[i];
					cout << endl << "Изменённый массив:" << endl << endl;
					showArray(arrayOfNumbers, elementsCount);
					cout << endl << "Время, затраченное на удаление: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl << endl;
					delete[] arrayOfNumbers2;
					break;
				}
				case 'I': case 'i': {
					cout << endl << "Введите номер элемента, на место которого нужно вставить новый элемент: ";
					userNumber = getIndex(elementsCount);
					cout << endl << "Введите значение нового элемента: ";
					userNumber2 = getValue();
					int *arrayOfNumbers2 = new int[elementsCount + 1];
					auto begin = chrono::steady_clock::now();
					arrayOfNumbers2[userNumber] = userNumber2;
					for (int i = userNumber + 1; i < elementsCount + 1; ++i)
						arrayOfNumbers2[i] = arrayOfNumbers[i - 1];
					for (int i = userNumber - 1; i >= 0; i--)
						arrayOfNumbers2[i] = arrayOfNumbers[i];
					auto end = chrono::steady_clock::now();
					++elementsCount;
					for (int i = 0; i < elementsCount; ++i)
						arrayOfNumbers[i] = arrayOfNumbers2[i];
					cout << endl << "Изменённый массив:" << endl << endl;
					showArray(arrayOfNumbers, elementsCount);
					cout << endl << "Время, затраченное на вставку: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl << endl;
					if (sorted = 1 && ((userNumber2 >= arrayOfNumbers[userNumber - 1] && userNumber2 <= arrayOfNumbers[userNumber + 1]) || (userNumber == 0 && userNumber2 <= arrayOfNumbers[userNumber + 1])))
						sorted = 1;
					else
						sorted = 0;
					delete[] arrayOfNumbers2;
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
							int count = 0, indexLeft = desiredIndex;
							count = forthIndex(arrayOfNumbers, desiredIndex, count);
							++count;
							cout << endl << "В массиве несколько элементов со значением " << userNumber << ", их количество равно: " << count << endl;
							cout << endl << "Они находятся под индексами с " << indexLeft << " по " << desiredIndex << endl << endl;
						}
						else if (desiredIndex >= 0 && arrayOfNumbers[desiredIndex] != arrayOfNumbers[desiredIndex + 1] && arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex - 1]) {
							int count = 0, indexRight = desiredIndex;
							count = backIndex(arrayOfNumbers, desiredIndex, count);
							++count;
							cout << endl << "В массиве обнаружено несколько элементов со значением " << userNumber << ", их количество равно: " << count << endl;
							cout << endl << "Они находятся под индексами с " << desiredIndex << " по " << indexRight << endl << endl;
						}
						else if (desiredIndex >= 0 && arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex + 1] && arrayOfNumbers[desiredIndex] == arrayOfNumbers[desiredIndex - 1]) {
							int count = 0, desiredIndex2 = desiredIndex, indexLeft = 0, indexRight = 0;
							count = backIndex(arrayOfNumbers, desiredIndex, count);
							indexLeft = desiredIndex;
							count = forthIndex(arrayOfNumbers, desiredIndex2, count);
							indexRight = desiredIndex2;
							++count;
							cout << endl << "В массиве обнаружено несколько элементов со значением " << userNumber << ", их количество равно: " << count << endl;
							cout << endl << "Они находятся под индексами с " << indexLeft << " по " << indexRight << endl << endl;
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
				cout << endl << "Нет массива." << endl << endl;
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
						cout << endl << "Следует ввести два различных индекса. Попробуйте ещё раз." << endl << endl;
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
				cout << endl << "Нет массива." << endl << endl;
			}
			else {
				cout << endl << "Выберите опцию . . ." << endl;
				cout << "1. Первый вариант" << endl;
				cout << "2. Второй вариант" << endl;
				cout << "3. Третий вариант" << endl;
				cout << "4. Четвёртый вариант" << endl;
				cout << "5. Пятый вариант" << endl;
				cout << "Опция: ";
				menuOption = getSubMenuOption();
				switch (menuOption) {
				case 1: {
					int *arrayOfNumbers2 = 0, *arrayOfNumbers3 = 0, elementsCount2, elementsCount3, countComparison = 0;
					elementsCount2 = elementsCount / 2;
					if (elementsCount2 * 2 == elementsCount)
						elementsCount3 = elementsCount / 2;
					else
						elementsCount3 = elementsCount / 2 + 1;
					arrayOfNumbers2 = new int[elementsCount2];
					arrayOfNumbers3 = new int[elementsCount3];
					firstVariant(arrayOfNumbers, arrayOfNumbers2, arrayOfNumbers3, elementsCount, elementsCount2, countComparison);
					cout << endl << "Первый новый массив: " << endl << endl;
					showArray(arrayOfNumbers2, elementsCount2);
					cout << "Второй новый массив: " << endl << endl;
					showArray(arrayOfNumbers3, elementsCount3);
					if (countComparison == 0)
						cout << "Нет элементов, которые больше в первом новом массиве, чем во втором новом массиве (попарное сравнение)." << endl << endl;
					else
						cout << "Количество элементов, которые больше в первом новом массиве, чем во втором новом массиве (попарное сравнение): " << countComparison << endl << endl;
					break;
				}
				case 2: {
					cout << endl << "Введите число, на которое уменьшится каждый чётный элемент: ";
					userNumber = getValue();
					secondVariant(arrayOfNumbers, elementsCount, userNumber);
					cout << endl << "Массив, где каждый чётный элемент уменьшен на " << userNumber << " и умножен на случайное число от 1 до 9:" << endl << endl;
					showArray(arrayOfNumbers, elementsCount);
					int odd = 0, even = 0;
					for (int i = 0; i < elementsCount; ++i) {
						if (i % 2 == 0) {
							if (arrayOfNumbers[i] % 2 == 0)
								++even;
						}
						else if (i % 2 == 1) {
							if (arrayOfNumbers[i] % 2 == 1)
								++odd;
						}
					}
					if (even == 0)
						cout << "Нет чётных элементов, имеющих чётные значения." << endl;
					else
						cout << endl << "Количество чётных элементов, имеющих чётные значения: " << even << endl;
					if (odd == 0)
						cout << "Нет нечётных элементов, имеющих нечётные значения." << endl << endl;
					else
						cout << "Количество нечётных элементов, имеющих нечётные значения: " << odd << endl << endl;
					break;
				}
				case 3: {
					cout << endl << "Введите число, на которое уменьшится каждый нечётный элемент: ";
					userNumber = getValue();
					thirdVariant(arrayOfNumbers, elementsCount, userNumber);
					cout << endl << "Массив, где каждый нечётный элемент уменьшен на " << userNumber << " и умножен на случайное число от 1 до 9:" << endl << endl;
					showArray(arrayOfNumbers, elementsCount);
					int cnt2, cnt3, cnt4, cnt5, cnt6, cnt7, cnt8, cnt9;
					cnt2 = cnt3 = cnt4 = cnt5 = cnt6 = cnt7 = cnt8 = cnt9 = 0;
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
					break;
				}
				case 4: {
					fourthVariant(arrayOfNumbers, elementsCount);
					cout << endl << "Массив, в котором значение текущего элемента было изменено на сумму текущего и следующего (последний элемент равен сумме последнего и первого), а также сделана 'обратная сортировка':" << endl;
					showArray(arrayOfNumbers, elementsCount);
					break;
				}
				case 5: {
					short symmetry = fifthVariant(arrayOfNumbers, elementsCount);
					if (symmetry == 2)
						cout << endl << "Массив уже симметричен" << endl << endl;
					else if (symmetry == 1) {
						cout << endl << "Получился симметричный массив:" << endl << endl;
						showArray(arrayOfNumbers, elementsCount);
					}
					else
						cout << endl << "Не удалось получить симметричный массив." << endl << endl;
					break;
				}
				}
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
