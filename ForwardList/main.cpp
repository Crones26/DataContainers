#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "------------------------------------------------------------"

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
		Head = nullptr; // Когда список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head) pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//					Adding elements:
	void push_front(int Data)
	{
		// 1. Создаем новый элемент:
		Element* New = new Element(Data);
		// 2. Включаем новый элемент в список:
		New->pNext = Head;
		// 3. Переводим голову на новый элемент
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		// 1. Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}

		// 2. Создаем новый элемент:
		Element* New = new Element(Data);

		// 3. Включаем новый элемент в список
		Temp->pNext = New;
	}
	void insert(int index, int Data)
	{

		if (index == 0) return push_front(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; ++i)
		{
			if (Temp->pNext == nullptr) break;
			Temp = Temp->pNext;
		}
		Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}

	//					Removing elements:
	void pop_front()
	{
		if (Head == nullptr) return;
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;
	}

	void pop_back()
	{
		if (Head == nullptr) return;
		if (Head->pNext == nullptr) return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	void erase(int index)
	{
		if (index == 0) return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < index - 1; ++i)
		{
			if (Temp->pNext == nullptr) return;
			Temp = Temp->pNext;
		}
		if (Temp->pNext == nullptr) return;
		Element* ToDelete = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete ToDelete;
	}

	//				Methods:
	void print() const
	{
		cout << "Head:\t" << Head << endl;
		Element* Temp = Head;	// Temp это итератор
								// Итератор – это указатель, при помощи которого можно перебирать элементы структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; // Переход на следующий элемент
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите количество элементов: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	list.push_front(1234);
	cout << "Добавление первого элемента: " << endl;
	list.print();
	cout << delimiter << endl;
	list.push_back(123);
	cout << "Добавление последнего элемента: " << endl;
	list.print();
	cout << delimiter << endl;
	list.pop_front();
	cout << "Удаления первого элемента: " << endl;
	list.print();
	cout << delimiter << endl;
	list.pop_back();
	cout << "Удаления последнего элемента: " << endl;
	list.print();
	cout << delimiter << endl;
	list.insert(2, 777);
	cout << "Вставка элемента 777 на позицию 2: " << endl;
	list.print();
	cout << delimiter << endl;
	list.erase(2);
	cout << "Удаления элемента на позиции 2: " << endl;
	list.print();
}