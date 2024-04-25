#include <iostream>
using namespace std;

int f = 0;

double calcASM(double a, double b) {
	const double c1 = 1, c_9 = -9, c5 = 5;
	double res = 0;
	__asm {
		finit;						инциализация сопроцессора
		fld b;						st0 = b
		fld a;						st0 = a, st1 = b
		fcom;						a ? b
		fstsw ax;					сохраняем регистор флагов сопроцессора
		sahf;						записываем в регистор флагов процессора
		ja a_bigger;				переход если а больше
		jb b_bigger;				переход если b больше
		;							если равны
		fld c_9;					st0 = -9, st1 = a, st2 = b
		jmp endcalc
	a_bigger:
		ftst;						сравнение а с 0
		fstsw ax;					сохраняем регистор флагов сопроцессора
		sahf;						записываем в реистор флагов процессора
		je error;					переход если а = 0
		fld st(1);					st0 = b, st1 = a, st2 = b
		fmul st(2), st;				st0 = b, st1 = a, st2 = b * b
		fmulp st(2), st;			st0 = a, st1 = b ^ 3
		fdivp st(1), st;			st0 = b ^ 3 / a
		fsub c1;					st0 = b ^ 3 / a - 1
		jmp endcalc
	b_bigger:
		fldz;						st0 = 0, st1 = a; st2 = b
		fcomp st(2);				b ? 0
		;							st0 = a, st2 = b
		fnstsw ax;					сохраняем регистор флагов сопроцессора
		sahf;						записываем в реистор флагов процессора
		je error;					переход если b = 0
		fld st;						st0 = a, st1 = a, st2 = b
		fmul;						st0 = a * a, st1 = a, st2 = b
		fmulp st(1), st;			st0 = a ^ 3, st1 = b
		fadd c5;					st0 = a ^ 3 + 5, st1 = b
		fxch;						st0 = b, st1 = a ^ 3 + 5
		fdivp st(1), st;			st0 = (a ^ 3 + 5) / b
		jmp endcalc
	error:
		mov f, 1
	endcalc:
		fstp res

	}
	return res;
}

double calcCPP(double a, double b) {
	if (a > b) return b * b * b / a - 1;
	if (a < b) return (a * a * a + 5) / b;
	return -9;
}

int main() {
	while (true) {
		double a, b;
		cout << "If a > b => (b ^ 3 / a - 1)\nIf a = b => -9\nIf a < b => ((a ^ 3 + 5) / b)\n";
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
		double result = calcASM(a, b);
		if (f) cout << "Division by zero!" << endl;
		else cout << "acm: " << result << endl
			<< "cpp: " << calcCPP(a, b) << endl;

		f = 0;
		cin.clear();
		system("pause");
		system("cls");
	}
	return 0;
}
