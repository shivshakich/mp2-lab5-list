#pragma once

template <class T>
struct TNode {
	T value;
	TNode* pNext = nullptr;
};

template <class T>
class TSinglyLinkedList {
	TNode* pFirst;

	TNode* GetLastNode() const;							// выдать указатель на последнее звено
	TNode* GetNode(int index) const;					// выдать указатель на звено с номером i							
public:
	TSinglyLinkedList();								// констркутор по умолчанию
	TSinglyLinkedList(const T& value);					// конструктор преобразования типа
	TSinglyLinkedList(const TSinglyLinkedList& list);	// конструктор копирования
	~TSinglyLinkedList();								// деструктор

	int IsEmpty() const;								// проверка на пустоту
	void Del(int index);								// удалить index звено
	void Clear();										// удалить все звенья
	int Count() const;									// количество звеньев списка

	void Push_Front(const T& val);						// добавить звено в начало
	void Push_Back(const T& val);						// добавить звено в конец
	void Push(const T& val, int index);					// добавить звено на i-ую позицию (i = 0, ..., N, N - кол-во звеньев)

	T Pop_Front();										// удалить звено в начале, выдав его значение
	T Pop_Back();										// удалить звено в конце, выдав его значение
	T Pop(int index);									// удалить звено на i-ой позицию (i = 0, ..., N, N - кол-во звеньев), выдав его значение

	friend int Count(const TSinglyLinkedList& list);
	friend int Count(const TNode& node);

	friend std::ostream& operator<<(std::ostream& os, const TSinglyLinkedList& list);
};


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
	if (index < 0 || index > Count())
		throw "GetNode, wrong index";

	TNode<T>* result = pFirst;

	int i;
	for (i = 0; i < index; ++i)
		result = result->pNext;

	return result;
}

template <class T>
TSinglyLinkedList<T>::TSinglyLinkedList() : pFirst(nullptr);

template <class T>
TSinglyLinkedList<T>::TSinglyLinkedList(const T& value) {
	pFirst = new TNode<T>;
	pFirst->value = value;
}

template <class T>
TSinglyLinkedList<T>::TSinglyLinkedList(const TSinglyLinkedList& list) {
	TNode* tmp = list.pFirst;					// пробегает по списку list
	TNode* i;									// пробегает по списку this

	pFirst = nullptr;						// если 0 звеньев в list

	if (tmp != nullptr) {					// зайдём в тело условия, если >=1 звено в list
		pFirst = new TNode;
		pFirst->value = tmp->value;
		
		i = pFirst;
		tmp = tmp->pNext;
	}

	while (tmp != nullptr) {				// зайдёт в тело цикла, если в list >1 звена
		i = i->pNext = new TNode;
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

template <class T>
int TSinglyLinkedList<T>::IsEmpty() const { return pFirst == nullptr; }

template <class T>
void 

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
	int count = Count();

	if (index < 0 || index > count)
		throw "Push, wrong index";

	TNode<T>* pointer = new TNode<T>;
	pointer->value = val;

	if (index == 0) {
		pointer->pNext = pFirst;
		pFirst = pointer;
	}
	else if (index == count) 
		GetLastNode()->pNext = pointer;		// Т.О., МЫ ДВА РАЗА ПРОБЕГАЕМ ПУТЬ ОТ ПЕРВОГО ЗВЕНА ДО ПОСЛЕДНЕГО - ИСПРАВИТЬ!!!
	else {
		// ЗДЕСЬ СХОЖАЯ С ПРЕДЫДУЩИМ КОММЕНТАРИЕМ ПРОБЛЕМА

		TNode<T>* previousNode =  
	}
}

// написать Del, Clear, в Push(index) учесть случай, когда список пустой