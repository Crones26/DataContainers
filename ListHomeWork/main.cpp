#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------------------\n"

class Element
{
    int Data;           //значение элемента
    Element* pNext;     //указатель на следующий элемент
    Element* pPrev;     //указатель на предыдущий элемент
    static int count;

public:
    Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev)
    {
        count++;
    }

    ~Element()
    {
        count--;
    }

    friend class DoublyLinkedList;
    friend class Iterator;
};

int Element::count = 0;

class Iterator
{
    Element* Temp;

public:
    Iterator(Element* Temp = nullptr) : Temp(Temp) {}
    ~Iterator() {}

    Iterator& operator++()   // Префиксный инкремент
    {
        Temp = Temp->pNext;
        return *this;
    }

    Iterator& operator--()   // Префиксный декремент
    {
        Temp = Temp->pPrev;
        return *this;
    }

    bool operator!=(const Iterator& other) const
    {
        return this->Temp != other.Temp;
    }

    int operator*()
    {
        return Temp->Data;
    }
};

class DoublyLinkedList
{
    Element* Head;
    Element* Tail;
    unsigned int size;

public:
    Iterator begin() const
    {
        return Iterator(Head);
    }

    Iterator end() const
    {
        return Iterator(nullptr);
    }

    Iterator rbegin() const
    {
        return Iterator(Tail);
    }

    Iterator rend() const
    {
        return Iterator(nullptr);
    }

    //              Constrictor
    DoublyLinkedList() : Head(nullptr), Tail(nullptr), size(0) {}

    DoublyLinkedList(const std::initializer_list<int>& il) : DoublyLinkedList()
    {
        for (int const* it = il.begin(); it != il.end(); it++)
        {
            push_back(*it);
        }
    }

    DoublyLinkedList(const DoublyLinkedList& other) : DoublyLinkedList()
    {
        *this = other;
    }

    DoublyLinkedList(DoublyLinkedList&& other) noexcept : Head(other.Head), Tail(other.Tail), size(other.size)
    {
        other.Head = nullptr;
        other.Tail = nullptr;
        other.size = 0;
    }

    ~DoublyLinkedList()
    {
        while (Head) pop_front();
    }

    //              Операторы присваивания
    DoublyLinkedList& operator=(const DoublyLinkedList& other)
    {
        if (this == &other) return *this;
        while (Head) pop_front();
        for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
            push_back(Temp->Data);
        return *this;
    }

    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept
    {
        if (this != &other)
        {
            while (Head) pop_front();  
            Head = other.Head;
            Tail = other.Tail;
            size = other.size;
            other.Head = nullptr;
            other.Tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    //              Добавление элементов
    void push_front(int Data)
    {
        Element* New = new Element(Data, Head);
        if (Head) Head->pPrev = New;
        Head = New;
        if (!Tail) Tail = Head;
        size++;
    }

    void push_back(int Data)
    {
        Element* New = new Element(Data, nullptr, Tail);
        if (Tail) Tail->pNext = New;
        Tail = New;
        if (!Head) Head = Tail;
        size++;
    }

    void insert(int Data, int Index)
    {
        if (Index < 0 || Index > size) return;
        if (Index == 0) return push_front(Data);
        if (Index == size) return push_back(Data);
        Element* Temp = (Index < size / 2) ? Head : Tail;
        if (Index < size / 2)
        {
            for (int i = 0; i < Index; i++) Temp = Temp->pNext;
        }
        else
        {
            for (int i = size - 1; i > Index; i--) Temp = Temp->pPrev;
        }
        Element* New = new Element(Data, Temp, Temp->pPrev);
        Temp->pPrev->pNext = New;
        Temp->pPrev = New;
        size++;
    }

    //              Удаление элементов
    void pop_front()
    {
        if (!Head) return;
        //if (Head == nullptr && Tail == nullptr)return;
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
        if (!Tail) return;
        //if (Head == nullptr && Tail == nullptr)return;
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
        if (Index < 0 || Index >= size) return;
        if (Index == 0) return pop_front();
        if (Index == size - 1) return pop_back();

        Element* Temp = (Index < size / 2) ? Head : Tail;
        if (Index < size / 2)
        {
            for (int i = 0; i < Index; i++) Temp = Temp->pNext;
        }
        else
        {
            for (int i = size - 1; i > Index; i--) Temp = Temp->pPrev;
        }
        Temp->pPrev->pNext = Temp->pNext;
        Temp->pNext->pPrev = Temp->pPrev;
        delete Temp;
        size--;
    }

    //              Metods
    void reverse()
    {
        Element* Temp = Head;
        Head = Tail;
        Tail = Temp;

        while (Temp)
        {
            std::swap(Temp->pNext, Temp->pPrev);
            Temp = Temp->pPrev;
        }
    }

    void print() const
    {
        cout << "Head:\t" << Head << endl;
        for (Element* Temp = Head; Temp; Temp = Temp->pNext)
            cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
        cout << "Tail:\t" << Tail << endl;
        cout << "Количество элементов списка: " << size << endl;
    }

    void reverse_print() const
    {
        cout << "Tail:\t" << Tail << endl;
        for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
            cout << Temp << tab << Temp->Data << tab << Temp->pPrev << endl;
        cout << "Head:\t" << Head << endl;
        cout << "Количество элементов списка: " << size << endl;
    }
};

#define BASE_CHECK
#define ITERATORS_CHECK

void main()
{
    setlocale(LC_ALL, "");

    // Инициализация генератора случайных чисел
    //srand(static_cast<unsigned>(time(nullptr))); // нашел на просторах не объятного

#ifdef BASE_CHECK
    int n;
    cout << "Введите размер списка: "; cin >> n;
    DoublyLinkedList list;

    // Заполнение списка случайными числами
    for (int i = 0; i < n; i++)
    {
        list.push_front(rand() % 100);
    }

    list.print();
    cout << delimiter << endl;
    list.push_front(321);
    list.print();
    cout << delimiter << endl;
    list.push_back(123);
    list.print();
    cout << delimiter << endl;
    list.pop_front();
    list.pop_back();
    list.print();
    list.reverse_print();
    cout << delimiter << endl;

    int index;
    int value;
    // Добавление элемента
    cout << "Введите индекс добавляемого элемента: "; cin >> index;
    cout << "Введите значение добавляемого элемента: "; cin >> value;
    list.insert(value, index);
    list.print();
    // Удаление элемента
    cout << "Введите индекс удаляемого элемента: "; cin >> index;
    list.erase(index);
    list.print();
    list.reverse_print();
#endif // BASE_CHECK



}
