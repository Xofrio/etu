#define NOMINMAX
#include <iostream>
#include <fstream>
#include <chrono>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

HANDLE textColour = GetStdHandle(STD_OUTPUT_HANDLE);

#ifndef FUNC_H
#define FUNC_H

struct dLL {
	int data; /*Поле данных*/
	struct dLL *next; /*Указатель на следующий эл-т*/
	struct dLL *prev; /*Указатель на предыдущий эл-т*/
};/*Объявления структуры двусвязного линейного списка*/

void showConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; /*Установка видимости курсора*/
	SetConsoleCursorInfo(out, &cursorInfo);
} /*Отмена мигающего подчёркивания (для выбора в меню)*/

void draw(string str) {
	SetConsoleTextAttribute(textColour, 14);
	cout << str << endl;
	SetConsoleTextAttribute(textColour, 7);
} /*Прорисовка цветных пунктов, т.е. тех, которые выбраны в данный момент*/

short menu() {
	short key = 0;
	int code = 0;
	do {
		system("cls");
		showConsoleCursor(false);
		key = (key + 10) % 10;
		if (key == 0)
			draw(">Создать динамический массив");
		else
			cout << "Создать динамический массив" << endl;
		if (key == 1)
			draw(">Вывести скорость создания динамического массива");
		else
			cout << "Вывести скорость создания динамического массива" << endl;
		if (key == 2)
			draw(">Вставить/найти/удалить элемент в динамическом массиве");
		else
			cout << "Вставить/найти/удалить элемент в динамическом массиве" << endl;
		if (key == 3)
			draw(">Вывести скорость вставки/поиска/удаления элемента динамического массива");
		else
			cout << "Вывести скорость вставки/поиска/удаления элемента динамического массива" << endl;
		if (key == 4)
			draw(">Создать двусвязный список");
		else
			cout << "Создать двусвязный список" << endl;
		if (key == 5)
			draw(">Вывести скорость создания двусвязного списка");
		else
			cout << "Вывести скорость создания двусвязного списка" << endl;
		if (key == 6)
			draw(">Вставить/найти/удалить элемент в двусвязном списке");
		else
			cout << "Вставить/найти/удалить элемент в двусвязном списке" << endl;
		if (key == 7)
			draw(">Вывести скорость вставки/поиска/удаления элемента двусвязного списка");
		else
			cout << "Вывести скорость вставки/поиска/удаления элемента двусвязного списка" << endl;
		if (key == 8)
			draw(">Вывести кол-во чётных эл-тов, которые имеют чётные значения, кол-во нечётных эл-тов, которые имеют нечётные значения.\nСравнить скорость выполнения в динамическом массиве и двусвязном списке");
		else
			cout << "Вывести кол-во чётных эл-тов, которые имеют чётные значения, кол-во нечётных эл-тов, которые имеют нечётные значения.\nСравнить скорость выполнения в динамическом массиве и двусвязном списке" << endl;
		if (key == 9)
			draw(">Выйти");
		else
			cout << "Выйти" << endl;
		if (code != 13) {
			code = _getch();
			if (code == 80 || code == 115)
				++key;
			if (code == 72 || code == 119)
				--key;
		}
	} while (code != 13);
	system("cls");
	return key;
} /*Меню, управление - стрелки вверх и вниз, а также клавиши w и s*/

short creationMenu() {
	short key = 0;
	int code = 0;
	do {
		system("cls");
		showConsoleCursor(false);
		key = (key + 4) % 4;
		if (key == 0)
			draw(">Сгенерировать автоматически");
		else
			cout << "Сгенерировать автоматически" << endl;
		if (key == 1)
			draw(">Ввести элементы вручную");
		else
			cout << "Ввести элементы вручную" << endl;
		if (key == 2)
			draw(">Считать с файла");
		else
			cout << "Считать с файла" << endl;
		if (key == 3)
			draw(">Назад");
		else
			cout << "Назад" << endl;
		if (code != 13) {
			code = _getch();
			if (code == 80 || code == 115)
				++key;
			if (code == 72 || code == 119)
				--key;
		}
	} while (code != 13);
	system("cls");
	return key;
} /*Меню для массива, управление - стрелки вверх и вниз, а также клавиши w и s*/

short valuesManipulationMenu() {
	short key = 0;
	int code = 0;
	do {
		system("cls");
		showConsoleCursor(false);
		key = (key + 4) % 4;
		if (key == 0)
			draw(">Добавить элемент");
		else
			cout << "Добавить элемент" << endl;
		if (key == 1)
			draw(">Найти элемент");
		else
			cout << "Найти элемент" << endl;
		if (key == 2)
			draw(">Удалить элемент");
		else
			cout << "Удалить элемент" << endl;
		if (key == 3)
			draw(">Назад");
		else
			cout << "Назад" << endl;
		if (code != 13) {
			code = _getch();
			if (code == 80 || code == 115)
				++key;
			if (code == 72 || code == 119)
				--key;
		}
	} while (code != 13);
	system("cls");
	return key;
} /*Меню для добавления/поиска/удаления элемента, управление - стрелки вверх и вниз, а также клавиши w и s*/

