#include "functions.h"

int main() {
	setlocale(0, "");
	srand((unsigned)time(NULL));
	Tree* root = 0;
	int amount = 0;
	bool condition = 1;
	showConsoleCursor(0);
	while (condition) {
		short option = menu();
		switch (option) {
		case 0: { // Создать AVL дерево
			createTree(root, amount);
			break;
		}
		case 1: { // Вывести в консоль и файл AVL дерево
			representTree(root);
			break;
		}
		case 2: { // Вставить, найти или удалить элемент в AVL дереве
			actionsWithTree(root, amount);
			break;
		}
		case 3: { // Проверить на сбалансированность AVL дерево
			balanceSpeed(root);
			break;
		}
		case 4: { // Создать ещё одно дерево той же размерности, заполненное случайными числами [-99...99], и соединить их
			myVariant(root, amount);
			break;
		}
		case 5: {
			condition = 0;
			break;
		}
		}
	}
	deleteTree(root);
	return 0;
}