#include <conio.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

HANDLE textColour = GetStdHandle(STD_OUTPUT_HANDLE);

#ifndef FUNC_H
#define FUNC_H

void showConsoleCursor(bool showFlag) { //Отмена мигающего подчёркивания (для выбора в меню)
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; //Установка видимости курсора
	SetConsoleCursorInfo(out, &cursorInfo);
}

void draw(string str) { //Прорисовка цветных пунктов, т.е. тех, которые выбраны в данный момент
	SetConsoleTextAttribute(textColour, 14);
	cout << str << endl;
	SetConsoleTextAttribute(textColour, 7);
}

short menu() { //Меню, управление - стрелки вверх и вниз, а также клавиши w и s
	short key = 0, code = 0;
	do {
		system("cls");
		showConsoleCursor(false);
		key = (key + 6) % 6;
		if (key == 0)
			draw(">Преобразовать выражение");
		else
			cout << "Преобразовать выражение" << endl;
		if (key == 1)
			draw(">Проверка на корректность введённого выражения");
		else
			cout << "Проверка на корректность введённого выражения" << endl;
		if (key == 2)
			draw(">Вычисление выражения");
		else
			cout << "Вычисление выражения" << endl;
		if (key == 3)
			draw(">Сгенерировать несколько вариантов проверки");
		else
			cout << "Сгенерировать несколько вариантов проверки" << endl;
		if (key == 4)
			draw(">Буфер клавиатуры");
		else
			cout << "Буфер клавиатуры" << endl;
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

short inputMenu() { //Меню выбора клавиатура/файл, управление - стрелки вверх и вниз, а также клавиши w и s
	short key = 0, code = 0;
	do {
		system("cls");
		showConsoleCursor(false);
		key = (key + 3) % 3;
		if (key == 0)
			draw(">Произвести ввод с клавиатуры");
		else
			cout << "Произвести ввод с клавиатуры" << endl;
		if (key == 1)
			draw(">Считать с файла");
		else
			cout << "Считать с файла" << endl;
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
}

short formMenu() { //Меню выбора формы записи выражения, управление - стрелки вверх и вниз, а также клавиши w и s
	short key = 0, code = 0;
	do {
		system("cls");
		showConsoleCursor(false);
		key = (key + 4) % 4;
		if (key == 0)
			draw(">Инфиксная форма");
		else
			cout << "Инфиксная форма" << endl;
		if (key == 1)
			draw(">ПН");
		else
			cout << "ПН" << endl;
		if (key == 2)
			draw(">ОПН");
		else
			cout << "ОПН" << endl;
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

void fallBack() { //Отобразить одиночный пункт "Назад" после какого-либо ввода/выбора действия
	cout << endl;
	draw(">Назад");
	int code = 0;
	do {
		code = _getch();
	} while (code != 13);
}

void checkString(string &input, bool &bad) { //Проверка строки на наличие допустимых символов, коими считаются [0..9], [a..z], [()+-*/^]
	if (input.length() == 0)
		bad = 1;
	for (unsigned int i = 0; i < input.length(); ++i) {
		if (((input[i] < '0' && input[i] > '9') || (input[i] < 'a' && input[i] > 'z') || (int(input[i]) < 40 && int(input[i]) > 43)) && (int(input[i]) != 45 || int(input[i]) != 47)) {
			bad = 1;
			break;
		}
	}
}

void checkValue(string &input, bool &bad) { //Проверка значения на наличие только цифр
	if (input.length() == 0)
		bad = 1;
	for (unsigned int i = 0; i < input.length(); ++i) {
		if (input[i] < '0' && input[i] > '9') {
			bad = 1;
			break;
		}
		else if (input[0] == '0' && isdigit(input[1])) { //Незначащий ноль в записи не предусмотрен
			bad = 1;
			break;
		}
	}
}

struct letters { //Создание структуры для переменных
	char letter;
	bool exists;
	int value;
};

int getElement(bool &bad, char letter) { //Получение значения переменной
	string input;
	while (true) {
		cout << "Введите значение переменной '" << letter << "': ";
		getline(cin, input);
		checkValue(input, bad);
		if (bad == 1) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Введите значение переменной'" << letter << "': ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return stoi(input);
		}
	}
}

void reroll(letters alphabet[]) { //Обнуление существования переменных
	for (int i = 0; i < 26; ++i)
		alphabet[i].exists = 0;
}

string swapVariables(letters alphabet[], string inputInfix, string inputPN, string inputRPN) { //Определение наличия переменных и задание им значений
	string input;
	if (inputPN.length() > 0 && inputRPN.length() > 0)
		input = inputPN;
	else if (inputPN.length() != 0)
		input = inputPN;
	else if (inputRPN.length() != 0)
		input = inputRPN;
	else if (inputInfix.length() != 0)
		input = inputInfix;
	for (unsigned int i = 0; i < input.length(); ++i) { //Проверка наличия переменной в строке
		if (input[i] == alphabet[0].letter)
			alphabet[0].exists = 1;
		else if (input[i] == alphabet[1].letter)
			alphabet[1].exists = 1;
		else if (input[i] == alphabet[2].letter)
			alphabet[2].exists = 1;
		else if (input[i] == alphabet[3].letter)
			alphabet[3].exists = 1;
		else if (input[i] == alphabet[4].letter)
			alphabet[4].exists = 1;
		else if (input[i] == alphabet[5].letter)
			alphabet[5].exists = 1;
		else if (input[i] == alphabet[6].letter)
			alphabet[6].exists = 1;
		else if (input[i] == alphabet[7].letter)
			alphabet[7].exists = 1;
		else if (input[i] == alphabet[8].letter)
			alphabet[8].exists = 1;
		else if (input[i] == alphabet[9].letter)
			alphabet[9].exists = 1;
		else if (input[i] == alphabet[10].letter)
			alphabet[10].exists = 1;
		else if (input[i] == alphabet[11].letter)
			alphabet[11].exists = 1;
		else if (input[i] == alphabet[12].letter)
			alphabet[12].exists = 1;
		else if (input[i] == alphabet[13].letter)
			alphabet[13].exists = 1;
		else if (input[i] == alphabet[14].letter)
			alphabet[14].exists = 1;
		else if (input[i] == alphabet[15].letter)
			alphabet[15].exists = 1;
		else if (input[i] == alphabet[16].letter)
			alphabet[16].exists = 1;
		else if (input[i] == alphabet[17].letter)
			alphabet[17].exists = 1;
		else if (input[i] == alphabet[18].letter)
			alphabet[18].exists = 1;
		else if (input[i] == alphabet[19].letter)
			alphabet[19].exists = 1;
		else if (input[i] == alphabet[20].letter)
			alphabet[20].exists = 1;
		else if (input[i] == alphabet[21].letter)
			alphabet[21].exists = 1;
		else if (input[i] == alphabet[22].letter)
			alphabet[22].exists = 1;
		else if (input[i] == alphabet[23].letter)
			alphabet[23].exists = 1;
		else if (input[i] == alphabet[24].letter)
			alphabet[24].exists = 1;
		else if (input[i] == alphabet[25].letter)
			alphabet[25].exists = 1;
	}
	for (int i = 0; i < 26; ++i) { //Задание переменным значения
		if (alphabet[i].exists == 1) {
			bool bad = 0;
			alphabet[i].value = getElement(bad, alphabet[i].letter);
		}
	}
	string  outputInfix, outputPN, outputRPN;
	unsigned int i = 0;
	bool doneInfix = 0, donePN = 0, doneRPN = 0;
	if (inputPN.length() > 0 && inputRPN.length() > 0) { //Замена переменных на соответстующие им значения для ПН и ОПН
		while (i != inputPN.length()) {
			if (!isalpha(inputPN[i]))
				outputPN.push_back(inputPN[i]);
			else {
				for (int j = 0; j < 26; ++j) {
					if (inputPN[i] == alphabet[j].letter) {
						outputPN += to_string(alphabet[j].value);
						donePN = 1;
					}
				}
			}
			++i;
		}
		i = 0;
		while (i != inputRPN.length()) {
			if (!isalpha(inputRPN[i]))
				outputRPN.push_back(inputRPN[i]);
			else {
				for (int j = 0; j < 26; ++j) {
					if (inputRPN[i] == alphabet[j].letter) {
						outputRPN += to_string(alphabet[j].value);
						doneRPN = 1;
					}
				}
			}
			++i;
		}
	}
	else if (inputPN.length() > 0) { //Замена переменных на соответстующие им значения для ПН
		while (i != inputPN.length()) {
			if (!isalpha(inputPN[i]))
				outputPN.push_back(inputPN[i]);
			else {
				for (int j = 0; j < 26; ++j) {
					if (inputPN[i] == alphabet[j].letter) {
						outputPN += to_string(alphabet[j].value);
						donePN = 1;
					}
				}
			}
			++i;
		}
	}
	else if (inputRPN.length() > 0) { //Замена переменных на соответстующие им значения для ОПН
		while (i != inputRPN.length()) {
			if (!isalpha(inputRPN[i]))
				outputRPN.push_back(inputRPN[i]);
			else {
				for (int j = 0; j < 26; ++j) {
					if (inputRPN[i] == alphabet[j].letter) {
						outputRPN += to_string(alphabet[j].value);
						doneRPN = 1;
					}
				}
			}
			++i;
		}
	}
	else if (inputInfix.length() > 0) { //Замена переменных на соответстующие им значения для инфиксной записи
		while (i != inputInfix.length()) {
			if (!isalpha(inputInfix[i]))
				outputInfix.push_back(inputInfix[i]);
			else {
				for (int j = 0; j < 26; ++j) {
					if (inputInfix[i] == alphabet[j].letter) {
						outputInfix += to_string(alphabet[j].value);
						doneInfix = 1;
					}
				}
			}
			++i;
		}
	}
	cout << endl;
	reroll(alphabet);
	if (donePN == 1 && doneRPN == 1) {
		cout << "Выражение в ПН, где переменные заменены на свои значения: " << outputPN << endl;
		cout << "Выражение в ОПН, где переменные заменены на свои значения: " << outputRPN << endl << endl;
	}
	else if (donePN == 1)
		cout << "Выражение в ПН, где переменные заменены на свои значения: " << outputPN << endl << endl; 
	else if (doneRPN == 1)
		cout << "Выражение в ОПН, где переменные заменены на свои значения: " << outputRPN << endl << endl;
	if (donePN == 1)
		return outputPN;
	else if (doneRPN == 1)
		return outputRPN;
	else if (doneInfix == 1)
		return outputInfix;
	else if (inputPN.length() > 0)
		return inputPN;
	else if (inputRPN.length() > 0)
		return inputRPN;
	else if (inputInfix.length() > 0)
		return inputInfix;
	return "0";
}

string getExpression() { //Запись выражения и проверка на некорректные символы
	while (true) {
		string input;
		bool bad = 0;
		getline(cin, input);
		checkString(input, bad);
		if (cin.fail() || bad == 1) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "Введите выражение, используя [0..9], [a..z], [()+-*/^]: ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return input;
		}
	}
}

int getOrder(char statement) { //Функция для определения порядка операторов
	if (statement == '^')
		return 3;
	else if (statement == '*' || statement == '/')
		return 2;
	else if (statement == '+' || statement == '-')
		return 1;
	return 0;
}

string infixToPN(string input) { //Функция перевода из инфиксной формы в ПН
	long int arrayPNConversionSpeed, stackPNConversionSpeed;
	stack <char> PNStack;
	string outputStack;
	auto begin = chrono::steady_clock::now();
	reverse(input.begin(), input.end()); //Реверсируем строку
	for (unsigned int i = 0; i < input.length(); ++i) { //Преобразование с помощью стека
		if (input[i] >= 'a' && input[i] <= 'z') { //Если текущий символ - операнд, то кладём его в строку вывода
			outputStack += input[i];
			outputStack += " ";
		}
		else if (isdigit(input[i])) { //Если текущий символ - число
			int number = 0;
			while (isdigit(input[i])) { //Пока следующий символ - тоже число
				number = number * 10 + (int)(input[i] - '0'); // Находим все его разряды
				++i;
			}
			--i;
			outputStack += to_string(number);
			outputStack += " ";
		}
		else if (input[i] == ')') //Если текущий символ - ')', то кладём в его в стек
			PNStack.push(')');
		else if (input[i] == '(') { //Если текущий символ - '(', то берём из стека всё, что идёт до ')', и помещаем в строку вывода
			while (!PNStack.empty() && PNStack.top() != ')') {
				outputStack += PNStack.top(); //Записываем в строку вывода верхний элемент стека
				PNStack.pop(); //Удаляем верхний элемент стека
				outputStack += " ";
			}
			if (PNStack.top() == ')')
				PNStack.pop();
		}
		else { //Если текущий символ - оператор
			while (!PNStack.empty() && getOrder(input[i]) < getOrder(PNStack.top()) && PNStack.top() != ')') { //Пока стек не пуст и порядок текущей операции меньше порядка операции, находящейся на вершине стека
				outputStack += PNStack.top();
				PNStack.pop();
				outputStack += " ";
			}
			if (input[i] == '-' && (i == input.length() - 1 || input[i + 1] == '(')) //Если это унарный минус (первая позиция в строке, либо после минуса стоит открывающая скобка)
				outputStack += "0 "; //Моя реализация унарного минуса
			PNStack.push(input[i]);
		}
	}
	while (!PNStack.empty()) { //В конце (при проходе всей строки) достаём из стека все оставшиеся элементы
		outputStack += PNStack.top();
		PNStack.pop();
		outputStack += " ";
	}
	reverse(outputStack.begin(), outputStack.end()); //Реверсируем финальную строку ещё один раз
	auto end = chrono::steady_clock::now();
	stackPNConversionSpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count());
	vector <char> PNVector;
	string outputVector;
	reverse(input.begin(), input.end()); //Реверсируем начальную строку в исходное положение для преобразования с массивом (чтобы сравнение скорости выполнения было справедливым)
	auto start = chrono::steady_clock::now();
	reverse(input.begin(), input.end()); //Реверсируем строку
	for (unsigned int i = 0; i < input.length(); ++i) { //Преобразование с помощью массива
		if (input[i] >= 'a' && input[i] <= 'z') { //Если текущий символ - операнд, то кладём его в строку вывода
			outputVector += input[i];
			outputVector += " ";
		}
		else if (isdigit(input[i])) { //Если текущий символ - число
			int number = 0;
			while (isdigit(input[i])) { //Пока следующий символ - тоже число
				number = number * 10 + (int)(input[i] - '0'); // Находим все его разряды
				++i;
			}
			--i;
			outputVector += to_string(number);
			outputVector += " ";
		}
		else if (input[i] == ')') //Если текущий символ - ')', то кладём в его в массив
			PNVector.push_back(')');
		else if (input[i] == '(') { //Если текущий символ - '(', то берём из стека всё, что идёт до ')', и помещаем в строку вывода
			while (!PNVector.empty() && PNVector.back() != ')') {
				outputVector += PNVector.back(); //Записываем в строку вывода последний элемент массива
				PNVector.pop_back(); //Удаляем последний элемент массива
				outputVector += " ";
			}
			if (PNVector.back() == ')')
				PNVector.pop_back();
		}
		else { //Если текущий символ - оператор
			while (!PNVector.empty() && getOrder(input[i]) < getOrder(PNVector.back()) && PNVector.back() != ')') { //Пока массив не пуст и порядок текущей операции меньше порядка операции, находящейся в последнем элементе массива
				outputVector += PNVector.back();
				PNVector.pop_back();
				outputVector += " ";
			}
			if (input[i] == '-' && (i == input.length() - 1 || input[i + 1] == '(')) //Если это унарный минус (первая позиция в строке, либо после минуса стоит открывающая скобка)
				outputVector += "0 "; //Моя реализация унарного минуса
			PNVector.push_back(input[i]);
		}
	}
	while (!PNVector.empty()) { //В конце (при проходе всей строки) достаём из массива все оставшиеся элементы
		outputVector += PNVector.back();
		PNVector.pop_back();
		outputVector += " ";
	}
	reverse(outputVector.begin(), outputVector.end()); //Реверсируем финальную строку ещё один раз
	auto finish = chrono::steady_clock::now();
	arrayPNConversionSpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(finish - start).count());
	cout << endl;
	cout << "Ваше выражение в ПН (через массив): " << outputVector << endl;
	cout << "Ваше выражение в ПН (через стек):   " << outputStack << endl;
	cout << endl;
	cout << "Время, затраченное на конвертацию в ПН (через массив): " << arrayPNConversionSpeed << " наносек." << endl;
	cout << "Время, затраченное на конвертацию в ПН (через стек):   " << stackPNConversionSpeed << " наносек." << endl;
	cout << endl;
	return outputStack;
}

string infixToRPN(string input) { //Функция перевода из инфиксной формы в ОПН
	long int arrayPRNConversionSpeed, stackPRNConversionSpeed;
	stack <char> RPNStack;
	string outputStack;
	auto begin = chrono::steady_clock::now();
	for (unsigned int i = 0; i < input.length(); ++i) { //Преобразование с помощью стека
		if (input[i] >= 'a' && input[i] <= 'z') { //Если текущий символ - операнд, то кладём его в строку вывода
			outputStack += input[i];
			outputStack += " ";
		}
		else if (isdigit(input[i])) { //Если текущий символ - число
			int number = 0;
			while (isdigit(input[i])) { //Пока следующий символ - тоже число
				number = number * 10 + (int)(input[i] - '0'); // Находим все его разряды
				++i;
			}
			--i;
			outputStack += to_string(number);
			outputStack += " ";
		}
		else if (input[i] == '(') //Если текущий символ - '(', то кладём в его в стек
			RPNStack.push('(');
		else if (input[i] == ')') { //Если текущий символ - ')', то берём из стека всё, что идёт до '(', и помещаем в строку вывода
			while (!RPNStack.empty() && RPNStack.top() != '(') {
				outputStack += RPNStack.top(); //Записываем в строку вывода верхний элемент стека
				RPNStack.pop(); //Удаляем верхний элемент стека
				outputStack += " ";
			}
			if (RPNStack.top() == '(')
				RPNStack.pop();
		}
		else { //Если текущий символ - оператор
			while (!RPNStack.empty() && getOrder(input[i]) <= getOrder(RPNStack.top()) && RPNStack.top() != '(') { //Пока стек не пуст и порядок текущей операции меньше либо равен порядку операции, находящейся на вершине стека
				outputStack += RPNStack.top();
				RPNStack.pop();
				outputStack += " ";
			}
			if (input[i] == '-' && (i == 0 || input[i - 1] == '(')) //Если это унарный минус (первая позиция в строке, либо перед минусом стоит открывающая скобка)
				outputStack += "0 "; //Моя реализация унарного минуса
			RPNStack.push(input[i]);
		}
	}
	while (!RPNStack.empty()) { //В конце (при проходе всей строки) достаём из стека все оставшиеся элементы
		outputStack += RPNStack.top();
		RPNStack.pop();
		outputStack += " ";
	}
	auto end = chrono::steady_clock::now();
	stackPRNConversionSpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count());
	vector <char> RPNVector;
	string outputVector;
	auto start = chrono::steady_clock::now();
	for (unsigned int i = 0; i < input.length(); ++i) { //Преобразование с помощью массива
		if (input[i] >= 'a' && input[i] <= 'z') { //Если текущий символ - операнд, то кладём его в строку вывода
			outputVector += input[i];
			outputVector += " ";
		}
		else if (isdigit(input[i])) { //Если текущий символ - число
			int number = 0;
			while (isdigit(input[i])) { //Пока следующий символ - тоже число
				number = number * 10 + (int)(input[i] - '0'); // Находим все его разряды
				++i;
			}
			--i;
			outputVector += to_string(number);
			outputVector += " ";
		}
		else if (input[i] == '(') //Если текущий символ - '(', то кладём в его в массив
			RPNVector.push_back('(');
		else if (input[i] == ')') { //Если текущий символ - ')', то берём из массива всё, что идёт до '(', и помещаем в строку вывода
			while (!RPNVector.empty() && RPNVector.back() != '(') {
				outputVector += RPNVector.back(); //Записываем в строку вывода последний элемент массива
				RPNVector.pop_back(); //Удаляем последний элемент массива
				outputVector += " ";
			}
			if (RPNVector.back() == '(')
				RPNVector.pop_back();
		}
		else { //Если текущий символ - оператор
			while (!RPNVector.empty() && getOrder(input[i]) <= getOrder(RPNVector.back()) && RPNVector.back() != '(') { //Пока массив не пуст и порядок текущей операции меньше либо равен порядку операции, находящейся в последнем элементе массива
				outputVector += RPNVector.back();
				RPNVector.pop_back();
				outputVector += " ";
			}
			if (input[i] == '-' && (i == 0 || input[i - 1] == '(')) //Если это унарный минус (первая позиция в строке, либо перед минусом стоит открывающая скобка)
				outputVector += "0 "; //Моя реализация унарного минуса
			RPNVector.push_back(input[i]);
		}
	}
	while (!RPNVector.empty()) { //В конце (при проходе всей строки) достаём из массива все оставшиеся элементы
		outputVector += RPNVector.back();
		RPNVector.pop_back();
		outputVector += " ";
	}
	auto finish = chrono::steady_clock::now();
	arrayPRNConversionSpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(finish - start).count());
	cout << "Ваше выражение в ОПН (через массив): " << outputVector << endl;
	cout << "Ваше выражение в ОПН (через стек):   " << outputStack << endl;
	cout << endl;
	cout << "Время, затраченное на конвертацию в ОПН (через массив): " << arrayPRNConversionSpeed << " наносек." << endl;
	cout << "Время, затраченное на конвертацию в ОПН (через стек):   " << stackPRNConversionSpeed << " наносек." << endl;
	cout << endl;
	return outputStack;
}

