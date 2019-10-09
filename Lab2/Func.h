#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

#ifndef FUNC_H
#define FUNC_H

void swap(int *first, int *second) {
	*first = *first + *second;
	*second = *first - *second;
	*first = *first - *second;
}

int getValue() {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректное число: ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}

int getIndex(int elements_count) {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail() || userNumber < 0 || userNumber >= elements_count) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректный индекс (от 0 до " << elements_count - 1 << "): ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}

int getMenuOption() {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 9): ";
		}
		else if (userNumber == 0 || userNumber == 1 || userNumber == 2 || userNumber == 3 || userNumber == 4 || userNumber == 5 || userNumber == 6 || userNumber == 7 || userNumber == 8 || userNumber == 9) {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
		else
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 9): ";
	}
}

int getSubMenuOption() {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректную опцию (от 1 до 5): ";
		}
		else if (userNumber == 1 || userNumber == 2 || userNumber == 3 || userNumber == 4 || userNumber == 5) {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
		else
			cout << endl << "Попробуйте ввести корректную опцию (от 1 до 5): ";
	}
}

char getMethod() {
	while (true) {
		char method;
		cin >> method;
		cin.ignore(cin.rdbuf()->in_avail());
		if (method == 'B' || method == 'b' || method == 'S' || method == 's' || method == 'C' || method == 'c' || method == 'I' || method == 'i' || method == 'Q' || method == 'q')
			return method;
		else
			cout << endl << "Попробуйте ещё раз." << endl << endl << "B(b) - Bubble, S(s) - Shaker; C(c) - Comb; I(i) - Insert; Q(q) - Quick: ";
	}
}

char getOption() {
	while (true) {
		char option;
		cin >> option;
		cin.ignore(cin.rdbuf()->in_avail());
		if (option == 'D' || option == 'd' || option == 'I' || option == 'i' || option == 'F' || option == 'f')
			return option;
		else
			cout << endl << "Попробуйте ещё раз." << endl << endl << "D(d) - удалить, I(i) - вставить, F(f) - поиск значения : ";
	}
}

void bubbleSorting(int *A, int count) {
	for (int i = 0; i < count; ++i) {
		for (int j = 0; j < count - 1; ++j) {
			if (A[j] > A[j + 1])
				swap(&A[j], &A[j + 1]);
		}
	}
}

void cocktailSorting(int *A, int count) {
	int left = 0, right = count - 1;
	bool motion = 1;
	while ((left < right) && motion == 1) {
		motion = 0;
		for (int i = left; i < right; ++i) {
			if (A[i] > A[i + 1]) {
				swap(&A[i], &A[i + 1]);
				motion = 1;
			}
		}
		--right;
		for (int i = right; i > left; --i) {
			if (A[i - 1] > A[i]) {
				swap(&A[i - 1], &A[i]);
				motion = 1;
			}
		}
		++left;
	}
}

void combSorting(int *A, int count) {
	int gap = count;
	bool motion = 1;
	while (gap != 1 || motion == 1) {
		gap = (gap * 10) / 13;
		if (gap < 1)
			gap = 1;
		motion = 0;
		for (int i = 0; i < count - gap; ++i) {
			if (A[i] > A[i + gap]) {
				swap(&A[i], &A[i + gap]);
				motion = 1;
			}
		}
	}
}

void insertionSorting(int *A, int count) {
	int i, k, j;
	for (i = 1; i < count; ++i) {
		k = A[i];
		j = i - 1;
		while (j >= 0 && A[j] > k) {
			A[j + 1] = A[j];
			--j;
		}
		A[j + 1] = k;
	}
}

void quickSorting(int *A, int start, int end) {
	int i = start, j = end, tmp;
	int separator = A[(start + end) / 2];
	while (i <= j) {
		while (A[i] < separator)
			++i;
		while (A[j] > separator)
			--j;
		if (i <= j) {
			tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
			++i;
			--j;
		}
	}
	if (start < j)
		quickSorting(A, start, j);
	if (i < end)
		quickSorting(A, i, end);
}

int search(int *A, int start, int end, int number) {
	if (end >= start) {
		int mid = start + (end - start) / 2;
		if (A[mid] == number)
			return mid;
		if (A[mid] > number)
			return search(A, start, mid - 1, number);
		if (A[mid] < number)
			return search(A, mid + 1, end, number);
	}
	return -1;
}

int back(int *A, int index, int count) {
	while (A[index] == A[index - 1]) {
		--index;
		++count;
	}
	return count;
}

int forth(int *A, int index, int count) {
	while (A[index] == A[index + 1]) {
		++index;
		++count;
	}
	return count;
}

int backIndex(int *A, int &index, int count) {
	while (A[index] == A[index - 1]) {
		--index;
		++count;
	}
	return count;
}

int forthIndex(int *A, int &index, int count) {
	while (A[index] == A[index + 1]) {
		++index;
		++count;
	}
	return count;
}

