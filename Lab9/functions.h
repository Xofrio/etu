#include "accessory.h"

void addBranch(branch *&newOne, int value) { //Функция создания ветви
	if (!newOne) { //Если ветви(поддерева/листа) не существует - создаём ветвь
		newOne = new branch;
		newOne->data = value;
		newOne->left = newOne->right = 0;
		return;
	}
	else //Иначе сравниваем число с имеющимися ветвями
		if (newOne->data >= value) //Если оно меньше того, что в этой ветви - добавим влево
			addBranch(newOne->left, value);
		else if (newOne->data < value) //Иначе вправо
			addBranch(newOne->right, value);
}

void deleteTree(branch *aBranch) { //Удаление дерева
	if (!aBranch)
		return;
	deleteTree(aBranch->left);
	deleteTree(aBranch->right);
	delete aBranch;
}

void createTree(branch *&root, bool &done) { //Создание бинарного дерева
	bool condition = 1;
	while (condition) {
		short methodOption = methodMenu();
		switch (methodOption) {
		case 0: { //Пользователь вводит размерность дерева, сами элементы генерируются автоматически в диапазоне [-99...99]
			cout << "Введите размерность: ";
			showConsoleCursor(1);
			int amount = getAmount();
			showConsoleCursor(0);
			deleteTree(root);
			root = 0;
			for (int i = 0; i < amount; ++i)
				addBranch(root, rand() % 199 - 99);
			cout << "Бинарное дерево из " << amount << " элементов успешно создано" << endl;
			done = 0;
			fallBack();
			return;
		}
		case 1: { //Пользователь вводит элементы с клавиатуры
			int amount = 0;
			string::size_type size;
			cout << "Введите через пробел значения бинарного дерева: ";
			showConsoleCursor(1);
			string input = getValues(amount);
			showConsoleCursor(0);
			deleteTree(root);
			root = 0;
			for (int i = 0; i < amount; ++i) {
				addBranch(root, stoi(input, &size));
				input = input.substr(size);
			}
			cout << "Бинарное дерево из " << amount << " элементов успешно создано" << endl;
			done = 0;
			fallBack();
			return;
		}
		case 2: { //Элементы считываются с файла
			ifstream file("input.txt");
			if (file.is_open()) {
				string input;
				int amount = 0;
				bool bad = 0;
				getline(file, input, '\0');
				cout << input << "." << endl;
				file.close();
				checkString(input, amount, bad);
				if (bad == 0) {
					string::size_type size;
					deleteTree(root);
					root = 0;
					for (int i = 0; i < amount; ++i) {
						addBranch(root, stoi(input, &size));
						input = input.substr(size);
					}
					cout << "Бинарное дерево из " << amount << " элементов успешно создано" << endl;
					done = 0;
				}
				else
					cout << "Бинарное дерево не было создано. Проверьте содержание файла 'input.txt'." << endl;
			}
			else
				cout << "Файл с именем 'input.txt' не найден." << endl;
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

void printTree(branch *root, int space, int value, short right, short mode) { //Отображение дерева в консоли
	if (root == 0)
		return;
	space += 3; //Расстояние между уровнями
	printTree(root->right, space, value, 1, mode); //Правая ветвь
	for (int i = 3; i < space; ++i)
		cout << " ";
	if (right == 1) //Если правая - точка
		cout << ".";
	else if (right == 0) //Если левая - тильда
		cout << '`';
	cout << "-->";
	if (value == root->data && mode == 1)
		SetConsoleTextAttribute(textColour, 13);
	else if (root->data >= 0 && mode == 2)
		SetConsoleTextAttribute(textColour, 11);
	cout << root->data << "\n"; //Значение
	SetConsoleTextAttribute(textColour, 7);
	printTree(root->left, space, value, 0, mode); //Левая ветвь
}

void outputTree(ofstream &file, branch *root, int space, short right) { //Отображение дерева в файле
	if (root == 0)
		return;
	space += 3; //Увеличиваем расстояние между уровнями
	outputTree(file, root->right, space, 1); //Правая ветвь
	for (int i = 3; i < space; ++i)
		file << " ";
	if (right == 1) //Если правая - точка
		file << ".";
	else if (right == 0) //Если левая - тильда
		file << '`';
	file << "-->" << root->data << "\n"; //Стрелка и значение
	outputTree(file, root->left, space, 0); //Левая ветвь
}

void representTree(branch *root) { //Отобразить дерево в консоли и записать его в файл
	if (root != 0) {
		printTree(root, 0, 0, 2, 0);
		ofstream file;
		int space = 0;
		file.open("C:\\tree.txt");
		outputTree(file, root, space, 2);
		file.close();
		cout << endl << "Дерево записано в С:\\tree.txt." << endl;
	}
	else
		cout << "В дереве нет элементов.";
	fallBack();
}

void searchInTree(branch *root, branch *treeCopy, int &amount, int value) { //Поиск элемента в дереве
	treeCopy = root;
	if (root == 0)
		return;
	bool condition = 1;
	auto begin = chrono::steady_clock::now();
	while (condition) {
		if (root == 0) {
			condition = 0;
			break;
		}
		if (value > root->data) { //Если значение искомого элемента больше, чем значение элемента в текущей ветви - продолжаем поиск в правой ветви
			if (root->right == 0) {
				condition = 0;
				break;
			}
			root = root->right;
		}
		else if (value < root->data) { //Если значение искомого элемента меньше, чем значение элемента в текущей ветви - продолжаем поиск в левой ветви
			if (root->left == 0) {
				condition = 0;
				break;
			}
			root = root->left;
		}
		else if (value == root->data) { //Если значение искомого элемента равно значению элемента в текущей ветви - продолжаем поиск в левой ветви (там может быть элемент с таким же значением)
			++amount;
			if (root->left == 0) {
				condition = 0;
				break;
			}
			root = root->left;
		}
	}
	auto end = chrono::steady_clock::now();
	if (amount == 0) {
		cout << "Таких элементов в дереве нет." << endl;
		cout << "Ваше дерево:" << endl << endl;
	}
	else {
		cout << "Количество элементов со значением '" << value << "' : " << amount << "." << endl;
		cout << "Ваше дерево (найденные элементы подсвечены):" << endl << endl;
	}
	int space = 0;
	printTree(treeCopy, space, value, 2, 1);
	cout << endl << "Время, затраченное на поиск в дереве (наносек.):            " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()) << endl;
	return;
}

dLL *&initializeList(dLL *&list, short value) { //Создание узла двусвязного списка
	list = new dLL;
	list->data = value;
	list->next = list->prev = 0;
	return list;
} 

void addAtFront(dLL **head, short value) { //Добавление узла в начало двусвязного списка
	dLL *temp = initializeList(temp, value);
	if (*head == 0) {
		*head = temp;
		return;
	}
	dLL *travel = *head;
	temp->next = travel;
	travel->prev = temp;
	*head = temp;
}

void insertAtPosition(dLL **list, int value, int index) { //Вставка элемента в список на определённую позицию
	dLL *temp = initializeList(temp, value);
	dLL *travel = *list;
	int i = 0;
	while (i != index) {
		travel = travel->next;
		++i;
	}
	if (travel != *list) {
		temp->next = travel;
		temp->prev = travel->prev;
		travel->prev->next = temp;
		travel->prev = temp;
		return;
	}
	else {
		travel->prev = temp;
		temp->next = travel;
		*list = temp;
		return;
	}
} 

dLL *deleteHead(dLL *head) { //Удаление головы списка
	dLL *temp = 0;
	if (head->next == 0)
		return temp;
	temp = head->next;
	temp->prev = 0;
	free(head);
	return temp;
}

void deleteNode(dLL **head, dLL *item, unsigned int &amount) { //Удаление узла списка
	if (*head == 0 || item == 0)
		return;
	if (*head == item)
		*head = item->next;
	if (item->next != 0)
		item->next->prev = item->prev;
	if (item->prev != 0)
		item->prev->next = item->next;
	free(item);
	--amount;
	return;
}

void createArrayAndListFromTree(branch *forArray, dLL *&list, vector <short> &array) { //Создание массива и списка из дерева
	if (forArray == 0)
		return;
	queue <branch *> chainForArray; //Создаём очередь
	chainForArray.push(forArray); //Помещаем корень в очередь
	while (!chainForArray.empty()) {
		branch* copy = chainForArray.front();
		chainForArray.pop();
		array.push_back(copy->data);
		if (copy->left != 0) //Если указатель на левую ветвь не указывает на 0 - помещаем в очередь левую ветвь
			chainForArray.push(copy->left);
		if (copy->right != 0) //Если указатель на правую ветвь не указывает на 0 - помещаем в очередь правую ветвь
			chainForArray.push(copy->right);
	}
	list = initializeList(list, array[array.size() - 1 ]);
	for (unsigned int i = array.size() - 1; i >= 0; --i) {
		addAtFront(&list, array[i]);
		if (i == 0)
			break;
	}
}

void searchInArrayAndList(dLL *list, vector <short> array, short value) { //Поиск в массиве и списке
	int count = 0;
	cout << endl;
	auto begin = chrono::steady_clock::now();
	for (unsigned int i = 0; i < array.size(); ++i) {
		if (array[i] == value)
			++count;
	}
	auto end = chrono::steady_clock::now();
	cout << "Время, затраченное на поиск в массиве (наносек.):           " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()) << endl << endl;
	count = 0;
	begin = chrono::steady_clock::now();
	for (unsigned int i = 0; i < array.size(); ++i) {
		if (list->data == value)
			++count;
		if (list->next == 0)
			break;
		list = list->next;
	}
	end = chrono::steady_clock::now();
	cout << "Время, затраченное на поиск в двусвязном списке (наносек.): " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()) << endl;
}

void addToArrayAndList(branch *root, dLL *&list, vector <short> &array, short value) {
	if (list == 0)
		return;
	vector <short> temporary;
	queue <branch *> chainForArray; //Создаём очередь
	chainForArray.push(root); //Помещаем корень в очередь
	while (!chainForArray.empty()) {
		branch* copy = chainForArray.front();
		chainForArray.pop();
		temporary.push_back(copy->data);
		if (copy->left != 0) //Если указатель на левую ветвь не указывает на 0 - помещаем в очередь левую ветвь
			chainForArray.push(copy->left);
		if (copy->right != 0) //Если указатель на правую ветвь не указывает на 0 - помещаем в очередь правую ветвь
			chainForArray.push(copy->right);
	}
	unsigned int index = array.size();
	for (unsigned int i = 0; i < array.size(); ++i) {
		if (temporary[i] != array[i]) {
			index = i;
			break;
		}
	}
	array.clear();
	auto begin = chrono::steady_clock::now();
	for (unsigned int i = 0; i < index; ++i)
		array.push_back(temporary[i]);
	array.push_back(value);
	for (unsigned int i = index + 1; i < temporary.size(); ++i)
		array.push_back(temporary[i]);
	auto end = chrono::steady_clock::now();
	cout << endl << "Время, затраченное на добавление элемента в массив (наносек.):            " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()) << endl << endl;
	begin = chrono::steady_clock::now();
	insertAtPosition(&list, value, index);
	end = chrono::steady_clock::now();
	cout << "Время, затраченное на добавление элемента в двусвязный список (наносек.): " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()) << endl;
}

