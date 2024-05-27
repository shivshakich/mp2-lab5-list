#pragma once

#include "tlist.h"

// Кольцевой список с головой, наследуемый от TList<T>
template <class T> class THeadRing : public TList<T> {
protected:
	TNode<T>* pHead;

	using TList<T>::pStop;
	using TList<T>::pFirst;
	using TList<T>::pLast;
	using TList<T>::pCurr;
	using TList<T>::pPrev;
	using TList<T>::length;
	using TList<T>::pos;
public:
	THeadRing();
	THeadRing(const T& val);
	THeadRing(TList<T>& l);
	THeadRing(THeadRing<T>& hl);
	~THeadRing();

	THeadRing<T>& operator=(const T& _val);
	THeadRing<T>& operator=(TList<T>& _list);
	THeadRing<T>& operator=(THeadRing<T>& _list);

	bool operator==(THeadRing<T>& _list);
	bool operator!=(THeadRing<T>& _list);

	void InsFirst(const T& val);
	using TList<T>::InsLast;
	using TList<T>::InsCurr;
	void DelFirst();
	using TList<T>::DelCurr;
	using TList<T>::GetCurr;
	using TList<T>::SetPos;
	using TList<T>::Reset;
	using TList<T>::GoNext;
	using TList<T>::IsEnd;
	using TList<T>::DelList;
	using TList<T>::GetLength;
};

// CONSTRUCTORS & DESTRUCTOR

template <class T>
THeadRing<T>::THeadRing() {
	pHead = new TNode<T>;
	pHead->pNext = pHead;
	pStop = pFirst = pLast = pCurr = pPrev = pHead;
	length = 0;
	pos = -1;
}

template <class T>
THeadRing<T>::THeadRing(const T& val) {
	pHead = new TNode<T>;
	pHead->pNext = pFirst = pLast = new TNode<T>();
	pLast->value = val;
	pLast->pNext = pHead;

	pCurr = pPrev = pStop = pHead;
	length = 1;
	pos = -1;
}

template <class T>
THeadRing<T>::THeadRing(TList<T>& l)
{
	this->TList<T>::TList(l);
	pHead = new TNode<T>;
	if (length == 0) pFirst = pLast = pHead;

	pHead->pNext = pFirst;
	pLast->pNext = pCurr = pPrev = pStop = pHead;
}

template <class T> 
THeadRing<T>::THeadRing(THeadRing<T>& hl) 
{
	pHead = new TNode<T>;
	pStop = pHead;
	length = hl.length;
	pFirst = pLast = pCurr = pPrev = pStop;
	pos = -1;

	for (hl.Reset(); !hl.IsEnd(); hl.GoNext()) {
		pLast->pNext = new TNode<T>;
		pLast = pLast->pNext;
		pLast->value = hl.pCurr->value;
	}
	
	if (length > 0)
		pFirst = pHead->pNext;

	pLast->pNext = pHead;
}

template <class T> 
THeadRing<T>::~THeadRing()
{
	TList<T>::DelList();
	delete pHead;
}

// OPERATOR=

template <class T>
THeadRing<T>& THeadRing<T>::operator=(const T& val) 
{
	TList<T>::DelList();
	pFirst = pLast = pHead->pNext = new TNode<T>;
	pLast->value = val;
	pLast->pNext = pHead;

	pLast->pNext = pHead;
	++length;

	return *this;
}

template <class T>
THeadRing<T>& THeadRing<T>::operator=(TList<T>& l)
{
	this->TList<T>::operator=(l);

	pHead->pNext = pFirst;
	pLast->pNext = pHead;

	return *this;
}

template <class T>
THeadRing<T>& THeadRing<T>::operator=(THeadRing<T>& hl)
{
	if (this == &hl) return *this;

	const int LEN = hl.length;
	while (length > LEN)
		this->DelFirst();

	// гарантируется, что length <= LEN
	for (Reset(), hl.Reset(); !IsEnd(); GoNext(), hl.GoNext())
		pCurr->value = hl.pCurr->value;

	for (; !hl.IsEnd(); hl.GoNext())
		this->InsLast(hl.pCurr->value);

	return *this;
}

// COMPARISON OPERATORS

template <class T>
bool THeadRing<T>::operator==(THeadRing<T>& l)
{
	if (this == &l)
		return true;

	if (length != l.length)
		return false;

	bool res = true;

	for (Reset(), l.Reset(); !IsEnd() && res; GoNext(), l.GoNext())
		res = pCurr->value == l.pCurr->value;

	return res;
}

template <class T>
bool THeadRing<T>::operator!=(THeadRing<T>& l) {
	return !this->operator==(l);
}

// INSERT AND DELETE METHODS

template <class T>
void THeadRing<T>::InsFirst(const T& val) {
	TList<T>::InsFirst(val);
	pHead->pNext = pFirst;
}

template <class T>
void THeadRing<T>::DelFirst()
{
	TList<T>::DelFirst();
	pHead->pNext = pFirst;
}