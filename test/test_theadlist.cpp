#include "../gtest/gtest.h"
#include "../include/theadlist.h"

// CONSTRUCTORS

TEST(THeadList, can_create_list) {
	ASSERT_NO_THROW(THeadList<double> l);			// default constructor
	ASSERT_NO_THROW(THeadList<char> l(123));		// conversion constructor

	TList<int> v;
	TList<int> v2(123);
	THeadList<int> l(123);
	THeadList<int> l2;
	ASSERT_NO_THROW(THeadList<int> list1(v));		// copy constructor
	ASSERT_NO_THROW(THeadList<int> list2(l));
	ASSERT_NO_THROW(THeadList<int> list3(v2));
	ASSERT_NO_THROW(THeadList<int> list4(l2));
}

TEST(THeadList, list_created_by_default_constructor_has_only_header_vertex) {
	THeadList<double> list;
	ASSERT_EQ(list.GetLength(), 0);
}

TEST(THeadList, list_created_by_conversion_constructor_contains_one_vertex_and_has_correct_value) {
	int n = 5976;
	THeadList<int> list(n);

	list.Reset();
	ASSERT_TRUE(list.GetCurr()->value == n);
	ASSERT_EQ(list.GetLength(), 1);
}

TEST(THeadList, list_filled_by_insert_methods_has_correct_values) {
	int n1 = 65443, n2 = 56, n3 = -12, n4 = 8000;
	THeadList<int> list(n2);
	list.InsFirst(n1);						// InsFirst
	list.InsLast(n4);						// InsLast

	list.Reset();
	list.GoNext(); list.GoNext();
	list.InsCurr(n3);						// InsCurr

	ASSERT_EQ(list.GetLength(), 4);

	/*
	std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << std::endl;
	for (list.Reset(); !list.IsEnd(); list.GoNext())
		std::cout << list.GetCurr()->value << std::endl;
	*/


	list.Reset();
	ASSERT_TRUE(list.GetCurr()->value == n1);	list.GoNext();
	ASSERT_TRUE(list.GetCurr()->value == n2);	list.GoNext();
	ASSERT_TRUE(list.GetCurr()->value == n3);	list.GoNext();
	ASSERT_TRUE(list.GetCurr()->value == n4);	list.GoNext();
}

TEST(THeadList, list_created_by_copy_constructor_is_equivalent_to_original_one) {
	THeadList<int> voidList;
	THeadList<int> _list(voidList);
	ASSERT_EQ(_list.GetLength(), 0);

	int n1 = 93, n2 = 56, n3 = -2;
	THeadList<int> originalList(n2);
	originalList.InsFirst(n1);
	originalList.InsLast(n3);
	// n1 n2 n3

	THeadList<int> copyList(originalList);
	ASSERT_TRUE(originalList == copyList);
}

// OPERATOR=

TEST(THeadList, list_assigned_to_the_value_consists_of_a_single_vertex_that_contains_the_input_value) {
	THeadList<int> l(12);
	l.InsLast(34);
	l.InsLast(56);
	ASSERT_NO_THROW(l = 78);

	l.Reset();
	ASSERT_EQ(l.GetCurr()->value, 78);
	ASSERT_EQ(l.GetLength(), 1);
}

TEST(THeadList, list_assigned_to_another_list_is_equivalent_to_original_one) {
	THeadList<int> l(12); l.InsLast(34); l.InsLast(56);
	THeadList<int> m;
	ASSERT_NO_THROW(m = l);
	ASSERT_TRUE(&m != &l);
	ASSERT_TRUE(m == l);
}

// COMPARISON OPERATORS: == 

TEST(THeadList, correct_operation_of_the_equivality_operator) {
	const int SIZE = 5;
	int n[SIZE] = { 12, 34, 56, 78, 90 };

	THeadList<int> l1, l2;
	for (int i = 0; i < SIZE; ++i) {
		l1.InsLast(n[i]);
		l2.InsFirst(n[SIZE - 1 - i]);
	}

	ASSERT_TRUE(l1 == l2);
}

// SetPos, InsCurr, DelCurr

TEST(THeadList, can_set_only_minus_one_position_for_an_empty_list) {
	int n = 908;
	THeadList<int> l;
	ASSERT_NO_THROW(l.SetPos(-1));
	ASSERT_ANY_THROW(l.SetPos(1));
	ASSERT_ANY_THROW(l.SetPos(0));
}

TEST(THeadList, correct_operation_of_the_vertex_insertion_method_by_current_pointer) {
	const int SIZE = 3;
	int n[SIZE] = { 12, 34, 56 };

	THeadList<int> l1(n[2]);

	l1.Reset();
	l1.SetPos(0);
	ASSERT_NO_THROW(l1.InsCurr(n[0]));
	l1.SetPos(1);
	ASSERT_NO_THROW(l1.InsCurr(n[1]));

	ASSERT_EQ(l1.GetLength(), SIZE);

	l1.Reset();
	ASSERT_EQ(l1.GetCurr()->value, n[0]);	l1.GoNext();
	ASSERT_EQ(l1.GetCurr()->value, n[1]);	l1.GoNext();
	ASSERT_EQ(l1.GetCurr()->value, n[2]);
}

TEST(THeadList, correct_deletion_of_the_vertex_by_current_pointer) {
	const int SIZE = 5;
	int n[SIZE] = { 12, 34, 56, 78, 90 };

	THeadList<int> l;

	l.Reset();
	ASSERT_ANY_THROW(l.DelCurr());

	for (int i = 0; i < SIZE; ++i)
		l.InsLast(n[i]);
	// n[0] n[1] n[2] n[3] n[4]

	l.SetPos(4);
	ASSERT_NO_THROW(l.DelCurr());
	ASSERT_EQ(l.GetLength(), 4);
	ASSERT_ANY_THROW(l.DelCurr());
	// n[0] n[1] n[2] n[3] ----

	l.SetPos(1);
	ASSERT_NO_THROW(l.DelCurr());
	// n[0] ---- n[2] n[3] ----
	ASSERT_EQ(l.GetLength(), 3);

	l.Reset();
	ASSERT_EQ(l.GetCurr()->value, n[0]);	l.GoNext();
	ASSERT_EQ(l.GetCurr()->value, n[2]);	l.GoNext();
	ASSERT_EQ(l.GetCurr()->value, n[3]);
}