branch* deleteBranch(branch *root, short value) { //Функция удаления элемента в дереве
	if (root == 0)
		return root;
	if (root->data > value) { //Если значение текущего элемента больше, чем требуемого, идём в левую ветвь
		root->left = deleteBranch(root->left, value);
		return root;
	}
	else if (root->data < value) { //Если значение текущего элемента меньше, чем требуемого, идём в правую ветвь
		root->right = deleteBranch(root->right, value);
		return root;
	}
	if (root->left == 0) { //Если в левой ветви ничего нет
		branch* temp = root->right; //Заменяем текущий элемент на элемент из правой ветви
		delete root;
		return temp;
	}
	else if (root->right == 0) { //Если в правой ветви ничего нет
		branch* temp = root->left; //Заменяем текущий элемент на элемент из левой ветви
		delete root;
		return temp;
	}
	else { //Если есть обе ветви - идём в правую ветвь
		branch *parent = root;
		branch *successor = root->right; //В качестве преемника делаем элемент из правой ветви
		while (successor->left != 0) { //Пока в левой ветви не пусто
			parent = successor;
			successor = successor->left; //Теперь в качестве преемника выбираем элемент из левой ветви
		}
		if (parent != root)
			parent->left = successor->right;
		else
			parent->right = successor->right; //Если оказалось, что продвижения не произошло - передаём указатель на элемент через 1 в правой ветви
		root->data = successor->data; //В поле данных записываем значение "преемника"
		delete successor;
		return root;
	}
}