void convert(letters alphabet[]) { //Преобразование обычной записи в ПН и ОПН
	string input, PN, RPN, withoutVariables;
	vector <unsigned int> positionsPN, positionsRPN;
	bool condition = 1;
	while (condition) {
		short inputOption = inputMenu();
		switch (inputOption) {
		case 0: { //С клавиатуры
			cout << "Введите выражение: ";
			input = getExpression();
			string inputToPN = input, inputToRPN = input;
			PN = infixToPN(inputToPN);
			RPN = infixToRPN(inputToRPN);
			withoutVariables = swapVariables(alphabet, "", PN, RPN);
			fallBack();
			return;
		}
		case 1: { //С файла
			ifstream file("inputForConversion.txt");
			if (file.is_open()) {
				string input;
				bool bad = 0;
				getline(file, input, '\0');
				file.close();
				checkString(input, bad);
				if (bad == 0) {
					string inputToPN = input, inputToRPN = input;
					cout << "Ваше выражение в инфиксной форме, взятое из файла inputForConversion.txt: " << input << endl;
					PN = infixToPN(inputToPN);
					RPN = infixToRPN(inputToRPN);
					withoutVariables = swapVariables(alphabet, "", PN, RPN);
				}
				else
					cout << "Выражение не было преобразовано (были использованы недопустимые символы). Проверьте содержание файла 'inputForConversion.txt'.";
			}
			else
				cout << "Файл с именем 'inputForConversion.txt' не найден." << endl << endl;
			fallBack();
			return;
		}
		case 2: {
			condition = 0;
			break;
		}
		}
	}
	return;
}

