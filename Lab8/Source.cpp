#include "Func.h"

int main() {
	setlocale(0, "");
	letters variables[26] = {
		{'a', 0}, {'b', 0}, {'c', 0}, {'d', 0}, {'e', 0}, {'f', 0}, {'g', 0}, {'h', 0}, {'i', 0}, {'j', 0}, {'k', 0}, {'l', 0}, {'m', 0},
		{'n', 0}, {'o', 0}, {'p', 0}, {'q', 0}, {'r', 0}, {'s', 0}, {'t', 0}, {'u', 0}, {'v', 0}, {'w', 0}, {'x', 0}, {'y', 0}, {'z', 0},
	};
	long int stackPNValidationSpeed, arrayPNValidationSpeed, stackRPNValidationSpeed, arrayRPNValidationSpeed;
	bool condition = 1;
	while (condition) {
		short option = menu();
		switch (option) {
		case 0: { /*Преобразовать выражение*/
			convert(variables);
			break;
		}
		case 1: { /*Проверить на корректность введённое выражение*/
			validate();
			break;
		}
		case 2: { /*Вычислить выражение*/
			solve(variables);
			break;
		}
		case 3: { /*Сгенерировать вариант проверочной работы*/

			break;
		}
		case 4: { /*Буфер клавиатуры*/

			break;
		}
		case 5: {
			condition = 0;
			break;
		}
		}
	}
	return 0;
}
