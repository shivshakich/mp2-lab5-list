#pragma once

template <class T>
struct TNode {
	T value;
	TNode<T>* pNext;
	TNode() { pNext = nullptr; }
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
	TList(TList<T>& _list);
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

	const TNode<T>* GetCurr() const;							// доступ к pCurr значению
	void SetPos(const int _pos);								// установить значение pCurr в зависимости от позиция _pos
	void Reset();										// установить pCurr на начало списка
	void GoNext();										// перейти к следующему звену
	bool IsEnd() const noexcept;

	// другие методы
					
	void DelList();
	int GetLength() const noexcept;

	// comparison operators

	bool operator==(TList<T>& _list);
	bool operator!=(TList<T>& _list);
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
TList<T>::TList(TList<T>& _list) {
	this->pStop		= _list.pStop;
	this->length	= _list.length;
	pCurr = pPrev = pStop;
	pos = -1;

	if (_list.pFirst == pStop) {
		pFirst = pLast = pStop;
		return;
	}

	_list.Reset();
	pLast = pFirst = new TNode<T>;
	pFirst->value = _list.pCurr->value;
	_list.GoNext();

	for (; !_list.IsEnd(); _list.GoNext()) {
		pLast->pNext = new TNode<T>;
		pLast = pLast->pNext;
		pLast->value = _list.pCurr->value;
	}
}

template <class T>										/* destructor */
TList<T>::~TList() { DelList(); }

// ITERATORS : getcurr, setpos, reset, gonext, isend

template <class T>
const TNode<T>* TList<T>::GetCurr() const { return pCurr; }

template <class T>
void TList<T>::SetPos(const int _pos) {
	if (_pos < -1 || this->length <= _pos)
		throw "TList<T>::SetPos, invalid input value";

	if (_pos == -1) {
		pCurr = pPrev = pStop;
		pos = -1;
	}
	else
		for (Reset(); pos != _pos; GoNext())
			;
}

template <class T>
void TList<T>::Reset() {
	pPrev = pStop;
	pCurr = pFirst;
	pos = (pFirst != pStop) - 1;
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

	return *this;
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

	return *this;
}

// OTHER METHODS: dellist, getlength

template <class T>
void TList<T>::DelList() {
	pCurr = pFirst;

	while (pCurr != pStop) {
		pPrev = pCurr;
		pCurr = pCurr->pNext;

		delete pPrev;
	}

	pFirst = pLast = pPrev = pStop;
	length = 0;
	pos = -1;
}

template <class T>
int TList<T>::GetLength() const noexcept { return length; }

// COMPARISON METHODS

template <class T>
bool TList<T>::operator==(TList<T>& l) {
	if (this == &l)
		return true;

	if (length != l.length)
		return false;

	bool res = true;

	// если lenght == l.length == 0, то вернётся true

	for (Reset(), l.Reset(); !IsEnd() && res; GoNext(), l.GoNext()) 
		res = pCurr->value == l.pCurr->value;

	return res;
}

template <class T>
bool TList<T>::operator!=(TList<T>& l) { return this->operator==(l); }

// INSERT AND DELETE METHODS

template <class T>
void TList<T>::InsFirst(const T& val) {
	TNode<T>* addNode = new TNode<T>;
	addNode->value = val;
	addNode->pNext = pFirst;

	pFirst = addNode;
	++length;

	if (pos >= 0) {
		if (pPrev == pStop) pPrev = pFirst;
		++pos;
	}
}

template <class T>
void TList<T>::InsLast(const T& val) {
	TNode<T>* addNode = new TNode<T>;
	addNode->value = val;
	addNode->pNext = pStop;

	if (length == 0)
		pFirst = pLast = addNode;
	else
		pLast = pLast->pNext = addNode;

	++length;
}

template <class T>
void TList<T>::InsCurr(const T& val) {
	if (pCurr == pStop)
		throw "TList<T> InsCurr, invalid pCurr";

	if (pCurr == pFirst) 
		this->InsFirst(val);
	else {
		TNode<T>* pNew = new TNode<T>();
		pNew->value = val;
		pNew->pNext = pCurr;

		pPrev->pNext = pNew;
		pPrev = pNew;
		++pos; ++length;
	}
}

template <class T>
void TList<T>::DelFirst() {
	if (pFirst == pStop)
		throw "TList<T> DelFirst, pFirst == pStop";

	TNode<T>* delNode = pFirst;
	pFirst = pFirst->pNext;

	if (length == 1)
		pLast = pStop;

	if (pos >= 0) {
		if (pPrev == delNode) pPrev = pStop;
		if (pCurr == delNode) pCurr = pStop;
		--pos;
	}

	delete delNode;
	--length;
}

template <class T>
void TList<T>::DelCurr() {
	if (pCurr == pStop)
		throw "TList<T> DelCurr, pCurr == pStop";

	if (pCurr == pFirst) {
		DelFirst();
		return;
	}

	TNode<T>* delNode = pCurr;
	pPrev->pNext = pCurr = pCurr->pNext;

	delete delNode;
	--length;
}