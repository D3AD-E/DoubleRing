// DoubleRing.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Ring.h"
template <typename Key, typename Info>
void split(const Ring<Key,Info>& source,bool direction, Ring<Key, Info>& result1, int Ruence1, int rep1, Ring<Key, Info>& result2, int Ruence2, int rep2)
{
	if (Ruence1 < 0 || Ruence2 < 0)
		throw std::logic_error("Length cannot be less than 0");
	if (rep1 < 0 || rep2 < 0)
		throw std::logic_error("Cannot repeat less than 0 elements");
	result1.clear();
	result2.clear();
	if (source.empty())
		return;
	auto iter1 = source.begin();
	for (int j = (rep1 <= rep2) ? rep1 : rep2; j > 0; j--)
	{
		for (int i = Ruence1; i > 0; i--)
		{
			result1 += source.copy(iter1);
			if (direction)
				iter1++;
			else
				iter1--;
		}
		for (int i = Ruence2; i > 0; i--)
		{
			result2 += source.copy(iter1);
			if (direction)
				iter1++;
			else
				iter1--;
		}
	}

	for (int j = (rep1 >= rep2) ? rep1-rep2 : rep2 - rep1; j > 0; j--)
	{
		for (int i = (rep1 >= rep2) ? Ruence1 : Ruence2; i > 0; i--)
		{
			(rep1 >= rep2) ? result1 += source.copy(iter1) : result2 += source.copy(iter1);
			if (direction)
				iter1++;
			else
				iter1--;
		}
	}
}

int main()
{
	Ring<int, char> R1;
	for (int i = 1; i < 13; i++)
	{
		R1.push(i, 'c');
	}
	R1.displayList();
	Ring<int, char> R2;
	Ring<int, char> R3;
	split(R1, false, R2, 3, 2, R3, 2, 4);

	R2.displayList();
	//R2.displayListRev();

	R3.displayList();
	//R3.displayListRev();

	R2 = R1; //test =
	R2.push(200, 'c');
	R2.erase(R2.begin() + 2, R2.begin() + 4);//remove 2nd-4th element (counting from 0)
	R2.displayList();

	auto it = R2.begin();
	it = R2.insert(it + 2, 5, 5, 'p'); //test insert duplicates
	R2.displayList();

	Ring<int, char> R5(R2); //test copyconstructor
	if (R5.contains(3))
		std::cout << "Key found" << std::endl;
	else
		std::cout << "No key" << std::endl;
	R3.insert(R3.begin() + 2000, 2, 'c');
	R3.displayList();

	R1.erase(R1.begin(), R1.end()); //similar to clear()
	R1.displayList();
	R1 += R2; //+=
	R1.displayList();

	R1.erase(R1.begin() + 3, R1.end());
	R1.displayList();
	
	R1 += R2.copy(R2.begin() + 2, R2.end());//test copy
	R1.displayList();
	{
		Ring<int, char> R4(R2.begin() + 3, R2.end()); //test copyconstructor
		R4.displayList();
	}

	auto it2 = R1.insert(R1.begin() + 2, 5, 2, 'f'); //test of insert return value
	R1.displayList();


	return 0;
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
