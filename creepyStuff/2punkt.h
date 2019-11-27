#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <ctime>
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
string getword(int a)
{
	if (a == 1)
	{
		char name[9999]; // áóôåð ïðîìåæóòî÷íîãî õðàíåíèÿ ñ÷èòûâàåìîãî èç ôàéëà òåêñòà
		ifstream fin("data.txt"); // îòêðûëè ôàéë äëÿ ÷òåíèÿ
		fin >> name; // ñ÷èòàëè ïåðâîå ñëîâî èç ôàéëà
		fin.close(); // çàêðûâàåì ôàéë
		char username[9999];
		while (true)
		{
			cin >> username;
			if (strcmp(username, name) != 0)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << endl << "èìÿ ïîëüçîâàòåëÿ íå ñîâïàäàåò,ïîïðîáóéòå åù¸ ðàç\n";
			}
			else
			{
				cin.ignore(cin.rdbuf()->in_avail());
				return username;
			}
		}
	}
	else
	{
		string userpass;
		char passw[9999]; // áóôåð ïðîìåæóòî÷íîãî õðàíåíèÿ ñ÷èòûâàåìîãî èç ôàéëà òåêñòà
		ifstream fin("data.txt"); // îòêðûëè ôàéë äëÿ ÷òåíèÿ
		fin >> passw;
		fin >> passw;
		fin.close(); // çàêðûâàåì ôàéë
		while (true)
		{
			string pass;
			for (;;)
			{
				auto userpass = _getch();
				cout << userpass;
				if (userpass == 13)
				{
					cout << endl;
					break;  // åñëè ýíòåð
				}

				if (userpass == 224)
					_getch(),
					userpass = 8;

				if (userpass == 8)
				{
					std::cout << "\b \b";
					if (!pass.empty())
						pass.pop_back();
				}
				else
				{
					const auto ch = static_cast<char>(userpass);
					pass += ch;
					std::cout << "*";
				}
			}
		}
		if (userpass != passw) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "ïàðîëü íå ñîâïàäàåò,ïîïðîáóéòå åù¸ ðàç\n";
		}
		else
		{
			cin.ignore(cin.rdbuf()->in_avail());
			return userpass;
		}
	}
}
int failcin()
{
	while (true) {
		int userNumber;
		cin >> userNumber;
		if (cin.fail() || userNumber < 0) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Ïîïðîáóéòå ââåñòè êîððåêòíîå ÷èñëî: ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}
void enter()
{
	setlocale(LC_ALL, "");
	string userpass, username, Userpassword, name, pass;
	int option;
	cout << "0.ðåãèñòðàöèÿ ïîëüçîâàòåëÿ\n";
	cout << "1.âõîä ïîëüçîâàòåëÿ\n";
	option = failcin();
	switch (option)
	{
	case 0:
	{
		cout << "wow";
	}
	break;
	default:
	{
		cout << "âõîä ïîëüçîâàòåëÿ\n";
		cout << "èìÿ ïîëüçîâàòåëÿ:";
		username = getword(1);
		cout << "ïàðîëü ïîëüçîâàòåëÿ:";
		userpass = getword(2);
		cout << "Äîáðî ïîæàëîâàòü)))(â àä)\n";
	}
	break;
	}
}
void groupnumber()
{
	short int a = 9894;
	int i = 16;
	bool r2;
	r2 = a & (1U << --i);
	SetConsoleTextAttribute(h, 05);
	cout << r2 << " ";
	for (--i; i >= 0; --i)
	{
		r2 = a & (1U << i);
		if (i % 4 == 0)
		{
			SetConsoleTextAttribute(h, 02);
			cout << r2 << " ";
		}
		else
		{
			SetConsoleTextAttribute(h, 02);
			cout << r2;
		}
	}
	cout << " \n";
}
/*void secndname()
{
	char s;
	cin >> s;
	for (int i = sizeof(s) * 8 - 1; i >= 0; --i)
	{
		printf((s >> i) & 1);
		cout << " \n";
	}
	SetConsoleTextAttribute(h, 07);
}*/
void greetingN()
{
	char name[9999] = "ïîëüçîâàòåëü N";
	cout << "Ïðèâåòñòâóþ, òåáÿ," << name << ", Íà óëèöå òàêàÿ âüþãà. Ïðèñàæèâàéñÿ ó î÷àãà, çäåñü òåáå âñåãäà ðàäû";
	cout << "Ýòó ïðîãðàììó íàïèñàë ñòóäåíò ãðóïïû 9894, Øàðîíèí Àëåêñåé. Êñòàòè, â ïàìÿòè ìîåãî êîìïüþòåðà íîìåð ìîé ãðóïïû âûãëÿäèò êàê: ";
	groupnumber();
	SetConsoleTextAttribute(h, 07);
	cout << "À Ôàìèëèÿ êàê ";
	//secndname();
	cout << endl;
	system("pause");
}
void greeting()
{
	char name[9999]; // áóôåð ïðîìåæóòî÷íîãî õðàíåíèÿ ñ÷èòûâàåìîãî èç ôàéëà òåêñòà
	ifstream fin("data.txt"); // îòêðûëè ôàéë äëÿ ÷òåíèÿ
	fin >> name; // ñ÷èòàëè ïåðâîå ñëîâî èç ôàéëà
	fin.close(); // çàêðûâàåì ôàéë
	cout << "Ïðèâåòñòâóþ, òåáÿ," << name << ", Íà óëèöå òàêàÿ âüþãà. Ïðèñàæèâàéñÿ ó î÷àãà, çäåñü òåáå âñåãäà ðàäû\n";
	//cout << "Ýòó ïðîãðàììó íàïèñàë ñòóäåíò ãðóïïû 9894, Øàðîíèí Àëåêñåé. Êñòàòè, â ïàìÿòè ìîåãî êîìïüþòåðà íîìåð ìîé ãðóïïû âûãëÿäèò êàê: " << groupnumber() << ", à Ôàìèëèÿ êàê " << secndname();
	system("pause");
}
void showmas(int* A, int count) {
	if (count == 0)
		cout << "íåò ìàññèâà" << endl;
	else {
		for (int i = 0; i < count; ++i)
			cout << A[i] << " ";
		cout << endl;
	}
}
void inputArrayFromFile(int*& A, int& elements)
{
	ifstream in("array.txt");
	if (in.is_open())
	{
		int temp;
		while (!in.eof())
		{
			in >> temp;
			++elements;
		}
		in.seekg(0, ios::beg);
		in.clear();
		A = new int[elements];
		int i = 0;
		while (!in.eof()) {
			in >> A[i];
			++i;
		}
		in.close();
	}
	else {
		cout << "Ôàéë ñ èìåíåì 'array.txt' íå íàéäåí." << endl << endl;
	}
}
void mas()
{
	srand(unsigned(time(NULL)));
	int* array = 0;
	int rows = 0;
	setlocale(0, "ru");
	cout << "âûáåðèòå ìåòîä çàïîëíåíèÿ ìàññèâà\n";
	cout << "0.ðó÷êàìè\n";
	cout << "1.ðàíäîì\n";
	cout << "2.÷èòàòü ñ ôàéëà\n";
	int option = failcin();
	switch (option)
	{
	case 0:
	{
		cout << "ââåäèòå êîëè÷åâñòâî ñòðîê(öåëîå íåîòðèöàòåëüíîå ÷èñëî): ";
		rows = failcin();
		for (int i = 0; i < rows; i++)
		{
			cout << "Ââåäèòå çíà÷åíèå ýëåìåíòà ñ èíäåêñîì [" << i + 1 << "]";
			cin >> array[i];
		}
		showmas(array, rows);
		delete[] array;
		break;
	}
	case 1:
	{
		rows = rand() % 5;
		int* array = new int[rows];
		for (int i = 0; i < rows; i++)
		{
			array[i] = rand() % 100;
		}
		showmas(array, rows);
		//bubble(array, rows);
		showmas(array, rows);
		delete[] array;
		break;
	}
	case 2: {
		int elements = 0;
		inputArrayFromFile(array, elements);
		showmas(array, elements);
		break;
	}
			
	}
	system("pause");
}
void flagi()
{
	HANDLE g = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "ôëàã Ðîññèè\n";
	SetConsoleTextAttribute(g, 240);
	cout << "                                  \n";
	SetConsoleTextAttribute(g, 240);
	cout << "                                  \n";
	SetConsoleTextAttribute(g, 240);
	cout << "                                  \n";
	SetConsoleTextAttribute(g, 147);
	cout << "                                  \n";
	SetConsoleTextAttribute(g, 147);
	cout << "                                  \n";
	SetConsoleTextAttribute(g, 147);
	cout << "                                  \n";
	SetConsoleTextAttribute(g, 200);
	cout << "                                  \n";
	SetConsoleTextAttribute(g, 200);
	cout << "                                  \n";
	SetConsoleTextAttribute(g, 200);
	cout << "                                  \n\n\n";
	SetConsoleTextAttribute(g, 07);
	cout << "ôëàã Øâåöèè\n";
	SetConsoleTextAttribute(g, 147);
	cout << "         ";
	SetConsoleTextAttribute(g, 230);
	cout << "         ";
	SetConsoleTextAttribute(g, 147);
	cout << "                \n";
	SetConsoleTextAttribute(g, 147);
	cout << "         ";
	SetConsoleTextAttribute(g, 230);
	cout << "         ";
	SetConsoleTextAttribute(g, 147);
	cout << "                \n";
	SetConsoleTextAttribute(g, 147);
	cout << "         ";
	SetConsoleTextAttribute(g, 230);
	cout << "         ";
	SetConsoleTextAttribute(g, 147);
	cout << "                \n";
	SetConsoleTextAttribute(g, 230);
	cout << "                                  \n";
	SetConsoleTextAttribute(g, 230);
	cout << "                                  \n";
	SetConsoleTextAttribute(g, 230);
	cout << "                                  \n";
	SetConsoleTextAttribute(g, 147);
	cout << "         ";
	SetConsoleTextAttribute(g, 230);
	cout << "         ";
	SetConsoleTextAttribute(g, 147);
	cout << "                \n";
	SetConsoleTextAttribute(g, 147);
	cout << "         ";
	SetConsoleTextAttribute(g, 230);
	cout << "         ";
	SetConsoleTextAttribute(g, 147);
	cout << "                \n";
	SetConsoleTextAttribute(g, 147);
	cout << "         ";
	SetConsoleTextAttribute(g, 230);
	cout << "         ";
	SetConsoleTextAttribute(g, 147);
	cout << "                \n";
	_getch();
}
void bubble(int* A, int count)
{
	int t = 0;
	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count - 1; ++j)
		{
			if (A[j] > A[j + 1])
			{
				t = A[j];
				A[j] = A[j + 1];
				A[j + 1] = t;

			}
		}
	}
}
void shaker(int* A, int count)
{
	int left = 0, right = count - 1;
	bool motion = 1;
	int t = 0;
	while ((left < right) && motion == 1)
	{
		motion = 0;
		for (int i = left; i < right; ++i)
		{
			if (A[i] > A[i + 1])
			{
				t = A[i];
				A[i] = A[i + 1];
				A[i + 1] = t;
				motion = 1;
			}
		}
		--right;
		for (int i = right; i > left; --i)
		{
			if (A[i - 1] > A[i])
			{
				t = A[i];
				A[i] = A[i + 1];
				A[i + 1] = t;
				motion = 1;
			}
		}
		++left;
	}
}
void insert(int* A, int count)
{
	int i, k, j;
	for (i = 1; i < count; ++i)
	{
		k = A[i];
		j = i - 1;
		while (j >= 0 && A[j] > k)
		{
			A[j + 1] = A[j];
			--j;
		}
		A[j + 1] = k;
	}
}
void quick(int* A, int start, int end)
{
	int i = start, j = end, tmp;
	int separator = A[(start + end) / 2];
	while (i <= j)
	{
		while (A[i] < separator)
			++i;
		while (A[j] > separator)
			--j;
		if (i <= j)
		{
			tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
			++i;
			--j;
		}
	}
	if (start < j)
		quick(A, start, j);
	if (i < end)
		quick(A, i, end);
}
int meny()
{
	while (true)
	{
		int opt = failcin();
		if (opt == 1 || opt == 2 || opt == 3 || opt == 4 || opt == 5)
		{
			return opt;
		}
		else
		{
			cout << "ïîïðîáóéòå åù¸ ðàç 1 -bubble,2-shaker,3-insert,4-quick,5-comb";
		}
	}
}