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
	int pos;									// ��������� ���������� � 0
public:

	// ������������, ���������� � ��������� �����������

	TList();
	TList(const T& _val);
	TList(const TList<T>& _list);
	~TList();
	TList<T>& operator=(const T& _val);
	TList<T>& operator=(const TList<T>& _list);

	// ������� ��� �������� �����

	void InsFirst(const T& _val);
	void InsLast(const T& _val);
	void InsCurr(const T& _val);
	void DelFirst();
	void DelCurr();

	// ������ ������� � pCurr

	TNode<T>* GetCurr() const;							// ������ � pCurr ��������
	void SetPos(int _pos);								// ���������� �������� pCurr � ����������� �� ������� _pos
	void Reset();										// ���������� pCurr �� ������ ������
	void GoNext();										// ������� � ���������� �����
	bool IsEnd() const noexcept;

	// ������ ������
					
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

	while (currNode != pStop) {				// ������ ������
		TNode<T>* tmpNode = new TNode<T>;
		tmpNode->value = currNode->value;
		pLast->pNext = tmpNode;
		pLast = tmpNode;
	}
	pLast->pNext = pStop;
}

template <class T>										/* destructor */
TList<T>::~TList() { DelList(); }

// OPERATOR=

template <class T>
TList<T>& TList<T>::operator=(const T& _val) {
	this->DelList();
	this->InsLast(_val);
}

template <class T> 
TList<T>& TList<T>::operator=(const TList<T>& in) {
	if (this == &in)
		return *this;

	TNode<T>* currNode = in.pFirst;
	const int IN_LEN = in.length;

	pPrev = pCurr = pStop;
	pos = -1;

}