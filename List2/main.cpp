#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-------------------------------------------------\n"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Element* New = new Element(Data);	//1)
			New->pNext = Head;					//2)
			Head->pPrev = New;					//3)
			Head = New;							//4) 
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Element* New = new Element(Data);	//1)
			New->pPrev = Tail;					//2)
			Tail->pNext = New;					//3)
			Tail = New;							//4)
		}
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > size) return;				   // Если индекс больше размера списка, выходим из метода
		if (Index == 0) return push_front(Data);   // Если индекс равен 0, добавляем элемент в начало списка
		if (Index == size) return push_back(Data); // Если индекс равен размеру списка, добавляем элемент в конец

		Element* Temp;
		if (Index < size / 2) // Если индекс ближе к началу списка
		{
			Temp = Head;      // Начинаем с головы списка
			for (int i = 0; i < Index; i++) Temp = Temp->pNext; // Перемещаемся к нужной позиции
		}
		else				 // Если индекс ближе к концу списка
		{
			Temp = Tail;     // Начинаем с хвоста списка
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev; // Перемещаемся к нужной позиции
		}

		Element* New = new Element(Data);    // Создаем новый элемент
		New->pNext = Temp;                   // Устанавливаем указатель на следующий элемент для нового элемента
		New->pPrev = Temp->pPrev;            // Устанавливаем указатель на предыдущий элемент для нового элемента
		Temp->pPrev->pNext = New;            // Устанавливаем указатель на новый элемент у предыдущего элемента
		Temp->pPrev = New;                   // Устанавливаем указатель на новый элемент у текущего элемента

		size++;  // Увеличиваем размер списка
	}

	//				Removing elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;		//1)
			delete Head->pPrev;		//2)
			Head->pPrev = nullptr;	//3) 
		}
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;		//1)
			delete Tail->pNext;		//2)
			Tail->pNext = nullptr;	//3)
		}
		size--;
	}
	void erase(int Index)
	{
		if (Index >= size) return;				 // Если индекс больше или равен размеру списка, выходим из метода
		if (Index == 0) return pop_front();		 // Если индекс равен 0, удаляем первый элемент
		if (Index == size - 1) return pop_back();// Если индекс равен последнему элементу, удаляем последний элемент

		Element* Temp;
		if (Index < size / 2) // Если индекс ближе к началу списка
		{
			Temp = Head;	  // Начинаем с головы списка
			for (int i = 0; i < Index; i++) Temp = Temp->pNext; // Перемещаемся к нужной позиции
		}
		else				  // Если индекс ближе к концу списка
		{
			Temp = Tail;      // Начинаем с хвоста списка
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev; // Перемещаемся к нужной позиции
		}

		Temp->pPrev->pNext = Temp->pNext; // Связываем предыдущий элемент с последующим
		Temp->pNext->pPrev = Temp->pPrev; // Связываем следующий элемент с предыдущим

		delete Temp; // Удаляем текущий элемент

		size--;      // Уменьшаем размер списка
	}

	//				Methods:
	void print()const
	{
		cout << delimiter << endl;
		cout << "Head:\t" << Head << endl;

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout
			<< Temp->pPrev << tab
			<< Temp << tab
			<< Temp->Data << tab
			<< Temp->pNext << endl;

		cout << "Tail:\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << delimiter << endl;
	}
	void reverse_print()const
	{
		cout << delimiter << endl;
		cout << "Tail:\t" << Tail << endl;

		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout
			<< Temp->pPrev << tab
			<< Temp << tab
			<< Temp->Data << tab
			<< Temp->pNext << endl;

		cout << "Head:\t" << Head << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << delimiter << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	//for (int i = 0; i < 100; i++)list.pop_back();
	//list.reverse_print();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
}