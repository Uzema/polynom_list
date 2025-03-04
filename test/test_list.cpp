#include "list.h"

#include <gtest.h>

TEST(list, can_create_list_with_positive_length) {
	ASSERT_NO_THROW(List<int> l(5));
}

TEST(list, cant_create_list_with_negative_length) {
	ASSERT_ANY_THROW(List<int> l(-5));
}

TEST(list, cant_set_too_large_element) {
	List<int> l(5);
	ASSERT_ANY_THROW(l[5] = 5);
}

TEST(list, can_create_copied_list) {
	List<int> l1(5, 2);
	ASSERT_NO_THROW(List<int> l2(l1));
}

TEST(list, can_set_and_get_elements) {
	List<int> l(5);
	l[0] = 10;
	EXPECT_EQ(l[0], 10);
}

TEST(list, copied_list_has_its_own_memory) {
	List<int> l1(5, 2);
	List<int> l2(l1);
	l2[3] = 10;
	EXPECT_EQ(l2[0], 2);
	EXPECT_EQ(l2[3], 10);
	EXPECT_EQ(l1[3], 2);
}

TEST(list, can_assign_list_to_itself) {
	List<int> l(5);
	ASSERT_NO_THROW(l = l);
}

TEST(list, can_assign_lists_of_different_sizes_1) {
	List<int> l1(5, 2);
	List<int> l2(7, 3);

	ASSERT_NO_THROW(l1 = l2);
}

TEST(list, can_assign_lists_of_different_sizes_2) {
	List<int> l1(5, 2);
	List<int> l2(7, 3);

	ASSERT_NO_THROW(l2 = l1);
}

TEST(list, can_get_size) {
	List<int> l(5);
	EXPECT_EQ(l.size(), 5);
}

TEST(list, can_get_empty_list_size) {
	List<int> l;
	EXPECT_EQ(0, l.size());
}

TEST(list, can_insert_front) {
	List<int> l(1);
	ASSERT_NO_THROW(l.insert_front(2));
}

TEST(list, correctly_insert_front) {
	List<int> l(1);
	l.insert_front(2);
	EXPECT_EQ(l[0], 2);
}

TEST(list, can_insert) {
	List<int> l(5);
	ASSERT_NO_THROW(l.insert(1, l.get_first()));
}

TEST(list, correctly_insert) {
	List<int> l(5);
	l.insert(2, l.get_first());
	EXPECT_EQ(l[1], 2);
}

TEST(list, can_insert_front_in_empty_list) {
	List<int> l;
	ASSERT_NO_THROW(l.insert_front(228));
}

TEST(list, correctly_erase) {
	List<int> l1(5, 1);
	l1[1] = 2;
	l1.erase(l1.get_first());
	List<int> l2(4, 1);
	for (int i = 0; i < 4; i++) {
		EXPECT_EQ(l1[i], l2[i]);
	}
}

TEST(list, can_erase) {
	List<int> l(5, 3);
	ASSERT_NO_THROW(l.erase(l.get_first()));
}

TEST(list, can_erase_front) {
	List<int> l(5, 3);
	ASSERT_NO_THROW(l.erase_front());
}

TEST(list, correctly_erase_front) {
	List<int> l1(5, 1);
	l1[0] = 2;
	l1.erase_front();
	List<int> l2(4, 1);
	for (int i = 0; i < 4; i++) {
		EXPECT_EQ(l1[i], l2[i]);
	}
}

TEST(list, cant_erase_front_in_empty_list) {
	List<int> l;
	ASSERT_ANY_THROW(l.erase_front());
}

TEST(list, can_find_element) {
	List<int> l;
	l.insert_front(5);
	l.insert_front(6);
	l.insert_front(7);
	EXPECT_EQ(l.find(7), l.get_first());
}

TEST(list, return_nullptr_when_no_element_is_found) {
	List<int> l;
	l.insert_front(5);
	l.insert_front(6);
	l.insert_front(7);
	EXPECT_EQ(l.find(3), nullptr);
}

TEST(list, iterator_begin) {
	List<int> l(5, 2);
	List<int>::iterator it = l.begin();
	EXPECT_EQ(2, *it);
}

TEST(list, iterator_can_iterate) {
	List<int> l(5, 2);
	l[1] = 5;
	List<int>::iterator it = l.begin();
	++it;
	EXPECT_EQ(5, *it);
}

TEST(list, can_erase_all_elements) {
	List<int> l(5, 2);
	l.print();
	for (int i = 0; i < 5; i++) {
		l.erase_front();
	}
	EXPECT_EQ(nullptr, l.get_first());
}

TEST(list, shift_correctly) {
	List<int> l1;
	l1.insert_front(5);
	l1.insert_front(4);
	l1.insert_front(3);
	l1.insert_front(2);
	l1.insert_front(1);

	List<int> l2;
	l2.insert_front(2);
	l2.insert_front(1);
	l2.insert_front(5);
	l2.insert_front(4);
	l2.insert_front(3);
	l1.shift(3);
	
	for (int i = 0; i < 5; i++) {
		EXPECT_EQ(l1[i], l2[i]);
	}
}

TEST(list, throw_when_shift_with_negative_k) {
	List<int> l(5, 2);
	ASSERT_ANY_THROW(l.shift(-5));
}

TEST(list, throw_when_shift_with_k_greater_than_size) {
	List<int> l(5, 2);
	ASSERT_ANY_THROW(l.shift(6));
}