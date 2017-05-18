/*
**********DEQUE**********
*Create by Anton Chesnov*
*************************
*/


#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

/**
*Шаблонный класс очереди
*/
template <class T>
class Deq
{
public:
	Deq() // конструктор
	{
		sizedeq = 0;
		left = NULL;
		right = NULL;
	} 
	~Deq() // деструктор
	{
		ELDEQ *deqpoint;
		while (left) {
			deqpoint = left->next;
			//delete left;
			left = deqpoint;
		}
	}
	void addFront(T elem)
	{
		if (sizedeq == 0)
		{
			ELDEQ *deqpoint = new ELDEQ;
			deqpoint->next = NULL;
			deqpoint->prev = NULL;
			deqpoint->data = elem;
			left = right = deqpoint;
			sizedeq++;
			deqpoint->number = sizedeq;
		}
		else
		{
			ELDEQ *deqpoint = new ELDEQ;
			deqpoint->data = elem;
			deqpoint->next = left;
			deqpoint->prev = NULL;
			left->prev = deqpoint;
			left = deqpoint;
			sizedeq++;
			deqpoint->number = sizedeq;
		}
	}
	void addEnd(T elem)
	{
		if (sizedeq == 0)
		{
			ELDEQ *deqpoint = new ELDEQ;
			deqpoint->next = NULL;
			deqpoint->prev = NULL;
			deqpoint->data = elem;
			left = right = deqpoint;
			sizedeq++;
			deqpoint->number = sizedeq;
		}
		else
		{
			ELDEQ *deqpoint = new ELDEQ;
			deqpoint->next = NULL;
			deqpoint->prev = right;
			deqpoint->data = elem;
			right->next = deqpoint;
			right = deqpoint;
			sizedeq++;
			deqpoint->number = sizedeq;
		}
	}
	void delFront()
	{
		if (sizedeq == 1)
		{
			delete left;
			left = right = NULL;
			sizedeq--;
		}
		else if (sizedeq == 2)
		{
			delete left;
			right->prev = NULL;
			left = right;
			sizedeq--;
		}
		else if (sizedeq > 2)
		{
			ELDEQ *deqpoint = left->next;
			delete left;
			left = deqpoint;
			left->prev = NULL;
			sizedeq--;
		}

	}
	void delEnd()
	{
		if (sizedeq == 1)
		{
			delete right;
			left = right = NULL;
			sizedeq--;
		}
		else if (sizedeq == 2)
		{
			delete right;
			left->next = NULL;
			left = right;
			sizedeq--;
		}
		else if (sizedeq > 2)
		{
			ELDEQ *deqpoint = right->prev;
			delete right;
			right = deqpoint;
			right->next = NULL;
			sizedeq--;
		}
	}
	string getLeft()
	{
		return left->data.getInfo();
	}
	string getRight()
	{
		return right->data.getInfo();;
	}
	void print()
	{
		ELDEQ *deqpoint = new ELDEQ;
		deqpoint = left;
		while (deqpoint != NULL)
		{
			deqpoint->data.show();
			deqpoint = deqpoint->next;
		}
		cout << "\n";
	}
	void sort() // сортирует очередь по фамилии студентов
	{
		for (bool go = true; go; )
		{
			go = false;
			ELDEQ* deqpoint1;
			ELDEQ* deqpoint2;
			deqpoint1 = left;
			deqpoint2 = left->next;
			while (deqpoint2 != NULL)
			{
				if (deqpoint1->data.getLastName() > deqpoint2->data.getLastName())
				{
					ELDEQ* deqpoint3 = new ELDEQ;
					deqpoint3->data = deqpoint1->data;
					deqpoint1->data = deqpoint2->data;
					deqpoint2->data = deqpoint3->data;
					go = true;
				}
				deqpoint1 = deqpoint1->next;
				deqpoint2 = deqpoint2->next;
			}
		}
	}
	void grep(string feature, Deq<T>& newDeq) // разделение по группе или по предмету
	{
		ELDEQ *deqpoint;
		deqpoint = left;
		while (deqpoint != NULL)
		{
			if ( !feature.compare(deqpoint->data.getFeature()) )
			{
				newDeq.addEnd(deqpoint->data);
			}
			deqpoint = deqpoint->next;
		}
	}
	void concatenation(Deq<T>& deq2) // склеивает две очереди
	{
		right->next = deq2.left;
		deq2.left->prev = right;
		deq2 = Deq<T>();
	}
	void merge(Deq<T>& deq2)
	{
		concatenation(deq2);
		sort();
	}
	int getSize()
	{
		return sizedeq;
	}
	bool equal(Deq<T>& deq2)
	{
		ELDEQ* deqpoint1 = left;
		ELDEQ* deqpoint2 = deq2.left;
		while (deqpoint1 != NULL)
		{
			if (deqpoint1->data.getInfo() != deqpoint2->data.getInfo())
			{
				return false;
			}
			deqpoint1 = deqpoint1->next;
			deqpoint2 = deqpoint2->next;
		}
		if (deqpoint1 == NULL && deqpoint2 == NULL)
		{
			return true;
		}
		return false;
	}
private:

