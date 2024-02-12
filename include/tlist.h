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
	TList();
	TList(const T& _val);
	TList(const TList<T>& _list);
	TList<T>& operator=(const T& _val);
	TList<T>& operator=(const TList<T>& _list);
	~TList();

	void InsFirst(const T& _val);
	void InsLast(const T& _val);
	void InsCurr(const T& _val);
	void DelFirst();
	void DelCurr();

	TNode<T>* GetCurr() const;							// ������ � pCurr ��������
	void SetPos(int _pos);								// ���������� �������� pCurr � ����������� �� ������� _pos
	void Reset();										// ���������� pCurr �� ������ ������
	void GoNext();										// ������� � ���������� �����
	bool IsEnd() const noexcept;						
	void DelList();
};

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
	pStop = _list.pStop;

	int tmp = _list.length;
	for (int i = 0; i < tmp; )
}