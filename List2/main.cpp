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
		int Data;		//значение элемента
		Element* pNext;	//указатель на следующий элемент
		Element* pPrev;	//указатель на предыдущий элемент
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			//cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			//cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;
	size_t size;
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
			//cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			//cout << "ItDestructor:\t" << this << endl;
		}

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		//				Comparison operators:
		bool operator==(const Iterator& other) const
		{
			return this->Temp == other.Temp;
		}

		bool operator!=(const Iterator& other) const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}

		int& operator*()
		{
			return Temp->Data;
		}

		Element* operator->()
		{
			return Temp;
		}
	};
	
	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "RItConstructor:\t" << this << endl;
		}
		~ReverseIterator()
		{
			cout << "RItDestructor:\t" << this << endl;
		}

		//				Increment/Decrement:
		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		//				Comparison operators:
		bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		//				Dereference operators:
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};

	const Iterator begin()const
	{ 
		return Head;
	}
	Iterator begin()
	{
		return Head;
	}

	const Iterator end()const
	{
		return nullptr;
	}
	Iterator end()
	{
		return nullptr;
	}

	const ReverseIterator rbegin()const
	{
		return Tail;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}

	const ReverseIterator rend()const
	{
		return nullptr;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}

	List() : Head(nullptr), Tail(nullptr), size(0)
	{
		cout << "LConstructor:\t" << this << endl;
	}

	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "CopyConstructor:" << this << endl;
	}

	~List()
	{
		while (Tail) pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//						Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	//						Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			//Element* New = new Element(Data); //1)
			//New->pNext = Head;                //2)
			//Head->pPrev = New;                //3)
			//Head = New;                       //4) 

			Head = Head->pPrev = new Element(Data, Head);
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
			//Element* New = new Element(Data); //1)
			//New->pPrev = Tail;                //2)
			//Tail->pNext = New;                //3)
			//Tail = New;                       //4)

			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index > size) return;                  // Если индекс больше размера списка, выходим из метода
		if (Index == 0) return push_front(Data);   // Если индекс равен 0, добавляем элемент в начало списка
		if (Index == size) return push_back(Data); // Если индекс равен размеру списка, добавляем элемент в конец

		Element* Temp;
		if (Index < size / 2) // Если индекс ближе к началу списка
		{
			Temp = Head;      // Начинаем с головы списка
			for (int i = 0; i < Index; i++) Temp = Temp->pNext; // Перемещаемся к нужной позиции
		}
		else                  // Если индекс ближе к концу списка
		{
			Temp = Tail;      // Начинаем с хвоста списка
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev; // Перемещаемся к нужной позиции
		}

		//Element* New = new Element(Data);    // Создаем новый элемент
		//New->pNext = Temp;                   // Устанавливаем указатель на следующий элемент для нового элемента
		//New->pPrev = Temp->pPrev;            // Устанавливаем указатель на предыдущий элемент для нового элемента
		//Temp->pPrev->pNext = New;            // Устанавливаем указатель на новый элемент у предыдущего элемента
		//Temp->pPrev = New;                   // Устанавливаем указатель на новый элемент у текущего элемента

		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);

		size++;     // Увеличиваем размер списка
	}

	//					Removing elements:
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
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
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
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}

	void erase(int Index)
	{
		if (Index >= size) return;                // Если индекс больше или равен размеру списка, выходим из метода
		if (Index == 0) return pop_front();       // Если индекс равен 0, удаляем первый элемент
		if (Index == size - 1) return pop_back(); // Если индекс равен последнему элементу, удаляем последний элемент

		Element* Temp;
		if (Index < size / 2) // Если индекс ближе к началу списка
		{
			Temp = Head;      // Начинаем с головы списка
			for (int i = 0; i < Index; i++) Temp = Temp->pNext; // Перемещаемся к нужной позиции
		}
		else                  // Если индекс ближе к концу списка
		{
			Temp = Tail;      // Начинаем с хвоста списка
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev; // Перемещаемся к нужной позиции
		}

		Temp->pPrev->pNext = Temp->pNext; // Связываем предыдущий элемент с последующим
		Temp->pNext->pPrev = Temp->pPrev; // Связываем следующий элемент с предыдущим

		delete Temp; // Удаляем текущий элемент

		size--;      // Уменьшаем размер списка
	}

	//					Methods:
	void print() const
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

	void reverse_print() const
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
List operator+(const List& left, const List& right)
{
	List buffer = left;
	for (List::Iterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
	}
	return buffer;
}

//#define BASE_CHECK
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHEK
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
#endif // BASE_CHEK

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	//list.print();
	//list.reverse_print();
	for (int i : list)cout << i << tab; cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
#endif // ITERATORS_CHECK

	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	List list3 = list1 + list2;
	list1.print();
	list2.print();
	list3.print();

}