void verify(string input, short type) { //Функция проверки выражения на корректность
	if (input.length() == 0) { //Проверка на количество символов (для любой записи)
		cout << "Введена пустая строка." << endl;
		return;
	}
	if (type == 2) { //Инфиксная запись

	}
	else if (type == 1) { //ПН
		for (unsigned int i = 0; i < input.length(); ++i) { //Проверка на наличие пробела перед каждым (включая первый) оператором/операндом, а также на наличие некорректных символов (а также незначащих нулей)
			if (((input[i] < '0' && input[i] > '9') || (input[i] < 'a' && input[i] > 'z') || (int(input[i]) < 42 && int(input[i]) > 43)) && (int(input[i]) != 32 || int(input[i]) != 45 || int(input[i]) != 47)) {
				cout << "Были введены некорретные символы." << endl;
				return;
			}
			else if (input[i] >= 'a' && input[i] <= 'z' || int(input[i]) >= 42 && int(input[i]) <= 43 || (int(input[i]) == 47)) {
				if (i == input.length() - 1 || input[i + 1] != ' ') {
					cout << "После операнда (переменной) или операции в ОПН должен стоять пробел." << endl;
					return;
				}
			}
			else if (input[1] == '0' && isdigit(input[2]) || i != 0 && i != input.length() - 1 && input[i] == '0' && input[i - 1] == ' ' && isdigit(input[i + 1])) {
				cout << "В выражении не должно быть незначащего нуля." << endl;
				return;
			}
			else if (isdigit(input[i])) {
				while (isdigit(input[i + 1]))
					++i;
				++i;
				if (input[i] != ' ') {
					cout << "После операнда (цифры) в ОПН должен стоять пробел." << endl;
					return;
				}
			}
			else if (input[i] == '-') {
				if (!isdigit(input[i + 1]) && input[i + 1] != ' ') {
					cout << "После операции в ОПН должен стоять пробел." << endl;
					return;
				}
				else if (isdigit(input[i + 1])) {
					while (isdigit(input[i + 1]))
						++i;
					++i;
					if (input[i] != ' ') {
						cout << "После операнда в ОПН должен стоять пробел." << endl;
						return;
					}
				}
			}
		}
		//Переделать условия для ПН
	}
	else { //ОПН
		for (unsigned int i = 0; i < input.length(); ++i) { //Проверка на наличие пробела после каждого (включая последний) оператора/операнда, а также на наличие некорректных символов (а также незначащих нулей)
			if (((input[i] < '0' && input[i] > '9') || (input[i] < 'a' && input[i] > 'z') || (int(input[i]) < 42 && int(input[i]) > 43)) && (int(input[i]) != 32 || int(input[i]) != 45 || int(input[i]) != 47)) {
				cout << "Были введены некорретные символы." << endl;
				return;
			}
			else if  (input[i] >= 'a' && input[i] <= 'z' || int(input[i]) >= 42 && int(input[i]) <= 43 || (int(input[i]) == 47)) {
				if (i == input.length() - 1 || input[i + 1] != ' ') {
					cout << "После операнда (переменной) или операции в ОПН должен стоять пробел." << endl;
					return;
				}
			}
			else if (input[0] == '0' && isdigit(input[1]) || i != 0 && input[i] == '0' && input[i - 1] == ' ' && isdigit(input[i + 1])) {
				cout << "В выражении не должно быть незначащего нуля." << endl;
				return;
			}
			else if (isdigit(input[i])) {
				while (isdigit(input[i + 1]))
					++i;
				++i;
				if (input[i] != ' ') {
					cout << "После операнда (цифры) в ОПН должен стоять пробел." << endl;
					return;
				}
			}
			else if (input[i] == '-') {
				if (!isdigit(input[i + 1]) && input[i + 1] != ' ') {
					cout << "После операции в ОПН должен стоять пробел." << endl;
					return;
				}
				else if (isdigit(input[i + 1])) {
					while (isdigit(input[i + 1]))
						++i;
					++i;
					if (input[i] != ' ') {
						cout << "После операнда в ОПН должен стоять пробел." << endl;
						return;
					}
				}
			}
		}
		for (unsigned int i = 0; i < input.length(); ++i) { // Проверка первых двух символов (должны быть операндами)
			if (isalpha(input[0])) { //Если первый символ - операнд (переменная)
				if ((!isdigit(input[2]) && !isalpha(input[2]) || (input[2] == '-' && (!isdigit(input[3]) || !isalpha(input[3]))))) { //Проверка второго операнда
					cout << "На второй позиции в ОПН должен стоять операнд." << endl;
					return;
				}
				else
					break;
			}
			else if (isdigit(input[0]) || (input[0] == '-' && (isdigit(input[1] || isalpha(input[1]))))) { //Если первый символ - операнд (число)
				if (input[0] == '-')
					++i;
				while (isdigit(input[i + 1])) //Смотрим, если число состоит из нескольких цифр
					++i;
				if (!isdigit(input[i + 2]) && !isalpha(input[i + 2]) || (input[i + 2] == '-' && (!isdigit(input[i + 3]) || !isalpha(input[i + 3])))) {
					cout << "На второй позиции в ОПН должен стоять операнд." << endl;
					return;
				}
				else break;
			}
			else { //Если первый символ - не операнд
				cout << "На первой позиции в ОПН должен стоять операнд." << endl;
				return;
			}
		}
		int operators = 0, actions = 0;
		for (unsigned int i = 0; i < input.length(); ++i) {
			if (isalpha(input[i]) || input[i] == '-' && isalpha(input[i + 1]) || isdigit(input[i]) || (input[i] == '-' && isdigit(input[i + 1]))) { //Если первый символ последовательности операндов переменная, или число, или отрицательная переменная, или отрицательное число
				if (input[i] == '-')
					++i;
				if (isdigit(input[i])) {
					while (isdigit(input[i + 1]))
						++i;
				}
				++operators;
				++i;
				bool condition = 1;
				while (condition) { //Идём по последовательности операндов, пока не встретим символ операции, и считаем количество операндов
					if (i == input.length() || ((input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^') && input[i + 1] == ' '))
						condition = 0;
					if (isalpha(input[i]) || input[i] == '-' && isalpha(input[i + 1])) {
						if (input[i] == '-')
							++i;
						++operators;
					}
					else if (isdigit(input[i]) || input[i] == '-' && isdigit(input[i + 1])) {
						if (input[i] == '-')
							++i;
						while (isdigit(input[i + 1]))
							++i;
						++operators;
					}
					++i;
				}
				--i;
				condition = 1;
				while (condition) { //После прохождения последовательности операндов идём по последовательности операций
					if (i == input.length())
						condition = 0;
					else if (isalpha(input[i]) || isdigit(input[i]) || (input[i] == '-' && (isalpha(input[i + 1]) || isdigit(input[i + 1])))) {
						i -= 2;
						condition = 0;
					}
					else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^')
						++actions;
					++i;
				}
				if (operators > actions + 1 && operators != actions + 1) { //Если [количество операторов] больше [количества операций + 1], начинаем проверку всей строки до последовательности операций, где последняя операция по порядку ниже, чем текущая операция
					bool subCondition = 1;
					short order = getOrder(input[i]);
					while (subCondition) {
						if ((input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^') && (i == input.length() - 2 || (i != input.length() - 2 && actions + 2 >= operators && (isdigit(input[i + 2]) || isalpha(input[i + 2] || (input[i + 2] == '-' && (isdigit(input[i + 3]) || isalpha(input[i + 3])))))))) {
							++actions;
							subCondition = 0;
						}
						else if ((input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^') && (!isalpha(input[i + 1]) || !isdigit(input[i + 1])))
							++actions;
						else if (isalpha(input[i]) || isdigit(input[i]) || (input[i] == '-' && (isalpha(input[i + 1]) || isdigit(input[i + 1])))) {
							if (input[i] == '-')
								++i;
							if (isalpha(input[i]))
								++operators;
							else if (isdigit(input[i])) {
								while (isdigit(input[i + 1]))
									++i;
								++operators;
							}
						}
						++i;
					}
					if (operators != actions + 1) { //Если [количество операторов] не равно [количеству операций + 1] после новой проверки, то выдаём сообщение об ошибке
						cout << "В выражениях действия производятся над двумя операндами." << endl;
						return;
					}
				}
				else if (operators <= actions) { //Если операторов меньше операций - выдаём сообщение об ошибке
					cout << "Между двумя операндами производится одна операция." << endl;
					return;
				}
			}
		}
		for (unsigned int i = 0; i < input.length(); ++i) { //Проверка деления на ноль
			if (i != 0 && input[i] == '0' && input[i - 1] == ' ' && input[i + 1] == ' ' && input[i + 2] == '/') {
				cout << "Нельзя делить на ноль." << endl;
				return;
			}
		}
		cout << "Выражение правильное." << endl;
		return;
	}
}

void validate() { //Проверка выражения на корректность (инфиксная запись, ПН, ОПН)
	bool condition = 1;
	while (condition) {
		short formOption = formMenu();
		switch (formOption) {
		case 0: { //Инфиксная запись
			bool subCondition = 1;
			while (subCondition) {
				short inputOption = inputMenu();
				switch (inputOption) {
				case 0: { //С клавиатуры

					fallBack();
					return;
				}
				case 1: { //С файла

					fallBack();
					return;
				}
				case 2: {
					subCondition = 0;
					break;
				}
				}
			}
			break;
		}
		case 1: { //ПН
			bool subCondition = 1;
			while (subCondition) {
				short inputOption = inputMenu();
				switch (inputOption) {
				case 0: { //С клавиатуры

					fallBack();
					return;
				}
				case 1: { //С файла

					fallBack();
					return;
				}
				case 2: {
					subCondition = 0;
					break;
				}
				}
			}
			break;
		}
		case 2: { //ОПН
			bool subCondition = 1;
			while (subCondition) {
				short inputOption = inputMenu();
				switch (inputOption) {
				case 0: { //С клавиатуры
					cout << "Введите выражение: ";
					string input;
					getline(cin, input);
					auto begin = chrono::steady_clock::now();
					verify(input, 0);
					auto end = chrono::steady_clock::now();
					cout << "Время, затраченное на проверку выражения ОПН: " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()) << " наносек." << endl;
					fallBack();
					return;
				}
				case 1: { //С файла
					ifstream file("inputForValidationRPN.txt");
					if (file.is_open()) {
						string input;
						getline(file, input, '\0');
						file.close();
						cout << "Ваше выражение, взятое из файла 'inputForValidationRPN.txt': " << input << endl;
						auto begin = chrono::steady_clock::now();
						verify(input, 0);
						auto end = chrono::steady_clock::now();
						cout << "Время, затраченное на проверку выражения ОПН: " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()) << " наносек." << endl;
					}
					else
						cout << "Файл с именем 'inputForValidationRPN.txt' не найден." << endl << endl;
					fallBack();
					return;
				}
				case 2: {
					subCondition = 0;
					break;
				}
				}
			}
			break;
		}
		case 3: {
			condition = 0;
			break;
		}
		}
	}
	return;
}

double calculate(char operation, double firstValue, double secondValue) { //Вычисление результата операции над двумя операндами
	switch (operation) {
	case '+':
		return(secondValue + firstValue);
	case '-':
		return(secondValue - firstValue);
	case '*':
		return(secondValue * firstValue);
	case '/':
		return(secondValue / firstValue);
	case '^':
		return(pow(secondValue, firstValue));
	}
	return 0;
}

void evaluate(stack <double> resultStack, vector <double> resultVector,  string input, short type) { //Калькулятор
	long int stackSpeed, arraySpeed;
	if (type == 2) { //Инфиксная запись
		stack <char> operatorsStack;
		auto begin = chrono::steady_clock::now();
		for (unsigned int i = 0; i < input.length(); ++i) { //Вычисление с помощью стека
			if ((i == 0 && input[i] == '-' && isdigit(input[i + 1])) || (i != 0 && input[i] == '-' && input[i - 1] == '(' && isdigit(input[i + 1]))) { //Добавление отрицательных чисел
				int number = 0;
				++i;
				while (i < input.length() && isdigit(input[i])) {
					number = (number * 10) + (input[i] - '0');
					++i;
				}
				--i;
				resultStack.push(-number);
			}
			else if ((i == 0 && input[i] == '-' && input[i + 1] == '(') || (i != 0 && input[i] == '-' && input[i - 1] == '(' && input[i + 1] == ')')) { //Добавление унарного минуса [Пример: -(8+x)]
				resultStack.push(0);
				operatorsStack.push('-');
			}
			else if (isdigit(input[i])) { //Добавление чисел в стек
				int number = 0;
				while (i < input.length() && isdigit(input[i])) {
					number = (number * 10) + (input[i] - '0');
					++i;
				}
				--i;
				resultStack.push(number);
			}
			else if (input[i] == '(') { //Если текущий символ - '(', то кладём в его в стек 'операций'
				operatorsStack.push(input[i]);
			}
			else if (input[i] == ')') { //Если текущий символ - ')', то решаем всё, что находится до '('
				while (!operatorsStack.empty() && operatorsStack.top() != '(') {
					double firstValue = resultStack.top();
					resultStack.pop();
					double secondValue = resultStack.top();
					resultStack.pop();
					char action = operatorsStack.top();
					operatorsStack.pop();
					resultStack.push(calculate(action, firstValue, secondValue));
				}
				if (operatorsStack.top() == '(')
					operatorsStack.pop();
			}
			else { //Если текущий символ оператор
				while (!operatorsStack.empty() && getOrder(operatorsStack.top()) >= getOrder(input[i])) {
					double firstValue = resultStack.top();
					resultStack.pop();
					double secondValue = resultStack.top();
					resultStack.pop();
					char action = operatorsStack.top();
					operatorsStack.pop();
					resultStack.push(calculate(action, firstValue, secondValue));
				}
				operatorsStack.push(input[i]);
			}
		}
		while (!operatorsStack.empty()) { //В конце (при проходе всей строки) достаём из стека все оставшиеся элементы и вычисляем оставшиеся действия
			double firstValue = resultStack.top();
			resultStack.pop();
			double secondValue = resultStack.top();
			resultStack.pop();
			char action = operatorsStack.top();
			operatorsStack.pop();
			resultStack.push(calculate(action, firstValue, secondValue));
		}
		auto end = chrono::steady_clock::now();
		stackSpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count());
		vector <char> operatorsVector;
		auto start = chrono::steady_clock::now();
		for (unsigned int i = 0; i < input.length(); ++i) { //Вычисление с помощью массива
			if (i == 0 && input[i] == '-' && isdigit(input[i + 1]) || i != 0 && input[i] == '-' && input[i - 1] == '(' && isdigit(input[i + 1])) { //Добавление отрицательных чисел
				int number = 0;
				++i;
				while (i < input.length() && isdigit(input[i])) {
					number = (number * 10) + (input[i] - '0');
					++i;
				}
				--i;
				resultVector.push_back(-number);
			}
			else if (i == 0 && input[i] == '-' && input[i + 1] == '(' || i != 0 && input[i] == '-' && input[i - 1] == '(' && input[i + 1] == ')') { //Добавление унарного минуса
				resultVector.push_back(0);
				operatorsVector.push_back('-');
			}
			else if (isdigit(input[i])) { //Добавление чисел в массив
				int number = 0;
				while (i < input.length() && isdigit(input[i])) {
					number = (number * 10) + (input[i] - '0');
					++i;
				}
				--i;
				resultVector.push_back(number);
			}
			else if (input[i] == '(') { //Если текущий символ - '(', то кладём в его в массив 'операций'
				operatorsVector.push_back(input[i]);
			}
			else if (input[i] == ')') { //Если текущий символ - ')', то решаем всё, что находится до '('
				while (!operatorsVector.empty() && operatorsVector.back() != '(') {
					double firstValue = resultVector.back();
					resultVector.pop_back();
					double secondValue = resultVector.back();
					resultVector.pop_back();
					char action = operatorsVector.back();
					operatorsVector.pop_back();
					resultVector.push_back(calculate(action, firstValue, secondValue));
				}
				if (operatorsVector.back() == '(')
					operatorsVector.pop_back();
			}
			else { //Если текущий символ оператор
				while (!operatorsVector.empty() && getOrder(operatorsVector.back()) >= getOrder(input[i])) {
					double firstValue = resultVector.back();
					resultVector.pop_back();
					double secondValue = resultVector.back();
					resultVector.pop_back();
					char action = operatorsVector.back();
					operatorsVector.pop_back();
					resultVector.push_back(calculate(action, firstValue, secondValue));
				}
				operatorsVector.push_back(input[i]);
			}
		}
		while (!operatorsVector.empty()) { //В конце (при проходе всей строки) достаём из массива все оставшиеся элементы и вычисляем оставшиеся действия
			double firstValue = resultVector.back();
			resultVector.pop_back();
			double secondValue = resultVector.back();
			resultVector.pop_back();
			char action = operatorsVector.back();
			operatorsVector.pop_back();
			resultVector.push_back(calculate(action, firstValue, secondValue));
		}
		auto finish = chrono::steady_clock::now();
		arraySpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(finish - start).count());
		cout << "Результат выражения, записанного в инфиксной форме (через массив): " << resultVector.back() << endl;
		cout << "Результат выражения, записанного в инфиксной форме (через стек): " << resultStack.top() << endl;
		cout << endl;
		cout << "Время, затраченное на вычисление выражения, записанного в инфиксной форме (через массив): " << stackSpeed << " наносек." << endl;
		cout << "Время, затраченное на вычисление выражения, записанного в инфиксной форме (через стек): " << arraySpeed << " наносек." << endl;
	}
	else if (type == 1) { //ПН
		auto begin = chrono::steady_clock::now();
		for (unsigned int i = input.length() - 1; i >= 0; --i) { //Вычисление с помощью стека
			if (isdigit(input[i])) { //Добавление чисел в стек
				int number = 0, power = 0;
				while (isdigit(input[i])) {
					number += (input[i] - '0') * pow(10, power);
					++power;
					--i;
				}
				if (input[i] == '-') { //Добавление отрицательных чисел в стек
					number = -number;
					--i;
				}
				++i;
				resultStack.push(number);
			}
			else if (input[i] != ' ') { //Операции
				double firstValue = resultStack.top();
				resultStack.pop();
				double secondValue = resultStack.top();
				resultStack.pop();
				resultStack.push(calculate(input[i], firstValue, secondValue));
			}
			if (i == 0)
				break;
		}
		auto end = chrono::steady_clock::now();
		stackSpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count());
		auto start = chrono::steady_clock::now();
		for (unsigned int i = input.length() - 1; i >= 0; --i) { //Вычисление с помощью массива
			if (isdigit(input[i])) { //Добавление чисел в стек
				int number = 0, power = 0;
				while (isdigit(input[i])) {
					number += (input[i] - '0') * pow(10, power);
					++power;
					--i;
				}
				if (input[i] == '-') { //Добавление отрицательных чисел в стек
					number = -number;
					--i;
				}
				++i;
				resultVector.push_back(number);
			}
			else if (input[i] != ' ') { //Операции
				double firstValue = resultVector.back();
				resultVector.pop_back();
				double secondValue = resultVector.back();
				resultVector.pop_back();
				resultVector.push_back(calculate(input[i], firstValue, secondValue));
			}
			if (i == 0)
				break;
		}
		auto finish = chrono::steady_clock::now();
		arraySpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(finish - start).count());
		cout << "Результат выражения, записанного в ПН (через массив): " << resultVector.back() << endl;
		cout << "Результат выражения, записанного в ПН (через стек): " << resultStack.top() << endl;
		cout << endl;
		cout << "Время, затраченное на вычисление выражения, записанного в ПН (через массив): " << stackSpeed << " наносек." << endl;
		cout << "Время, затраченное на вычисление выражения, записанного в ПН (через стек): " << arraySpeed << " наносек." << endl;
	}
	else { //ОПН
		auto begin = chrono::steady_clock::now();
		for (unsigned int i = 0; i < input.length(); ++i) { //Вычисление с помощью стека
			if (isdigit(input[i])) { //Добавление чисел в стек
				int number = 0;
				while (isdigit(input[i])) {
					number = number * 10 + (int)(input[i] - '0');
					++i;
				}
				--i;
				resultStack.push(number);
			}
			else if (input[i] == '-' && (isdigit(input[i + 1]) || isalpha(input[i + 1]))) { //Добавление отрицательных чисел в стек
				++i;
				int number = 0;
				while (isdigit(input[i])) {
					number = number * 10 + (int)(input[i] - '0');
					++i;
				}
				--i;
				number = -number;
				resultStack.push(number);
			}
			else if (input[i] != ' ') { //Операции
				double firstValue = resultStack.top();
				resultStack.pop();
				double secondValue = resultStack.top();
				resultStack.pop();
				resultStack.push(calculate(input[i], firstValue, secondValue));
			}
		}
		auto end = chrono::steady_clock::now();
		stackSpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count());
		auto start = chrono::steady_clock::now();
		for (unsigned int i = 0; i < input.length(); ++i) { //Вычисление с помощью массива
			if (isdigit(input[i])) { //Добавление чисел в стек
				int number = 0;
				while (isdigit(input[i])) {
					number = number * 10 + (input[i] - '0');
					++i;
				}
				--i;
				resultVector.push_back(number);
			}
			else if (input[i] == '-' && (isdigit(input[i + 1]) || isalpha(input[i + 1]))) { //Добавление отрицательных чисел в стек
				++i;
				int number = 0;
				while (isdigit(input[i])) {
					number = number * 10 + (input[i] - '0');
					++i;
				}
				--i;
				number = -number;
				resultVector.push_back(number);
			}
			else if (input[i] != ' ') { //Операции
				double firstValue = resultVector.back();
				resultVector.pop_back();
				double secondValue = resultVector.back();
				resultVector.pop_back();
				resultVector.push_back(calculate(input[i], firstValue, secondValue));
			}
		}
		auto finish = chrono::steady_clock::now();
		arraySpeed = static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(finish - start).count());
		cout << "Результат выражения, записанного в ОПН (через массив): " << resultVector.back() << endl;
		cout << "Результат выражения, записанного в ОПН (через стек): " << resultStack.top() << endl;
		cout << endl;
		cout << "Время, затраченное на вычисление выражения, записанного в ОПН (через массив): " << arraySpeed << " наносек." << endl;
		cout << "Время, затраченное на вычисление выражения, записанного в ОПН (через стек): " << stackSpeed << " наносек." << endl;
	}
}

