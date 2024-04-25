#include <iostream>
using namespace std;

int main() {
	while (true) {
		int a, b, c, of = 0, dz = 0;
		int res;
		cout << "Enter a, b, c for (2*c*b + a - 21)/(-c / a * b + 256):\n";
		cout << "Please enter a: ";
		while (!(cin >> a) || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Please enter an integer value" << endl;
		}
		cout << "Please enter b: ";
		while (!(cin >> b) || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Please enter an integer value" << endl;
		}
		cout << "Please enter c: ";
		while (!(cin >> c) || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Please enter an integer value" << endl;
		}
		__asm {
			mov eax, c; <eax> = c
			mov ebx, a; <ebx> = a

			or ebx, ebx; <ebx> ? 0
			jz err_zero; ошибка деления на 0

			neg eax; <eax> = -c
			cdq; eax ==> <edx:eax> = -c
			idiv ebx; <eax> = -c / a

			imul eax, b; <eax> = -c / a * b

			jo overflow; ошибка переполнения

			add eax, 256; <eax> = -c / a * b + 256

			jz err_zero; ошибка деления на 0

			push eax; в стеке - c / a * b + 256

			mov eax, 2; <eax> = 2
			imul eax, c; <eax> = 2 * c

			jo overflow; ошибка переполнения

			imul eax, b; <eax> = 2 * c * b

			jo overflow; ошибка переполнения

			add eax, a; <eax> = 2 * c * b + a

			jo overflow; ошибка переполнения

			sub eax, 21; <eax> = 2 * c * b + a - 21

			jo overflow; ошибка переполнения

			pop ebx; <ebx> = -c / a * b + 256
			cdq; eax ==> <edx:eax> = 2 * c * b + a - 21
			idiv ebx; <eax> = (2 * c * b + a - 21) / (-c / a * b + 256)

			mov res, eax; res = (2 * c * b + a - 21) / (-c / a * b + 256)
			jmp fin; переход в конец программы

		overflow:
			mov of, 1; of = 1
			jmp fin; переход в конец программы

		err_zero:
			mov dz, 1; dz = 1
			jmp fin; переход в конец программы

		fin:

		}
		if (of) cout << "Overflow error!\n";
		else if (dz) cout << "Division by zero!\n";
		else cout << "cpp: " << (2 * c * b + a - 21) / (-c / a * b + 256) << endl
			<< "asm: " << res << endl;
		cin.clear();
		system("pause");
		system("cls");
	}
	return 0;
}
