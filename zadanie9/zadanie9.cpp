// zadanie9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
using namespace std;


const int arryy_size = 8;
int mas[arryy_size];

DWORD WINAPI create(LPVOID iNum)
{
	for (int i = 0; i < (int)iNum; i++)
	{
		mas[i] = rand() % 10;
		cout << mas[i] << " ";
	}
	return 0;
}

DWORD WINAPI comb(LPVOID n)
{
	vector<int> vect;
	for (int i = 0; i != (int)n;i++)
	{
		vect.push_back(mas[i]);//копируем элементы из массива в вектор
	}
	while (next_permutation(vect.begin(), vect.end()))//генерация и вывод всех возможных комбинаций элементов массива
	{
		copy(vect.begin(), vect.end(), ostream_iterator<int>(cout, ""));
		cout << endl;
	}

	return 0;
}


int main()
{
	setlocale(LC_ALL, "ru");
	int inc;
	cout << "enter massiv size: ";
	cin >> inc;
	int *mas=new int[inc];
	HANDLE hThread;
	DWORD IDThread;

	HANDLE hThreadComb1;
	DWORD IDThreadComb1;

	HANDLE hThreadComb2;
	DWORD IDThreadComb2;

	cout << "massiv: " << endl;

	//запуск потока create
	hThread = CreateThread(NULL, 0, create, (void*)inc, 0, &IDThread);
	if (hThread == NULL)
		return GetLastError();

	//ждем пока поток create закончит работу
	WaitForSingleObject(hThread, INFINITE);

	//закрытие дескриптора потока create
	CloseHandle(hThread);

	delete[] mas;
	mas = nullptr;

	cout << "\nКомбинации чисел: " << endl;
	hThreadComb1 = CreateThread(NULL, 0, comb, (void*)inc, 0, &IDThreadComb1);
	if (hThreadComb1 == NULL)
		return GetLastError();
	WaitForSingleObject(hThreadComb1, INFINITE);
	CloseHandle(hThreadComb1);
	
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