short fifthVariant(int *A, int count) {
	int left = 0, right = count - 1;
	int *B = new int[count];
	for (int i = 0; i < count; ++i)
		B[i] = A[i];
	bool minIsNotFound = 1, maxIsNotFound = 1, symmetryNotAchieved = 1, symmetry = 0;
	while (symmetryNotAchieved) {
		int index1, index2;
		while (minIsNotFound) {
			bool cycleMinFail = 0, cycleMaxFail = 0;
			int minimum = 100;
			for (int i = left; i < right + 1; ++i) {
				if (B[i] <= minimum) {
					minimum = B[i];
					index1 = i;
				}
			}
			swap(B[left], B[index1]);
			++left;
			minimum = 100;
			for (int i = right; i >= left; --i) {
				if (B[i] <= minimum) {
					minimum = B[i];
					index2 = i;
				}
			}
			swap(B[right], B[index2]);
			--left;
			if (B[left] == B[right]) {
				if (right * 2 == count || (right - 1) * 2 + 1 == count) {
					symmetry = 1;
					symmetryNotAchieved = 0;
				}
				++left;
				--right;
			}
			else {
				swap(B[index2], B[right]);
				swap(B[index1], B[left]);
				cycleMinFail = 1;
				while (maxIsNotFound) {
					int maximum = -1;
					for (int i = left; i < right + 1; ++i) {
						if (B[i] >= maximum) {
							maximum = B[i];
							index1 = i;
						}
					}
					swap(B[left], B[index1]);
					++left;
					maximum = -1;
					for (int i = right; i >= left; --i) {
						if (B[i] >= maximum) {
							maximum = B[i];
							index2 = i;
						}
					}
					swap(B[right], B[index2]);
					--left;
					if (B[left] == B[right]) {
						if (right * 2 == count || (right - 1) * 2 + 1 == count) {
							symmetry = 1;
							symmetryNotAchieved = 0;
						}
						++left;
						--right;
					}
					else {
						swap(B[index2], B[right]);
						swap(B[index1], B[left]);
						cycleMaxFail = 1;
						maxIsNotFound = 0;
					}
				}
			}
			if (cycleMinFail == 1 && cycleMaxFail == 1)
				minIsNotFound = 0;
		}
		symmetryNotAchieved = 0;
	}
	if (symmetry == 1) {
		int comparison = 0;
		for (int i = 0; i < count; ++i) {
			if (A[i] == B[i])
				++comparison;
		}
		if (comparison == count) {
			delete[] B;
			return 2;
		}
		else
			for (int i = 0; i < count; ++i) {
				A[i] = B[i];
			}
		delete[] B;
		return 1;
	}
	else {
		delete[] B;
		return 0;
	}
}

void fourthVariant(int *A, int count) {
	int first = A[0], last = A[count - 1];
	for (int i = 0; i < count; ++i) {
		if (i == count - 1)
			A[i] = first + last;
		else
			A[i] = A[i] + A[i + 1];
	}
	for (int i = 0; i < count; ++i)
		swap(A[i], A[rand() % count]);
}

void thirdVariant(int *A, int count, int number) {
	for (int i = 0; i < count; ++i) {
		if (i % 2 == 1)
			A[i] = (A[i] - number) * (rand() % 9 + 1);
	}
}

void secondVariant(int *A, int count, int number) {
	for (int i = 0; i < count; ++i) {
		if (i % 2 == 0)
			A[i] = (A[i] - number) * (rand() % 9 + 1);
	}
}

void firstVariant(int *A, int *B, int *C, int count, int count2, int &countComparison) {
	int index = 0;
	for (int i = 0; i < count2; ++i) {
		B[i] = A[i];
	}
	for (int i = count2; i < count; ++i) {
		C[index] = A[i];
		++index;
	}
	for (int i = 0; i < count2; ++i) {
		if (i % 2 != 0)
			swap(B[i], C[i - 1]);
	}
	for (int i = 0; i < count2; ++i) {
		if (C[i] % 2 != 0)
			C[i] = C[i] + 1;
	}
	for (int i = 0; i < count2; ++i) {
		if (B[i] > C[i])
			++countComparison;
	}
}

void generateArray(int *A, int count) {
	for (int i = 0; i < count; ++i)
		A[i] = rand() % 4 + 1; //To demonstrate var. no. 5; was rand() % 100 ([0..99])
}

void showArray(int *A, int count) {
	if (count == 0)
		cout << "Количество элементов в массиве равно 0, следовательно, его не сущесвтует." << endl;
	else {
		for (int i = 0; i < count; ++i)
			cout << i << ". " << A[i] << endl;
		cout << endl;
	}
}

void searchMinMax(int *A, int count, int &min, int &max) {
	for (int i = 0; i < count; ++i) {
		if (A[i] < min)
			min = A[i];
		if (A[i] > max)
			max = A[i];
	}
}

#endif