void eraseFromArrayAndList(dLL *&list, vector <short> &array, short value) {
	unsigned int amount = array.size();
	auto begin = chrono::steady_clock::now();
	for (unsigned int i = 0; i < array.size(); ++i) {
		if (array[i] == value) {
			array.erase(array.begin()+i);
			--i;
		}
	}
	auto end = chrono::steady_clock::now();
	cout << endl << "Время, затраченное на удаление элемента из массива (наносек.):            " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()) << endl;
	dLL * temp = list;
	bool flag = 0;
	auto start = chrono::steady_clock::now();
	for (unsigned int i = 0; i < amount; ++i) {
		if (list->data == value) {
			deleteNode(&list, temp, amount);
			if (list->prev != 0) {
				list = list->prev;
				flag = 0;
			}
			else
				flag = 1;
		}
		if (list->next == 0)
			break;
		temp = list;
		if (flag == 0) {
			list = list->next;
			temp = temp->next;
		}
	}
	auto finish = chrono::steady_clock::now();
	cout << endl << "Время, затраченное на удаление элемента из двусвязного списка (наносек.): " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(finish - start).count()) << endl;
}

void rearrangeTree(branch *&root) { //Меняем местами элементы, т.к. после домножения на случайную величину [-2...2] в BST, которое я реализовал, полностью рушится порядок (слева меньше, справа - больше)
	if (root == 0)
		return;
	queue <branch *> chainForArray; //Создаём очередь
	vector <short> array;
	chainForArray.push(root); //Помещаем корень в очередь
	while (!chainForArray.empty()) {
		branch* copy = chainForArray.front();
		chainForArray.pop();
		array.push_back(copy->data);
		if (copy->left != 0) //Если указатель на левую ветвь не указывает на 0 - помещаем в очередь левую ветвь
			chainForArray.push(copy->left);
		if (copy->right != 0) //Если указатель на правую ветвь не указывает на 0 - помещаем в очередь правую ветвь
			chainForArray.push(copy->right);
	}
	sort(array.begin(), array.end());
	root = 0;
	for (unsigned int i = 0; i < array.size(); ++i)
		addBranch(root, array[i]);
}

