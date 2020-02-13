#include "Func.h"

int main() {
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	student* students = 0;
	const short booksAmount = 15;
	book books[booksAmount] = {
		{"Достоевский Ф. М.", "Преступление и наказание", 2001, 583, 0}, 
	    {"Булгаков М. А.", "Мастер и Маргарита", 2003, 367, 0},
		{"Булгаков М. А.", "Собачье сердце", 1989, 93, 0},
		{"Толстой Л. Н.", "Война и Мир. Том 1", 1996, 308, 0},
		{"Толстой Л. Н.", "Война и Мир. Том 2", 1996, 322, 0},
		{"Толстой Л. Н.", "Война и Мир. Том 3", 1996, 346, 0},
		{"Толстой Л. Н.", "Война и Мир. Том 4", 1996, 202, 0},
		{"Толстой Л. Н.", "Война и Мир. Эпилог", 1996, 96, 0},
		{"Солженицын А. И.", "Раковый корпус", 1968, 512, 0},
		{"Солженицын А. И.", "Архипелаг ГУЛАГ", 2013, 1724, 0},
		{"Дюма А.", "Граф Монте-Кристо. Том 1", 2012, 650, 0},
		{"Дюма А.", "Граф Монте-Кристо. Том 2", 2012, 650, 0},
		{"Кастанеда К. С. С. А.", "Отдельная реальность", 1971, 416, 0},
		{"Шолохов М. А.", "Тихий Дон", 2011, 940, 0},
		{"Гоголь Н. В.", "Мёртвые души", 1967, 368, 0},
	};
	int amount = 0, library = 1;
	short menuOption;
	bool condition = 1;
	while (condition) {
		menu();
		menuOption = getMenuOption();
		switch(menuOption) {
		case 0: {
			students = addStudent(students, amount);
			addData(students, amount, library);
			students = deleteData(students, amount);
			sort(students, amount);
			break;
		}
		case 1: {
			if (amount == 0)
				std::cout << std::endl << "Нет записей." << std::endl << std::endl;
			else {
				editData(students, amount);
				students = deleteData(students, amount);
				sort(students, amount);
			}
			break;
		}
		case 2: {
			if (amount == 0)
				std::cout << std::endl << "Нет записей." << std::endl << std::endl;
			else {
				drawTable();
				for (int i = 0; i < amount; ++i)
					showData(students, i);
				std::cout << std::endl;
			}
			break;
		}
		case 3: {
			if (amount == 0)
				std::cout << std::endl << "Нет записей." << std::endl << std::endl;
			else
				groupStudents(students, amount);
			break;
		}
		case 4: {
			if (amount == 0)
				std::cout << std::endl << "Нет записей." << std::endl << std::endl;
			else
				topStudents(students, amount);
			break;
		}
		case 5: {
			if (amount == 0)
				std::cout << std::endl << "Нет записей." << std::endl << std::endl;
			else
				maleFemaleAmount(students, amount);
			break;
		}
		case 6: {
			if (amount == 0)
				std::cout << std::endl << "Нет записей." << std::endl << std::endl;
			else
				scholarshipAmount(students, amount);
			break;
		}
		case 7: {
			if (amount == 0)
				std::cout << std::endl << "Нет записей." << std::endl << std::endl;
			else
				specialStudents(students, amount);
			break;
		}
		case 8: {
			if (amount == 0)
				std::cout << std::endl << "Нет записей." << std::endl << std::endl;
			else
				timeStudents(students, amount);
			break;
		}
		case 9: {
			if (amount == 0)
				std::cout << std::endl << "Нет записей." << std::endl << std::endl;
			else
				indexStudents(students, amount);
			break;
		}
		case 10: {
			if (amount == 0)
				std::cout << std::endl << "Нет записей." << std::endl << std::endl;
			else
				output(students, amount);
			break;
		}
		case 11: {
			if (amount == 0)
				std::cout << std::endl << "Нет студентов. Библиотека закрыта." << std::endl << std::endl;
			else {
				bool libraryCondition = 1;
				short libraryMenuOption;
				while (libraryCondition) {
					libraryMenu();
					libraryMenuOption = libraryOption();
					switch(libraryMenuOption) {
					case 0: {
						drawLibrary(books, booksAmount);
						libraryBooks(students, books, amount, 1);
						break;
					}
					case 1: {
						drawLibrary(books, booksAmount);
						libraryBooks(students, books, amount, 0);
						break;
					}
					case 2: {
						libraryCondition = 0;
						std::cout << std::endl;
						break;
					}
					}
				}
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