short findEraseMenu(bool type) {
	short key = 0;
	int code = 0;
	do {
		system("cls");
		showConsoleCursor(false);
		key = (key + 4) % 4;
		if (key == 0 && type == 1)
			draw(">Удалить элемент по индексу");
		else if (key == 0 && type == 0)
			draw(">Найти элемент по индексу");
		else if (type == 1)
			cout << "Удалить элемент по индексу" << endl;
		else if (type == 0)
			cout << "Найти элемент по индексу" << endl;
		if (key == 1 && type == 1)
			draw(">Удалить элемент по значению");
		else if (key == 1 && type == 0)
			draw(">Найти элемент по значению");
		else if (type == 1)
			cout << "Удалить элемент по значению" << endl;
		else if (type == 0)
			cout << "Найти элемент по значению" << endl;
		if (key == 2)
			draw(">Назад");
		else
			cout << "Назад" << endl;
		if (code != 13) {
			code = _getch();
			if (code == 80 || code == 115)
				++key;
			if (code == 72 || code == 119)
				--key;
		}
	} while (code != 13);
	system("cls");
	return key;
} /*Меню для поиска/удаления элемента, управление - стрелки вверх и вниз, а также клавиши w и s*/

void fallBack() {
	cout << endl;
	draw(">Назад");
	int code = 0;
	do {
		code = _getch();
	} while (code != 13);
} /*Отобразить одиночный пункт "Назад" после какого-либо ввода/выбора действия*/

int getAmount() {
	while (true) {
		string input;
		int output;
		bool bad = 0;
		getline(cin, input);
		if (input.length() > 0 && input.length() < 11) {
			for (unsigned int i = 0; i < input.length(); ++i) {
				if (int(input[i]) < 48 || int(input[i]) > 57) { /*Если символ входящей строки не [0..9] - устанавливается флаг*/
					bad = 1;
					break;
				}
			}
			if (int(input[0]) == 48) /*Количество элементов не должно начинаться с незначащего нуля и не должно равняться нулю*/
				bad = 1;
		}
		if (input.length() == 0 || cin.fail() || bad == 1 || input.length() > 10 || stoi(input) > numeric_limits<int>::max()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Введите размерность: ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return output = stoi(input);
		}
	}
} /*Получить количество элементов массива при его генерации*/

int getIndex(int &amount) {
	while (true) {
		string input;
		int output;
		bool bad = 0;
		getline(cin, input);
		if (input.length() > 0 && input.length() < 11) {
			for (unsigned int i = 0; i < input.length(); ++i) {
				if (int(input[i]) < 48 || int(input[i]) > 57) { /*Если символ входящей строки не [0..9] - устанавливается флаг*/
					bad = 1;
					break;
				}
			}
			if (int(input[0]) == 48 && int(input[1]) != 0) /*Индекс не должен начинаться с незначащего нуля*/
				bad = 1;
		}
		if (input.length() == 0 || cin.fail() || bad == 1 || input.length() > 10 || stoi(input) < 0 || stoi(input) >= amount) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Введите индекс: ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return output = stoi(input);
		}
	}
} /*Получить индекс массива*/

void check(string &input, bool &bad, bool purpose) {
	for (unsigned int i = 0; i < input.length(); ++i) {
		if (((int(input[i]) < 48 || int(input[i]) > 57) && int(input[i]) != 32 && int(input[i]) != 45)) { /*В строке не должно быть ничего, кроме цифр [0..9], пробелов и знака "-"*/
			bad = 1;
			break;
		}
		else if (int(input[i]) == 32 && (i == 0 || int(input[i + 1]) == 0 || int(input[i + 1]) == 32)) { /*После пробела не должно быть ещё одного пробела или конца строки, пробел не может быть первым символом*/
			bad = 1;
			break;
		}
		else if ((int(input[i]) > 47 && int(input[i]) < 58) && int(input[i + 1]) == 45) { /*После цифры не должно быть знака "-"*/
			bad = 1;
			break;
		}
		else if (int(input[i]) == 45 && (int(input[i + 1]) == 0 || int(input[i + 1]) == 32 || int(input[i + 1]) == 48)) { /*После знака "-" не должно быть конца строки, пробела или цифры 0*/
			bad = 1;
			break;
		}
		else if (int(input[i]) == 48 && (int(input[i + 1]) >= 48 && int(input[i + 1]) <= 57) && (i == 0 || int(input[i - 1]) == 32)) { /*После цифры 0 не должно быть никаких цифр, если он незначащий*/
			bad = 1;
			break;
		}
	}
	if (bad == 0) {
		int count = 0;
		string::size_type size;
		string clone = input;
		long int checking;
		for (unsigned int i = 0; i < clone.length(); ++i) {
			checking = stoi(clone, &size);
			if (checking < numeric_limits<int>::min() || checking > numeric_limits<int>::max()) { /*Проверка числа на границы типа int*/
				bad = 1;
				break;
			}
			++count;
			clone = clone.substr(size);
		}
		if (count > 1 && purpose == 1) { /*Проверка количества чисел. Если их больше, чем 1 для добавления/поиска/удаления - устанавливаем флаг*/
			bad = 1;
		}
	}
}/*Проверка корректности строки на значения целого типа*/

