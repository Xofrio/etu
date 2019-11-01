#include <iostream>
#include <string>

using namespace std;

#ifndef FUNC_H
#define FUNC_H

int getMenuOption() {
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 2): ";
		}
		else if (userNumber == 0 || userNumber == 1 || userNumber == 2) {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
		else
			cout << endl << "Попробуйте ввести корректную опцию (от 0 до 2): ";
	}
}

string getSequence(int &length) {
	string userInput;
	while (true) {
		int charactersCount = 0, wordCount = 0, wrongCharactersCount = 0, maxSymbols = 0, dots = 0, dotPosition = -1;
		cout << endl << "Введите последовательность символов, содержащую от 1 до 50 слов." << endl << "Cлово - последовательность 1 до 10 символов." << endl << "Cимвол - латинские буквы, цифры и знаки препинания (,;)." << endl << "Последовательность должна заканчиваться точкой (.)." << endl << endl;
		getline(cin, userInput);
		length = userInput.length();
		cout << endl;
		for (int i = 0; i < length; ++i) {
			if ((int(userInput[i]) > 47 && int(userInput[i]) < 58) || (int(userInput[i]) > 64 && int(userInput[i]) < 91) || (int(userInput[i]) > 96 && int(userInput[i]) < 123))
				++charactersCount;
			if (userInput[i] != ' ' && (userInput[i + 1] == ' ' || userInput[i + 1] == '\0'))
				++wordCount;
			if ((int(userInput[i]) < 48 || int(userInput[i]) > 57) && (int(userInput[i]) < 65 || int(userInput[i]) > 90) && (int(userInput[i]) < 97 || int(userInput[i]) > 122) && int(userInput[i]) != 32 && int(userInput[i]) != 44 && int(userInput[i]) != 46 && int(userInput[i]) != 59)
				++wrongCharactersCount;
			if (userInput[i] == '.') {
				++dots;
				dotPosition = i;
			}
		}
		if (wordCount <= 50) {
			int i = 0, symbols = 0;
			bool condition = 1;
			while (condition) {
				if (userInput[i] != ' ' && userInput[i] != '\0') {
					++symbols;
					while (userInput[i + 1] != ' ') {
						if (userInput[i + 1] == '\0')
							break;
						++i;
						++symbols;
					}
					if (symbols >= maxSymbols) {
						maxSymbols = symbols;
						symbols = 0;
					}
					else
						symbols = 0;
					++i;
				}
				else
					++i;
				if (i == length + 1)
					condition = 0;
			}
		}
		if (charactersCount == 0)
			cout << "Последовательность не содержит слов." << endl;
		else if (wrongCharactersCount > 0)
			cout << "Последовательность содержит недопустимые символы." << endl;
		else if (wordCount > 50)
			cout << "Последовательность содержит более 50 слов." << endl;
		else if (maxSymbols > 10)
			cout << "Последовательность содержит слово, в котором больше 10 символов." << endl;
		else if (dots != 1 || dotPosition != length - 1)
			cout << "В конце последовательности и только в конце должна стоять точка (.)." << endl;
		else
			return userInput;
	}
}