	typedef struct eldeq // стркутура для элемента дека
	{
	public:
		T data; // данные
		int number; // номер в очереди
		struct eldeq *next, *prev; //указатель на следующий и предыдущий элемент очереди
	} ELDEQ;

	unsigned int sizedeq; // количество элементов в очереди
	ELDEQ *right; // указатель на самый правый элемент очереди
	ELDEQ *left; // указатель на самый левый элемент очереди
};

class Student
{
public:
	Student() : name(""), lastname(""), info("") {}
	void setInfo() // ввод информации о студенте с клавиатуры
	{
		cin >> lastname >> name >> info;
	}
	void setInfo(string lastname, string name, string info)
	{
		this->info = info;
		this->name = name;
		this->lastname = lastname;
	}
	string getInfo() // получение информации о студенте
	{
		string str = lastname + " " + name + " " + info;
		return str;
	}
	string getFeature() { return info; }
	string getName() { return name; }
	string getLastName() { return lastname; }
	void show() // вывод информации на экран
	{
		cout << lastname << "   " << name << "   " << info << endl;
	}

	friend istream& operator>>(istream& os, Student& pumba)
	{
		os >> pumba.lastname >> pumba.name >> pumba.info;
		return os;
	}
private:
	string name, lastname, info;
};

class Teacher
{
public:
	Teacher() : name(""), lastname(""), info("") {}
	void setInfo() // ввод информации о преподавателе с клавиатуры
	{
		cin >> lastname >> name >> info;
	}
	void setInfo(string name, string lastname, string info)
	{
		this->info = info;
		this->name = name;
		this->lastname = lastname;
	}
	string getInfo() // получение информации о преподавателе
	{
		string str = lastname + " " + name + " " + info;
		return str;
	}
	string getFeature() { return info; }
	string getName() { return name; }
	string getLastName() { return lastname; }
	void show() // вывод информации на экран
	{
		cout << lastname << "   " << name << "   " << info << endl;
	}
private:
	string name, lastname, info;
};

