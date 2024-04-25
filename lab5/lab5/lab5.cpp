#include <iostream>
using namespace std;

int f = 0;

double calc_asm(double a, double b, double c) {
	const double d2 = 2, d21 = 21, d256 = 256;
	double result;
	__asm {
		finit;
		fld d2;								st0 = 2
		fmul c;								st0 = 2 * c
		fmul b;								st0 = 2 * c * b
		fadd a;								st0 = 2 * c * b + a
		fsub d21;							st0 = 2 * c * b + a - 21
		fld c;								st0 = c, st1 = 2 * c * b + a - 21
		fchs;								st0 = -c, st1 = 2 * c * b + a - 21
		fld a;								st0 = a, st1 = -c, st2 = 2 * c * b + a - 21
		fldz;								st0 = 0, st1 = a, st2 = -c, st3 = 2 * c * b + a - 21
		fucompp;							st0 = -c, st1 = 2 * c * b + a - 21
		fnstsw ax;							сохраняем регистр sw в ax
		sahf;								копирование в регистр флагов
		jz error_0;							в случае 0 переход
		fdiv a;								st0 = -c / a, st1 = 2 * c * b + a - 21
		fmul b;								st0 = -c / a * b, st1 = 2 * c * b + a - 21
		fadd d256;							st0 = -c / a * b + 256, st1 = 2 * c * b + a - 21
		fldz;								st0 = 0, st1 = -c / a * b + 256, st2 = 2 * c * b + a - 21
		fucomp;								st0 ? st1
		fnstsw ax;							сохраняем регистр sw в ax
		sahf;								копирование в регистр флагов
		jz error_0;							в случае 0 переход
		fdivp st(1), st;					st0 = (2 * c * b + a - 21) / (-c / a * b + 256)
		jmp exit_asm;
	error_0:
		mov f, 1; f = 1
	exit_asm:
		fstp result;						result = (2 * c * b + a - 21) / (-c / a * b + 256)
	}
	return result;
}

double calc_cpp(double a, double b, double c) {
	return (2 * c * b + a - 21) / (-c / a * b + 256);
}

int main() {
	while (true) {
		double a, b, c, res;
		cout << "Enter a, b, c for (2*c*b + a - 21)/(-c / a * b + 256):\n";
		cout << "Please enter a: ";
		while (!(cin >> a) || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Error! Try again: " << endl;
		}
		cout << "Please enter b: ";
		while (!(cin >> b) || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Error! Try again: " << endl;
		}
		cout << "Please enter c: ";
		while (!(cin >> c) || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Error! Try again: " << endl;
		}
		res = calc_asm(a, b, c);
		if (f) cout << "Division by zero!\n";
		else cout << "cpp: " << calc_cpp(a, b, c) << endl
			<< "asm: " << res << endl;

		f = 0;
		cin.clear();
		system("pause");
		system("cls");
	}
	return 0;
}
