#include "accessory.h"

void deleteTree(Tree* branch) { // Удаление дерева
	if (!branch)
		return;
	deleteTree(branch->left);
	deleteTree(branch->right);
	delete branch;
}

void searchInTree(Tree* root, int& count, int value) { // Поиск элемента в дереве
	Tree* treeCopy = root;
	if (root == 0)
		return;
	bool condition = 1;
	auto begin = steady_clock::now();
	while (condition) {
		if (root == 0) {
			condition = 0;
			break;
		}
		if (value > root->data) { // Если значение искомого элемента больше, чем значение элемента в текущей ветви - продолжаем поиск в правой ветви
			if (root->right == 0)
				condition = 0;
			root = root->right;
		}
		else if (value < root->data) { // Если значение искомого элемента меньше, чем значение элемента в текущей ветви - продолжаем поиск в левой ветви
			if (root->left == 0)
				condition = 0;
			root = root->left;
		}
		else if (value == root->data) { // Если значение искомого элемента равно значению элемента в текущей ветви - берём значение количества
			count = root->count;
			condition = 0;
		} 
	}
	auto end = steady_clock::now();
	if (count == 0) {
		cout << "Таких элементов в дереве нет." << endl;
		cout << "Ваше дерево:" << endl << endl;
	}
	else {
		cout << "Количество элементов со значением '" << value << "' : " << count << "." << endl;
		cout << "Ваше дерево (найденные элементы подсвечены):" << endl << endl;
	}
	printTree(treeCopy, 0, value, 2, 1);
	cout << endl << "Время, затраченное на поиск в дереве (наносек.): " << static_cast<long int>(duration_cast<nanoseconds>(end - begin).count()) << endl;
	return;
}

int getHeight(Tree* branch) { // Вычисление высоты
	return branch ? branch->height : 0;
}

int getBalance(Tree* branch) { // Вычисление баланса между правым и левым
	return branch ? getHeight(branch->right) - getHeight(branch->left) : 0;
}

void balancePlus(Tree* branch){ // Вычисление баланса + 1
	branch->height = (getHeight(branch->left) > getHeight(branch->right) ? getHeight(branch->left) : getHeight(branch->right)) + 1;
}

Tree* rotateRight(Tree* branch) { // Правый поворот
	Tree* leftBranch = branch->left;
	branch->left = leftBranch->right;
	leftBranch->right = branch;
	balancePlus(branch);
	balancePlus(leftBranch);
	return leftBranch;
}

Tree* rotateLeft(Tree* branch) { // Левый поворот
	Tree* rightBranch = branch->right;
	branch->right = rightBranch->left;
	rightBranch->left = branch;
	balancePlus(branch);
	balancePlus(rightBranch);
	return rightBranch;
}

Tree* balance(Tree* branch) { // Балансировка дерева
	balancePlus(branch);
	if (getBalance(branch) == 2)	{ // Если баланс между левым и правым равен 2
		if (getBalance(branch->right) < 0)
			branch->right = rotateRight(branch->right);
		return rotateLeft(branch);
	}
	if (getBalance(branch) == -2) { // Если баланс между левым и правым равен -2
		if (getBalance(branch->left) > 0)
			branch->left = rotateLeft(branch->left);
		return rotateRight(branch);
	}
	return branch;
}

void insert(Tree*& branch, int value, int count, bool mode) { // Вставка ветви
	if (!branch) { // Если ветви не существует - создаём ветвь
		branch = new Tree;
		branch->data = value;
		branch->left = branch->right = 0;
		branch->height = branch->count = 1;
		if (mode == 1)
			branch->count = count;
		branch = balance(branch);
		return;
	}
	if (value == branch->data) // Для повторяющихся элементов счётчик их количества увеличивается на 1
		++branch->count;
	if (branch->data > value) // Если оно меньше того, что в этой ветви - добавляем в левую ветвь
		insert(branch->left, value, count, mode);
	else if (branch->data < value) // Иначе в правую ветвь
		insert(branch->right, value, count, mode);
	branch = balance(branch); // После добавления балансируем дерево
}

Tree* findMinimum(Tree* branch) { // Нахождение минимального элемента
	return branch->left ? findMinimum(branch->left) : branch; // Возрващаем минимум из левой ветви
}

