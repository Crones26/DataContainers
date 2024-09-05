#include"List2.cpp"

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