template <class T>
void MyDeque(Deq<T> deq1, Deq<T> deq2, int f) // функция для менюшки
{
	T man1;
	T man2;
	int ChSize1 = 0;
	cout << "\nHow many members have your first Deque?\n";
	cin >> ChSize1;
	cout << "\nEnter first Deque\n";
	for (int i = 0; i < ChSize1; i++)
	{
		man1.setInfo();
		deq1.addEnd(man1);
	}
	
	int ChSize2 = 0;
	cout << "\nHow many members have your second Deque?\n";
	cin >> ChSize2;
	cout << "\nEnter first Deque\n";
	for (int i = 0; i < ChSize2; i++)
	{
		man2.setInfo();
		deq2.addEnd(man2);
	}
	int ChMeth = 0;
	while (ChMeth != 11)
	{
		cout << "\nChoose method, which you would like to use for first Deque\n1 - Add new member in the End Deque\n2 - Add new member in the Front Deque\n"
			<< "3 - Get Left element\n4 - Get Right element\n5 - Delete Left element\n6 - Delete Right element\n7 - Sort Deque\n8 - Select items in other Deque groups or subjects\n"
			<< "9 - Perform Concatenation with secon Deque\n0 - Print Deque\n10 - Perform merge with secon Deque\n11 - Exit\n";
		cin >> ChMeth;
		if (ChMeth == 1)
		{
			T petr;
			petr.setInfo();
			deq1.addEnd(petr);
		}
		else if (ChMeth == 2)
		{
			T petr;
			petr.setInfo();
			deq1.addFront(petr);
		}
		else if (ChMeth == 3)
		{
			string el1 = deq1.getLeft();
			cout << "Left element:" << "\n" << el1 << endl;
		}
		else if (ChMeth == 4)
		{
			string el2 = deq1.getRight();
			cout << "Right element:" << "\n" << el2 << endl;
		}
		else if (ChMeth == 5)
		{
			deq1.delFront();
		}
		else if (ChMeth == 6)
		{
			deq1.delEnd();
		}
		else if (ChMeth == 7)
		{
			deq1.sort();
		}
		else if (ChMeth == 8)
		{
			Deq<T> newstud;
			string feature;
			cout << "Enter group or subject:";
			cin >> feature;
			deq1.grep(feature, newstud);
			cout << "\nNew Deque:\n";
			newstud.print();
		}
		else if (ChMeth == 9)
		{
			deq1.concatenation(deq2);
			deq1.print();
		}
		else if (ChMeth == 0)
		{
			cout << "First Deque:" << endl;
			deq1.print();
			cout << "Second Deque:" << endl;
			deq2.print();
		}
		else if (ChMeth == 10)
		{
			deq1.merge(deq2);
		}
	}
	cout << "GOODBYE!!!" << endl;
}