void actionsWithTree(branch *&root, bool done) { //Добавление, поиск, удаление элемента в дереве
	if (root == 0) {
		cout << "В дереве нет элементов" << endl;
		fallBack();
		return;
	}
	if (done == 1)
		rearrangeTree(root);
	bool condition = 1;
	while (condition) {
		short actionOption = actionMenu();
		switch (actionOption) {
		case 0: { //Добавление элемента
			if (root == 0) {
				cout << "В дереве нет элементов" << endl;
				fallBack();
				return;
			}
			dLL *list = 0;
			vector <short> array;
			cout << "Введите значение добавляемого элемента в диапазоне [-99...99]: ";
			int amount = 0;
			short element = getElement();
			cout << endl;
			createArrayAndListFromTree(root, list, array);
			auto begin = chrono::steady_clock::now();
			addBranch(root, element);
			auto end = chrono::steady_clock::now();
			branch *treeCopy = root, *temporary = root;
			int space = 0;
			printTree(treeCopy, space, 0, 2, 0);
			cout << endl << "Время, затраченное на добавление элемента в дерево (наносек.):            " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()) << endl;
			addToArrayAndList(temporary, list, array, element);
			while (list->prev != 0)
				list = list->prev;
			for (unsigned int i = 0; i < array.size() - 1; ++i)
			  list = deleteHead(list);
			array.clear();
			fallBack();
			break;
		}
		case 1: { //Поиск элемента
			if (root == 0) {
				cout << "В дереве нет элементов" << endl;
				fallBack();
				return;
			}
			branch *temporaryTree = root,  *treeCopy = 0;
			dLL *list = 0;
			vector <short> array;
			cout << "Введите значение искомого элемента в диапазоне [-99...99]: ";
			int amount = 0;
			short element = getElement();
			createArrayAndListFromTree(root, list, array);
			searchInTree(temporaryTree, treeCopy, amount, element);
			searchInArrayAndList(list, array, element);
			while (list->prev != 0)
				list = list->prev;
			for (unsigned int i = 0; i < array.size(); ++i)
				list = deleteHead(list);
			array.clear();
			fallBack();
			return;
		}
		case 2: { //Удаление элемента
			if (root == 0) {
				cout << "В дереве нет элементов" << endl;
				fallBack();
				return;
			}
			branch *temporaryTree = root, * treeCopy = 0;
			dLL *list = 0;
			vector <short> array;
			cout << "Введите значение удаляемого элемента в диапазоне [-99...99]: ";
			int amount = 0;
			short element = getElement();
			searchInTree(temporaryTree, treeCopy, amount, element);
			if (amount != 0) {
				createArrayAndListFromTree(root, list, array);
				auto begin = chrono::steady_clock::now();
				root = deleteBranch(root, element);
				root = deleteBranch(root, element);
				auto end = chrono::steady_clock::now();
				int space = 0;
				cout << endl << "Ваше дерево:" << endl << endl;
				printTree(root, space, 0, 2, 0);
				cout << endl << "Время, затраченное на удаление элемента из дерева (наносек.):             " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()) << endl;
				eraseFromArrayAndList(list, array, element);
				while (list->prev != 0)
					list = list->prev;
				for (unsigned int i = 0; i < array.size(); ++i)
					list = deleteHead(list);
				array.clear();
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

void prefixTraversal(branch *root) { //Функция прямого (префиксного) обхода дерева
	if (root != 0) {
		cout << root->data << " ";
		prefixTraversal(root->left);
		prefixTraversal(root->right);
	}
}

void postfixTraversal(branch *root) { //Функция обратного (постфиксного) обхода дерева
	if (root != 0) {
		postfixTraversal(root->left);
		postfixTraversal(root->right);
		cout << root->data << " ";
	}
}

void levelTraversal(branch *root) { //Функция обхода дерева в ширину
	if (root == 0)
		return;
	queue <branch *> chain; //Создаём очередь
	chain.push(root); //Помещаем корень в очередь
	while (!chain.empty()) {
		branch* copy = chain.front();
		chain.pop();
		cout << copy->data << " ";
		if (copy->left != 0) //Если указатель на левую ветвь не указывает на 0 - помещаем в очередь левую ветвь
			chain.push(copy->left);
		if (copy->right != 0) //Если указатель на правую ветвь не указывает на 0 - помещаем в очередь правую ветвь
			chain.push(copy->right);
	}
}

void treeTraversal(branch *root) { //Обходы дерева: прямой, обратный, в ширину
	if (root != 0) {
		branch *prefixCopy, *postfixCopy;
		prefixCopy = postfixCopy = root;
		cout << "Ваше дерево: " << endl << endl;
		int space = 0;
		printTree(root, space, 0, 2, 0);
		cout << endl << "Прямой обход дерева: ";
		prefixTraversal(prefixCopy);
		cout << endl << endl << "Обратный обход дерева: ";
		postfixTraversal(postfixCopy);
		cout << endl << endl << "Обход дерева в ширину: ";
		levelTraversal(root);
		cout << endl;
	}
	else
		cout << "В дереве нет элементов.";
	fallBack();
}

branch *deleteNegativeBranch(branch *root) { //Функция удаления всех отрицательных элементов в левом поддереве
	if (root == 0)
		return root;
	while (root->data < 0) {
		if (root->right == 0)
			break;
		root = root->right;
	}
	if (root->data < 0) { //Если значение текущего элемента меньше 0 - удаляем ветвь
		delete root;
		return NULL;
	}
	if (root->data >= 0)//Если значение текущего элемента больше, либо равно 0 - идём в левую ветвь
		root->left = deleteNegativeBranch(root->left);
	return root;
}

branch *multiplyElements(branch *root) { //Функция умножения всех элементов в дереве на случайную величину [-2...2]
	if (root == 0)
		return root;
	root->data *= rand() % 5 - 2;
	if (root->left != 0) {
		root->left = multiplyElements(root->left);
	}
	if (root->right != 0)
		root->right = multiplyElements(root->right);
	return root;
}

void myVariant(branch *&root, bool &done) { //Удалить все отрицательные элементы из дерева, все остальные умножить на случайную величину [-2...2]
	if (root == 0) {
		cout << "В дереве нет элементов.";
		fallBack();
		return;
	}
	if (done == 1)
		rearrangeTree(root);
	dLL *list = 0;
	vector <short> array;
	queue <branch *> chain; //Создаём очередь
	createArrayAndListFromTree(root, list, array);
	bool condition = 1;
	int space = 0;
	cout << "Дерево до операции (неотрицательные элементы подсвечены):" << endl << endl;
	printTree(root, space, 0, 2, 2);
	auto start = chrono::steady_clock::now();
	while (condition) {
		while (root->data < 0) //Удаляем начиная с корня левую ветвь, если текущий элемент меньше 0
			root = root->right;
		if (root == 0) { //Если в дереве ничего не осталось - выходим
			condition = 0;
			break;
		}
		else {
			root = deleteNegativeBranch(root); //Удаляем все отрицательные элементы в левом поддереве, если дерево не опустело
			root = multiplyElements(root); //Домножаем оставшиеся элементы на случайную величину [-2...2]
			condition = 0;
			break;
		}
	}
	auto finish = chrono::steady_clock::now();
	space = 0;
	cout << endl << "Дерево после операции:" << endl << endl;
	printTree(root, space, 0, 2, 0);
	cout << endl << "Время, затраченное на удаление отрицательных элементов и домножение положительных на случайную величину [-2...2] в дереве (наносек.):            " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(finish - start).count()) << endl;
	unsigned int amount = array.size();
	auto begin = chrono::steady_clock::now();
	for (unsigned int i = 0; i < array.size(); ++i) { //Сначала удаляем все отрицательные элементы
		if (array[i] < 0) {
			array.erase(array.begin() + i);
			--i;
		}
	}
	for (unsigned int i = 0; i < array.size(); ++i) //Домножаем оставшиеся элементы на случайную величину [-2...2]
		array[i] *= rand() % 5 - 2;
	auto end = chrono::steady_clock::now();
	cout << endl << "Время, затраченное на удаление отрицательных элементов и домножение положительных на случайную величину [-2...2] в массиве (наносек.):           " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(end - begin).count()) << endl;
	while (list->prev != 0)
		list = list->prev;
	dLL *temp = list;
	bool flag = 0;
	auto mark = chrono::steady_clock::now();
	for (unsigned int i = 0; i < amount; ++i) { //Сначала удаляем все отрицательные элементы
		if (list->data < 0) {
			deleteNode(&list, temp, amount);
			if (list->prev != 0) {
				list = list->prev;
				flag = 0;
			}
			else
				flag = 1;
		}
		if (list->next == 0)
			break;
		temp = list;
		if (flag == 0) {
			list = list->next;
			temp = temp->next;
		}
	}
	while (list->prev != 0)
		list = list->prev;
	for (unsigned int i = 0; i < amount; ++i) { //Домножаем оставшиеся элементы на случайную величину [-2...2]
		list->data *= rand() % 5 - 2;
		if (list->next == 0)
			break;
		list = list->next;
	}
	auto stop = chrono::steady_clock::now();
	cout << endl << "Время, затраченное на удаление отрицательных элементов и домножение положительных на случайную величину [-2...2] в двусвязном списке (наносек.): " << static_cast<long int>(chrono::duration_cast<chrono::nanoseconds>(stop - mark).count()) << endl;
	while (list->prev != 0)
		list = list->prev;
	for (unsigned int i = 0; i < array.size(); ++i)
		list = deleteHead(list);
	array.clear();
	done = 1;
	fallBack();
	return;
}
