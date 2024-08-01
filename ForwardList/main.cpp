#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
	int Data;		// �������� ��������
	Element* pNext; // ��������� �� ��������� �������
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
		Head = nullptr;// ����� ������ ����
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
			//1. ������� ����� �������:
			Element* New = new Element(Data);
			//2. �������� ����� ������� � ������:
			New->pNext = Head;
			//3. ��������� ������ �� ����� �������
			Head = New;

		}
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1. ������� �� ����� ������:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}

		//2. ������� ����� �������:
		Element* New = new Element(Data);

		//3. �������� ����� ������� � ������
		Temp->pNext = New;
	}


	//				Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		Element* Temp = Head;	// Temp ��� �������� 
								// �������� � ��� ��������� ��� ������ �������� ����� ���������� �������� ��������� ������ 
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; // ������� �� ��������� �������
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
	cout << "������� ���������� ���������: "; cin >> n;
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