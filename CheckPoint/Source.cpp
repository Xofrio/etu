#include "Func.h"

using namespace std;

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand((unsigned)time(NULL));
	bool condition = 1, created = 0, *digits = 0, entered = 0, sorted = 0;
	string login, rlogin, clogin, sortingMethod;
	vector<char> pass, rpass;
	char c, *cpass = 0;
	int count = 32, groupNumber = 9894, elementsCount, *arrayOfNumbers = 0, sum = 0;
	float avg;
mainMenu:
	while (condition) {
		int answer = mainMenu();
		switch (answer) {
		case 0: {
			int answer3 = userMenu();
			switch (answer3) {
			case 0: {
				cout << "Введите логин: ";
				cin >> rlogin;
				cout << "Введите пароль: ";
				while ((c = _getch()) != '\r') {
					pass.push_back(c);
					_putch('*');
				}
				ofstream flogin("login.txt");
				flogin << rlogin;
				flogin.close();
				ofstream fpass("pass.txt");
				for (size_t i = 0; i < pass.size(); ++i)
					fpass << pass[i];
				fpass.close();
				cout << endl << "Регистрация прошла успешно!" << endl;
				fallBack();
				break;
			}
			case 1: {
				ifstream flogin("login.txt");
				while (!flogin.eof())
					flogin >> clogin;
				int passCharacters = 0;
				ifstream in("pass.txt");
				if (in.is_open()) {
					int temp;
					while (!in.eof()) {
						in >> temp;
						++passCharacters;
					}
					in.seekg(0, ios::beg);
					in.clear();
					cpass = new char[passCharacters];
					int i = 0;
					while (!in.eof()) {
						in >> cpass[i];
						++i;
					}
					in.close();
				}
				cout << "Введите логин: ";
				cin >> login;
				cout << "Введите пароль: ";
				pass.clear();
				vector<char>().swap(pass);
				while ((c = _getch()) != '\r') {
					pass.push_back(c);
					_putch('*');
				}
				flogin.close();
				char *examine = 0;
				examine = new char[pass.size()];
				for (size_t i = 0; i < pass.size(); ++i)
					examine[i] = cpass[i];
				cout << endl;
				int comparison = 0;
				for (size_t i = 0; i < pass.size(); ++i) {
					if (examine[i] == pass[i])
						++comparison;
				}
				bool win = 0;
				if (comparison == pass.size())
					win = 1;
				if (login == clogin && win) {
					cout << endl << "Авторизация прошла успешно! Здравствуйте, " << login << "!" << endl;
					entered = 1;
					fallBack();
				}
				else if (login != clogin) {
					cerr << endl << "Пользователь не найден" << endl;
					fallBack();
				}
				else if (win == 0) {
					cerr << endl << "Неправильный пароль" << endl;
					fallBack();
				}
				break;
			}
			case 2: goto mainMenu;
			}
			break;
		}
		case 1: {
			int answer4;
			if (entered == 0) {
				answer4 = anonymousMenu();
				switch (answer4) {
				case 0: {
					ifstream flogin("login.txt");
					while (!flogin.eof())
						flogin >> clogin;
					int passCharacters = 0;
					ifstream in("pass.txt");
					if (in.is_open()) {
						int temp;
						while (!in.eof()) {
							in >> temp;
							++passCharacters;
						}
						in.seekg(0, ios::beg);
						in.clear();
						cpass = new char[passCharacters];
						int i = 0;
						while (!in.eof()) {
							in >> cpass[i];
							++i;
						}
						in.close();
					}
					cout << "Введите логин: ";
					cin >> login;
					cout << "Введите пароль: ";
					pass.clear();
					vector<char>().swap(pass);
					while ((c = _getch()) != '\r') {
						pass.push_back(c);
						_putch('*');
					}
					flogin.close();
					char *examine = 0;
					examine = new char[pass.size()];
					for (size_t i = 0; i < pass.size(); ++i)
						examine[i] = cpass[i];
					cout << endl;
					int comparison = 0;
					for (size_t i = 0; i < pass.size(); ++i) {
						if (examine[i] == pass[i])
							++comparison;
					}
					bool win = 0;
					if (comparison == pass.size())
						win = 1;
					if (login == clogin && win) {
						cout << endl << "Авторизация прошла успешно! Здравствуйте, " << login << "!" << endl;
						entered = 1;
						cout << "Приветствую тебя, " << login << ". На улице такая вьюга, присаживайся у очага, здесь тебе всегда рады." << endl;
						cout << "Эту программу написал студент группы 9894 Белов Андрей." << endl;
						digits = new bool[count];
						intArray(groupNumber, digits);
						cout << "Кстати, в памяти моего компьютера номер моей группы выглядит так: " << endl;
						output(digits);
						cout << endl << "А фамилия: " << endl;
						char surname[5];
						surname[0] = 'Б';
						surname[1] = 'е';
						surname[2] = 'л';
						surname[3] = 'о';
						surname[4] = 'в';
						for (int i = 0; i < 5; ++i) {
							charArray(surname[i], digits);
							output(digits);
							cout << " ";
						}
						cout << endl << endl;
						fallBack();
					}
					else if (login != clogin) {
						cout << endl << "Пользователь не найден" << endl;
						goto notAuthorized;
					}
					else if (win == 0) {
						cout << endl << "Неправильный пароль" << endl;
						goto notAuthorized;
					}
					break;
				}
				case 1: {
					cout << "Это ваше право, отныне вы будете именоваться пользователь N." << endl;
				notAuthorized:
					login = "пользователь N";
					cout << "Приветствую тебя, " << login << ". На улице такая вьюга, присаживайся у очага, здесь тебе всегда рады." << endl;
					cout << "Эту программу написал студент группы 9894 Белов Андрей." << endl;
					digits = new bool[count];
					intArray(groupNumber, digits);
					cout << "Кстати, в памяти моего компьютера номер моей группы выглядит так: " << endl;
					output(digits);
					cout << endl << "А фамилия: " << endl;
					char surname[5];
					surname[0] = 'Б';
					surname[1] = 'е';
					surname[2] = 'л';
					surname[3] = 'о';
					surname[4] = 'в';
					for (int i = 0; i < 5; ++i) {
						charArray(surname[i], digits);
						output(digits);
						cout << " ";
					}
					cout << endl << endl;
					fallBack();
					break;
				}
				case 2: goto mainMenu;
				}
			}
			else {
			cout << "Приветствую тебя, " << login << ". На улице такая вьюга, присаживайся у очага, здесь тебе всегда рады." << endl;
			cout << "Эту программу написал студент группы 9894 Белов Андрей." << endl;
			digits = new bool[count];
			intArray(groupNumber, digits);
			cout << "Кстати, в памяти моего компьютера номер моей группы выглядит так: " << endl;
			output(digits);
			cout << endl << "А фамилия: " << endl;
			char surname[5];
			surname[0] = 'Б';
			surname[1] = 'е';
			surname[2] = 'л';
			surname[3] = 'о';
			surname[4] = 'в';
			for (int i = 0; i < 5; ++i) {
				charArray(surname[i], digits);
				output(digits);
				cout << " ";
			}
			cout << endl << endl;
			fallBack();
			}
			break;
		}
		case 2: {
			int answer2 = arrayMenu();
			switch (answer2) {
			case 0: {
				cout << "Ввведите размерность массива:";
				elementsCount = getValue();
				arrayOfNumbers = new int[elementsCount];
				inputArray(arrayOfNumbers, elementsCount);
				showArray(arrayOfNumbers, elementsCount);
				created = 1;
				fallBack();
				break;
			}
			case 1: {
				cout << "Ввведите размерность массива:";
				elementsCount = getValue();
				arrayOfNumbers = new int[elementsCount];
				generateArray(arrayOfNumbers, elementsCount);
				showArray(arrayOfNumbers, elementsCount);
				created = 1;
				fallBack();
				break;
			}
			case 2: {
				inputArrayFromFile(arrayOfNumbers, elementsCount, created);
				showArray(arrayOfNumbers, elementsCount);
				fallBack();
				break;
			}
			case 3: goto mainMenu;
			}
			break;
		}
		case 3: {
			if (created == 0) {
				cout << "Массив не создан." << endl;
				fallBack();
			}
			else {
				int method = methodMenu();
				switch (method) {
				case 0: {
					auto begin = chrono::steady_clock::now();
					bubbleSorting(arrayOfNumbers, elementsCount);
					auto end = chrono::steady_clock::now();
					sortingMethod = "Bubble";
					cout <<"Время, затраченное на cортировку массива (метод сортировки - Bubble): " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl << endl;
					cout << endl << "Отсортированный массив (метод сортировки - Bubble):" << endl << endl;
					sorted = 1;
					break;
				}
				case 1: {
					auto begin = chrono::steady_clock::now();
					cocktailSorting(arrayOfNumbers, elementsCount);
					auto end = chrono::steady_clock::now();
					cout <<"Время, затраченное на сортировку массива (метод сортировки - Shaker): " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl << endl;
					cout << endl << "Отсортированный массив (метод сортировки - Shaker):" << endl << endl;
					sorted = 1;
					break;
				}
				case 2: {
					auto begin = chrono::steady_clock::now();
					combSorting(arrayOfNumbers, elementsCount);
					auto end = chrono::steady_clock::now();
					cout <<"Время, затраченное на сортировку массива (метод сортировки - Comb): " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl << endl;
					cout << endl << "Отсортированный массив (метод сортировки - Comb):" << endl << endl;
					sorted = 1;
					break;
				}
				case 3: {
					auto begin = chrono::steady_clock::now();
					insertionSorting(arrayOfNumbers, elementsCount);
					auto end = chrono::steady_clock::now();
					cout <<"Время, затраченное на сортировку массива (метод сортировки - Insert): " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl << endl;
					cout << endl << "Отсортированный массив (метод сортировки - Insert):" << endl << endl;
					sorted = 1;
					break;
				}
				case 4: {
					auto begin = chrono::steady_clock::now();
					quickSorting(arrayOfNumbers, 0, elementsCount - 1);
					auto end = chrono::steady_clock::now();
					cout <<"Время, затраченное на сортировку массива (метод сортировки - Quick): " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl << endl;
					cout << endl << "Отсортированный массив (метод сортировки - Quick):" << endl << endl;
					sorted = 1;
					break;
				}
				case 5: goto mainMenu;
				}
				if (sorted == 1) {
					showArray(arrayOfNumbers, elementsCount);
					for (int i = 0; i < elementsCount; ++i)
						sum = sum + arrayOfNumbers[i];
					avg = (float)sum / (float)elementsCount;
					cout << endl << "Среднее значение массива: " << avg << endl;
					if (elementsCount % 2 == 1)
						cout << "Медиана массива: " << arrayOfNumbers[elementsCount / 2] << endl;
					else
						cout << "Медиана массива: " << (arrayOfNumbers[elementsCount / 2 - 1] + arrayOfNumbers[elementsCount / 2]) / 2 << endl;
					int arrayOfCount[100] = {};
					for (int i = 0; i < elementsCount; ++i)
						++arrayOfCount[arrayOfNumbers[i]];
					int maxElement = arrayOfCount[0];
					for (int i = 1; i < 100; ++i) {
						if (maxElement < arrayOfCount[i])
							maxElement = arrayOfCount[i];
					}
					int countSummary = 0;
					cout << "Мода(ы) массива: ";
					for (int i = 0; i < 100; ++i) {
						if (arrayOfCount[i] == maxElement) {
							cout << i << " ";
							++countSummary;
						}
					}
					cout << endl << "Количество мод: " << countSummary << ". Сколько раз мода(ы) встречаются в массиве: " << maxElement << endl;
					fallBack();
				}
			}
			break;
		}
		case 4: {
			cout << "Флаг РФ: " << endl << endl;
			SetConsoleTextAttribute(textColour, 240);
			cout << "                  " << endl;
			cout << "                  " << endl;
			SetConsoleTextAttribute(textColour, 16);
			cout << "                  " << endl;
			cout << "                  " << endl;
			SetConsoleTextAttribute(textColour, 64);
			cout << "                  " << endl;
			cout << "                  " << endl;
			SetConsoleTextAttribute(textColour, 7);
			cout << endl << endl;
			cout << "Флаг Коста-Рики (16 вариант): " << endl << endl;
			SetConsoleTextAttribute(textColour, 16);
			cout << "                  " << endl;
			SetConsoleTextAttribute(textColour, 240);
			cout << "                  " << endl;
			SetConsoleTextAttribute(textColour, 64);
			cout << "                  " << endl;
			cout << "                  " << endl;
			SetConsoleTextAttribute(textColour, 240);
			cout << "                  " << endl;
			SetConsoleTextAttribute(textColour, 16);
			cout << "                  " << endl;
			SetConsoleTextAttribute(textColour, 7);
			cout << endl;
			fallBack();
			break;
		}
		case 5: {
			condition = 0;
			break;
		}
		}
	}
	system("pause");
	return 0;
}
