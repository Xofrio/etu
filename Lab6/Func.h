#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <Windows.h>

#ifndef FUNC_H
#define FUNC_H

HANDLE textColour = GetStdHandle(STD_OUTPUT_HANDLE);

struct student {
	std::string name, lastName, patronymic, createdTime, modTime;
	int libraryCard;
	short group, index, grades[8], formOfEducation;
	bool sex;
};/*Создание структуры student со всеми необходимыми полями.*/

struct book {
	std::string author, name;
	short year, pages;
	int libraryCard;
};/*Создание структуры book со всеми необходимыми полями*/

void showMenu() {
	std::cout << "Выберите опцию . . ." << std::endl;
	std::cout << "0. Добавить студента" << std::endl;
	std::cout << "1. Редактировать данные о студенте" << std::endl;
	std::cout << "2. Информация о студентах" << std::endl;
	std::cout << "3. Информация о студентах из определённой группы" << std::endl;
	std::cout << "4. Информация о студентах, средний балл которых выше среднего" << std::endl;
	std::cout << "5. Количество студентов мужского и женского пола" << std::endl;
	std::cout << "6. Количество студентов, которые будут получать стипендию" << std::endl;
	std::cout << "7. Информация о студентах, которые не получают стипендию; учатся только на «хор»; учатся на «хор» и «отл»; учатся только на «отл»." << std::endl;
	std::cout << "8. Информация о студентах, записи которых были сделаны в определённый день" << std::endl;
	std::cout << "9. Информация о студентах, имеющих определённый порядковый номер в списке группы" << std::endl;
	std::cout << "10. Вывести всю информацию о студентах в students.txt" << std::endl;
	std::cout << "11. Пройти в библиотеку" << std::endl;
	std::cout << "12. Выйти" << std::endl;
	std::cout << "Опция: ";
}/*Вывод меню*/

short getMenuOption() {
	while (true) {
		short userNumber;
		std::cin >> userNumber;
		if (std::cin.fail() || userNumber < 0 || userNumber > 12) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << std::endl << "Введите опцию [0...12]: ";
		}
		else if (userNumber == 0 || userNumber == 1 || userNumber == 2 || userNumber == 3 || userNumber == 4 || userNumber == 5 || userNumber == 6 || userNumber == 7 || userNumber == 8 || userNumber == 9 || userNumber == 10 || userNumber == 11 || userNumber == 12) {
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}/*Выбор в меню.*/

std::string getPartOfTheName(short part) {
	while (true) {
		std::string userInput;
		bool capital = 0, notAllowed = 0;
		std::cin >> userInput;
		for (unsigned int i = 0; i < userInput.length(); ++i) {
			if ((int(userInput[0]) < -64 || int(userInput[0]) > -33) && int(userInput[0]) != -88) {
				capital = 1;
				break;
			}
			if (i != 0 && ((int(userInput[i]) < -32 || int(userInput[i]) > -1) && int(userInput[i]) != -72)) {
				notAllowed = 1;
				break;
			}
		}
		if (std::cin.fail() || userInput.length() > 15 || capital == 1 || notAllowed == 1) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			if (part == 2)
				std::cout << std::endl << "Введите фамилию (только русские буквы, не более 14 символов, 1 - заглавная): ";
			else if (part == 1)
				std::cout << std::endl << "Введите имя (только русские буквы, не более 14 символов, 1 - заглавная): ";
			else
				std::cout << std::endl << "Введите отчество (только русские буквы, не более 14 символов, 1 - заглавная): ";
		}
		else {
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			return userInput;
		}
	}
}/*Запись оценки.*/