Tree* deleteMinimum(Tree* branch) { // Удаление минимального элемента
	if (branch->left == 0)
		return branch->right;
	branch->left = deleteMinimum(branch->left);
	return balance(branch);
}

Tree* deleteBranch(Tree* branch, int& amount, int value) { // Удаление ветви
	if (!branch)
		return 0;
	if (value < branch->data)
		branch->left = deleteBranch(branch->left, amount, value);
	else if (value > branch->data)
		branch->right = deleteBranch(branch->right, amount, value);
	else {
		if (branch->count > 1) {
			--branch->count;
			--amount;
			return branch;
		}
		Tree* leftBranch = branch->left;
		Tree* rightBranch = branch->right;
		--amount;
		delete branch;
		if (!rightBranch)
			return leftBranch;
		Tree* minimum = findMinimum(rightBranch);
		minimum->right = deleteMinimum(rightBranch);
		minimum->left = leftBranch;
		return balance(minimum);
	}
	return balance(branch);
}

void createTree(Tree*& root, int &amount) { // Создание AVL дерева
	bool condition = 1;
	while (condition) {
		short methodOption = methodMenu();
		switch (methodOption) {
		case 0: { // Пользователь вводит размерность дерева, сами элементы генерируются автоматически в диапазоне [-99...99]
			cout << "Введите размерность AVL дерева: ";
			showConsoleCursor(1);
			amount = getAmount();
			showConsoleCursor(0);
			deleteTree(root);
			root = 0;
			auto begin = steady_clock::now();
			for (int i = 0; i < amount; ++i)
				insert(root, rand() % 199 - 99, 0, 0);
			auto end = steady_clock::now();
			cout << "AVL дерево из " << amount << " элементов успешно создано" << endl;
			cout << "Время, затраченное на создание дерева (наносек): " << static_cast<long int>(duration_cast<nanoseconds>(end - begin).count()) << endl;
			fallBack();
			return;
		}
		case 1: { // Пользователь вводит элементы с клавиатуры
			amount = 0;
			string::size_type size;
			cout << "Введите через пробел значения AVL дерева: ";
			showConsoleCursor(1);
			string input = getValues(amount);
			showConsoleCursor(0);
			deleteTree(root);
			root = 0;
			auto begin = steady_clock::now();
			for (int i = 0; i < amount; ++i) {
				insert(root, stoi(input, &size), 0, 0);
				input = input.substr(size);
			}
			auto end = steady_clock::now();
			cout << "AVL дерево из " << amount << " элементов успешно создано" << endl;
			cout << "Время, затраченное на создание дерева (наносек): " << static_cast<long int>(duration_cast<nanoseconds>(end - begin).count()) << endl;
			fallBack();
			return;
		}
		case 2: { // Элементы считываются с файла
			ifstream file("input.txt");
			if (file.is_open()) {
				string input;
				bool bad = 0;
				getline(file, input, '\0');
				cout << input << "." << endl;
				file.close();
				checkString(input, amount, bad);
				if (bad == 0) {
					int amount = 0;
					string::size_type size;
					deleteTree(root);
					root = 0;
					auto begin = steady_clock::now();
					for (int i = 0; i < amount; ++i) {
						insert(root, stoi(input, &size), 0, 0);
						input = input.substr(size);
					}
					auto end = steady_clock::now();
					cout << "AVL дерево из " << amount << " элементов успешно создано" << endl;
					cout << "Время, затраченное на создание дерева (наносек): " << static_cast<long int>(duration_cast<nanoseconds>(end - begin).count()) << endl;
				}
				else
					cout << "AVL дерево не было создано. Проверьте содержание файла 'inputAVL.txt'." << endl;
			}
			else
				cout << "Файл с именем 'inputAVL.txt' не найден." << endl;
			fallBack();
			return;
		}
		case 3: {
			condition = 0;
			break;
		}
		}
	}
	return;
}