string correction(string userInput, int &length) {
	int i = 0, j = 0, k = 0, i2;
	string temp;
	bool condition = 1;
	while (condition) {
		for (i; i < length; ++i) {
			int excessSymbols = 0;
			if (userInput[i] == ' ') {
				i2 = i;
				while (userInput[i + 1] == ' ') {
					++i;
					++excessSymbols;
				}
				if (excessSymbols > 0)
					userInput.erase(i2, excessSymbols);
				length = userInput.length();
				i = i - excessSymbols;
			}
			if (userInput[i] == ',') {
				i2 = i;
				while (userInput[i + 1] == ',') {
					++i;
					++excessSymbols;
				}
				if (excessSymbols > 0)
					userInput.erase(i2, excessSymbols);
				length = userInput.length();
				i = i - excessSymbols;
			}
			if (userInput[i] == ';') {
				i2 = i;
				while (userInput[i + 1] == ';') {
					++i;
					++excessSymbols;
				}
				if (excessSymbols > 0)
					userInput.erase(i2, excessSymbols);
				length = userInput.length();
				i = i - excessSymbols;
			}
			if (i != 0) {
				if (isupper(userInput[i]))
					userInput[i] = tolower(userInput[i]);
			}
			else if (i == 0) {
				if (islower(userInput[i]))
					userInput[i] = toupper(userInput[i]);
			}
		}
		if (userInput[0] == ' ') {
			k = 1;
			while (userInput[0 + k] == ' ')
				++k;
		}
		temp.insert(j, userInput, k, length - k);
		condition = 0;
	}
	i = 0;
	for (i; i < length; ++i) {
		int excessSymbols = 0;
		if (temp[i] == ',' || temp[i] == ';') {
			i2 = i;
			if (i == 0) {
				while (temp[i + 1] == ',' || temp[i + 1] == ';') {
					++i;
					++excessSymbols;
				}
				++excessSymbols;
				temp.erase(i2, excessSymbols);
				length = temp.length();
			}
			else {
				while (temp[i + 1] == ',' || temp[i + 1] == ';' || temp[i + 1] == '.') {
					++i;
					++excessSymbols;
				}
				temp.erase(i2, excessSymbols);
				length = temp.length();
			}
			i = i - excessSymbols;
		}
	}
	i = 0;
	for (i; i < length; ++i) {
		int excessSymbols = 0;
		if (temp[i] == ',' || temp[i] == ';') {
			if (temp[i - 1] == ' ' && temp[i + 1] == ' ') {
				excessSymbols = 2;
				temp.erase(i, excessSymbols);
				length = temp.length();
			}
			else if ((int(temp[i + 1]) > 96 && int(temp[i + 1]) < 123) || (int(temp[i + 1]) > 47 && int(temp[i + 1]) < 58)) {
				excessSymbols = 1;
				temp.erase(i, excessSymbols);
				length = temp.length();
			}
			i = i - excessSymbols;
		}
	}
	i = length - 2;
	int excessSymbols = 0;
	if (temp[i] == ' ') {
		++excessSymbols;
		if (temp[i - 1] == ';' || temp[i - 1] == ',') {
			++excessSymbols;
			--i;
		}
		temp.erase(i, excessSymbols);
		length = temp.length();
	}
	return temp;
}

void wordsWithoutNumbers(string userInput, int length) {
	int neededWords = 0;
	for (int i = 0; i < length; ++i) {
		int numbers = 0;
		bool condition = 1;
		while (condition) {
			if (int(userInput[i]) > 47 && int(userInput[i]) < 58)
				++numbers;
			++i;
			if (userInput[i] == ' ' || userInput[i] == '\0')
				condition = 0;
		}
		if (numbers == 0)
			++neededWords;
	}
	if (neededWords == 0)
		cout << "Последовательность не содержит слов без цифр." << endl << endl;
	else {
		cout << "Последовательность содержит " << neededWords << " слов без цифр:" << endl << endl;
		int i2, t = 0;
		for (int i = 0; i < length; ++i) {
			int numbers = 0;
			bool condition = 1;
			i2 = i;
			while (condition) {
				if (int(userInput[i]) > 47 && int(userInput[i]) < 58)
					++numbers;
				++i;
				if (userInput[i] == ' ' || userInput[i] == '\0')
					condition = 0;
			}
			t = i;
			if (numbers == 0) {
				if (userInput[i - 1] == ',' || userInput[i - 1] == ';' || userInput[i - 1] == '.')
					--t;
				for (i2; i2 < t; ++i2)
					cout << userInput[i2];
				cout << endl;
			}
		}
		cout << endl;
	}
}

#endif
