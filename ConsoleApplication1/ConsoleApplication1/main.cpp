// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>


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
		deqpoint = left->next;
		while (deqpoint != NULL)
		{
			delete left;
			left = deqpoint;
			deqpoint = deqpoint->next;
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
	Deq<T>& grep(string feature) // разделение по группе или по предмету
	{
		ELDEQ *deqpoint;
		Deq<T> newDeq;
		deqpoint = left;
		while (deqpoint != NULL)
		{
			if ( !feature.compare(deqpoint->data.getInfo()) )
			{
				newDeq.addEnd(deqpoint->data);
			}
			deqpoint = deqpoint->next;
		}
		newDeq.print();
		return newDeq;
	}
	void concatenation(Deq<T> deq2) // склеивает две очереди
	{
		deq2.left->prev = right;
		right->next = deq2.left;
	}
	int getSize()
	{
		return sizedeq;
	}
private:

	typedef struct eldeq // стркутура для элемента дека
	{
	public:
		T data; // данные
		int number; // номер в очереди
		eldeq *next, *prev; //указатель на следующий и предыдущий элемент очереди
	} ELDEQ;

	unsigned int sizedeq; // количество элементов в очереди
	eldeq *right; // указатель на самый левый элемент очереди
	eldeq *left; // указатель на самый правый элемент очереди
};

class Student
{
public:
	Student() : name(""), lastname(""), info("") {}
	void setInfo() // ввод информации о студенте с клавиатуры
	{
		cin >> lastname >> name >> info;
	}
	string getInfo() { return info; }// получение информации о студенте
	string getName() { return name; }
	string getLastName() { return lastname; }
	void show() // вывод информации на экран
	{
		cout << lastname << "   " << name << "   " << info << endl;
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
	string getInfo() { return info; }// получение информации о преподавателе
	string getName() { return name; }
	string getLastName() { return lastname; }
	void show() // вывод информации на экран
	{
		cout << lastname << "   " << name << "   " << info << endl;
	}
private:
	string name, lastname, info;
};

/*template <class T>
void MyDeque(Deq<T> deq1, Deq<T> deq2, int f)
{
	T man1;
	T man2;
	int ChSize1 = 0;
	cout << "\nHow many members in your first Deque have?";
	cin >> ChSize1;
	cout << "\nEnter first Deque\n";
	for (int i = 0; i < ChSize1; i++)
	{
		man1.setInfo();
		deq1.addEnd(man1);
	}
	
	int ChSize2 = 0;
	cout << "\nHow many members in your second Deque have?";
	cin >> ChSize2;
	cout << "\nEnter first Deque\n";
	for (int i = 0; i < ChSize2; i++)
	{
		man2.setInfo();
		deq2.addEnd(man1);
	}

	cout << "\nChoose method, which you would like to use\n1 - Add new member";
}*/

int main()
{
	/*int ChTest = 0;
	cout << "1 - Work with Deque\n2 - Test Deque\nYour choice:";
	cin >> ChTest;
	if (ChTest == 1)
	{
		//test(); // функция, вызывающая тест
	}
	else if (ChTest == 2)
	{
		int ChDeq = 0;
		cout << "\n1 - Student\n2 - Teacher";
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
			MyDeque(nina,artem, f);
		}
	}*/
	Deq<Student> stud;
	Student vitya;
	for (int i = 0; i < 3; i++)
	{
		vitya.setInfo();
		stud.addEnd(vitya);
	}
	Deq<Student> newstud;
	string feature;
	cout << "Enter feature:";
	cin >> feature;
	newstud = stud.grep(feature);
	int l = newstud.getSize();
	cout << "size=" << l << "\n";
	newstud.print();
	/*cout << "\n";
	stud.print();
	stud.sort();
	cout << "\n";
	stud.print();*/
}