void createArrayFromTree(Tree* forArray, vector <short>& array, vector <short>& count) { // Создание массива и списка из дерева
	if (forArray == 0)
		return;
	queue <Tree*> chainForArray; // Создаём очередь
	chainForArray.push(forArray); // Помещаем корень в очередь
	while (!chainForArray.empty()) {
		Tree* copy = chainForArray.front();
		chainForArray.pop();
		array.push_back(copy->data);
		if (copy->left != 0) // Если указатель на левую ветвь не указывает на 0 - помещаем в очередь левую ветвь
			chainForArray.push(copy->left);
		if (copy->right != 0) // Если указатель на правую ветвь не указывает на 0 - помещаем в очередь правую ветвь
			chainForArray.push(copy->right);
	}
	queue <Tree*> chainForCount;
	chainForCount.push(forArray);
	while (!chainForCount.empty()) {
		Tree* copy = chainForCount.front();
		chainForCount.pop();
		count.push_back(copy->count);
		if (copy->left != 0) // Если указатель на левую ветвь не указывает на 0 - помещаем в очередь левую ветвь
			chainForCount.push(copy->left);
		if (copy->right != 0) // Если указатель на правую ветвь не указывает на 0 - помещаем в очередь правую ветвь
			chainForCount.push(copy->right);
	}
}

void actionsWithTree(Tree*& root, int amount) { // Добавление, поиск, удаление элемента в дереве
	if (root == 0) {
		cout << "В дереве нет элементов" << endl;
		fallBack();
		return;
	}
	bool condition = 1;
	while (condition) {
		short actionOption = actionMenu();
		switch (actionOption) {
		case 0: { // Добавление элемента
			if (root == 0) {
				cout << "В дереве нет элементов" << endl;
				fallBack();
				return;
			}
			cout << "Введите значение добавляемого элемента в диапазоне [-99...99]: ";
			short element = getElement();
			cout << endl;
			auto begin = steady_clock::now();
			insert(root, element, 0, 0);
			++amount;
			auto end = steady_clock::now();
			printTree(root, 0, 0, 2, 0);
			cout << endl << "Время, затраченное на добавление элемента в дерево (наносек.): " << static_cast<long int>(duration_cast<nanoseconds>(end - begin).count()) << endl;
			fallBack();
			break;
		}
		case 1: { // Поиск элемента
			if (root == 0) {
				cout << "В дереве нет элементов" << endl;
				fallBack();
				return;
			}
			cout << "Введите значение искомого элемента в диапазоне [-99...99]: ";
			short element = getElement();
			int count = 0;
			searchInTree(root, count, element);
			fallBack();
			break;
		}
		case 2: { // Удаление элемента
			if (root == 0) {
				cout << "В дереве нет элементов" << endl;
				fallBack();
				return;
			}
			cout << "Введите значение удаляемого элемента в диапазоне [-99...99]: ";
			int count = 0;
			short element = getElement();
			searchInTree(root, count, element);
			if (count != 0) {
				auto begin = steady_clock::now();
				root = deleteBranch(root, amount, element);
				auto end = steady_clock::now();
				cout << endl << "Ваше дерево:" << endl << endl;
				printTree(root, 0, 0, 2, 0);
				cout << endl << "Время, затраченное на удаление элемента из дерева (наносек.): " << static_cast<long int>(duration_cast<nanoseconds>(end - begin).count()) << endl;
			}
			fallBack();
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

void balanceSpeed(Tree* root) { // Скорость проверки на сбалансированность
	if (!root) {
		cout << "В дереве нет элементов." << endl;
		fallBack();
		return;
	}
	auto begin = steady_clock::now();
	root = balance(root);
	auto end = steady_clock::now();
	cout << "Время, затраченное на проверку сбалансированности AVL дерева (наносек.): " << static_cast<long int>(duration_cast<nanoseconds>(end - begin).count()) << endl;
	fallBack();
}

void myVariant(Tree*& root, int& amount) { // Создание ещё одного дерева той же размерности, заполненного случайными числами [-99...99], и соединить их
	if (!root) {
		cout << "В дереве нет элементов" << endl;
		fallBack();
		return;
	}
	Tree* newTree = 0;
	for (int i = 0; i < amount; ++i)
		insert(newTree, rand() % 199 - 99, 0, 0);
	amount *= 2;
	cout << "Начальное дерево:" << endl << endl;
	printTree(root, 0, 0, 2, 0);
	cout << endl << "Второе дерево:" << endl << endl;
	printTree(newTree, 0, 0, 2, 0);
	cout << endl;
	vector <short> array, count;
	createArrayFromTree(newTree, array, count);
	deleteTree(newTree);
	for (unsigned int i = 0; i < array.size(); ++i) {
		insert(root, array[i], count[i], 1);
		root = balance(root);
	}
	cout << "Новое дерево:" << endl << endl;
	printTree(root, 0, 0, 2, 0);
	fallBack();
}
