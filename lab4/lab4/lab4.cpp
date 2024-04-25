
#include <iostream>
#include <string>
using namespace std;

int of = 0;
int bd = 0;

int input_int(string msg) {
	int n;
	cout << msg;
	while (!(cin >> n) || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Error! Try again:";
	}
	return n;
}

int input_unsign_int(string msg) {
	int n;
	cout << msg;
	while (!(cin >> n) || cin.peek() != '\n' || n < 1) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Error! Try again:";
	}
	return n;
}

int calcASM(int* array, int arrsize, int b, int d)
{
	int result = 0;
	__asm
	{
		mov ebx, b; ebx = b
		cmp ebx, d; ebx ? d
		jg b_more_d; Переход если b>d
		xor esi, esi; подготовка регистра индекса в массиве
		mov ebx, array; <ebx> указывает на начало массива
		mov ecx, arrsize; счетчик цикла
	begin_loop:
		mov eax, [ebx + esi * 4]; определяем текущий элемент
			jo error_of; проверка на переполнение
		cmp eax, b; сравниваем a[i] и b
		jl end_loop; если a < b
		cmp eax, d; сравниваем a[i] и d
		jg end_loop; если a[i] > d
		add result, eax; result += eax
		jo error_of; Преполнение
	end_loop:
		inc esi; переходим к следующему элементу
		loop begin_loop;
		jmp ex; по окончанию цикла выходим из asm части
	error_of :
		mov of, 1;
		jmp ex;
	b_more_d:
		mov bd, 1;
		jmp ex;
	ex:
	}
	return result;
}

int main() {
	while (true)
	{
		cout << "Find the sum of elements of the array A={a[i]} satisfying the condition: b <= a[i] <= d" << endl;
		int* array, size, b, d;
		size = input_unsign_int("Input size of array: ");
		array = new int[size];
		for (int i = 0; i < size; i++)
			array[i] = input_int("Input a[" + to_string(i) + "]:");
		b = input_int("Please enter b: ");
		d = input_int("Please enter d: ");

		int result_cpp = 0;
		int result_asm = calcASM(array, size, b, d);
		if (of) cout << "Overflow error!" << endl;
		else if (bd) cout << "d can be only > b" << endl;
		else {
			cout << "Array: ";
			for (int i = 0; i < size; ++i) {
				if (array[i] <= d && array[i] >= b)
					result_cpp += array[i];
				cout << array[i] << " ";
			}
			cout << "\nResult ASM: " << result_asm << endl;
			cout << "Result CPP: " << result_cpp << endl;
		}

		delete[] array;
		of = 0; bd = 0;
		cin.clear();
		system("pause");
		system("cls");
	}
	return 0;
}