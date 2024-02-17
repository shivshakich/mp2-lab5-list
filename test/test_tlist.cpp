#include "../gtest/gtest.h"
#include "../include/tlist.h"

TEST(TList, can_create_list) {
	ASSERT_NO_THROW(TList<double> l);
	ASSERT_NO_THROW(TList<char> l(123));
	TList<int> l(123);
	ASSERT_NO_THROW(TList<int> list(l));
}

TEST(TList, list_created_by_default_constructor_is_empty) {
	TList<double> list;
	ASSERT_ANY_THROW(list.DelFirst());
}

TEST(TList, list_created_by_conversion_constructor_contains_one_vertex_and_has_correct_value) {
	int n = 1234;
	TList<int> list(n);

	list.Reset();
	ASSERT_TRUE(list.GetCurr()->value == n);
	ASSERT_NO_THROW(list.DelFirst());
	ASSERT_ANY_THROW(list.DelFirst());
}

TEST(TList, list_filled_by_insert_methods_has_correct_values) {
	int n1 = 65443, n2 = 56, n3 = -12, n4 = 8000;
	TList<int> list(n2);
	list.InsFirst(n1);
	list.InsLast(n4);

	list.Reset();
	list.GoNext(); list.GoNext();
	list.InsCurr(n3);

	ASSERT_TRUE(list.IsEnd());

	list.Reset();
	ASSERT_TRUE(list.GetCurr()->value == n1);	ASSERT_NO_THROW(list.GoNext());	
	ASSERT_TRUE(list.GetCurr()->value == n2);	ASSERT_NO_THROW(list.GoNext());
	ASSERT_TRUE(list.GetCurr()->value == n3);	ASSERT_NO_THROW(list.GoNext());
	ASSERT_TRUE(list.GetCurr()->value == n4);	ASSERT_ANY_THROW(list.GoNext());
}

TEST(TList, list_created_by_copy_constructor_is_equivalent_to_original_one) {
	TList<int> voidlist;
	ASSERT_NO_THROW(TList<int> _list(voidlist));
	TList<int> _list(voidlist);
	ASSERT_ANY_THROW(_list.DelFirst());

	int n1 = 65443, n2 = 56, n3 = -12;
	TList<int> original(n2);
	original.InsFirst(n1); 
	original.InsLast(n3);
	// n1 n2 n3

	ASSERT_NOT
}