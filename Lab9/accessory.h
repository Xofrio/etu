#define NOMINMAX

#include <conio.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <Windows.h>

using namespace std;

HANDLE textColour = GetStdHandle(STD_OUTPUT_HANDLE);

struct branch { //Структура одной ветви
	short data;
	branch *left, *right;
};

struct dLL { //Структура двусвязного списка
	short data;
	dLL *next, *prev;
};

void draw(string str) { //Прорисовка цветных пунктов, т.е. тех, которые выбраны в данный момент
	SetConsoleTextAttribute(textColour, 14);
	cout << str << endl;
	SetConsoleTextAttribute(textColour, 7);
}

void showConsoleCursor(bool showFlag) { //Отмена мигающего подчёркивания (для выбора в меню)
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; //Установка видимости курсора
	SetConsoleCursorInfo(out, &cursorInfo);
}

void fallBack() { //Отобразить одиночный пункт "Назад" после какого-либо ввода/выбора действия
	cout << endl;
	draw(">Назад");
	int code = 0;
	do {
		code = _getch();
	} while (code != 13);
}

short menu() { //Меню, управление - стрелки вверх и вниз, а также клавиши w и s
	short key = 0, code = 0;
	do {
		system("cls");
		key = (key + 6) % 6;
		if (key == 0)
			draw(">Создать бинарное дерево");
		else
			cout << "Создать бинарное дерево" << endl;
		if (key == 1)
			draw(">Вывести в консоль и файл бинарное дерево");
		else
			cout << "Вывести в консоль и файл бинарное дерево" << endl;
		if (key == 2)
			draw(">Вставить, найти или удалить элемент в бинарном дереве");
		else
			cout << "Вставить, найти или удалить элемент в бинарном дереве" << endl;
		if (key == 3)
			draw(">Прямой обход, обратный обход, обход в ширину бинарного дерева");
		else
			cout << "Прямой обход, обратный обход, обход в ширину бинарного дерева" << endl;
		if (key == 4)
			draw(">Удалить все отрицательные элементы, каждый элемент умножить на случайную величину [-2...2]");
		else
			cout << "Удалить все отрицательные элементы, каждый элемент умножить на случайную величину [-2...2]" << endl;
		if (key == 5)
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
}

short methodMenu() { //Меню выбора метода создания бинарного дерева, управление - стрелки вверх и вниз, а также клавиши w и s
	short key = 0, code = 0;
	do {
		system("cls");
		key = (key + 4) % 4;
		if (key == 0)
			draw(">Сгенерировать автоматически");
		else
			cout << "Сгенерировать автоматически" << endl;
		if (key == 1)
			draw(">Считать значения с клавиатуры");
		else
			cout << "Считать значения с клавиатуры" << endl;
		if (key == 2)
			draw(">Считать значения с файла");
		else
			cout << "Считать значения с файла" << endl;
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
}

short actionMenu() { //Меню выбора действия с бинарным деревом, управление - стрелки вверх и вниз, а также клавиши w и s
	short key = 0, code = 0;
	do {
		system("cls");
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
}

int getAmount() { //Получить количество элементов дерева при его генерации
	while (true) {
		string input;
		int output;
		bool bad = 0;
		getline(cin, input);
		if (input.length() > 0 && input.length() < 11) {
			for (unsigned int i = 0; i < input.length(); ++i) {
				if (int(input[i]) < 48 || int(input[i]) > 57) { //Если символ входящей строки не [0...9] - устанавливается флаг
					bad = 1;
					break;
				}
			}
			if (int(input[0]) == 48) //Количество элементов не должно начинаться с незначащего нуля и не должно равняться нулю
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
}

short getElement() {
	while (true) {
		string input;
		short output;
		bool bad = 0;
		getline(cin, input);
		if (input.length() > 0 && input.length() < 4) {
			for (unsigned int i = 0; i < input.length(); ++i) {
				if (!isdigit(input[i]) && int(input[i]) != 45) { //Если символ входящей строки не '-' или не лежит в диапазоне [0...9]  - устанавливается флаг
					bad = 1;
					break;
				}
				else if (input[i] == '0' && isdigit(input[i + 1])) {
					bad = 1;
					break;
				}
				else if (isdigit(input[i] || input[i] == '-' && isdigit(input[i + 1]))) {
					while (isdigit(input[i + 1])) {
						++i;
					}
					if (i != input.length() - 1) {
						bad = 1;
						break;
					}
				}
			}
		}
		if (input.length() == 0 || cin.fail() || bad == 1 || input.length() > 3 || abs(stoi(input)) > 99) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Введите значение искомого элемента в диапазоне [-99...99]: ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return output = stoi(input);
		}
	}
}

void checkString(string &input, int &amount, bool &bad) { //Проверка строки на наличие целых чисел в диапазоне [-99...99]
	if (input.length() == 0)
		bad = 1;
	int number;
	for (unsigned int i = 0; i < input.length(); ++i) {
		if ((input[i] < '0' && input[i] > '9') && (int(input[i]) != 32 || int(input[i]) != 45)) {
			bad = 1;
			break;
		}
		else if (!isdigit(input[0]) && (int(input[0]) == 45 && !isdigit(input[1]))) { //Строка должна начинаться с цифры, либо с унарного минуса, за которым следует цифра
			bad = 1;
			break;
		}
		else if (input[0] == '0' && isdigit(input[1]) || input[i] == '-' && input[i + 1] == '0' || i != 0 && input[i] == 0 && input[i - 1] == ' ' && isdigit(input[i + 1])) { //Незначащих нулей быть не должно
			bad = 1;
			break;
		}
		else if (isdigit(input[i]) || input[i] == '-' && isdigit(input[i + 1])) {
			if (input[i] == '-')
				++i;
			number = 0;
			while (isdigit(input[i + 1])) {
				number = number * 10 + input[i] - 0x30;
				if (number > 99) { //Сравнение числа с 99 (унарный минус в сравнении не учитывается)
					bad = 1;
					break;
				}
				++i;
			}
			number = 0;
			if (i != input.length() - 1 && input[i + 1] != ' ') {
				bad = 1;
				break;
			}
		}
		else if (input[i] == ' ')
			++amount;
	}
	++amount;
}

string getValues(int &amount) { //Запись последовательности целых чисел на числа в диапазоне [-99...99] и проверка на то, что они таковыми являются
	while (true) {
		string input;
		bool bad = 0;
		getline(cin, input);
		checkString(input, amount, bad);
		if (cin.fail() || bad == 1) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			amount = 0;
			cout << "Введите через пробел целые числа в диапазоне [-99...99]: ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return input;
		}
	}
}
