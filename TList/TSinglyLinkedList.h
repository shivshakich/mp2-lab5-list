#pragma once

#include <iostream>

template <class T>
struct TNode {
	T value;
	TNode* pNext = nullptr;
};

template <class T>
class TSinglyLinkedList {
	TNode<T>* pFirst;

	TNode<T>* GetLastNode() const;							// ������ ��������� �� ��������� �����
	TNode<T>* GetNode(int index) const;					// ������ ��������� �� ����� � ������� i							
public:
	TSinglyLinkedList();								// ����������� �� ���������
	TSinglyLinkedList(const T& value);					// ����������� �������������� ����
	TSinglyLinkedList(const TSinglyLinkedList& list);	// ����������� �����������
	~TSinglyLinkedList();								// ����������

	int IsEmpty() const;								// �������� �� �������
	void Del(int index);								// ������� index �����
	void Clear();										// ������� ��� ������
	int Count() const;									// ���������� ������� ������

	void Push_Front(const T& val);						// �������� ����� � ������
	void Push_Back(const T& val);						// �������� ����� � �����
	void Push(const T& val, int index);					// �������� ����� �� i-�� ������� (i = 0, ..., N, N - ���-�� �������)

	T Pop_Front();										// ������� ����� � ������, ����� ��� ��������
	T Pop_Back();										// ������� ����� � �����, ����� ��� ��������
	T Pop(int index);									// ������� ����� �� i-�� ������� (i = 0, ..., N, N - ���-�� �������), ����� ��� ��������

	friend int Count(const TNode<T>& node);

	friend std::ostream& operator<<(std::ostream& os, const TSinglyLinkedList& list);
};

// ������ �� private ������

template <class T>
TNode<T>* TSinglyLinkedList<T>::GetLastNode() const {
	TNode* result = pFirst;

	if (result != nullptr)
		while (result->pNext != nullptr)
			result = result->pNext;

	return result;
}

template <class T>
TNode<T>* TSinglyLinkedList<T>::GetNode(int index) const {
	if (index < 0)
		throw "GetNode, wrong index < 0";

	TNode<T>* result = pFirst;

	for (int i = 0; i < index; ++i) {
		if (result == nullptr) 
			throw "GetNode, wrong index >= count of nodes";

		result = result->pNext;
	}

	if (result == nullptr)	// �.�. ��������� �� lastNode->pNext �����, �������� �� ����������
		throw "GetNode, wrong index == count of nodes";

	// result == nullptr	<=>		pFirst == nullptr, index == 0 
	return result;
}

// ������������ � ����������

template <class T>
TSinglyLinkedList<T>::TSinglyLinkedList() : pFirst(nullptr) {}

template <class T>
TSinglyLinkedList<T>::TSinglyLinkedList(const T& value) {
	pFirst = new TNode<T>;
	pFirst->value = value;
}

template <class T>
TSinglyLinkedList<T>::TSinglyLinkedList(const TSinglyLinkedList& list) {
	TNode* tmp = list.pFirst;					// ��������� �� ������ list
	TNode* i;									// ��������� �� ������ this

	pFirst = nullptr;						// ���� 0 ������� � list

	if (tmp != nullptr) {					// ����� � ���� �������, ���� >=1 ����� � list
		pFirst = new TNode<T>;
		pFirst->value = tmp->value;
		
		i = pFirst;
		tmp = tmp->pNext;
	}

	while (tmp != nullptr) {				// ����� � ���� �����, ���� � list >1 �����
		i = i->pNext = new TNode<T>;
		i->value = tmp->value;
	}
}

template <class T>
TSinglyLinkedList<T>::~TSinglyLinkedList() {
	TNode<T>* i = pFirst;
	TNode<T>* j;

	while (i != nullptr) {
		j = i->pNext;
		delete i;
		i = j;
	}
}

// ��������� ������

template <class T>
int TSinglyLinkedList<T>::IsEmpty() const { return pFirst == nullptr; }

