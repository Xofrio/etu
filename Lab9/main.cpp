#include "Functions.h"

int main() {
	setlocale(0, "");
	srand((unsigned)time(NULL));
	branch *root = 0;
	bool condition = 1, done = 0;
	showConsoleCursor(0);
	while (condition) {
		short option = menu();
		switch (option) {
		case 0: { //Создать бинарное дерево
			createTree(root, done);
			break;
		}
		case 1: { //Вывести в файл и консоль бинарное дерево
			representTree(root);
			break;
		}
		case 2: { //Вставить, найти или удалить элемент в бинарном дереве
			actionsWithTree(root, done);
			break;
		}
		case 3: { //Прямой обход, обратный обход, обход в ширину бинарного дерева
			treeTraversal(root);
			break;
		}
		case 4: { //Удалить все отрицательные элементы, каждый элемент умножить на случайную величину [-2...2]
			myVariant(root, done);
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
