#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-------------------------------------------------\n"


template<typename T>
class List
{
	class Element
	{
		T Data;			//значение элемента
		Element* pNext;	//указатель на следующий элемент
		Element* pPrev;	//указатель на предыдущий элемент
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	}*Head, * Tail;
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}

		//					Comparison operators:
		bool operator==(const ConstBaseIterator& othe)const;
		bool operator!=(const ConstBaseIterator& othe)const;

		//					Dereference operator
		const T& operator*() const;
	};

public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
			cout << "CItConstructor:\t" << this << endl;
		}
		~ConstIterator()
		{
			cout << "CItDestructor:\t" << this << endl;
		}
		//				Increment/Decrement:
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);

	};

	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
			cout << "CRevItConstructor:\t" << this << endl;
		}
		~ConstReverseIterator()
		{
			cout << "CRevItDestructor:\t" << this << endl;
		}

		//				Incremento/Decremento:
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
	};

	ConstIterator begin()const;
	Iterator begin();

	ConstIterator end()const;
	Iterator end();

	ConstReverseIterator rbegin()const;
	ReverseIterator rbegin();

	ConstReverseIterator rend()const;
	ReverseIterator rend();

	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	//						Operators:
	List<T>& operator=(const List<T>& other);

	//						Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//					Removing elements:
	void pop_front();
	void pop_back();
	void erase(int Index);

	//					Methods:
	void print() const;
	void reverse_print() const;
};

////////////////////////////////////////////////////////////////////////////////////////

template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
	:Data(Data), pNext(pNext), pPrev(pPrev)
{
	cout << "EConstructor:\t" << this << endl;
}
template<typename T>List<T>::Element::~Element()
{
	cout << "EDestructor:\t" << this << endl;
}

///////////////////////////////////////////////////////////////////////////////////////

//					Comparison operators:
template<typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& othe)const
{
	return this->Temp == othe.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& othe)const
{
	return this->Temp != othe.Temp;
}
//					Dereference operator
template<typename T>const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

//				Increment/Decrement:
template<typename T> List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T> List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
//				Incremento/Decremento:
template<typename T> List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T> List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
//					Iterator:
template<typename T>T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
//					ReversIterator:
template<typename T>T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

////////////////////////////////////////////////////////////////////////////////////
template<typename T> List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T> List<T>::Iterator List<T>::begin()
{
	return Head;
}

template<typename T> List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T> List<T>::Iterator List<T>::end()
{
	return nullptr;
}

template<typename T> List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T> List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}

template<typename T> List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}
template<typename T> List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T> List<T>::List() : Head(nullptr), Tail(nullptr), size(0)
{
	cout << "LConstructor:\t" << this << endl;
}

template<typename T> List<T>::List(const std::initializer_list<T>& il) : List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		push_back(*it);
	}
}
template<typename T> List<T>::List(const List<T>& other) :List()
{
	*this = other;
	cout << "CopyConstructor:" << this << endl;
}

template<typename T> List<T>::~List()
{
	while (Tail) pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//						Operators:
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "CopyAssignment:\t" << this << endl;
	return *this;
}

//						Adding elements:
template<typename T>void List<T>::push_front(T Data)
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

template<typename T>void List<T>::push_back(T Data)
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

template<typename T>void List<T>::insert(T Data, int Index)
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
template<typename T>void List<T>::pop_front()
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

template<typename T>void List<T>::pop_back()
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

template<typename T>void List<T>::erase(int Index)
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
template<typename T>void List<T>::print() const
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

template<typename T>void List<T>::reverse_print() const
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

///////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> buffer = left;	//CopyConstructor
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}

template<typename T> void Grow(List<T>& list)
{
	for (typename List<T>::Iterator it = list.begin(); it != list.end(); ++it)
		*it *= 10;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//#define BASE_CHECK
//#define ITERATORS_CHECK
//#define OPERATOR_PLUS_CHECK
//#define DOUBLE_CHEK
#define STD_STRING_CHEK

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

#ifdef OPERATOR_PLUS_CHECK

	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;
	/*list3.print();
	list3.reverse_print();*/
	for (int i : list1)cout << i << tab; cout << endl;

#endif // OPERATOR_PLUS_CHECK

#ifdef DOUBLE_CHEK
	//				Double:
	List<double> d_list = { 2.7, 3.14, 5.5, 8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;
	for (List<double>::Iterator it = d_list.begin(); it != d_list.end(); ++it)
		cout << *it << tab; cout << endl;
	for (List<double>::ReverseIterator it = d_list.rbegin(); it != d_list.rend(); ++it)
		cout << *it << tab; cout << endl;
	cout << delimiter << endl;

	/*List<double> d_list1 = { 3.14, 2.71, 1.41, 1.73 };
	List<double> d_list2 = { 6.28, 3.14 };
	List<double> d_list3 = d_list1 + d_list2;
	for (double d : d_list3) cout << d << tab;
	cout << endl;

	Grow(double_list3);
	for (double d : d_list3) cout << d << tab;
	cout << endl << endl;*/
#endif // DOUBLE_CHEK

#ifdef STD_STRING_CHEK
	//				std::string:
	List<std::string> s_list = { "Hello", "World" ,"Templates" ,"DONE" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
	for (List<std::string>::Iterator it = s_list.begin(); it != s_list.end(); ++it)
		cout << *it << tab; cout << endl;
	for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
		cout << *it << tab; cout << endl;
	cout << delimiter << endl;

	/*List<std::string> s_list1 = { "Hello", "World","Templates" };
	List<std::string> s_list2 = {"Powerful", "DONE"};
	List<std::string> s_list3 = s_list1 + s_list2;
	for (const std::string& s : s_list3) cout << s << tab;
	cout << endl;*/
#endif // STD_STRING_CHEK

}