template <class T>
void TSinglyLinkedList<T>::Del(int index) {
	if (pFirst == nullptr)
		throw "Del, pFirst == nullptr";
	// pFirst != nullptr, ������ ������ �������� >= 1 �����

	TNode<T>* tmp;

	if (index == 0) {
		tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
	else {	// index >= 1
		tmp = GetNode(index - 1);				// �� �������� ����������, ������ ���������� ����� � ������� index-1
		TNode<T> delNode = tmp->pNext;

		if (delNode == nullptr)
			throw "Del, delNode == nullptr";
		else {
			tmp->pNext = delNode->pNext;
			delete delNode;
		}
	}
}

template <class T>
void TSinglyLinkedList<T>::Clear() {
	TNode<T> tmp1 = pFirst;
	TNode<T> tmp2;

	while (tmp1 != nullptr) {
		tmp2 = tmp1->pNext;
		delete tmp1;
		tmp1 = tmp2;
	}
}

template <class T> 
int TSinglyLinkedList<T>::Count() const {
	int result = 0;
	TNode<T>* tmp = pFirst;

	while (tmp != nullptr) {
		++result;
		tmp = tmp->pNext;
	}

	return result;
}

// push-������

template <class T>
void TSinglyLinkedList<T>::Push_Front(const T& val) {
	TNode<T>* pointer = new TNode<T>;
	pointer->value = val;
	pointer->pNext = pFirst;
	pFirst = pointer;
}

template <class T>
void TSinglyLinkedList<T>::Push_Back(const T& val) {
	TNode<T>* pointer = GetLastNode()->pNext = new TNode<T>;
	pointer->value = val;
}

template <class T>
void TSinglyLinkedList<T>::Push(const T& val, int index) {
	// ���� �������, ��� � ������ COUNT �������, �� index �.�. �����, ��� 0 <= index <= COUNT

	if (index < 0)
		throw "Push, index < 0";

	TNode<T>* insNode;

	if (index == 0) {
		insNode = new TNode<T>;
		insNode->value = val;
		insNode->pNext = pFirst;
		pFirst = insNode;
	}
	else {
		TNode<T>* previousNode = GetNode(index - 1);	// ���� �� �������� ����������, �� ����� � �������� index-1 ����������
		TNode<T>* currentNode = previousNode->pNext;

		insNode = new TNode<T>;
		insNode->value = val;

		previousNode->pNext = insNode;
		insNode->pNext = currentNode;
	}
}

// pop-������

template <class T>
T TSinglyLinkedList<T>::Pop_Front() {
	if (IsEmpty())
		throw "Pop_Front, IsEmpty()";

	T res = pFirst->value;

	TNode<T>* tmp = pFirst;
	pFirst = pFirst->pNext;
	delete tmp;

	return res;
}

template <class T>
T TSinglyLinkedList<T>::Pop_Back() {
	if (IsEmpty())
		throw "Pop_Back, IsEmpty()";

	TNode<T>* tmp = GetNode(Count() - 1);	// ����� ��������, ��� tmp != nullptr

	T res = tmp->pNext->value;
	delete tmp->pNext;
	tmp->pNext = nullptr;

	return res;
}

template <class T>
T TSinglyLinkedList<T>::Pop(int index) {
	if (IsEmpty())
		throw "Pop, IsEmpty()";
	else if (index < 0)
		throw "Pop, index < 0";

	if (index == 0)
		return Pop_Front();

	TNode<T>* previousNode = GetNode(index - 1);
	TNode<T>* currentNode = previousNode->pNext;

	if (currentNode == nullptr)
		throw "Pop, node with index equals \"index\" does not exist";

	T res = currentNode->value;
	previousNode->pNext = currentNode->pNext;
	delete currentNode;

	return res;
}

// ������������� ������� 

template <class T>
int Count(const TNode<T>& node) {
	int res = 0;
	TNode<T>* currentNode = node;

	while (currentNode != nullptr) {
		currentNode = currentNode->pNext;
		++res;
	}

	return res;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const TSinglyLinkedList<T> list) {
	TNode<T>* currentNode = list.pFirst;

	while (currentNode != nullptr) {
		os << currentNode->value;
		currentNode = currentNode->pNext;
	}

	return os;
}