void solve(letters alphabet[]) { //Вычисление выражения (инфиксная запись, ПН, ОПН)
	bool condition = 1;
	while (condition) {
		short formOption = formMenu();
		switch (formOption) {
		case 0: { //Инфиксная запись
			bool subCondition = 1;
			while (subCondition) {
				short inputOption = inputMenu();
				switch (inputOption) {
				case 0: { //С клавиатуры
					stack <double> resultStack;
					vector <double> resultVector;
					cout << "Введите выражение в инфиксной форме записи: ";
					string input = getExpression();
					string withoutVariables = swapVariables(alphabet, input, "", "");
					evaluate(resultStack, resultVector, withoutVariables, 2);
					fallBack();
					return;
				}
				case 1: { //С файла
					ifstream file("inputForEvaluationInfix.txt");
					if (file.is_open()) {
						string input;
						bool bad = 0;
						getline(file, input, '\0');
						file.close();
						checkString(input, bad);
						if (bad == 0) {
							stack <double> resultStack;
							vector <double> resultVector;
							cout << "Ваше выражение в инфиксной форме записи, взятое из файла 'inputForEvaluationInfix.txt': " << input << endl;
							string withoutVariables = swapVariables(alphabet, input, "", "");
							evaluate(resultStack, resultVector, withoutVariables, 2);
						}
						else
							cout << "Выражение не было посчитано (были использованы недопустимые символы). Проверьте содержание файла 'inputForEvaluationInfix.txt'.";
					}
					else
						cout << "Файл с именем 'inputForEvaluationInfix.txt' не найден." << endl << endl;
					fallBack();
					return;
				}
				case 2: {
					subCondition = 0;
					break;
				}
				}
			}
			return;
		}
		case 1: { //ПН
			bool subCondition = 1;
			while (subCondition) {
				short inputOption = inputMenu();
				switch (inputOption) {
				case 0: { //С клавиатуры
					stack <double> resultStack;
					vector <double> resultVector;
					cout << "Введите выражение в форме записи ПН: ";
					string input = getExpression();
					string withoutVariables = swapVariables(alphabet, "", input, "");
					evaluate(resultStack, resultVector, withoutVariables, 1);
					fallBack();
					return;
				}
				case 1: { //С файла
					ifstream file("inputForEvaluationPN.txt");
					if (file.is_open()) {
						string input;
						bool bad = 0;
						getline(file, input, '\0');
						file.close();
						checkString(input, bad);
						if (bad == 0) {
							stack <double> resultStack;
							vector <double> resultVector;
							cout << "Ваше выражение в форме записи ПН, взятое из файла 'inputForEvaluationPN.txt': " << input << endl;
							string withoutVariables = swapVariables(alphabet, "", input, "");
							evaluate(resultStack, resultVector, withoutVariables, 1);
						}
						else
							cout << "Выражение не было посчитано (были использованы недопустимые символы). Проверьте содержание файла 'inputForEvaluationPN.txt'.";
					}
					else
						cout << "Файл с именем 'inputForEvaluationPN.txt' не найден." << endl << endl;
					fallBack();
					return;
				}
				case 2: {
					subCondition = 0;
					break;
				}
				}
			}
			break;
		}
		case 2: { //ОПН
			bool subCondition = 1;
			while (subCondition) {
				short inputOption = inputMenu();
				switch (inputOption) {
				case 0: { //С клавиатуры
					stack <double> resultStack;
					vector <double> resultVector;
					cout << "Введите выражение в форме записи ОПН: ";
					string input = getExpression();
					string withoutVariables = swapVariables(alphabet, "", "", input);
					evaluate(resultStack, resultVector, withoutVariables, 0);
					fallBack();
					return;
				}
				case 1: { //С файла
					ifstream file("inputForEvaluationRPN.txt");
					if (file.is_open()) {
						string input;
						bool bad = 0;
						getline(file, input, '\0');
						file.close();
						checkString(input, bad);
						if (bad == 0) {
							stack <double> resultStack;
							vector <double> resultVector;
							cout << "Ваше выражение в форме записи ОПН, взятое из файла 'inputForEvaluationRPN'.txt: " << input << endl;
							string withoutVariables = swapVariables(alphabet, "", "", input);
							evaluate(resultStack, resultVector, withoutVariables, 0);
						}
						else
							cout << "Выражение не было посчитано (были использованы недопустимые символы). Проверьте содержание файла 'inputForEvaluationRPN'.txt.";
					}
					else
						cout << "Файл с именем 'inputForEvaluationRPN.txt' не найден." << endl << endl;
					fallBack();
					return;
				}
				case 2: {
					subCondition = 0;
					break;
				}
				}
			}
			break;
		}
		case 3: {
			condition = 0;
			break;
		}
		}
	}
	return;
}

/*
2) Реализует проверку на корректность простого выражения и выражения, записанного в прямой и обратной польским нотациям (на выбор пользователя). 
Ввод выражения должен быть реализовать двумя способами: с клавиатуры и с файла.

Также сравните скорость проверки на корректность выражения в прямой и обратной польских нотациях.

4) Генерирует несколько (на выбор пользователя) вариантов проверочной работы по польской нотации (прямой и обратной). 
Задание и ответы к ним необходимо вывести в отдельные файлы (ответы должны быть максимально подробными).

3 вариант: Реализуйте буфер клавиатуры.

Реализуйте программу выше двумя способами: с использованием стека и массивов.

*/
#endif