int getElement(string &input, bool &bad, short type) {
	while (true) {
		cout << "Введите значение элемента, который вы хотите";
		if (type == 2)
			cout << " добавить: ";
		else if (type == 1)
			cout << " найти: ";
		else
			cout << " удалить: ";
		getline(cin, input);
		check(input, bad, 1);
		if (bad == 1) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Введите значение элемента: ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return stoi(input);
		}
	}
}

int*& createArray(int *&array, int &amount, long int &speed, short &method, int &amountCreated) {
	short option = creationMenu();
	switch (option) {
	case 0: { /*Генерация массива из N значений; N задаёт пользователь, значения заполняются автоматически от 0 до 99*/
		delete[] array;
		system("cls");
		cout << "Введите размерность динамического массива: ";
		showConsoleCursor(true);
		amount = getAmount();
		showConsoleCursor(false);
		auto begin = chrono::steady_clock::now(); /*Начало отсчёта - выделение памяти под динамический массив*/
		array = new int[amount];
		for (int i = 0; i < amount; ++i)
			array[i] = rand() % 100;
		auto end = chrono::steady_clock::now(); /*Конец отсчёта - добавление последнего элемента в массив*/
		speed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()); /*Скорость - время, затраченное на создание динамического массива*/
		cout << "Ваш динамический массив:" << endl;
		for (int i = 0; i < amount; ++i)
			cout << i << ". " << array[i] << endl;
		method = 0;
		amountCreated = amount;
		break;
		}
	case 1: {
		system("cls");
		cout << "Введите через пробел значения целочисленного динамического массива:" << endl;
		string input;
		bool bad = 0;
		showConsoleCursor(true);
		getline(cin, input);
		check(input, bad, 0);
		if (bad == 0) {
			delete[] array;
			amount = 0;
			unsigned int i = 0;
			while (int(input[i]) != 0) {
				while (int(input[i]) != 32 && int(input[i]) != 0) {
					++i;
				}
				++amount;
				if (int(input[i]) == 0)
					break;
				++i;
			}
			string::size_type size;
			auto begin = chrono::steady_clock::now(); /*Начало отсчёта - выделение памяти под динамический массив*/
			array = new int[amount];
			for (int i = 0; i < amount; ++i) {
				array[i] = stoi(input, &size);
				input = input.substr(size);
			}
			auto end = chrono::steady_clock::now(); /*Конец отсчёта - добавление последнего элемента в массив*/
			speed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()); /*Скорость - время, затраченное на создание динамического массива*/
			amountCreated = amount;
			method = 1;
			cout << "Ваш динамический массив:" << endl;
			for (int i = 0; i < amount; ++i)
				cout << i << ". " << array[i] << endl;
		}
		else
			cout << "Динамический массив не был создан." << endl;
		break;
	}
	case 2: {
		system("cls");
		amount = 0;
		ifstream file("input.txt");
		if (file.is_open()) {
			string input;
			bool bad = 0;
			getline(file, input, '\0');
			check(input, bad, 0);
			if (input.length() == 0)
				bad = 1;
			if (bad == 0) {
				delete[] array;
				file.seekg(0, ios::beg);
				file.clear();
				int temp;
				while (!file.eof()) {
					file >> temp;
					++amount;
				}
				file.seekg(0, ios::beg);
				file.clear();
				int i = 0;
				auto begin = chrono::steady_clock::now(); /*Начало отсчёта - выделение памяти под динамический массив*/
				array = new int[amount];
				while (!file.eof()) {
					file >> array[i];
					++i;
				}
				auto end = chrono::steady_clock::now(); /*Конец отсчёта - добавление последнего элемента в массив*/
				file.close();
				speed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()); /*Скорость - время, затраченное на создание динамического массива*/
				amountCreated = amount;
				method = 2;
				cout << "Ваш динамический массив:" << endl;
				for (int i = 0; i < amount; ++i)
					cout << i << ". " << array[i] << endl;
			}
			else
				cout << "Динамический массив не был создан. Проверьте содержание файла 'input.txt'.";
		}
		else {
			cout << "Файл с именем 'input.txt' не найден." << endl << endl;
		}
		break;
	}
	case 3: {
		return array;
	}
	}
	fallBack();
	return array;
} /*Создать массив*/

void creationSpeed(int *&array, dLL *&list, int &arrayAmountCreated, int &listAmountCreated, long int &arrayCreationSpeed, long int &listCreationSpeed, short &arrayMethod, short &listMethod, bool type) {
	if (type == 0 && array == 0)
		cout << "Нет массива." << endl;
	else if (type == 1 && list == 0)
		cout << "Нет двусвязного списка." << endl;
	else {
		if (type == 0) {
			cout << "Время, затраченное на создание динамического массива из "<< arrayAmountCreated << " элемент";
			if (arrayAmountCreated % 10 == 1 && arrayAmountCreated != 11)
				cout << "а,";
			else
				cout << "ов,";
			cout << " созданного в п.1 ";
			if (arrayMethod == 2)
				cout << "из файла";
			else if (arrayMethod == 1)
				cout << "вручную";
			else
				cout << "автоматически";
			cout << ": " << arrayCreationSpeed << " наносекунд." << endl;
		}
		else {
			cout << "Время, затраченное на создание двусвязного списка из " << listAmountCreated << " элемент";
			if (listAmountCreated % 10 == 1 && listAmountCreated != 11)
				cout << "а,";
			else
				cout << "ов,";
			cout << " созданного в п.5 ";
			if (listMethod == 2)
				cout << "из файла";
			else if (listMethod == 1)
				cout << "вручную";
			else
				cout << "автоматически";
			cout << ": " << listCreationSpeed << " наносекунд." << endl;
		}
	}
	fallBack();
} /*Показать время, затраченное на создание динамического массива/двусвязного списка*/

