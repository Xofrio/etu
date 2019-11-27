#include <iostream>
#include "2punkt.h"
#include <conio.h>
#include <Windows.h>
using namespace std;
int menu();
int main()
{
	setlocale(LC_ALL, "");
	int initial = 0;
start:
	int answer = menu();
	switch (answer)
	{
	case 0:
	{
	here:
		enter();
		initial = 1;
		goto start;
	}
	break;
	case 1:
	{
		if (initial == 1)
		{
			greeting();
			goto start;
		}
		else
		{
			cout << "íàñòîÿòåëüíî ðåêîìåíäóåì âîéòè â àêêàóíò,èëè,åñëè íåò àêêàóíòà,çàðåãåñòðèðîâàòüñÿ\n";
			cout << "ñäåëàòü ÝÒÎ??????(1-äà,0-íåò)";
			int choice;
			choice = failcin();
			if (choice == 1)
			{
				goto here;
			}
			else
			{
				greetingN();
				goto start;
			}
		}
		break;
	}
	case 2:
	{
		mas();
		goto start;
	}
	break;
	case 3:
	{
		flagi();
		system("color 07");
		goto start;
	}
	}
	system("pause");
	return 0;
}

int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 4) % 4;
		if (key == 0) cout << "->Ïóíêò 1" << endl;
		else  cout << "   Ïóíêò 1" << endl;

		if (key == 1) cout << "->Ïóíêò 2" << endl;
		else  cout << "   Ïóíêò 2" << endl;

		if (key == 2) cout << "->Ïóíêò 3" << endl;
		else  cout << "   Ïóíêò 3" << endl;

		if (key == 3) cout << "->Ïóíêò 4" << endl;
		else  cout << "   Ïóíêò 4" << endl;

		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80 || code == 119) key++;
			if (code == 72 || code == 115) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}