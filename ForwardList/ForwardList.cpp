#include "ForwardList.h"

template<typename T> int ForwardList<T>::Element::count = 0;

template<typename T> ForwardList<T>::ForwardList()
{
	Head = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T> ForwardList<T>::ForwardList(const std::initializer_list<T>& il) :ForwardList()
{
	//cout << typeid(il.begin()).name() << endl;
	for (T const * it = il.begin(); it != il.end(); it++)
		push_back (*it);
}
template<typename T> ForwardList<T>::ForwardList(const ForwardList& other) :ForwardList()
{
	*this = other;
	cout << "LCopyConstructor: " << this << endl;
}
template<typename T> ForwardList<T>::ForwardList(ForwardList&& other)noexcept
{
	*this = std::move(other);
	cout << "LMoveConstructor: " << this << endl;
}
template<typename T> ForwardList<T>::~ForwardList()
{
	while (Head) pop_front();
	pop_front();
	cout << "LDestructor:\t" << this << endl;
}

//									Operators:
template<typename T> ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
{
	if (this == &other) return *this;

	while (Head)
		pop_front();

	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_front(Temp->Data);

	reverse();
	cout << "LCopyAssignment: " << this << endl;
	return *this;
}
template<typename T> ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>&& other)noexcept
{
	if (this == &other) return *this;

	while (Head)
		pop_front();

	this->Head = other.Head;
	this->size = other.size;

	other.size = 0;
	other.Head = nullptr;

	cout << "LMoveAssignment: " << this << endl;

	return *this;
}

//								Class Iterator
template<typename T>typename ForwardList<T>::Iterator::Iterator ForwardList<T>::Iterator::operator++()
{
	Iter = Iter->pNext;
	return *this;
}
template<typename T> T& ForwardList<T>::Iterator::operator*() const
{
	return Iter->Data;
}
template<typename T> bool ForwardList<T>::Iterator::operator!=(const Iterator& other) const
{
	return Iter != other.Iter;
}

//								Class ConstIterator
template<typename T>typename ForwardList<T>::ConstIterator::ConstIterator ForwardList<T>::ConstIterator::operator++()
{
	ConstIter = ConstIter->pNext;
	return *this;
}
template<typename T>const T& ForwardList<T>::ConstIterator::operator*() const
{
	return ConstIter->Data;
}
template<typename T> bool ForwardList<T>::ConstIterator::operator!=(const ConstIterator& other) const
{
	return ConstIter != other.ConstIter;
}


template<typename T>typename ForwardList<T>::Iterator ForwardList<T>::begin()
{
	return Iterator(Head);
}
template<typename T>typename ForwardList<T>::Iterator ForwardList<T>::end()
{
	return Iterator(nullptr);
}
template<typename T>typename ForwardList<T>::ConstIterator ForwardList<T>::begin() const
{
	return ConstIterator(Head);
}
template<typename T>typename ForwardList<T>::ConstIterator ForwardList<T>::end() const
{
	return ConstIterator(nullptr);
}

//									Adding elements:
template<typename T> void ForwardList<T>::push_front(T Data)
{
	Head = new Element(Data, Head);

	size++;
}
template<typename T> void ForwardList<T>::push_back(T Data)
{
	if (Head == nullptr) return push_front(Data);

	Element* Temp = Head;
	while (Temp->pNext)
		Temp = Temp->pNext;

	Temp->pNext = new Element(Data);
	size++;
}
template<typename T> void ForwardList<T>::pop_front()
{
	if (Head == nullptr) return;
	Element* Temp = Head;
	Head = Head->pNext;
	delete Temp;
	size--;
}
template<typename T> void ForwardList<T>::pop_back()
{
	if (Head == nullptr || Head->pNext == nullptr) return pop_front();

	Element* Temp = Head;
	while (Temp->pNext->pNext)
		Temp = Temp->pNext;

	delete Temp->pNext;
	Temp->pNext = nullptr;
	size--;
}
template<typename T> void ForwardList<T>::insert(T Data, int index)
{
	if (index > size) return; 
	if (index == 0) return push_front(Data);

	Element* Temp = Head;
	for (int i = 0; i < index - 1; i++)
		Temp = Temp->pNext;

	Temp->pNext = new Element(Data, Temp->pNext);
	size++;
}
template<typename T> void ForwardList<T>::erase(int index)
{
	if (index > size) return;
	if (index == 0) return pop_front();

	Element* Temp = Head;
	for (int i = 0; i < index - 1; i++)
		Temp = Temp->pNext;

	Element* errased = Temp->pNext;
	Temp->pNext = Temp->pNext->pNext;
	delete errased;

	size--;
}

//							Methods:
template<typename T> void ForwardList<T>::reverse()
{
	ForwardList<T> buffer;

	while (Head)
	{
		buffer.push_back(Head->Data);
		pop_back();
	}

	this->Head = buffer.Head;
	this->size = buffer.size;
	buffer.Head = nullptr;
}
template<typename T> void ForwardList<T>::print()const
{
	cout << "Head:\t" << Head << endl;

	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << "Общее количество элементов списка: " << Element<T>::count << endl;
}


template<typename T> std::ostream& operator<<(std::ostream& os, const typename ForwardList<T>::Element& el)
{
	return os << el;
}