int* arrayAddFindErase(int *array, int &amount, long int &addingSpeed, long int &searchSpeed, long int &erasingSpeed) {
	short option = valuesManipulationMenu();
	switch (option) {
	case 0: { /*Добавление элемента*/
		system("cls");
		if (array == 0) { /*Проверяем массив на созданность, а не на количество элементов в нём*/
			cout << "Нет массива." << endl;
		}
		else {
			if (amount != 0) {
				cout << "Ваш массив:" << endl;
				for (int i = 0; i < amount; ++i)
					cout << i << ". " << array[i] << endl;
			}
			int *temp = 0;
			string input;
			bool bad = 0;
			showConsoleCursor(true);
			int element = getElement(input, bad, 2), index;
			if (amount != 0) {
				cout << "Введите индекс для нового элемента (от 0 до " << amount - 1 << "): ";
				index = getIndex(amount);
			}
			else
				index = 0;
			showConsoleCursor(false);
			++amount;
			auto begin = chrono::steady_clock::now(); /*Начало отсчёта - выделение памяти под динамический массив*/
			temp = new int[amount];
			for (int i = 0; i < index; ++i)
				temp[i] = array[i];
			temp[index] = element;
			for (int i = index + 1; i < amount; ++i)
				temp[i] = array[i - 1];
			auto end = chrono::steady_clock::now(); /*Конец отсчёта - добавление последнего элемента в массив*/
			addingSpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()); /*Скорость - время, затраченное на создание динамического массива*/
			cout << "Ваш динамический массив:" << endl;
			for (int i = 0; i < amount; ++i) {
				if (i == index) {
					SetConsoleTextAttribute(textColour, 10);
					cout << i << ". " << temp[i] << endl;
					SetConsoleTextAttribute(textColour, 7);
				} else
					cout << i << ". " << temp[i] << endl;
			}
			cout << endl;
			delete[] array;
			array = new int[amount];
			for (int i = 0; i < amount; ++i)
				array[i] = temp[i];
			fallBack();
			return array;
		}
		break;
	}
	case 1: { /*Поиск элемента*/
		short findOption = findEraseMenu(0);
		switch (findOption) {
		case 0: { /*Поиск по индексу*/
			system("cls");
			if (array == 0) {
				cout << "Нет массива." << endl;
			}
			else if (amount == 0) {
				cout << "В массиве нет элементов." << endl;
			}
			else {
				cout << "Ваш массив:" << endl;
				for (int i = 0; i < amount; ++i)
					cout << i << ". " << array[i] << endl;
				cout << "Введите индекс искомого элемента (от 0 до " << amount - 1 << "): ";
				showConsoleCursor(true);
				int index = getIndex(amount);
				showConsoleCursor(false);
				cout << "Ваш элемент: ";
				SetConsoleTextAttribute(textColour, 11);
				auto begin = chrono::steady_clock::now(); /*Начало отсчёта - вывод требуемого элемента массива*/
				cout << array[index]; /*Отсчёт количества позиций с адреса первой ячейки до требуемой, (номер ячейки - 1) * количество памяти, требуемое для хранения 1 элемента*/
				auto end = chrono::steady_clock::now(); /*Конец отсчёта - вывод требуемого элемента массива*/
				SetConsoleTextAttribute(textColour, 7);
				cout << endl;
				cout << "Ваш динамический массив:" << endl;
				for (int i = 0; i < amount; ++i) {
					if (i == index) {
						SetConsoleTextAttribute(textColour, 11);
						cout << i << ". " << array[i] << endl;
						SetConsoleTextAttribute(textColour, 7);
					}
					else
						cout << i << ". " << array[i] << endl;
				}
				searchSpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()); /*Скорость - время, затраченное на отображение требуемого элемента*/
				fallBack();
				return array;
			}
			break;
		}
		case 1: { /*Поиск по значению*/
			system("cls");
			if (array == 0) {
				cout << "Нет массива." << endl;
			}
			else if (amount == 0) {
				cout << "В массиве нет элементов, нечего искать." << endl;
			}
			else {
				cout << "Ваш массив:" << endl;
				for (int i = 0; i < amount; ++i)
					cout << i << ". " << array[i] << endl;
				string input;
				showConsoleCursor(true);
				bool bad = 0;
				int element = getElement(input, bad, 0);
				showConsoleCursor(false);
				int count = 0;
				auto begin = chrono::steady_clock::now(); /*Начало отсчёта - сравнение с первым элементом массива*/
				for (int i = 0; i < amount; ++i) {
					if (array[i] == element)
						++count;
				}
				auto end = chrono::steady_clock::now(); /*Конец отсчёта - сравнение с последним элементом массива*/
				searchSpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()); /*Скорость - время, затраченное на поиск подходящих элементов в массиве*/
				if (count == 0) {
					cout << "В массиве нет таких элементов." << endl;
					fallBack();
					return array;
				}
				else {
					int *positions = 0;
					positions = new int[count];
					for (int i = 0, j = 0; i < amount; ++i) {
						if (array[i] == element) {
							positions[j] = i;
							++j;
						}
					}
					cout << "Ваш динамический массив:" << endl;
					for (int i = 0, j = 0; i < amount; ++i) {
						if (i == positions[j]) {
							SetConsoleTextAttribute(textColour, 11);
							cout << i << ". " << array[i] << endl;
							SetConsoleTextAttribute(textColour, 7);
						}
						else
							cout << i << ". " << array[i] << endl;
						if (i > positions[j])
							++j;
					}
					fallBack();
					return array;
				}
			}
			break;
		}
		case 2: {
			return array;
			break;
		}
		}
		break;
	}
	case 2: { /*Удаление элемента*/
		short erasingOption = findEraseMenu(1);
		switch (erasingOption) {
		case 0: { /*Удаление по индексу*/
			system("cls");
			if (array == 0)
				cout << "Нет массива." << endl;
			else if (amount == 0)
				cout << "В массиве нет элементов, нечего удалять." << endl;
			else {
				cout << "Ваш массив:" << endl;
				for (int i = 0; i < amount; ++i)
					cout << i << ". " << array[i] << endl;
				cout << "Введите индекс удаляемого элемента (от 0 до " << amount - 1 << "): ";
				showConsoleCursor(true);
				int index = getIndex(amount);
				showConsoleCursor(false);
				--amount;
				int *temp = 0;
				auto begin = chrono::steady_clock::now(); /*Начало отсчёта - выделение памяти под динамический массив*/
				temp = new int[amount];
				for (int i = 0; i < index; ++i)
					temp[i] = array[i];
				for (int i = index + 1; i < amount + 1; ++i)
					temp[i - 1] = array[i];
				auto end = chrono::steady_clock::now(); /*Конец отсчёта - добавление последнего элемента в массив*/
				erasingSpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()); /*Скорость - время, затраченное на создание динамического массива*/
				if (amount == 0)
					cout << "В массиве не осталось элементов.";
				else {
					cout << "Ваш динамический массив:" << endl;
					for (int i = 0; i < amount; ++i) {
						if (i == index || i == index - 1) {
							SetConsoleTextAttribute(textColour, 12);
							cout << i << ". " << temp[i] << endl;
							SetConsoleTextAttribute(textColour, 7);
						}
						else
							cout << i << ". " << temp[i] << endl;
					}
				}
				cout << endl;
				delete[] array;
				array = new int[amount];
				for (int i = 0; i < amount; ++i)
					array[i] = temp[i];
				fallBack();
				return array;
			}
			break;
		}
		case 1: { /*Удаление по значению*/
			system("cls");
			if (array == 0)
				cout << "Нет массива." << endl;
			else if (amount == 0)
				cout << "В массиве нет элементов." << endl;
			else {
				cout << "Ваш массив:" << endl;
				for (int i = 0; i < amount; ++i)
					cout << i << ". " << array[i] << endl;
				int *temp = 0;
				string input;
				showConsoleCursor(true);
				bool bad = 0;
				int element = getElement(input, bad, 0);
				showConsoleCursor(false);
				int count = 0;
				for (int i = 0; i < amount; ++i) {
					if (array[i] == element)
						++count;
				}
				if (count == 0) {
					cout << "В массиве нет таких элементов." << endl;
					fallBack();
					return array;
				}
				else {
					int *positions = 0, *temp = 0;
					positions = new int[count];
					for (int i = 0, j = 0; i < amount, j < count; ++i) {
						if (array[i] == element) {
							positions[j] = i;
							++j;
						}
					}
					int i = 0, j = 0, k = 0;
					auto begin = chrono::steady_clock::now(); /*Начало отсчёта - выделение памяти под динамический массив*/
					temp = new int[amount - count];
					while (j != count) {
						for (i, k; i < positions[j]; ++i, ++k)
							temp[k] = array[i];
						++i;
						++j;
					}
					for (i, k; i < amount; ++i, ++k) {
						temp[k] = array[i];
					}
					auto end = chrono::steady_clock::now(); /*Конец отсчёта - добавление последнего элемента в массив*/
					erasingSpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()); /*Скорость - время, затраченное на создание динамического массива*/
					if (amount == 0)
						cout << "В массиве не осталось элементов.";
					else {
						cout << "Ваш динамический массив:" << endl;
						for (int d = 0, j = 0; d < amount - count; ++d) {
							if (d == positions[j] || d == positions[j] - 1) {
								SetConsoleTextAttribute(textColour, 12);
								cout << d << ". " << temp[d] << endl;
								SetConsoleTextAttribute(textColour, 7);
							}
							else
								cout << d << ". " << temp[d] << endl;
							if (d > positions[j])
								++j;
						}
					}
					cout << endl;
					delete[] array;
					array = new int[amount];
					for (int i = 0; i < amount; ++i)
						array[i] = temp[i];
					fallBack();
					return array;
				}
			}
			break;
		}
		case 2: {
			return array;
			break;
		}
		}
		break;
	}
	case 3: {
		return array;
		break;
	}
	}
	fallBack();
	return array;
}

