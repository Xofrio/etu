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
	std::string name;
	std::string lastName;
	std::string patronymic;
	bool sex;
	short group;
	short index;
	short grades[8];
	short formOfEducation;
	int libraryCard;
	std::string createdTime;
	std::string modTime;
};/*Создание структуры student со всеми необходимыми полями.*/

struct book {
	std::string author;
	std::string name;
	short year;
	short pages;
	int libraryCard;
};/*Создание структуры book со всеми необходимыми полями*/

int getMenuOption() {
	while (true) {
		int userNumber;
		std::cin >> userNumber;
		if (std::cin.fail() || userNumber < 0 || userNumber > 12) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << std::endl << "Введите опцию [0...12]: ";
		}
		else if (userNumber == 0 || userNumber == 1 || userNumber == 2 || userNumber == 3 || userNumber == 4 || userNumber == 5 || userNumber == 6 || userNumber == 7 || userNumber == 8 || userNumber == 9 || userNumber == 10 || userNumber == 12) {
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}/*Выбор в меню.*/

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

short getGroup(student* inmate, int amount, int position) {
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
}/*Запись группу.*/

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
	std::cout << "12. Выйти" << std::endl;
	std::cout << "Опция: ";
}/*Вывод меню*/

student* addStudent(student* inmate, int amount) {
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

void addData(student* inmate, int &amount, int &library) {
	std::cout << std::endl;
	std::cout << "Введите фамилию студента: ";
	std::cin >> inmate[amount].lastName;
	std::cout << "Введите имя студента: ";
	std::cin >> inmate[amount].name;
	std::cout << "Введите отчество студента: ";
	std::cin >> inmate[amount].patronymic;
	std::cout << "Введите пол студента (м - 1/ж - 0): ";
	inmate[amount].sex = getSex();
	std::cout << "Введите форму обучения студента (очная - 2/очно-заочная - 1/заочная - 0): ";
	inmate[amount].formOfEducation = getForm();
	std::cout << "Введите номер группы студента [0...9999]: ";
	inmate[amount].group = getGroup(inmate, amount, amount);
	for (int i = 0; i < 8; ++i) {
		if (i < 3) {
			std::cout << "Введите оценку студента за " << i + 1 << " экзамен: ";
			inmate[amount].grades[i] = getGrade();
		}
		else {
			std::cout << "Введите оценку студента за " << i - 2 << " зачёт: ";
			inmate[amount].grades[i] = getGrade();
		}
	}
	char temp[80];

	time_t now = time(NULL);
	tm* localTime = localtime(&now);
	strftime(temp, 17, "%H:%M %d.%m.%Y", localTime);
	for (int i = 0; temp[i] != '\0' ; ++i)
		inmate[amount].modTime.push_back(temp[i]);
	inmate[amount].createdTime = inmate[amount].modTime;
	inmate[amount].libraryCard = library;
	++amount;
	++library;
	std::cout << std::endl;
}/*Добавление данных о студенте*/

student* deleteData(student* inmate, int &amount) {
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

void editData(student* inmate, int amount)  {
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
		std::cin >> inmate[number - 1].lastName;
		std::cout << "Введите имя " << number << " студента: ";
		std::cin >> inmate[number - 1].name;
		std::cout << "Введите отчество " << number << " студента: ";
		std::cin >> inmate[number - 1].patronymic;
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

void showData(student* inmate, int number) {
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

void maleFemaleAmount(student* inmate, int &amount) {
	inmate = deleteData(inmate, amount);
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

void gettingScholarshipAmount(student* inmate, int &amount) {
	inmate = deleteData(inmate, amount);
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

void informationAboutSpecialStudents(student* inmate, int &amount) {
	inmate = deleteData(inmate, amount);
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

void informationAboutCertainGroup(student* inmate, int &amount) {
	inmate = deleteData(inmate, amount);
	std::cout << std::endl;
	int studentsAmount = 0;
	short group;
	std::cout << "Введите номер группы: ";
	group = getGroup(inmate, amount, amount);
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

void informationAboutTop(student* inmate, int &amount) {
	inmate = deleteData(inmate, amount);
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

void informationAboutCertainCreatedTimeStudents(student* inmate, int &amount) {
	inmate = deleteData(inmate, amount);
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

void informationAboutCertainIndexStudents(student* inmate, int &amount) {
	inmate = deleteData(inmate, amount);
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

void outputToFile(student* inmate, int &amount) {
	inmate = deleteData(inmate, amount);
	std::ofstream out;          // поток для записи с именем out
	out.open("C:\\students.txt"); // окрываем файл для записи
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
	out.close();
	std::cout << std::endl << "Данные успешно записаны в С:\\students.txt." << std::endl;
	std::cout << std::endl;
} /*Запись данных в файл C:\students.txt*/

#endif

/*На территории университета действует библиотека. Каждому студенту нужно присвоить номер его читательского билета. Создайте новую
структуру, где будет храниться данные о книгах: автор, название, год издания, количество страниц, номер студенческого билета студента,
который взял книгу. Если книга находится в библиотеке по умолчанию номер билета приравнивается к 0.
Студент может взять несколько книг. Необходимо обеспечить возможность возврата книги и ее приобретения.*/

//Сортировка в структуре (по группе), чтобы получить порядковый номер в списке.
//проверка на корректность ввода строки??!
//БИБЛИОТЕКА! KAK PROITI V BIBLIOTEKY???!
