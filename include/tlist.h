#pragma once

template <class T>
struct TNode {
	T value;
	TNode<T>* pNext = nullptr;
};

template <class T>
class TList {
protected:
	TNode<T> * pStop, * pFirst, * pLast;
	int length;

	TNode<T> * pCurr, * pPrev;
	int pos;									// нумерация начинается с 0
public:

	// конструкторы, деструктор и операторы копирования

	TList();
	TList(const T& _val);
	TList(const TList<T>& _list);
	~TList();
	TList<T>& operator=(const T& _val);
	TList<T>& operator=(const TList<T>& _list);

	// втсавка или удаление звена

	void InsFirst(const T& _val);
	void InsLast(const T& _val);
	void InsCurr(const T& _val);
	void DelFirst();
	void DelCurr();

	// методы доступа к pCurr

	TNode<T>* GetCurr() const;							// доступ к pCurr значению
	void SetPos(int _pos);								// установить значение pCurr в зависимости от позиция _pos
	void Reset();										// установить pCurr на начало списка
	void GoNext();										// перейти к следующему звену
	bool IsEnd() const noexcept;

	// другие методы
					
	void DelList();

	// comparison operators

	bool operator==(const TList<T>& _list) const;
	bool operator!=(const TList<T>& _list) const;
};

// CONSTRUCTORS & DESTRUCTOR

template <class T>
TList<T>::TList() : pStop(nullptr), pFirst(pStop), pLast(pStop), length(0), pCurr(pStop), pPrev(pStop), pos(-1) {}

template <class T>
TList<T>::TList(const T& _val) : pStop(nullptr), pCurr(pStop), pPrev(pStop), pos(-1) {
	pFirst = new TNode<T>{ _val, pStop };
	pLast = pFirst;
	length = 1;
}

template<class T> 
TList<T>::TList(const TList<T>& _list) {
	this->pStop		= _list.pStop;
	this->length	= _list.length;
	this->pos		= _list.pos;
	pPrev = pCurr = pStop;

	if (_list.pFirst == pStop) {
		pFirst = pLast = pStop;
		return;
	}

	pLast = pFirst = new TNode<T>;
	pFirst->value = _list.pFirst->value;

	TNode<T>* currNode = _list.pFirst->pNext;

	while (currNode != pStop) {				// создаём список
		TNode<T>* tmpNode = new TNode<T>;
		tmpNode->value = currNode->value;
		pLast->pNext = tmpNode;
		pLast = tmpNode;
	}
	pLast->pNext = pStop;

	// находим значения для pCurr, pPrev

	// для случая pos == -1 уже найдены ранее pCurr, pPrev
	
	if (pos == 0) 			// для случая pos == 0
		pCurr = pFirst;

	// для случая pos >= 1 находим pPrev, по которому найдём pCurr = pPrev->pNext
	else if (pos > 0) {
		pPrev = pFirst;
		int posPrev = pos - 1;
		for (int i = 0; i < posPrev; ++i) {
			pPrev = pPrev->pNext;
		}
		pCurr = pPrev->pNext;
	}
}

template <class T>
TList<T>::~TList() { DelList(); }

// OPERATOR=

template <class T>
TList<T>& TList<T>::operator=(const T& _val) {
	this->DelList();
	this->InsLast(_val);
}