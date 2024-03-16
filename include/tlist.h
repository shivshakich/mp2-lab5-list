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
	TList<T>& operator=(TList<T>& _list);

	// втсавка или удаление звена

	void InsFirst(const T& _val);
	void InsLast(const T& _val);
	void InsCurr(const T& _val);
	void DelFirst();
	void DelCurr();

	// методы доступа к pCurr; итераторы

	TNode<T>* GetCurr() const;							// доступ к pCurr значению
	void SetPos(const int _pos);						// установить значение pCurr в зависимости от позиция _pos
	void Reset();										// установить pCurr на начало списка
	void GoNext();										// перейти к следующему звену
	bool IsEnd() const noexcept;

	// другие методы
					
	void DelList();
	int GetLength() const;

	// comparison operators

	bool operator==(const TList<T>& _list) const;
	bool operator!=(const TList<T>& _list) const;
};

// CONSTRUCTORS & DESTRUCTOR

template <class T>										/* default constructor */
TList<T>::TList() : pStop(nullptr), pFirst(pStop), pLast(pStop), length(0), pCurr(pStop), pPrev(pStop), pos(-1) {}

template <class T>										/* type conversion constructor */
TList<T>::TList(const T& _val) : pStop(nullptr), pCurr(pStop), pPrev(pStop), pos(-1) {
	pFirst = new TNode<T>{ _val, pStop };
	pLast = pFirst;
	length = 1;
}

template<class T>										/* copy constructor */
TList<T>::TList(const TList<T>& _list) {
	this->pStop		= _list.pStop;
	this->length	= _list.length;
	this->pos		= -1;
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
}

template <class T>										/* destructor */
TList<T>::~TList() { DelList(); }

// ITERATORS : getcurr, setpos, reset, gonext, isend

template <class T>
TNode<T>* TList<T>::GetCurr() const { return pCurr; }

template <class T>
void TList<T>::SetPos(const int _pos) {
	if (_pos < 0 || this->length < _pos)
		throw "TList<T>::SetPos, invalid input value";

	if (pos == -1 || _pos < pos)
		Reset();

	for (; pos < _pos; GoNext())
		;
}

template <class T>
void TList<T>::Reset() {
	pPrev = pStop;
	pCurr = pFirst;
	pos = 0;
}

template <class T>
void TList<T>::GoNext() {
	if (IsEnd())
		throw "GoNext, pCurr points to pStop";

	pPrev = pCurr;
	pCurr = pCurr->pNext;
	++pos;
}

template <class T>
bool TList<T>::IsEnd() const noexcept {
	return pCurr == pStop;
}

// OPERATOR=

template <class T>
TList<T>& TList<T>::operator=(const T& _val) {
	this->DelList();
	this->InsLast(_val);
}

template <class T> 
TList<T>& TList<T>::operator=(TList<T>& in) {
	const int LEN = in.length;

	int count = LEN;

	if (length < LEN) {
		count = length;

		for (in.SetPos(length); !in.IsEnd(); in.GoNext())
			this->InsLast(in.pCurr->value);
	}

	while (LEN < length)
		this->DelFirst();

	// теперь length == LEN, причём нужно поменять значения звеньев с 0 по count-1

	this->Reset();
	in.Reset();
	for (int i = 0; i < count; ++i) {
		this->pCurr->value = in.pCurr->value;
		this->GoNext();
		in.GoNext();
	}

	this->pStop = in.pStop;

	return *this;
}