void test() // функция для тестов
{
	//тест добавления элементов в очередь
	Deq<Student> stud1;
	Student anton, vitya, pavel;
	anton.setInfo("Chesnov", "Anton", "B16511");
	vitya.setInfo("Coorits", "Victor", "B16505");
	pavel.setInfo("Parkhomets", "Pavel", "B16505");
	stud1.addFront(anton);
	stud1.addEnd(vitya);
	stud1.addFront(pavel);
	Deq<Student> stud2;
	Student ivan;
	ivan.setInfo("Ivan", "Dyatlov", "C16505");
	stud2.addEnd(ivan);

	Deq<Student> testdeq1;
	Deq<Student> testdeq2;

	ifstream fin("test.txt");
	if (!fin.is_open())
	{
		cout << "error" << endl;
		return;
	}	
	while (!fin.eof())
	{
		Student st;
		fin >> st;
		testdeq1.addEnd(st);
	}
	fin.close();
	Student st1;
	ifstream fin1("test2.txt");
	if (!fin1.is_open())
	{
		cout << "error" << endl;
		return;
	}
	fin1 >> st1;
	testdeq2.addEnd(st1);
	fin1.close();
	if (testdeq1.equal(stud1) && testdeq2.equal(stud2))
	{
		cout << "***Add test OK!***\n" << endl;
	}
	else
	{
		cout << "***Add test NOT OK!***\n" << endl;
	}
	
	// тест конкатенации

	Deq<Student> stud3;
	ifstream fin7("test.txt");
	if (!fin7.is_open())
	{
		cout << "error" << endl;
		return;
	}
	while (!fin7.eof())
	{
		Student st2;
		fin7 >> st2;
		stud3.addEnd(st2);
	}
	fin7.close();
	Deq<Student> stud4;
	ifstream fin8("test2.txt");
	if (!fin8.is_open())
	{
		cout << "error" << endl;
		return;
	}
	while (!fin8.eof())
	{
		Student st2;
		fin8 >> st2;
		stud4.addEnd(st2);
	}
	fin8.close();

	stud3.concatenation(stud4);

	Deq<Student> testdeq3;

	ifstream fin2("test3.txt");
	if (!fin2.is_open())
	{
		cout << "error" << endl;
		return;
	}
	while (!fin2.eof())
	{
		Student st2;
		fin2 >> st2;
		testdeq3.addEnd(st2);
	}
	fin2.close();

	if (testdeq3.equal(stud3))
	{
		cout << "***Concatenation test OK!***\n" << endl;
	}
	else
	{
		cout << "***Concatenation test NOT OK!\n***" << endl;
	}

	/**/
	// тест выделения очереди по заданному признаку
	Deq<Student> man1;
	Deq<Student> man2;

	ifstream fin3("test4.txt");
	if (!fin3.is_open())
	{
		cout << "error" << endl;
		return;
	}
	while (!fin3.eof())
	{
		Student st3;
		fin3 >> st3;
		man1.addEnd(st3);
	}
	fin3.close();

	Deq<Student> newman;
	man1.grep("B16511", newman);

	ifstream fin4("test5.txt");
	if (!fin4.is_open())
	{
		cout << "error" << endl;
		return;

	}
	while (!fin4.eof())
	{
		Student st4;
		fin4 >> st4;
		man2.addEnd(st4);
	}
	fin4.close();
	if (newman.equal(man2))
	{
		cout << "***Grep test OK!***\n" << endl;
	}
	else
	{
		cout << "***Grep test NOT OK!***\n" << endl;
	}

	// тест сортировки

	Deq<Student> sort;

	ifstream fin5("test6.txt");
	if (!fin5.is_open())
	{
		cout << "error";
		return;
	}
	while (!fin5.eof())
	{
		Student mary;
		fin5 >> mary;
		sort.addEnd(mary);
	}

	sort.sort();

	Deq<Student> eq;

	ifstream fin6("test7.txt");
	if (!fin6.is_open())
	{
		cout << "error";
		return;
	}
	while (!fin6.eof())
	{
		Student egor;
		fin6 >> egor;
		eq.addEnd(egor);
	}
	if (eq.equal(sort))
	{
		cout << "***Sort test OK!***\n" << endl;
	}
	else
	{
		cout << "***Sort test NOT OK!***\n" << endl;
	}

	// тест слияния

	Deq<Student> dima1;
	Deq<Student> dima2;
	Deq<Student> dima3;

	ifstream fint("test8.txt");
	if (!fint.is_open())
	{
		cout << "error";
		return;
	}
	while (!fint.eof())
	{
		Student egor;
		fint >> egor;
		dima1.addEnd(egor);
	}
	ifstream fint1("test9.txt");
	if (!fint.is_open())
	{
		cout << "error";
		return;
	}
	while (!fint1.eof())
	{
		Student egor;
		fint1 >> egor;
		dima2.addEnd(egor);
	}
	dima1.merge(dima2);
	ifstream fint2("test10.txt");
	if (!fint.is_open())
	{
		cout << "error";
		return;
	}
	while (!fint2.eof())
	{
		Student egor;
		fint2 >> egor;
		dima3.addEnd(egor);
	}
	if (dima3.equal(dima1))
	{
		cout << "***Merge test OK!***\n" << endl;
	}
	else
	{
		cout << "***Merge test NOT OK!***\n" << endl;
	}
	/**/
}

int main()
{
	int ChTest = 0;
	cout << "1 - Work with Deque\n2 - Test Deque\nYour choice:";
	cin >> ChTest;
	if (ChTest == 2)
	{
		test();
		cout << "**********GOODBYE!!!**********\n" << endl;
		//system("pause");
	}
	else if (ChTest == 1)
	{
		int ChDeq = 0;
		cout << "\n1 - Student\n2 - Teacher\nYour choice:";
		cin >> ChDeq;
		if (ChDeq == 1)
		{
			int f = 1;
			Deq<Student> vitya;
			Deq<Student> pavel;
			MyDeque(vitya, pavel, f);
		}
		else if (ChDeq == 2)
		{
			int f = 2;
			Deq<Teacher> nina;
			Deq<Teacher> artem;
			MyDeque(nina, artem, f);
		}
	}
	/**/
}
