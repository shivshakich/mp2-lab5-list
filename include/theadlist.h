#pragma once

#include "tlist.h"

// ��������� ������ � �������, ����������� �� TList<T>
template <class T> class THeadList : public TList {
protected:
	TNode<T>* pHead;
};