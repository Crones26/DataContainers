#include <iostream>
using std::cin;
using std::cout;
using std::endl;

using namespace std;

#define tab "\t"
#define delimiter "\n------------------------------------------------------------\n"

template<typename T> class ForwardList;
template<typename T> class Iterator;
template<typename T> class ConstIterator;

template <typename T>class Element
{
	T Data;		//значение элемента
	Element<T>* pNext; //указатель на следующий элемент
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		//cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		//cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList<T>;
	friend class Iterator<T>;
	friend class ConstIterator<T>;
};
template<typename T> int Element<T>::count = 0;

template <typename T>class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp) :Temp(Temp) {}
	~Iterator() {}

	//			Оператор разыменования
	T& operator*()
	{
		return Temp->Data;
	}

	//			Оператор инкремента
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	//			Операторы проверки на равенство
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
};

template <typename T>class ConstIterator
{
	Element<T>* Temp;
public:
	ConstIterator(Element<T>* ptr) :Temp(ptr) {}
	~ConstIterator() {}

	//			Оператор разыменования
	const T& operator*()
	{
		return Temp->Data;
	}

	//			Оператор инкремента
	ConstIterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	//			Операторы проверки на равенство
	bool operator!=(const ConstIterator& other)const
	{
		return Temp != other.Temp;
	}
	bool operator==(const ConstIterator& other)const
	{
		return Temp == other.Temp;
	}

};

template <typename T>class ForwardList
{
	Element<T>* Head;
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const initializer_list<T>& il) :ForwardList()
	{
		//initializer_list - это контейнер.
		//cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList<T>& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;   //здесь просто вызываем CopyAssignment
		cout << "LCopyConstructor: " << this << endl;
	}
	ForwardList(ForwardList<T>&& other) noexcept :ForwardList()
	{
		*this = std::move(other);
		cout << "LMoveConstructor: " << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//			Методы Begin и End
	Iterator<T> begin()
	{
		return Head;
	}
	Iterator<T> end()
	{
		return nullptr;
	}
	ConstIterator<T> begin()const
	{
		return Head;
	}
	ConstIterator<T> end()const
	{
		return nullptr;
	}


	//			Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "LCopyAssignment: " << this << endl;
		return *this;
	}
	ForwardList<T>& operator=(ForwardList<T>&& other) noexcept
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		return *this;
	}

	//					Adding elements:
	void push_front(T Data)
	{
		////1) Создаем новый элемент:
		//Element* New = new Element(Data);

		////2) Включаем новый элемент в список:
		//New->pNext = Head;

		////3) Переводим голову на новый элемент
		//Head = New;
		Head = new Element<T>(Data, Head);
		size++;
	}

	void push_back(T Data)
	{
		if (Head == nullptr) return push_front(Data);

		//1) Доходим до конца списка:
		Element<T>* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}

		////2) Создаем новый элемент
		//Element* New = new Element(Data);

		////3) Включаем новый элемент в список:
		//Temp->pNext = New;
		Temp->pNext = new Element<T>(Data);

		size++;
	}

	void pop_front()
	{
		if (Head == nullptr)return;
		Element<T>* Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr || Head->pNext == nullptr) return pop_front();
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void insert(T Data, int Index)
	{
		if (Index > size)return;
		if (Index == 0) return push_front(Data);
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}
	void erase(int Index)
	{
		if (Index >= size)return;
		if (Index == 0)return pop_front();
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Element<T>* Clear = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Clear;
		size--;
	}
	//				Methods:
	void reverse()
	{
		ForwardList<T> buffer;
		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		this->Head = buffer.Head;
		this->size = buffer.size;
		buffer.Head = nullptr;
	}
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		//Element* Temp = Head;	//Temp - это итератор
		////Итератор - это указатель, при помощи которого можно перебирать
		////элементы структуры данных.
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext; //Переход на следующий элемент
		//}
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Element<T>::count << endl;
	}
};

//#define BASE_CHECK
//#define COUNT_CHECK
//#define PERFORMANCE_CHEK
//#define RANGE_BASE_FOR_ARRAY
#define RANGE_BASED_FOR_LIST
void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
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
	//list.pop_back();
	//list.print();

	int index;
	int value;
	cout << "Введите индекс нового элемента: "; cin >> index;
	cout << "Введите значение нового элемента: "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
#endif // COUNT_CHECK

#ifdef PERFORMANCE_CHEK

	int n;
	cout << "Введите количество элементов: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	cout << "List filled" << endl;
	//list.print();

	cout << "Making copy" << endl;
	ForwardList list2 = list;	//CopyConstructor
	//ForwardList list2;
	//list2 = list;
	//list2.print();
	cout << "Copy DONE" << endl;

	ForwardList list3;
	list3 = std::move(list2);	//MoveAssignment
	list3.print();

#endif // PERFORMANCE_CHEK

#ifdef RANGE_BASE_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };

	/*int n = sizeof(arr) / sizeof(arr[0]);
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(arr[i]);
	}*/
	//list.print();
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
	//Range-based for:
	//Rage (Диапазон) в данном контексте понимается как контейнер.
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASE_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList<double> list = { 3.14, 2.71, 1.41, 1.62, 2.23 };
	for (double i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList<std::string> str_list = { "Hello", "World", "Forward", "List" };
	for (const std::string& str : str_list)
	{
		std::cout << str << tab;
	}
	std::cout << std::endl;
#endif // RANGE_BASED_FOR_LIST

}