void addFindEraseSpeed(int *&array, dLL *& list, long int &addingArraySpeed, long int &searchArraySpeed, long int &erasingArraySpeed, long int &addingListSpeed, long int &searchListSpeed, long int &erasingListSpeed, bool type) {
	if (type == 0) {
		if (array == 0) {
			cout << "Нет массива." << endl;
		}
		else if (addingArraySpeed == -1 && searchArraySpeed == -1 && erasingArraySpeed == -1) {
			cout << "В массив не добавлялся элемент. \nВ массиве не удалялся элемент. \nПоиск элемента не производился." << endl;
		}
		else {
			if (addingArraySpeed == -1)
				cout << "В массив не добавлялся элемент." << endl;
			else
				cout << "Время, затраченное на добавление элемента: " << addingArraySpeed << " наносекунд." << endl;
			if (erasingArraySpeed == -1)
				cout << "В массиве не удалялся элемент." << endl;
			else
				cout << "Время, затраченное на удаление элемента: " << erasingArraySpeed << " наносекунд." << endl;
			if (searchArraySpeed == -1)
				cout << "Поиск элемента не производился." << endl;
			else
				cout << "Время, затраченное на поиск элемента: " << searchArraySpeed << " наносекунд." << endl;
		}
	}
	else {
		if (list == 0) {
			cout << "Нет списка." << endl;
		}
		else if (addingListSpeed == -1 && searchListSpeed == -1 && erasingListSpeed == -1) {
			cout << "В список не добавлялся элемент. \nВ списке не удалялся элемент. \nПоиск элемента не производился." << endl;
		}
		else {
			if (addingListSpeed == -1)
				cout << "В список не добавлялся элемент." << endl;
			else
				cout << "Время, затраченное на добавление элемента: " << addingListSpeed << " наносекунд." << endl;
			if (erasingListSpeed == -1)
				cout << "В списке не удалялся элемент." << endl;
			else
				cout << "Время, затраченное на удаление элемента: " << erasingListSpeed << " наносекунд." << endl;
			if (searchListSpeed == -1)
				cout << "Поиск элемента не производился." << endl;
			else
				cout << "Время, затраченное на поиск элемента: " << searchListSpeed << " наносекунд." << endl;
		}
	}
	fallBack();
} /*Показать время, затраченное на вставку/поиск/удаление элемента*/

