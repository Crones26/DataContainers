#include <iostream>
using std::cin;
using std::cout;
using std::endl;

using namespace std;

#define tab "\t"
#define delimiter "\n------------------------------------------------------------\n"

template <typename T>
class Element
{
    T Data;        // значение элемента
    Element* pNext; // указатель на следующий элемент
    static int count;
public:
    Element(T Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
    {
        count++;
#ifdef DEBUG
        cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
    ~Element()
    {
        count--;
#ifdef DEBUG
        cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
    }

    friend class ForwardList<T>;
    friend class Iterator<T>;
};

template <typename T>
int Element<T>::count = 0;

template <typename T>
class Iterator
{
    Element<T>* Temp;
public:
    Iterator(Element<T>* Temp = nullptr) :Temp(Temp)
    {
        cout << "ItConstructor:\t" << this << endl;
    }
    ~Iterator()
    {
        cout << endl << "ItDestructor:\t" << this << endl;
    }

    Iterator& operator++()
    {
        Temp = Temp->pNext;
        return *this;
    }

    bool operator!=(const Iterator& other)const
    {
        return this->Temp != other.Temp;
    }

    T operator*()
    {
        return Temp->Data;
    }
};

template <typename T>
class ForwardList
{
    Element<T>* Head;
    unsigned int size;
public:
    Iterator<T> begin() const
    {
        return Iterator<T>(Head);
    }

    Iterator<T> end() const
    {
        return Iterator<T>(nullptr);
    }

    // Constructors
    ForwardList()
    {
        Head = nullptr; // Когда список пуст, его голова указывает на 0
        size = 0;
        cout << "LConstructor:\t" << this << endl;
    }

    ForwardList(const std::initializer_list<T>& il) : ForwardList()
    {
        // initializer_list - это контейнер.
        // Контейнер - это объект, который организует хранение других объектов в памяти.
        // У любого контейнера в обязательном порядке есть как минимум два метода:
        // begin() - возвразает итератор на начало контейнера.
        // end()   - возвращает итератор на конец контейнера.
        for (const T& val : il)
        {
            push_back(val);
        }
        /*for (T val : il)
        {
            push_back(val);
        }*/
    }

    // Конструктор копирования
    ForwardList(const ForwardList& other) :ForwardList()
    {
        /*for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
            push_back(Temp->Data);*/
        *this = other;    // здесь просто вызываем CopyAssignment
        cout << "LCopyConstructor:\t" << this << endl;
    }

    // Конструктор перемещения
    ForwardList(ForwardList&& other) noexcept : Head(other.Head), size(other.size)
    {
        other.Head = nullptr;
        other.size = 0;
        cout << "LMoveConstructor:\t" << this << endl;
    }

    ~ForwardList()
    {
        while (Head) pop_front();
        pop_back();
        cout << "LDestructor:\t" << this << endl;
    }

    // Operators
    // Оператор присваивания с копированием
    ForwardList& operator=(const ForwardList& other)
    {
        if (this == &other) return *this;
        if (other.size == 0) return *this;
        while (Head) pop_front();
        for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
            push_front(Temp->Data);
        revers();
        cout << "LCopyAssignment:\t" << this << endl;
        return *this;
    }

    // Оператор присваивания с перемещением
    ForwardList& operator=(ForwardList&& other) noexcept
    {
        if (this == &other) return *this;
        while (Head) pop_front();
        Head = other.Head;
        size = other.size;
        other.Head = nullptr;
        other.size = 0;
        cout << "LMoveAssignment:\t" << this << endl;
        return *this;
    }

    // Adding elements
    void push_front(T Data)
    {
        //// 1. Создаем новый элемент:
        //Element<T>* New = new Element<T>(Data);
        //// 2. Включаем новый элемент в список:
        //New->pNext = Head;
        //// 3. Переводим голову на новый элемент
        //Head = New;
        Head = new Element<T>(Data, Head);
        size++;
    }

    void push_back(T Data)
    {
        // Проверка
        if (Head == nullptr) return push_front(Data);
        // 1. Доходим до конца списка:
        Element<T>* Temp = Head;
        while (Temp->pNext)
        {
            Temp = Temp->pNext;
        }
        //// 2. Создаем новый элемент:
        //Element<T>* New = new Element<T>(Data);
        //// 3. Включаем новый элемент в список
        //Temp->pNext = New;
        Temp->pNext = new Element<T>(Data);
        size++;
    }

    void insert(T Data, int Index)
    {
        // Проверка
        if (Index > size) return;
        if (Index == 0) return push_front(Data);
        // 1) Доходим до нужного элемента:
        Element<T>* Temp = Head;
        for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
        //// 2) Создаем новый элемент:
        //Element<T>* New = new Element<T>(Data);
        //// 3) Включаем элемент в список:
        //New->pNext = Temp->pNext;
        //Temp->pNext = New;
        Temp->pNext = new Element<T>(Data, Temp->pNext);
        size++;
    }

    // Removing elements
    void pop_front()
    {
        // Проверка
        if (Head == nullptr) return;
        Element<T>* Temp = Head;    // 1) Запоминаем адрес удаляемого элемента
        Head = Head->pNext;        // 2) Смещаем Голову на следующий элемент (исключаем элемент из списка)
        delete Temp;            // 3) Удаляем элемент из памяти
        size--;
    }

    void pop_back()
    {
        // Проверка
        if (Head == nullptr || Head->pNext == nullptr) return pop_front();
        // 1) Доходим до предпоследнего элемента списка:
        Element<T>* Temp = Head;
        while (Temp->pNext->pNext) Temp = Temp->pNext;
        // 2) Удаляем последний элемент из памяти:
        delete Temp->pNext;
        // 3) Зануляем указатель на последний элемент:
        Temp->pNext = nullptr;
        size--;
    }

    void erase(int Index)
    {
        // Проверка
        if (Index >= size) return;
        if (Index == 0) return pop_front();
        // 1) Доходим до элемента перед удаляемым:
        Element<T>* Temp = Head;
        for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
        // 2) Запоминаем адрес удаляемого элемента:
        Element<T>* erased = Temp->pNext;
        // 3) Исключаем удаляемый элемент из списка:
        Temp->pNext = Temp->pNext->pNext;
        // 4) Удаляем элемент из памяти:
        delete erased;
        size--;
    }

    // Methods
    void revers()
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

    void print() const
    {
        cout << "Head:\t" << Head << endl;
        // Element<T>* Temp = Head;    // Temp это итератор
        //                         // Итератор – это указатель, при помощи которого можно перебирать элементы структуры данных
        // while (Temp)
        // {
        //     cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
        //     Temp = Temp->pNext; // Переход на следующий элемент
        // }
        for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
            cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
        cout << "Количество элементов списка: " << size << endl;
        cout << "Общее количество элементов списка: " << Element<T>::count << endl;
        // cout << "Общее количество элементов списка: " << Head->count << endl;
    }

};

//#define BASE_CHECK
//#define COUNT_CHECK
//#define PERFORMANCE_CHEK
//#define RANGE_BASE_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
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
	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

    ForwardList<double> list = { 3.14, 2.71, 1.41, 1.62, 2.23 };
    for (double i : list)
    {
        cout << i << tab;
    }
    cout << endl;

    ForwardList<std::string> str_list = { "Hello", "World", "Forward", "List" };
    for (const std::string& str : str_list)
    {
        cout << str << tab;
    }

}