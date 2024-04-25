#include <iostream>
using namespace std;

int of = 0;
int dz = 0;

int calcASM(int a, int b) {
	int res = 0;
	__asm {
		mov ebx, a; <ebx> = a
		mov ecx, b; <ecx> = b
		cmp ebx, ecx; a ? b
		jg a_bigger; a < b
		jl a_smaller; a > b
		mov res, -9; res = -9
		jmp fin; переход к концу программы
	a_bigger :
		or ebx, ebx; a ? 0
		jz err_zero; проверка деления на 0
		mov eax, ecx; <eax> = b
		imul ecx; <eax> = b ^ 2
		jo overflow; проверка переполнения
		imul ecx; <eax> = b ^ 3
		jo overflow; проверка переполнения
		cdq; <eax> = > <edx:eax> = b ^ 3
		idiv ebx; <eax> = b ^ 3 / a
		dec eax; <eax> = b ^ 3 / a - 1
		jo overflow; проверка переполнения
		mov res, eax; res = b ^ 3 / a - 1
		jmp fin; переход к концу программы
	a_smaller :
		or ecx, ecx; b ? 0
		jz err_zero; проверка деления на 0
		mov eax, ebx; <eax> = a
		imul ebx; <eax> = a ^ 2
		jo overflow; проверка переполнения
		imul ebx; <eax> = a ^ 3
		jo overflow; проверка переполнения
		add eax, 5; <eax> = a ^ 3 + 5
		jo overflow; проверка переполнения
		cdq; <eax> = > <edx:eax> = a ^ 3 + 5
		idiv ecx; <eax> = (a ^ 3 + 5) / b
		mov res, eax; res = (a ^ 3 + 5) / b
		jmp fin; переход к концу программы
	overflow :
		mov of, 1; of = 1
		jmp fin; переход к концу программы
	err_zero :
		mov dz, 1; dz = 1
		jmp fin; переход к концу программы
	fin :
	}
	return res;
}

int main() {
	while (true) {
		int a, b;
		cout << "If a > b => (b ^ 3 / a - 1)\nIf a = b => -9\nIf a < b => ((a ^ 3 + 5) / b)\n";
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
		int resultasm = calcASM(a, b);
		if (of) cout << "Overflow error!" << endl;
		else if (dz) cout << "Division by zero!" << endl;
		else cout << "Result: " << resultasm << endl;
		of = 0; dz = 0;
		cin.clear();
		system("pause");
		system("cls");
	}
	return 0;
}