short listMenu() {
	short key = 0;
	int code = 0;
	do {
		system("cls");
		showConsoleCursor(false);
		key = (key + 4) % 4;
		if (key == 0)
			draw(">Сгенерировать двусвязный список автоматически");
		else
			cout << "Сгенерировать двусвязный список автоматически" << endl;
		if (key == 1)
			draw(">Ввести элементы двусвязного списка вручную");
		else
			cout << "Ввести элементы двусвязного списка вручную" << endl;
		if (key == 2)
			draw(">Считать двусвязный список с файла");
		else
			cout << "Считать двусвязный список с файла" << endl;
		if (key == 3)
			draw(">Назад");
		else
			cout << "Назад" << endl;
		if (code != 13) {
			code = _getch();
			if (code == 80 || code == 115)
				++key;
			if (code == 72 || code == 119)
				--key;
		}
	} while (code != 13);
	system("cls");
	return key;
} /*Меню для массива, управление - стрелки вверх и вниз, а также клавиши w и s*/

dLL*& initializeList(dLL *&list, int value, bool parameter) {
	list = new dLL;
	if (parameter == 1)
		list->data = value;
	else
		list->data = rand() % 100;
	list->next = 0;
	list->prev = 0;
	return list;
} /*Создание первого узла двусвязного списка*/

void deleteList(dLL **head, dLL *item, int &amount) {
	if (*head == 0 || item == 0)
		return;
	if (*head == item)
		*head = item->next;
	if (item->next != 0)
		item->next->prev = item->prev;
	if (item->prev != 0)
		item->prev->next = item->next;
	free(item);
	--amount;
	return;
} /*Удаление двусвязного списка*/

void addAtEnd(dLL **head, int value, short parameter) {
	dLL *temp = initializeList(temp, value, parameter);
	if (*head == 0) {
		*head = temp;
		return;
	}
	dLL *travel = *head;
	while (travel->next != 0)
		travel = travel->next;
	travel->next = temp;
	temp->prev = travel;
} /*Добавление узла в конец двусвязного списка*/

void addAtFront(dLL **head, int value, short parameter) {
	dLL *temp = initializeList(temp, value, parameter);
	if (*head == 0) {
		*head = temp;
		return;
	}
	dLL *travel = *head;
	temp->next = travel;
	travel->prev = temp;
	*head = temp;
} /*Добавление узла в начало двусвязного списка*/

