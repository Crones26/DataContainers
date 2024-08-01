#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
	int Data;		// значение элемента
	Element* pNext; // указатель на следующий элемент
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr;// Когда список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//					Adding elements:
	void push_front(int Data)
	{
		{
			//1. Создаем новый элемент:
			Element* New = new Element(Data);
			//2. Включаем новый элемент в список:
			New->pNext = Head;
			//3. Переводим голову на новый элемент
			Head = New;

		}
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1. Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}

		//2. Создаем новый элемент:
		Element* New = new Element(Data);

		//3. Включаем новый элемент в список
		Temp->pNext = New;
	}

	//				Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		Element* Temp = Head;	// Temp это итератор 
								// Итератор – это указатель при помощи которого можно перебирать элементы структуры данных 
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; // Переход на следующий элемент
		}

		//for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			//cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");

	//Element element(5);
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.print();

}