short getGrade() {
	while (true) {
		short userNumber;
		std::cin >> userNumber;
		if (std::cin.fail() || userNumber < 2 || userNumber > 5) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << std::endl << "Введите оценку [2...5]: ";
		}
		else if (userNumber == 2 || userNumber == 3 || userNumber == 4 || userNumber == 5) {
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}/*Запись оценки.*/

short getForm() {
	while (true) {
		short userNumber;
		std::cin >> userNumber;
		if (std::cin.fail() || userNumber < 0 || userNumber > 2) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << std::endl << "Укажите форму образования (очная - 2/очно-заочная - 1/заочная - 0): ";
		}
		else if (userNumber == 0 || userNumber == 1 || userNumber == 2) {
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}/*Запись формы обучения.*/

bool getSex() {
	while (true) {
		bool userNumber;
		std::cin >> userNumber;
		if (std::cin.fail() && (userNumber != 0 || userNumber != 1)) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << std::endl << "Укажите пол (м - 1/ж - 0): ";
		}
		else if (userNumber == 0 || userNumber == 1) {
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}/*Запись пола.*/

short getGroup(student* &inmate, int amount, int position) {
	while (true) {
		short userNumber;
		std::cin >> userNumber;
		if (std::cin.fail() || userNumber < 0 || userNumber > 9999) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << std::endl << "Укажите группу [0...9999]: ";
		}
		else {
			if (amount > 0) {
				int p = -1;
				if (position == 0) {
					for (int j = position + 1; j < amount; ++j) {
						if (inmate[j].group == userNumber && inmate[j].formOfEducation != inmate[position].formOfEducation)
							p = j;
					}
				}
				else if (position == amount - 1) {
					for (int j = 0; j < position; ++j) {
						if (inmate[j].group == userNumber && inmate[j].formOfEducation != inmate[position].formOfEducation)
							p = j;
					}
				}
				else {
					for (int j = 0; j < position; ++j) {
						if (inmate[j].group == userNumber && inmate[j].formOfEducation != inmate[position].formOfEducation)
							p = j;
					}
					for (int j = position + 1; j < amount; ++j) {
						if (inmate[j].group == userNumber && inmate[j].formOfEducation != inmate[position].formOfEducation)
							p = j;
					}
				}
				if (p == -1) {
					std::cin.ignore(std::cin.rdbuf()->in_avail());
					return userNumber;
				}
				else {
					std::cout << std::endl << "В группе " << userNumber << " другая форма обучения (";
					if (inmate[p].formOfEducation == 2)
						std::cout << "очная). ";
					if (inmate[p].formOfEducation == 1)
						std::cout << "очно-заочная). ";
					if (inmate[p].formOfEducation == 0)
						std::cout << "заочная). ";
					std::cout << std::endl;
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());
					std::cout << std::endl << "Укажите другую группу: ";
				}
			}
			else {
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				return userNumber;
			}
		}
	}
}/*Запись группы.*/

short getGroupForSearch() {
	while (true) {
		short userNumber;
		std::cin >> userNumber;
		if (std::cin.fail() || userNumber < 0 || userNumber > 9999) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << std::endl << "Укажите группу [0...9999]: ";
		}
		else {
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}

int getID() {
	while (true) {
		int userNumber;
		std::cin >> userNumber;
		if (std::cin.fail() || userNumber < 0) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << std::endl << "Укажите номер читательского билета: ";
		}
		else {
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}/*Получить номер студента (номер читательского билета - ID)*/

short getIndex() {
	while (true) {
		short userNumber;
		std::cin >> userNumber;
		if (std::cin.fail() || userNumber < 0) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << std::endl << "Укажите номер студента в списке: ";
		}
		else {
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}/*Получить номер студента в списке*/

student* addStudent(student* &inmate, int &amount) {
	if (amount == 0)
		inmate = new student[amount + 1];
	else {
		student* temp = new student[amount + 1];
		for (int i = 0; i < amount; ++i)
			temp[i] = inmate[i];
		delete[] inmate;
		inmate = temp;
	}
	return inmate;
}/*Создание динамического массива структур*/

void addData(student* &inmate, int &amount, int &library) {
	std::cout << std::endl;
	++amount;
	std::cout << "Введите фамилию студента: ";
	inmate[amount - 1].lastName = getPartOfTheName(2);
	std::cout << "Введите имя студента: ";
	inmate[amount - 1].name = getPartOfTheName(1);
	std::cout << "Введите отчество студента: ";
	inmate[amount - 1].patronymic = getPartOfTheName(0);
	std::cout << "Введите пол студента (м - 1/ж - 0): ";
	inmate[amount - 1].sex = getSex();
	std::cout << "Введите форму обучения студента (очная - 2/очно-заочная - 1/заочная - 0): ";
	inmate[amount - 1].formOfEducation = getForm();
	std::cout << "Введите номер группы студента [0...9999]: ";
	inmate[amount - 1].group = getGroup(inmate, amount, amount - 1);
	for (int i = 0; i < 8; ++i) {
		if (i < 3) {
			std::cout << "Введите оценку студента за " << i + 1 << " экзамен: ";
			inmate[amount - 1].grades[i] = getGrade();
		}
		else {
			std::cout << "Введите оценку студента за " << i - 2 << " зачёт: ";
			inmate[amount - 1].grades[i] = getGrade();
		}
	}
	char temp[80];
	time_t now = time(NULL);
	tm* localTime = localtime(&now);
	strftime(temp, 17, "%H:%M %d.%m.%Y", localTime);
	for (int i = 0; temp[i] != '\0' ; ++i)
		inmate[amount - 1].modTime.push_back(temp[i]);
	inmate[amount - 1].createdTime = inmate[amount - 1].modTime;
	inmate[amount - 1].libraryCard = library;
	++library;
	std::cout << std::endl;
}/*Добавление данных о студенте*/

void sort(student* &inmate, int &amount) {
	if (amount > 1) {
		bool match = 0;
		for (int i = 0; i < amount - 1; ++i) {
			if (inmate[i].group == inmate[amount - 1].group) {
				match = 1;
				break;
			}
		}
		if (match == 0)
			inmate[amount - 1].index = 1;
		else {
			int studentsAmount = 1;
			for (int i = 0; i < amount - 1; ++i) {
				if (inmate[i].group == inmate[amount - 1].group) {
					++studentsAmount;
				}
			}
			student* temp = new student[studentsAmount];
			int j = 0;
			for (int i = 0; i < amount; ++i) {
				if (inmate[i].group == inmate[amount - 1].group) {
					temp[j] = inmate[i];
					++j;
				}
			}
			for (int i = 0; i < studentsAmount; ++i)
				temp[i].index = i + 1;
			std::string tempLastName, tempName, tempPatronymic, tempCreatedTime, tempModTime;
			int tempCard;
			short tempForm, tempGrades[8];
			bool tempSex;
			for (int i = 0; i < studentsAmount - 1; ++i) {
				for (int j = 0; j < studentsAmount - i - 1; ++j) {
					tempLastName.clear(), tempName.clear(), tempPatronymic.clear(), tempCreatedTime.clear(), tempModTime.clear();
					tempCard = 0, tempForm = 0,  tempSex = 0;
					for (int b = 0; b < 8; b++)
						tempGrades[b] = 0;
					if ((temp[j].lastName < temp[j + 1].lastName && temp[j].index > temp[j + 1].index) || (temp[j].lastName > temp[j + 1].lastName && temp[j].index < temp[j + 1].index)) {
						tempLastName = temp[j].lastName;
						tempName = temp[j].name;
						tempPatronymic = temp[j].patronymic;
						tempCreatedTime = temp[j].createdTime;
						tempModTime = temp[j].modTime;
						tempCard = temp[j].libraryCard;
						tempForm = temp[j].formOfEducation;
						tempSex = temp[j].sex;
						for (int a = 0; a < 8; ++a)
							tempGrades[a] = temp[j].grades[a];
						temp[j].lastName = temp[j + 1].lastName;
						temp[j].name = temp[j + 1].name;
						temp[j].patronymic = temp[j + 1].patronymic;
						temp[j].createdTime = temp[j + 1].createdTime;
						temp[j].modTime = temp[j + 1].modTime;
						temp[j].libraryCard = temp[j + 1].libraryCard;
						temp[j].formOfEducation = temp[j + 1].formOfEducation;
						temp[j].sex = temp[j + 1].sex;
						for (int a = 0; a < 8; ++a)
							temp[j].grades[a] = temp[j + 1].grades[a];
						temp[j + 1].lastName = tempLastName;
						temp[j + 1].name = tempName;
						temp[j + 1].patronymic = tempPatronymic;
						temp[j + 1].createdTime = tempCreatedTime;
						temp[j + 1].modTime = tempModTime;
						temp[j + 1].libraryCard = tempCard;
						temp[j + 1].formOfEducation = tempForm;
						temp[j + 1].sex = tempSex;
						for (int a = 0; a < 8; ++a)
							temp[j + 1].grades[a] = tempGrades[a];
					}
					else if ((temp[j].lastName == temp[j + 1].lastName && temp[j].name < temp[j + 1].name && temp[j].index > temp[j + 1].index) || (temp[j].lastName == temp[j + 1].lastName && temp[j].name > temp[j + 1].name && temp[j].index < temp[j + 1].index)) {
						tempLastName = temp[j].lastName;
						tempName = temp[j].name;
						tempPatronymic = temp[j].patronymic;
						tempCreatedTime = temp[j].createdTime;
						tempModTime = temp[j].modTime;
						tempCard = temp[j].libraryCard;
						tempForm = temp[j].formOfEducation;
						tempSex = temp[j].sex;
						for (int a = 0; a < 8; ++a)
							tempGrades[a] = temp[j].grades[a];
						temp[j].lastName = temp[j + 1].lastName;
						temp[j].name = temp[j + 1].name;
						temp[j].patronymic = temp[j + 1].patronymic;
						temp[j].createdTime = temp[j + 1].createdTime;
						temp[j].modTime = temp[j + 1].modTime;
						temp[j].libraryCard = temp[j + 1].libraryCard;
						temp[j].formOfEducation = temp[j + 1].formOfEducation;
						temp[j].sex = temp[j + 1].sex;
						for (int a = 0; a < 8; ++a)
							temp[j].grades[a] = temp[j + 1].grades[a];
						temp[j + 1].lastName = tempLastName;
						temp[j + 1].name = tempName;
						temp[j + 1].patronymic = tempPatronymic;
						temp[j + 1].createdTime = tempCreatedTime;
						temp[j + 1].modTime = tempModTime;
						temp[j + 1].libraryCard = tempCard;
						temp[j + 1].formOfEducation = tempForm;
						temp[j + 1].sex = tempSex;
						for (int a = 0; a < 8; ++a)
							temp[j + 1].grades[a] = tempGrades[a];
					}
					else if ((temp[j].lastName == temp[j + 1].lastName && temp[j].name == temp[j + 1].name && temp[j].patronymic < temp[j + 1].patronymic && temp[j].index > temp[j + 1].index) || (temp[j].lastName == temp[j + 1].lastName && temp[j].name == temp[j + 1].name && temp[j].patronymic > temp[j + 1].patronymic && temp[j].index < temp[j + 1].index)) {
						tempLastName = temp[j].lastName;
						tempName = temp[j].name;
						tempPatronymic = temp[j].patronymic;
						tempCreatedTime = temp[j].createdTime;
						tempModTime = temp[j].modTime;
						tempCard = temp[j].libraryCard;
						tempForm = temp[j].formOfEducation;
						tempSex = temp[j].sex;
						for (int a = 0; a < 8; ++a)
							tempGrades[a] = temp[j].grades[a];
						temp[j].lastName = temp[j + 1].lastName;
						temp[j].name = temp[j + 1].name;
						temp[j].patronymic = temp[j + 1].patronymic;
						temp[j].createdTime = temp[j + 1].createdTime;
						temp[j].modTime = temp[j + 1].modTime;
						temp[j].libraryCard = temp[j + 1].libraryCard;
						temp[j].formOfEducation = temp[j + 1].formOfEducation;
						temp[j].sex = temp[j + 1].sex;
						for (int a = 0; a < 8; ++a)
							temp[j].grades[a] = temp[j + 1].grades[a];
						temp[j + 1].lastName = tempLastName;
						temp[j + 1].name = tempName;
						temp[j + 1].patronymic = tempPatronymic;
						temp[j + 1].createdTime = tempCreatedTime;
						temp[j + 1].modTime = tempModTime;
						temp[j + 1].libraryCard = tempCard;
						temp[j + 1].formOfEducation = tempForm;
						temp[j + 1].sex = tempSex;
						for (int a = 0; a < 8; ++a)
							temp[j + 1].grades[a] = tempGrades[a];
					}
				}
			}
			for (int i = 0; i < amount; ++i) {
				if (inmate[i].group == temp[0].group) {
					for (int k = 0; k < studentsAmount; ++k)
						if (inmate[i].libraryCard == temp[k].libraryCard)
							inmate[i].index = temp[k].index;
				}
			}
		}
	}
	else if (amount > 0)
		inmate[amount - 1].index = 1;
}/*Индексация стунедтов в группе*/

student* deleteData(student* &inmate, int &amount) {
	bool mustBeDeleted;
	for (int i = 0; i < amount; ++i) {
		mustBeDeleted = 0;
		for (int j = 0; j < 8; ++j) {
			if (inmate[i].grades[j] == 2) {
				mustBeDeleted = 1;
				break;
			}
		}
		if (mustBeDeleted) {
			student* temp = new student[amount - 1];
			for (int k = 0; k < i; ++k)
				temp[k] = inmate[k];
			for (int k = i + 1; k < amount - 1; ++k)
				temp[k - 1] = inmate[k];
			delete[] inmate;
			inmate = temp;
			--amount;
		}
	}
	return inmate;
}/*Удаление данных о студентах с 2*/

void editData(student* &inmate, int &amount)  {
	std::cout << std::endl;
	std::cout << "Введите номер читательского билета студента, чьи данные необходимо изменить: ";
	int number = getID();
	bool found = 0;
	for (int i = 0; i < amount; ++i) {
		if (number == inmate[i].libraryCard) {
			found = 1;
			break;
		}
	}
	if (found == 0) {
		std::cout << "Нет такого студента." << std::endl;
	}
	else {
		std::cout << "Введите фамилию " << number << " студента: ";
		inmate[number - 1].lastName = getPartOfTheName(2);
		std::cout << "Введите имя " << number << " студента: ";
		inmate[number - 1].name = getPartOfTheName(1);;
		std::cout << "Введите отчество " << number << " студента: ";
		inmate[number - 1].patronymic = getPartOfTheName(0);;
		std::cout << "Введите пол " << number << " студента (м - 1/ж - 0): ";
		inmate[number - 1].sex = getSex();
		std::cout << "Введите форму обучения " << number << " студента (очная - 2/очно-заочная - 1/заочная - 0): ";
		inmate[number - 1].formOfEducation = getForm();
		std::cout << "Введите номер группы " << number << " студента [0...9999]: ";
		inmate[number - 1].group = getGroup(inmate, amount, number - 1);
		for (int i = 0; i < 8; ++i) {
			if (i < 3) {
				std::cout << "Введите оценку " << number << " студента за " << i + 1 << " экзамен: ";
				inmate[number - 1].grades[i] = getGrade();
			}
			else {
				std::cout << "Введите оценку " << number << " студента за " << i - 2 << " зачёт: ";
				inmate[number - 1].grades[i] = getGrade();
			}
		}
		char temp[80];
		time_t now = time(NULL);
		tm* localTime = localtime(&now);
		strftime(temp, 17, "%H:%M %d.%m.%Y", localTime);
		inmate[number - 1].modTime.clear();
		for (int i = 0; temp[i] != '\0'; ++i)
			inmate[number - 1].modTime.push_back(temp[i]);
	}
	std::cout << std::endl;
}/*Редактирование данных о студенте*/

void drawTable() {
	SetConsoleTextAttribute(textColour, 240);
	std::cout << std::endl;
	std::cout.width(16);
	std::cout << "Фамилия|";
	std::cout.fill(' ');
	std::cout.width(16);
	std::cout << "Имя|";
	std::cout.fill(' ');
	std::cout.width(16);
	std::cout << "Отчество|";
	std::cout.fill(' ');
	std::cout.width(6);
	std::cout << " Пол |";
	std::cout.width(16);
	std::cout << " Форма обучения|";
	std::cout.width(6);
	std::cout << " № гр.|";
	std::cout.width(9);
	std::cout << " № в гр.|";
	std::cout.width(9);
	std::cout << " Оценки:|";
	std::cout.width(7);
	std::cout << " экз.:|";
	for (int i = 0; i < 3; ++i) {
		std::cout.width(2);
		std::cout << i + 1 << " |";
	}
	std::cout.width(7);
	std::cout << " зач.:|";
	for (int i = 0; i < 5; ++i) {
		std::cout.width(2);
		std::cout << i + 1 << " |";
	}
	std::cout.width(15);
	std::cout << " № чит. билета|";
	std::cout.width(18);
	std::cout << " Запись создана|";
	std::cout.width(18);
	std::cout << " Запись изменена" << std::endl;
	SetConsoleTextAttribute(textColour, 7);
}/*Вывод хедера таблицы*/

void showData(student* &inmate, int number) {
	std::cout.width(15);
	std::cout << inmate[number].lastName << "|";
	std::cout.width(15);
	std::cout << inmate[number].name << "|";
	std::cout.width(15);
	std::cout << inmate[number].patronymic << "|";
	std::cout.width(5);
	if (inmate[number].sex) {
		SetConsoleTextAttribute(textColour, 9);
		std::cout << "М  ";
		SetConsoleTextAttribute(textColour, 7);
		std::cout << "|";
	}
	else {
		SetConsoleTextAttribute(textColour, 13);
		std::cout << "Ж  ";
		SetConsoleTextAttribute(textColour, 7);
		std::cout << "|";
	}
	std::cout.width(15);
	if (inmate[number].formOfEducation == 2) {
		SetConsoleTextAttribute(textColour, 12);
		std::cout << "Очная";
		SetConsoleTextAttribute(textColour, 7);
		std::cout << "|";
	}
	else if (inmate[number].formOfEducation == 1) {
		SetConsoleTextAttribute(textColour, 14);
		std::cout << "Очно-заочная";
		SetConsoleTextAttribute(textColour, 7);
		std::cout << "|";
	}
	else {
		SetConsoleTextAttribute(textColour, 11);
		std::cout << "Заочная";
		SetConsoleTextAttribute(textColour, 7);
		std::cout << "|";
	}
	std::cout.width(6);
	std::cout << inmate[number].group << "|";
	std::cout.width(8);
	std::cout << inmate[number].index << "|";
	std::cout.width(8);
	std::cout << "";
	std::cout.fill(' ');
	std::cout << "|";
	std::cout.width(6);
	std::cout << " ";
	std::cout.fill(' ');
	std::cout << "|";
	for (int j = 0; j < 3; ++j) {
		std::cout.width(2);
		if (inmate[number].grades[j] == 3)
			SetConsoleTextAttribute(textColour, 12);
		else if (inmate[number].grades[j] == 4)
			SetConsoleTextAttribute(textColour, 14);
		else
			SetConsoleTextAttribute(textColour, 10);
		std::cout << inmate[number].grades[j];
		SetConsoleTextAttribute(textColour, 7);
		std::cout << " |";
	}
	std::cout.width(6);
	std::cout << "";
	std::cout.fill(' ');
	std::cout << "|";
	for (int j = 3; j < 8; ++j) {
		std::cout.width(2);
		if (inmate[number].grades[j] == 3)
			SetConsoleTextAttribute(textColour, 12);
		else if (inmate[number].grades[j] == 4)
			SetConsoleTextAttribute(textColour, 14);
		else
			SetConsoleTextAttribute(textColour, 10);
		std::cout << inmate[number].grades[j];
		SetConsoleTextAttribute(textColour, 7);
		std::cout << " |";
	}
	std::cout << " ";
	std::cout.width(13);
	std::cout << inmate[number].libraryCard << "|";
	std::cout.width(17);
	std::cout << inmate[number].createdTime << "|";
	std::cout.width(18);
	std::cout << inmate[number].modTime << std::endl;
}/*Показать все данные о студенте*/

void maleFemaleAmount(student* &inmate, int &amount) {
	std::cout << std::endl;
	int male = 0;
	for (int i = 0; i < amount; ++i)
		if (inmate[i].sex)
			++male;
	if (male == 0) {
		std::cout << "Нет студентов мужского пола. Количество студентов женского пола: " << amount << std::endl;
	}
	else if (male == amount) {
		std::cout << "Количество студентов мужского пола: " << amount << ". Нет студентов женского пола." << std::endl;
	}
	else
		std::cout << "Количество студентов мужского пола: " << male << ". Количество студентов женского пола: " << amount - male << "." << std::endl;
	std::cout << std::endl;
}/*Показать количество студентов мужского и женского пола*/

void gettingScholarshipAmount(student* &inmate, int &amount) {
	std::cout << std::endl;
	int scholarship = 0, goodGradesAmount;
	for (int i = 0; i < amount; ++i) {
		goodGradesAmount = 0;
		for (int j = 0; j < 8; ++j) {
			if (inmate[i].grades[j] > 3)
				++goodGradesAmount;
		}
		if (goodGradesAmount == 8 && inmate[i].formOfEducation == 2)
			++scholarship;
	}
	if (scholarship == 0)
		std::cout << "Никто не будет получать стипендию." << std::endl;
	else
		std::cout << "Количество студентов, которые будут получать стипендию: " << scholarship << std::endl;
	std::cout << std::endl;
}/*Показать количество студентов, которые будут получать стипендию*/

void informationAboutSpecialStudents(student* &inmate, int &amount) {
	std::cout << std::endl;
	int noScholarship = 0, aAmount, bAmount, excellentAmount = 0, wellAmount = 0, goodAmount = 0;
	std::cout << std::endl;
	for (int i = 0; i < amount; ++i) {
		aAmount = 0, bAmount = 0;
		for (int j = 0; j < 8; ++j) {
			if (inmate[i].grades[j] == 5)
				++aAmount;
			if (inmate[i].grades[j] == 4)
				++bAmount;
		}
		if (aAmount + bAmount != 8 || (aAmount + bAmount == 8 && inmate[i].formOfEducation != 2))
			++noScholarship;
		if (aAmount == 8)
			++excellentAmount;
		if (bAmount == 8)
			++goodAmount;
		if (aAmount + bAmount == 8 && aAmount != 0 && bAmount !=0)
			++wellAmount;
	}
	if (noScholarship != 0) {
		std::cout << "Информация о студентах, не получающих стипендию:" << std::endl;
		drawTable();
		for (int i = 0; i < amount; ++i) {
			aAmount = 0, bAmount = 0;
			for (int j = 0; j < 8; ++j) {
				if (inmate[i].grades[j] == 4)
					++bAmount;
				if (inmate[i].grades[j] == 5)
					++aAmount;
			}
			if (aAmount + bAmount != 8 || (aAmount + bAmount == 8 && inmate[i].formOfEducation != 2))
				showData(inmate, i);
		}
	}
	else
		std::cout << "Никто не получает стипендию." << std::endl;
	std::cout << std::endl;
	if (goodAmount != 0) {
		std::cout << "Информация о студентах, которые учатся только на «хор»:" << std::endl;
		drawTable();
		for (int i = 0; i < amount; ++i) {
			bAmount = 0;
			for (int j = 0; j < 8; ++j) {
				if (inmate[i].grades[j] == 4)
					++bAmount;
			}
			if (bAmount == 8)
				showData(inmate, i);
		}
	}
	else
		std::cout << "Нет студентов, которые учатся только на «хор»." << std::endl;
	std::cout << std::endl;
	if (wellAmount != 0) {
		std::cout << "Информация о студентах, которые учатся одновременно на «хор» и «отл»:" << std::endl;
		drawTable();
		for (int i = 0; i < amount; ++i) {
			aAmount = 0, bAmount = 0;
			for (int j = 0; j < 8; ++j) {
				if (inmate[i].grades[j] == 4)
					++bAmount;
				if (inmate[i].grades[j] == 5)
					++aAmount;
			}
			if (aAmount + bAmount == 8 && aAmount != 0 && bAmount != 0)
				showData(inmate, i);
		}
	}
	else
		std::cout << "Нет студентов, которые учатся одновременно на «хор» и «отл»." << std::endl;
	std::cout << std::endl;
	if (excellentAmount != 0) {
		std::cout << "Информация о студентах, которые учатся только на «отл»:" << std::endl;
		drawTable();
		for (int i = 0; i < amount; ++i) {
			aAmount = 0;
			for (int j = 0; j < 8; ++j) {
				if (inmate[i].grades[j] == 5)
					++aAmount;
			}
			if (aAmount == 8)
				showData(inmate, i);
		}
	}
	else
		std::cout << "Нет студентов, которые учатся только на «отл»." << std::endl;
	std::cout << std::endl;
}/*Показать информацию о студентах, которые не получают стипендию, учатся только на «хор»; учатся на «хор» и «отл»; учатся только на «отл» */

void informationAboutCertainGroup(student* &inmate, int &amount) {
	std::cout << std::endl;
	int studentsAmount = 0;
	short group;
	std::cout << "Введите номер группы: ";
	group = getGroupForSearch();
	std::cout << std::endl;
	for (int i = 0; i < amount; ++i) {
		if (group == inmate[i].group)
			++studentsAmount;
	}
	if (studentsAmount == 0)
		std::cout << "В группе " << group << " студентов не числится." << std::endl;
	else {
		std::cout << "Информация о студентах, которые учатся в " << group << " группе:" << std::endl;
		drawTable();
		for (int i = 0; i < amount; ++i) {
			if (group == inmate[i].group)
				showData(inmate, i);
		}
	}
	std::cout << std::endl;
}/*Показать информацию о студентах из N группы, N инициализируется пользователем*/

void informationAboutTop(student* &inmate, int &amount) {
	std::cout << std::endl;
	int count = 0;
	double sum = 0, avg;
	for (int i = 0; i < amount; ++i) {
		for (int j = 0; j < 8; ++j)
			sum = sum + inmate[i].grades[j];
	}
	avg = sum / 8 / amount;
	for (int i = 0; i < amount; ++i) {
		sum = 0;
		for (int j = 0; j < 8; ++j)
			sum = sum + inmate[i].grades[j];
		if (sum / 8 > avg)
			++count;
	}
	if (count > 0) {
		std::cout << "Информация о студентах, средний балл которых выше среднего (" << avg << "):" << std::endl;
		drawTable();
		for (int i = 0; i < amount; ++i) {
			sum = 0;
			for (int j = 0; j < 8; ++j)
				sum = sum + inmate[i].grades[j];
			if (sum / 8 > avg)
				showData(inmate, i);
		}
	}
	else
		std::cout << "Нет студентов, средний балл которых выше среднего (" << avg << ")." << std::endl;
	std::cout << std::endl;
}/*Показать информацию о топе студентов*/

void informationAboutCertainCreatedTimeStudents(student* &inmate, int &amount) {
	std::cout << std::endl;
	int studentsAmount = 0, comparison;
	std::string date;
	std::cout << "Введите день в формате дд.мм.гггг: ";
	std::cin >> date;
	std::cout << std::endl;
	for (int i = 0; i < amount; ++i) {
		comparison = 0;
		for (int j = 6; j < 16; ++j) {
			if (date[j - 6] == inmate[i].createdTime[j])
				++comparison;
		}
		if (comparison == 10)
			++studentsAmount;
	}
	if (studentsAmount == 0)
		std::cout << "Нет записей, сделанных " << date << "." << std::endl;
	else {
		int am = 0, pm = 0;
		for (int i = 0; i < amount; ++i) {
			if ((inmate[i].createdTime[0] == 0 || inmate[i].createdTime[0] == 1) && inmate[i].createdTime[1] < 2)
				++am;
			else
				++pm;
		}
		std::cout << "Информация о студентах, записи которых были сделаны " << date << ":" << std::endl;
		if (am == 0) {
			std::cout << "Нет записей, сделанных " << date << " до полудня." << std::endl;
			std::cout << "Записи, сделанные " << date << " после полудня:" << std::endl;
			drawTable();
			for (int i = 0; i < amount; ++i) {
				if (!((inmate[i].createdTime[0] == 0 || inmate[i].createdTime[0] == 1) && inmate[i].createdTime[1] < 2))
					showData(inmate, i);
			}
		}
		else if (pm == 0) {
			std::cout << "Записи, сделанные " << date << " до полудня:" << std::endl;
			drawTable();
			for (int i = 0; i < amount; ++i) {
				if ((inmate[i].createdTime[0] == 0 || inmate[i].createdTime[0] == 1) && inmate[i].createdTime[1] < 2)
					showData(inmate, i);
			}
			std::cout << "Нет записей, сделанных " << date << " после полудня." << std::endl;
		}
		else {
			std::cout << "Записи, сделанные " << date << " до полудня:" << std::endl;
			drawTable();
			for (int i = 0; i < amount; ++i) {
				if ((inmate[i].createdTime[0] == 0 || inmate[i].createdTime[0] == 1) && inmate[i].createdTime[1] < 2)
					showData(inmate, i);
			}
			std::cout << "Записи, сделанные " << date << " после полудня:" << std::endl;
			drawTable();
			for (int i = 0; i < amount; ++i) {
				if (!((inmate[i].createdTime[0] == 0 || inmate[i].createdTime[0] == 1) && inmate[i].createdTime[1] < 2))
					showData(inmate, i);
			}
		}
	}
	std::cout << std::endl;
}/*Показать информацию о студентах, записи которых были сделаны определённого числа (до полудня/после полудня)*/

void informationAboutCertainIndexStudents(student* &inmate, int &amount) {
	std::cout << std::endl;
	int studentsAmount = 0;
	short index;
	std::cout << "Введите номер студента в списке: ";
	index = getIndex();
	std::cout << std::endl;
	for (int i = 0; i < amount; ++i) {
		if (index == inmate[i].index)
			++studentsAmount;
	}
	if (studentsAmount == 0)
		std::cout << "Нет студентов с порядковым номером " << index << "." << std::endl;
	else {
		std::cout << "Информация о студентах, которые имеют " << index << " порядковый номер в списке группы:" << std::endl;
		drawTable();
		for (int i = 0; i < amount; ++i) {
			if (index == inmate[i].index)
				showData(inmate, i);
		}
	}
	std::cout << std::endl;
}/*Показать информацию о студентах, имеющих k номер в списке*/

void outputToFile(student* &inmate, int &amount) {
	std::ofstream out;          /*Поток для записи с именем out*/
	out.open("C:\\students.txt"); /*Открытие файла*/
	if (out.is_open()) {
		out.width(16);
		out << "Фамилия|";
		out.fill(' ');
		out.width(16);
		out << "Имя|";
		out.fill(' ');
		out.width(16);
		out << "Отчество|";
		out.fill(' ');
		out.width(6);
		out << " Пол |";
		out.width(16);
		out << " Форма обучения|";
		out.width(6);
		out << " № гр.|";
		out.width(9);
		out << " № в гр.|";
		out.width(9);
		out << " Оценки:|";
		out.width(7);
		out << " экз.:|";
		for (int i = 0; i < 3; ++i) {
			out.width(2);
			out << i + 1 << " |";
		}
		out.width(7);
		out << " зач.:|";
		for (int i = 0; i < 5; ++i) {
			out.width(2);
			out << i + 1 << " |";
		}
		out.width(15);
		out << " № чит. билета|";
		out.width(18);
		out << " Запись создана|";
		out.width(18);
		out << " Запись изменена" << std::endl;
		for (int i = 0; i < amount; ++i) {
			out.width(15);
			out << inmate[i].lastName << "|";
			out.width(15);
			out << inmate[i].name << "|";
			out.width(15);
			out << inmate[i].patronymic << "|";
			out.width(5);
			if (inmate[i].sex) {
				out << "М  ";
				out << "|";
			}
			else {
				out << "Ж  ";
				out << "|";
			}
			out.width(15);
			if (inmate[i].formOfEducation == 2) {
				out << "Очная";
				out << "|";
			}
			else if (inmate[i].formOfEducation == 1) {
				out << "Очно-заочная";
				out << "|";
			}
			else {
				out << "Заочная";
				out << "|";
			}
			out.width(6);
			out << inmate[i].group << "|";
			out.width(8);
			out << inmate[i].index << "|";
			out.width(8);
			out << "";
			out.fill(' ');
			out << "|";
			out.width(6);
			out << " ";
			out.fill(' ');
			out << "|";
			for (int j = 0; j < 3; ++j) {
				out.width(2);
				out << inmate[i].grades[j];
				SetConsoleTextAttribute(textColour, 7);
				out << " |";
			}
			out.width(6);
			out << "";
			out.fill(' ');
			out << "|";
			for (int j = 3; j < 8; ++j) {
				out.width(2);
				out << inmate[i].grades[j];
				SetConsoleTextAttribute(textColour, 7);
				out << " |";
			}
			out << " ";
			out.width(13);
			out << inmate[i].libraryCard << "|";
			out.width(17);
			out << inmate[i].createdTime << "|";
			out.width(18);
			out << inmate[i].modTime << std::endl;
		}
	}
	out.close(); /*Закрытие файла*/
	std::cout << std::endl << "Данные успешно записаны в С:\\students.txt." << std::endl;
	std::cout << std::endl;
} /*Запись данных в файл C:\students.txt*/

void showLibraryMenu() {
	std::cout << std::endl;
	std::cout << "Выберите опцию . . ." << std::endl;
	std::cout << "0. Взять книгу" << std::endl;
	std::cout << "1. Вернуть книгу" << std::endl;
	std::cout << "2. Выйти" << std::endl;
	std::cout << "Опция: ";
}

short getLibraryMenuOption() {
	while (true) {
		short userNumber;
		std::cin >> userNumber;
		if (std::cin.fail() || userNumber < 0 || userNumber > 2) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << std::endl << "Введите опцию [0...2]: ";
		}
		else if (userNumber == 0 || userNumber == 1 || userNumber == 2) {
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}

void drawLibraryTable(book library[], const short &amount) {
	std::cout << std::endl;
	std::cout << "Если книга находится в библиотеке, № билета == 0" << std::endl;
	SetConsoleTextAttribute(textColour, 240);
	std::cout << std::endl;
	std::cout.width(9);
	std::cout << "№ книги|";
	std::cout.width(23);
	std::cout << " Автор|";
	std::cout.fill(' ');
	std::cout.width(26);
	std::cout << " Название|";
	std::cout.fill(' ');
	std::cout.width(13);
	std::cout << " Год издания|";
	std::cout.fill(' ');
	std::cout.width(9);
	std::cout << " Страниц|";
	std::cout.width(10);
	std::cout << " № билета";
	SetConsoleTextAttribute(textColour, 7);
	std::cout << std::endl;
	for (int i = 0; i < amount; ++ i) {
		std::cout.width(8);
		std::cout << i << "|";
		std::cout.width(22);
		std::cout << library[i].author << "|";
		std::cout.fill(' ');
		std::cout.width(25);
		std::cout << library[i].name << "|";
		std::cout.fill(' ');
		std::cout.width(12);
		std::cout << library[i].year << "|";
		std::cout.fill(' ');
		std::cout.width(8);
		std::cout << library[i].pages << "|";
		std::cout.width(10);
		if (library[i].libraryCard == 0)
			SetConsoleTextAttribute(textColour, 10);
		else
			SetConsoleTextAttribute(textColour, 13);
		std::cout << library[i].libraryCard;
		SetConsoleTextAttribute(textColour, 7);
		std::cout << std::endl;
	}
}

short getBook() {
	while (true) {
		short userNumber;
		std::cin >> userNumber;
		if (std::cin.fail() || userNumber < 0 || userNumber > 14) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << std::endl << "Введите № книги [0...14]: ";
		}
		else {
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}

void libraryBooks(student* &inmate, book library[], int &amount, bool action) {
	std::cout << std::endl;
	int ID, position;
	short number;
	bool found = 0;
	if (action) {
		std::cout << "Введите № книги [0...14], которую вы хотите взять: ";
		number = getBook();
		if (library[number].libraryCard == 0) {
			std::cout << "№ вашего читательского билета: ";
			ID = getID();
			for (int i = 0; i < amount; ++i) {
				if (ID == inmate[i].libraryCard) {
					found = 1;
					ID = inmate[i].libraryCard;
					position = i;
					break;
				}
			}
			if (found) {
				library[number].libraryCard = inmate[position].libraryCard;
				std::cout << inmate[position].name << " " << inmate[position].patronymic << ", теперь вы счастливый обладатель книги " << library[number].name << "!" << std::endl;
			}
			else
				std::cout << "Нет студента с таким № читательского билета." << std::endl;
		}
		else
			std::cout << "Книга №" << number << " у студента с читательским билетом №" << library[number].libraryCard << "." << std::endl;
	}
	else {
		std::cout << "Введите № возвращаемой книги [0...14]: ";
		number = getBook();
		if (library[number].libraryCard != 0) {
			library[number].libraryCard = 0;
			std::cout << "Книга успешно возвращена в библиотеку." << std::endl;
		}
		else
			std::cout << "Книга №" << number << " уже в библиотеке." << std::endl;
	}
}

#endif]