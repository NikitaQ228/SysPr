#include <iostream>
#include <math.h>
using namespace std;

double calc_asm(double x, double e) {
	const double one = 1, two = 2, six = 6;
	double n = 1, result;
	__asm {
		finit;
		fld x;								st0 = x
			fld st;							st0 = x, st1 = x
			For :
		fld x;								st0 = x, st1 = Cn, st2 = sum
			fmul st, st;					st0 = x * x, st1 = Cn, st2 = sum
			fld n;							st0 = n, st1 = x * x, st2 = Cn, st3 = sum
			fmul two;						st0 = n * 2, st1 = x * x, st2 = Cn, st3 = sum
			fld st;							st0 = n * 2, st1 = n * 2, st2 = x * x, st3 = Cn, st4 = sum
			fadd one;						st0 = n * 2 + 1, st1 = n * 2, st2 = x * x, st3 = Cn, st4 = sum
			fmulp st(1), st;				st0 = (n * 2) * (n * 2 + 1), st1 = x * x, st2 = Cn, st3 = sum
			fdivp st(1), st;				st0 = (x * x) / ((n * 2) * (n * 2 + 1)), st1 = Cn, st2 = sum
			fchs;							st0 = -(x * x) / ((n * 2) * (n * 2 + 1)), st1 = Cn, st2 = sum
			fmulp st(1), st;				st0 = Cn * (-(x * x) / ((n * 2) * (n * 2 + 1))), st1 = sum
			fldz;							st0 = 0, st1 = Cn * (-(x * x) / ((n * 2) * (n * 2 + 1))), st2 = sum
			fcomip st, st(1);				st0 = Cn * (-(x * x) / ((n * 2) * (n * 2 + 1))), st1 = sum
			ja absolut
			fld e;							st0 = e, st1 = Cn * (-(x * x) / ((n * 2) * (n * 2 + 1))), st2 = sum
			fcomip st, st(1);				st0 = Cn * (-(x * x) / ((n * 2) * (n * 2 + 1))), st1 = sum
			jae exit_asm
			metka :
		fadd st(1), st;					st0 = Cn * (-(x * x) / ((n * 2) * (n * 2 + 1))), st1 = sum + Cn * (-(x * x) / ((n * 2) * (n * 2 + 1)))
			fld n;							st0 = n, st1 = Cn * (-(x * x) / ((n * 2) * (n * 2 + 1))), st2 = sum2
			fadd one;						st0 = n + 1, st1 = Cn * (-(x * x) / ((n * 2) * (n * 2 + 1))), st2 = sum2
			fstp n;							st0 = Cn * (-(x * x) / ((n * 2) * (n * 2 + 1))), st1 = sum2
			jmp For;
	absolut:
		fchs;							st0 = -Cn * (-(x * x) / ((n * 2) * (n * 2 + 1))), st1 = sum
			fld e;							st0 = e, st1 = -Cn * (-(x * x) / ((n * 2) * (n * 2 + 1))), st2 = sum
			fcomip st, st(1);				st0 = -Cn * (-(x * x) / ((n * 2) * (n * 2 + 1))), st1 = sum
			jae exit_asm
			fchs;							st0 = Cn * (-(x * x) / ((n * 2) * (n * 2 + 1))), st1 = sum
			jmp metka
			exit_asm :
		fxch st(1)
			fstp result
	}
	return result;
}


int main() {
	while (true) {
		double x, e;
		cout << "Please enter x: ";
		while (!(cin >> x) || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Error! Try again: " << endl;
		}
		cout << "Please enter epsilon: ";
		while (!(cin >> e) || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Error! Try again: " << endl;
		}
		cout << "asm: " << calc_asm(x, e) << endl
			<< "cpp: " << sin(x) << endl;

		cin.clear();
		system("pause");
		system("cls");
	}
	return 0;
}