void displayList(dLL *head, int &amount, int index) {
	if (amount == 0) {
		cout << "В списке нет элементов.";
		return;
	}
	else if (head == 0) {
		cout << "Списка нет.";
		return;
	}
	else {
		cout << "Ваш двусвязный список:" << endl;
		while (head != 0) {
			cout << index << ". " << head->data << endl;
			head = head->next;
			++index;
		}
	}
} /*Отображение двусвязного списка*/

void createList(dLL *&list, int &amount, long int &speed, short &method, int &amountCreated) {
	short listOption = listMenu();
	switch (listOption) {
	case 0: {
		deleteList(&list, list, amount);
		system("cls");
		cout << "Введите размерность двусвязного списка: ";
		showConsoleCursor(true);
		amount = getAmount();
		showConsoleCursor(false);
		auto begin = chrono::steady_clock::now();
		list = initializeList(list, 0, 0);
		for (int i = 1; i < amount; ++i)
			addAtEnd(&list, 0, 0);
		auto end = chrono::steady_clock::now();
		speed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count());
		method = 0;
		amountCreated = amount;
		displayList(list, amount, 0);
		break;
	}
	case 1: {
		system("cls");
		cout << "Введите через пробел значения целочисленного двусвязного списка:" << endl;
		string input;
		bool bad = 0;
		showConsoleCursor(true);
		getline(cin, input);
		check(input, bad, 0);
		if (bad == 0) {
			deleteList(&list, list, amount);
			amount = 0;
			unsigned int i = 0;
			while (int(input[i]) != 0) {
				while (int(input[i]) != 32 && int(input[i]) != 0)
					++i;
				++amount;
				if (int(input[i]) == 0)
					break;
				++i;
			}
			
			string::size_type size;
			auto begin = chrono::steady_clock::now();
			list = initializeList(list, stoi(input, &size), 1);
			input = input.substr(size);
			for (int i = 1; i < amount; ++i) {
				addAtFront(&list, stoi(input, &size), 1);
				input = input.substr(size);
			}
			auto end = chrono::steady_clock::now();
			speed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count());
			amountCreated = amount;
			method = 1;
			displayList(list, amount, 0);
		}
		else
			cout << "Двусвязный список не был создан." << endl;
		break;
	}
	case 2: {
		system("cls");
		amount = 0;
		ifstream file("input.txt");
		if (file.is_open()) {
			string input;
			bool bad = 0;
			getline(file, input, '\0');
			check(input, bad, 0);
			if (input.length() == 0)
				bad = 1;
			if (bad == 0) {
				deleteList(&list, list, amount);
				file.seekg(0, ios::beg);
				file.clear();
				int temp;
				while (!file.eof()) {
					file >> temp;
					++amount;
				}
				file.seekg(0, ios::beg);
				file.clear();
				int i = 0, value;
				auto begin = chrono::steady_clock::now();
				while (i != 1) {
					file >> value;
					++i;
				}
				list = initializeList(list, value, 1);
				while (!file.eof()) {
					file >> value;
					addAtEnd(&list, value, 1);
				}
				auto end = chrono::steady_clock::now();
				file.close();
				speed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count());
				amountCreated = amount;
				method = 2;
				displayList(list, amount, 0);
			}
			else
				cout << "Двусвязный список не был создан. Проверьте содержание файла input.txt.";
		}
		else {
			cout << "Файл с именем 'input.txt' не найден." << endl << endl;
		}
		break;
	}
	case 3: {
		return;
		break;
	}
	}
	fallBack();
	return;
} /*Создание двусвязного списка*/

