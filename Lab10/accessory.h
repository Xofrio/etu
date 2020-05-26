#define NOMINMAX

#include <conio.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <Windows.h>

using namespace std::chrono;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::queue;
using std::string;
using std::vector;

class Tree {
public:
	short data;
	int height, count;
	Tree* left, * right;
};

void draw(string str) { // Прорисовка цветных пунктов, т.е. тех, которые выбраны в данный момент
	HANDLE descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(descriptor, 14);
	cout << str << endl;
	SetConsoleTextAttribute(descriptor, 7);
}

void showConsoleCursor(bool showFlag) { // Отмена мигающего подчёркивания (для выбора в меню)
	HANDLE descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(descriptor, &cursorInfo);
	cursorInfo.bVisible = showFlag; // Установка видимости курсора
	SetConsoleCursorInfo(descriptor, &cursorInfo);
}

void fallBack() { // Отобразить одиночный пункт "Назад" после какого-либо ввода/выбора действия
	cout << endl;
	draw(">Назад");
	short code = 0;
	do
		code = _getch();
	while (code != 13);
}

short menu() { // Меню, управление - стрелки вверх и вниз, а также клавиши w и s
	short key = 0, code = 0;
	do {
		system("cls");
		key = (key + 6) % 6;
		if (key == 0)
			draw(">Создать AVL дерево");
		else
			cout << "Создать AVL дерево" << endl;
		if (key == 1)
			draw(">Вывести в консоль и файл AVL дерево");
		else
			cout << "Вывести в консоль и файл AVL дерево" << endl;
		if (key == 2)
			draw(">Вставить, найти или удалить элемент в AVL дереве");
		else
			cout << "Вставить, найти или удалить элемент в AVL дереве" << endl;
		if (key == 3)
			draw(">Проверить на сбалансированность AVL дерево");
		else
			cout << "Проверить на сбалансированность AVL дерево" << endl;
		if (key == 4)
			draw(">Создать ещё одно дерево той же размерности, заполненное случайными числами [-99...99], и соединить их");
		else
			cout << "Создать ещё одно дерево той же размерности, заполненное случайными числами [-99...99], и соединить их" << endl;
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
	} 
	while (code != 13);
	system("cls");
	return key;
}

short methodMenu() { // Меню выбора метода создания AVL дерева, управление - стрелки вверх и вниз, а также клавиши w и s
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

short actionMenu() { // Меню выбора действия с AVL деревом, управление - стрелки вверх и вниз, а также клавиши w и s
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

int getAmount() { // Получить количество элементов дерева при его генерации
	while (true) {
		string input;
		bool bad = 0;
		getline(cin, input);
		if (input.length() > 0 && input.length() < 11) {
			for (unsigned int i = 0; i < input.length(); ++i) {
				if (int(input[i]) < 48 || int(input[i]) > 57) { // Если символ входящей строки не [0...9] - устанавливается флаг
					bad = 1;
					break;
				}
			}
			if (int(input[0]) == 48) // Количество элементов не должно начинаться с незначащего нуля и не должно равняться нулю
				bad = 1;
		}
		if (input.length() == 0 || cin.fail() || bad == 1 || input.length() > 10) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Введите размерность: ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return stoi(input);
		}
	}
}

short getElement() {
	while (true) {
		string input;
		bool bad = 0;
		getline(cin, input);
		if (input.length() > 0 && input.length() < 4) {
			for (unsigned int i = 0; i < input.length(); ++i) {
				if (!isdigit(input[i]) && int(input[i]) != 45) { // Если символ входящей строки не '-' или не лежит в диапазоне [0...9]  - устанавливается флаг
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
			return stoi(input);
		}
	}
}

void checkString(string& input, int& amount, bool& bad) { // Проверка строки на наличие целых чисел в диапазоне [-99...99]
	if (input.length() == 0)
		bad = 1;
	int number;
	for (unsigned int i = 0; i < input.length(); ++i) {
		if ((input[i] < '0' && input[i] > '9') && (int(input[i]) != 32 || int(input[i]) != 45)) {
			bad = 1;
			break;
		}
		else if (!isdigit(input[0]) && (int(input[0]) == 45 && !isdigit(input[1]))) { // Строка должна начинаться с цифры, либо с унарного минуса, за которым следует цифра
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
				if (number > 99) { // Сравнение числа с 99 (унарный минус в сравнении не учитывается)
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

string getValues(int& amount) { // Запись последовательности целых чисел на числа в диапазоне [-99...99] и проверка на то, что они таковыми являются
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

void printTree(Tree* root, int space, int value, short right, bool mode) { // Отображение AVL дерева в консоли
	if (root == 0)
		return;
	space += 3; // Расстояние между уровнями
	printTree(root->right, space, value, 1, mode); // Правая ветвь
	for (int i = 3; i < space; ++i)
		cout << " ";
	if (right == 1) // Если правая - точка
		cout << ".";
	else if (right == 0) // Если левая - тильда
		cout << '`';
	cout << "-->";
	HANDLE descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
	if (value == root->data && mode == 1)
		SetConsoleTextAttribute(descriptor, 13);
	if (root->count > 1)
		cout << root->data << "(" << root->count << ")" << "\n";
	else
		cout << root->data << "\n";
	SetConsoleTextAttribute(descriptor, 7);
	printTree(root->left, space, value, 0, mode); // Левая ветвь
}

void outputTree(ofstream& file, Tree* root, int space, short right) { // Отображение AVL дерева в файле
	if (root == 0)
		return;
	space += 3; // Увеличиваем расстояние между уровнями
	outputTree(file, root->right, space, 1); // Правая ветвь
	for (int i = 3; i < space; ++i)
		file << " ";
	if (right == 1) // Если правая - точка
		file << ".";
	else if (right == 0) // Если левая - тильда
		file << '`';
	if (root->count > 1)
		file <<  "-->" << root->data << "(" << root->count << ")" << "\n";
	else
		file << "-->" << root->data << "\n";
	outputTree(file, root->left, space, 0); // Левая ветвь
}

void representTree(Tree* root) { // Отобразить AVL дерево в консоли и записать его в файл
	if (root != 0) {
		printTree(root, 0, 0, 2, 0);
		ofstream file;
		file.open("C:\\AVL_tree.txt");
		outputTree(file, root, 0, 2);
		file.close();
		cout << endl << "AVL дерево записано в С:\\AVL_tree.txt." << endl;
	}
	else
		cout << "В дереве нет элементов.";
	fallBack();
}
