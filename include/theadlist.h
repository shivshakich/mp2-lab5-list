#pragma once

#include "tlist.h"

// Кольцевой список с головой, наследуемый от TList<T>
template <class T> class THeadList : public TList<T> {
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
	THeadList();
	THeadList(const T& val);
	THeadList(TList<T>& l);
	THeadList(THeadList<T>& hl);
	~THeadList();

	THeadList<T>& operator=(const T& _val);
	THeadList<T>& operator=(TList<T>& _list);
	THeadList<T>& operator=(THeadList<T>& _list);

	bool operator==(THeadList<T>& _list);
	bool operator!=(THeadList<T>& _list);

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

// CONSTRUCTORS & DESTRUCTORS

template <class T>
THeadList<T>::THeadList() {
	pHead = new TNode<T>;
	pHead->pNext = pHead;
	pStop = pFirst = pLast = pCurr = pPrev = pHead;
	length = 0;
	pos = -1;
}

template <class T>
THeadList<T>::THeadList(const T& val) {
	pHead = new TNode<T>;
	pHead->pNext = pFirst = pLast = new TNode<T>{ val, pHead };
	pCurr = pPrev = pStop = pHead;
	length = 1;
	pos = -1;
}

template <class T>
THeadList<T>::THeadList(TList<T>& l)
{
	TList<T>::TList(l);
	pHead = new TNode<T>;
	if (length == 0) pFirst = pLast = pHead;

	pHead->pNext = pFirst;
	pLast->pNext = pCurr = pPrev = pStop = pHead;
}

template <class T> 
THeadList<T>::THeadList(THeadList<T>& hl) 
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
THeadList<T>::~THeadList()
{
	TList<T>::DelList();
	delete pHead;
}

// OPERATOR=

template <class T>
THeadList<T>& THeadList<T>::operator=(const T& val) 
{
	TList<T>::DelList();
	pFirst = pLast = pHead->pNext = new TNode<T>{ val, pHead };
	pLast->pNext = pHead;
	++length;

	return *this;
}

template <class T>
THeadList<T>& THeadList<T>::operator=(TList<T>& l)
{
	this->TList<T>::operator=(l);

	pHead->pNext = pFirst;
	pLast->pNext = pHead;

	return *this;
}

template <class T>
THeadList<T>& THeadList<T>::operator=(THeadList<T>& hl)
{
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
bool THeadList<T>::operator==(THeadList<T>& l)
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
bool THeadList<T>::operator!=(THeadList<T>& l) {
	return !this->operator==(l);
}

// INSERT AND DELETE METHODS

template <class T>
void THeadList<T>::InsFirst(const T& val) {
	TList<T>::InsFirst(val);
	pHead->pNext = pFirst;
}

template <class T>
void THeadList<T>::DelFirst()
{
	TList<T>::DelFirst();
	pHead->pNext = pFirst;
}