void oddEven(int *array, dLL *list, int &arrayAmount, int &listAmount) {
	if (array == 0)
		cout << "Нужно создать динамический массив.";
	else if (list == 0)
		cout << "Нужно создать двусвязный список.";
	else if (arrayAmount != listAmount)
		cout << "Нужно, чтобы количество элементов в двусвязном списке и динамическом массиве совпадали.";
	else {
		int amountOddArray = 0, amountEvenArray = 0, amountOddList = 0, amountEvenList = 0;
		long int speedArray, speedList;
		auto begin = chrono::steady_clock::now();
		for (int i = 0; i < arrayAmount; ++i) {
			if (i % 2 == 0 && array[i] % 2 == 0)
				++amountEvenArray;
			else if (i % 2 == 1 && array[i] % 2 == 1)
				++amountOddArray;
		}
		auto end = chrono::steady_clock::now();
		speedArray = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count());
		auto start = chrono::steady_clock::now();
		for (int i = 0; i < listAmount; ++i) {
			if (i % 2 == 0 && list->data % 2 == 0)
				++amountEvenList;
			else if (i % 2 == 1 && list->data % 2 == 1)
				++amountOddList;
			if (list->next == 0)
				break;
			list = list->next;
		}
		auto fin = chrono::steady_clock::now();
		speedList = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(fin - start).count());
		int k = 1, j = 1;
		cout << "Динамический массив, где зелёным цветом помечены чётные элементы, имеющие чётный индекс, а бирюзовым - нечётные элементы, имеющие нечётный индекс: " << endl;
		short indexShift, valueShift;
		for (int i = 0; i < arrayAmount; ++i) {
			indexShift = 0, valueShift = 0;
			if (i % 2 == 0 && array[i] % 2 == 0) {
				SetConsoleTextAttribute(textColour, 10);
				cout << i << ". " << array[i];
				if (i >= 10 && i < 100)
					--indexShift;
				else if (i >= 100 && i < 1000)
					indexShift -= 2;
				else if (i >= 1000 && i < 10000)
					indexShift -= 3;
				if (abs(array[i]) >= 10 && abs(array[i]) < 100)
					--valueShift;
				else if (abs(array[i]) >= 100 && abs(array[i]) < 1000)
					valueShift -= 2;
				else if (abs(array[i]) >= 1000 && abs(array[i]) < 10000)
					valueShift -= 3;
				cout.width(30 + indexShift + valueShift);
				cout << right << k << endl;
				SetConsoleTextAttribute(textColour, 7);
				++k;
			}
			else if (i % 2 == 1 && array[i] % 2 == 1) {
				SetConsoleTextAttribute(textColour, 11);
				cout << i << ". " << array[i];
				if (i >= 10 && i < 100)
					--indexShift;
				else if (i >= 100 && i < 1000)
					indexShift -= 2;
				else if (i >= 1000 && i < 10000)
					indexShift -= 3;
				if (abs(array[i]) >= 10 && abs(array[i]) < 100)
					--valueShift;
				else if (abs(array[i]) >= 100 && abs(array[i]) < 1000)
					valueShift -= 2;
				else if (abs(array[i]) >= 1000 && abs(array[i]) < 10000)
					valueShift -= 3;
				cout.width(30 + indexShift + valueShift);
				cout << right << j << endl;
				SetConsoleTextAttribute(textColour, 7);
				++j;
			}
			else
				cout << i << ". " << array[i] << " " << endl;
		}
		j = 1, k = 1;
		cout << "\nДвусвязный список, где зелёным цветом помечены чётные элементы, имеющие чётный индекс, а бирюзовым - нечётные элементы, имеющие нечётный индекс: " << endl;
		while (list->prev != 0)
			list = list->prev;
		for (int i = 0; i < arrayAmount; ++i) {
			indexShift = 0, valueShift = 0;
			if (i % 2 == 0 && list->data % 2 == 0) {
				SetConsoleTextAttribute(textColour, 10);
				cout << i << ". " << list->data;
				if (i >= 10 && i < 100)
					--indexShift;
				else if (i >= 100 && i < 1000)
					indexShift -= 2;
				else if (i >= 1000 && i < 10000)
					indexShift -= 3;
				if (abs(list->data) >= 10 && abs(list->data) < 100)
					--valueShift;
				else if (abs(list->data) >= 100 && abs(list->data) < 1000)
					valueShift -= 2;
				else if (abs(list->data) >= 1000 && abs(list->data) < 10000)
					valueShift -= 3;
				cout.width(30 + indexShift + valueShift);
				cout << right << k << endl;
				SetConsoleTextAttribute(textColour, 7);
				++k;
			}
			else if (i % 2 == 1 && list->data % 2 == 1) {
				SetConsoleTextAttribute(textColour, 11);
				cout << i << ". " << list->data;
				if (i >= 10 && i < 100)
					--indexShift;
				else if (i >= 100 && i < 1000)
					indexShift -= 2;
				else if (i >= 1000 && i < 10000)
					indexShift -= 3;
				if (abs(list->data) >= 10 && abs(list->data) < 100)
					--valueShift;
				else if (abs(list->data) >= 100 && abs(list->data) < 1000)
					valueShift -= 2;
				else if (abs(list->data) >= 1000 && abs(list->data) < 10000)
					valueShift -= 3;
				cout.width(30 + indexShift + valueShift);
				cout << right << j << endl;
				SetConsoleTextAttribute(textColour, 7);
				++j;
			}
			else
				cout << i << ". " << list->data << " " << endl;
			if (list->next == 0)
				break;
			list = list->next;
		}
		cout << "\nДинамический массив и двусвязный список на " << arrayAmount << " элементов." << endl << endl;
		cout << "Динамический массив. \nКоличество чётных элементов, которые имеют чётные значения: " << amountEvenArray << ". \nКоличество нечётных элементов, которые имеют нечётные значения: " << amountOddArray << "." <<endl;
		cout << "Скорость выполнения поиска таких элементов в динамическом массиве: " << speedArray << " наносекунд." << endl;
		cout << "\nДвусвязный список. \nКоличество чётных элементов, которые имеют чётные значения: " << amountEvenList << ". \nКоличество нечётных элементов, которые имеют нечётные значения: " << amountOddList << "." << endl;
		cout << "Скорость выполнения поиска таких элементов в двусвязном списке: " << speedList << " наносекунд." << endl;
	}
	fallBack();
	return;
} /*Нахождение количества чётных элементов, имеющих чётный индекс, и нечётных элементов, имеющих нечётный индекс. Сравнение скорости работы двусвязного списка и динамического массива.*/

#endif