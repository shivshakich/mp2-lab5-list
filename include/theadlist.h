#pragma once

#include "tlist.h"

// Кольцевой список с головой, наследуемый от TList<T>
template <class T> class THeadList : public TList {
protected:
	TNode<T>* pHead;
};