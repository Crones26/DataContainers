#include "ForwardList.h"
#include "forwardList.cpp"

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
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
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
	/*ForwardList<double> list;
	list.push_back(3.14);
	list.push_back(2.71);
	list.push_back(1.41);
	list.push_back(1.62);
	list.push_back(2.23);

	for (double i : list)
	{
		cout << i << tab;
	}
	cout << endl;*/

	ForwardList<double> list = { 3.14, 2.71, 1.41, 1.62, 2.23 };
	for (double i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	/*ForwardList<std::string> str_list;
	str_list.push_back("Hello");
	str_list.push_back("World");
	str_list.push_back("Forward");
	str_list.push_back("List");

	for (const std::string& str : str_list)
	{
		std::cout << str << tab;
	}
	std::cout << std::endl;*/

	ForwardList<std::string> str_list = { "Hello", "World", "Forward", "List" };
	for (const std::string& str : str_list)
	{
		std::cout << str << tab;
	}
	std::cout << std::endl;
#endif // RANGE_BASED_FOR_LIST

}