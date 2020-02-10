#include "Func.h"

int main() {
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	student* students = 0;
	int amount = 0, library = 1;
	short menuOption;
	bool condition = 1;
	while (condition) {
		showMenu();
		menuOption = getMenuOption();
		switch(menuOption) {
		case 0: {
			students = addStudent(students, amount);
			addData(students, amount, library);
			sort(students, amount);
			break;
		}
		case 1: {
			if (amount == 0)
				std::cout << "Нет записей." << std::endl << std::endl;
			else {
				editData(students, amount);
				sort(students, amount);
			}
			break;
		}
		case 2: {
			if (amount == 0)
				std::cout << "Нет записей." << std::endl << std::endl;
			else {
				students = deleteData(students, amount);
				if (amount == 0)
					std::cout << "Нет записей." << std::endl << std::endl;
				else {
					sort(students, amount);
					drawTable();
					for (int i = 0; i < amount; ++i)
						showData(students, i);
					std::cout << std::endl;
				}
			}
			break;
		}
		case 3: {
			if (amount == 0)
				std::cout << "Нет записей." << std::endl << std::endl;
			else {
				students = deleteData(students, amount);
				if (amount == 0)
					std::cout << "Нет записей." << std::endl << std::endl;
				else
					informationAboutCertainGroup(students, amount);
			}
			break;
		}
		case 4: {
			if (amount == 0)
				std::cout << "Нет записей." << std::endl << std::endl;
			else {
				students = deleteData(students, amount);
				if (amount == 0)
					std::cout << "Нет записей." << std::endl << std::endl;
				else
					informationAboutTop(students, amount);
			}
			break;
		}
		case 5: {
			if (amount == 0)
				std::cout << "Нет записей." << std::endl << std::endl;
			else {
				students = deleteData(students, amount);
				if (amount == 0)
					std::cout << "Нет записей." << std::endl << std::endl;
				else
					maleFemaleAmount(students, amount);
			}
			break;
		}
		case 6: {
			if (amount == 0)
				std::cout << "Нет записей." << std::endl << std::endl;
			else {
				students = deleteData(students, amount);
				if (amount == 0)
					std::cout << "Нет записей." << std::endl << std::endl;
				else
					gettingScholarshipAmount(students, amount);
			}
			break;
		}
		case 7: {
			if (amount == 0)
				std::cout << "Нет записей." << std::endl << std::endl;
			else {
				students = deleteData(students, amount);
				if (amount == 0)
					std::cout << "Нет записей." << std::endl << std::endl;
				else
					informationAboutSpecialStudents(students, amount);
			}
			break;
		}
		case 8: {
			if (amount == 0)
				std::cout << "Нет записей." << std::endl << std::endl;
			else {
				students = deleteData(students, amount);
				if (amount == 0)
					std::cout << "Нет записей." << std::endl << std::endl;
				else
					informationAboutCertainCreatedTimeStudents(students, amount);
			}
			break;
		}
		case 9: {
			if (amount == 0)
				std::cout << "Нет записей." << std::endl << std::endl;
			else {
				students = deleteData(students, amount);
				if (amount == 0)
					std::cout << "Нет записей." << std::endl << std::endl;
				else
					informationAboutCertainIndexStudents(students, amount);
			}
			break;
		}
		case 10: {
			if (amount == 0)
				std::cout << "Нет записей." << std::endl << std::endl;
			else {
				students = deleteData(students, amount);
				if (amount == 0)
					std::cout << "Нет записей." << std::endl << std::endl;
				else
					outputToFile(students, amount);
			}
			break;
		}
		case 12: {
			condition = 0;
			break;
		}
		}
	}
	delete[] students;
	system("pause");
	return 0;
}