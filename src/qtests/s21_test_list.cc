#include <gtest/gtest.h>

#include "../s21_containers/s21_list/s21_list.h"

using namespace s21;

TEST(ListTest, DefaultConstructor) {
  list<int> mylist;
  EXPECT_TRUE(mylist.empty());
  EXPECT_EQ(mylist.size(), 0);
}

TEST(ListTest, ParameterizedConstructor) {
  list<int> mylist(5);
  EXPECT_FALSE(mylist.empty());
  EXPECT_EQ(mylist.size(), 5);
}

TEST(ListTest, InitializerListConstructor) {
  list<int> mylist({1, 2, 3});
  EXPECT_EQ(mylist.size(), 3);
  EXPECT_EQ(mylist.front(), 1);
  EXPECT_EQ(mylist.back(), 3);
}

TEST(ListTest, CopyConstructor) {
  list<int> mylist({1, 2, 3});
  list<int> copylist(mylist);
  EXPECT_EQ(copylist.size(), 3);
  EXPECT_EQ(copylist.front(), 1);
  EXPECT_EQ(copylist.back(), 3);
}

TEST(ListTest, PushBackPopBack) {
  list<int> mylist;
  mylist.push_back(1);
  EXPECT_EQ(mylist.back(), 1);
  mylist.pop_back();
  EXPECT_TRUE(mylist.empty());
}

TEST(ListTest, PushFrontPopFront) {
  list<int> mylist;
  mylist.push_front(1);
  EXPECT_EQ(mylist.front(), 1);
  mylist.pop_front();
  EXPECT_TRUE(mylist.empty());
}

TEST(ListTest, Insert) {
  list<int> mylist;
  auto it = mylist.insert(mylist.begin(), 1);
  EXPECT_EQ(*it, 1);
}

TEST(ListTest, Erase_0) {
  s21::list<int> mylist;
  mylist.push_back(1);
  mylist.push_back(2);
  auto it = mylist.begin();
  mylist.erase(it);
  EXPECT_EQ(mylist.size(), 1);
  EXPECT_EQ(*mylist.begin(), 2);
}

TEST(ListTest, Erase_1) {
  s21::list<int> mylist;
  mylist.push_back(1);
  mylist.push_back(2);
  mylist.push_back(3);
  mylist.push_back(4);
  auto it = mylist.begin();
  mylist.erase(it);
  EXPECT_EQ(mylist.size(), 3);
  EXPECT_EQ(*mylist.begin(), 2);
}

TEST(ListTest, Erase_2) {
  s21::list<int> mylist;
  mylist.push_back(1);
  auto it = mylist.begin();
  mylist.erase(it);
  EXPECT_EQ(mylist.size(), 0);
}

TEST(ListTest, Clear) {
  list<int> mylist({1, 2, 3});
  mylist.clear();
  EXPECT_TRUE(mylist.empty());
}

TEST(ListTest, Iterator) {
  list<int> mylist({1, 2, 3});
  auto it = mylist.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(ListTest, SwapNonEmptyLists) {
  list<int> list1({1, 2, 3});
  list<int> list2({4, 5, 6});
  list1.swap(list2);
  EXPECT_EQ(list1.size(), 3);
  EXPECT_EQ(list2.size(), 3);
  int expected_list1[] = {4, 5, 6};
  int expected_list2[] = {1, 2, 3};
  int i = 0;
  for (auto it = list1.begin(); it != list1.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected_list1[i]);
  }
  i = 0;
  for (auto it = list2.begin(); it != list2.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected_list2[i]);
  }
}

TEST(ListTest, SwapWithEmptyList) {
  list<int> list1;
  list<int> list2({1, 2, 3});
  list1.swap(list2);
  EXPECT_TRUE(list2.empty());
  EXPECT_EQ(list1.size(), 3);
  int expected_list1[] = {1, 2, 3};
  int i = 0;
  for (auto it = list1.begin(); it != list1.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected_list1[i]);
  }
}

TEST(ListTest, SwapEmptyLists) {
  list<int> list1;
  list<int> list2;
  list1.swap(list2);
  EXPECT_TRUE(list1.empty());
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, Merge) {
  s21::list<int> list1({1, 3, 5});
  s21::list<int> list2({2, 4, 6});
  list1.merge(list2);
  EXPECT_EQ(list1.size(), 6);
  EXPECT_EQ(list2.size(), 0);
  auto it = list1.begin();
  int prev = *it;
  ++it;
  while (it != list1.end()) {
    EXPECT_LE(prev, *it);
    prev = *it;
    ++it;
  }
}

TEST(ListTest, MergeListsOfDifferentLengths) {
  s21::list<int> list1({1, 3, 5, 7, 9});
  s21::list<int> list2({2, 4, 6});
  list1.merge(list2);
  int prev = list1.front();
  for (auto it = ++list1.begin(); it != list1.end(); ++it) {
    EXPECT_LE(prev, *it);
    prev = *it;
  }
  EXPECT_EQ(list1.size(), 8);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, MergeSelfAssignment) {
  list<int> mylist({1, 2, 3});
  EXPECT_NO_THROW({ mylist.merge(mylist); });
  EXPECT_EQ(mylist.size(), 3);
  int expected_values[] = {1, 2, 3};
  int i = 0;
  for (auto it = mylist.begin(); it != mylist.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected_values[i]);
  }
}

TEST(ListTest, MergeListWithSingleElement) {
  s21::list<int> list1({1});
  s21::list<int> list2({2, 3, 4});
  list1.merge(list2);
  int prev = list1.front();
  for (auto it = ++list1.begin(); it != list1.end(); ++it) {
    EXPECT_LE(prev, *it);
    prev = *it;
  }
  EXPECT_EQ(list1.size(), 4);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, MergeListWithEmptyList) {
  s21::list<int> list1({1, 3, 5});
  s21::list<int> list2;
  list1.merge(list2);
  int prev = list1.front();
  for (auto it = ++list1.begin(); it != list1.end(); ++it) {
    EXPECT_LE(prev, *it);
    prev = *it;
  }
  EXPECT_EQ(list1.size(), 3);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, MergeEmptyListWithList) {
  s21::list<int> list1;
  s21::list<int> list2({1, 3, 5});
  list1.merge(list2);
  int prev = list1.front();
  for (auto it = ++list1.begin(); it != list1.end(); ++it) {
    EXPECT_LE(prev, *it);
    prev = *it;
  }
  EXPECT_EQ(list1.size(), 3);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, MergeListWithAllElementsSmaller) {
  s21::list<int> list1({2, 4, 6});
  s21::list<int> list2({1, 3, 5});
  list1.merge(list2);
  int prev = list1.front();
  for (auto it = ++list1.begin(); it != list1.end(); ++it) {
    EXPECT_LE(prev, *it);
    prev = *it;
  }
  EXPECT_EQ(list1.size(), 6);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, MergeListWithAllElementsGreater) {
  s21::list<int> list1({1, 3, 5});
  s21::list<int> list2({2, 4, 6});
  list1.merge(list2);
  int prev = list1.front();
  for (auto it = ++list1.begin(); it != list1.end(); ++it) {
    EXPECT_LE(prev, *it);
    prev = *it;
  }
  EXPECT_EQ(list1.size(), 6);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, MergeListsWithSameElements) {
  s21::list<int> list1({1, 3, 5});
  s21::list<int> list2({1, 3, 5});
  list1.merge(list2);
  int prev = list1.front();
  for (auto it = ++list1.begin(); it != list1.end(); ++it) {
    EXPECT_LE(prev, *it);
    prev = *it;
  }
  EXPECT_EQ(list1.size(), 6);
  EXPECT_TRUE(list2.empty());
}

// Тест на слияние списков с повторяющимися элементами
TEST(ListTest, MergeListsWithDuplicateElements) {
  s21::list<int> list1({1, 2, 3, 3, 5});
  s21::list<int> list2({2, 3, 4, 4, 6});
  list1.merge(list2);
  int prev = list1.front();
  for (auto it = ++list1.begin(); it != list1.end(); ++it) {
    EXPECT_LE(prev, *it);
    prev = *it;
  }
  EXPECT_EQ(list1.size(), 10);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, MergeEmptyLists) {
  s21::list<int> list1;
  s21::list<int> list2;
  list1.merge(list2);
  EXPECT_TRUE(list1.empty());
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, MergeEmptyWithNonEmptyList) {
  s21::list<int> list1;
  s21::list<int> list2({1, 2, 3});
  list1.merge(list2);
  int prev = list1.front();
  for (auto it = ++list1.begin(); it != list1.end(); ++it) {
    EXPECT_LE(prev, *it);
    prev = *it;
  }
  EXPECT_EQ(list1.size(), 3);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, SpliceIntoBeginning) {
  list<int> list1({1, 2, 3});
  list<int> list2({4, 5, 6});
  list1.splice(list1.cbegin(), list2);
  EXPECT_TRUE(list2.empty());
  EXPECT_EQ(list1.size(), 6);
  int expected_values[] = {4, 5, 6, 1, 2, 3};
  int i = 0;
  for (auto it = list1.cbegin(); it != list1.cend(); ++it, ++i) {
    EXPECT_EQ(*it, expected_values[i]);
  }
}

TEST(ListTest, SpliceIntoEnd) {
  list<int> list1({1, 2, 3});
  list<int> list2({4, 5, 6});
  list1.splice(list1.cend(), list2);
  EXPECT_TRUE(list2.empty());
  EXPECT_EQ(list1.size(), 6);
  int expected_values[] = {1, 2, 3, 4, 5, 6};
  int i = 0;
  for (auto it = list1.cbegin(); it != list1.cend(); ++it, ++i) {
    EXPECT_EQ(*it, expected_values[i]);
  }
}

TEST(ListTest, SpliceIntoMiddle) {
  list<int> list1({1, 2, 3});
  list<int> list2({4, 5, 6});
  auto mid = list1.cbegin();
  ++mid;
  list1.splice(mid, list2);
  EXPECT_TRUE(list2.empty());
  EXPECT_EQ(list1.size(), 6);
  int expected_values[] = {1, 4, 5, 6, 2, 3};
  int i = 0;
  for (auto it = list1.cbegin(); it != list1.cend(); ++it, ++i) {
    EXPECT_EQ(*it, expected_values[i]);
  }
}

TEST(ListTest, SpliceWithSelf) {
  list<int> list1({1, 2, 3});
  EXPECT_NO_THROW({ list1.splice(list1.cbegin(), list1); });
  EXPECT_EQ(list1.size(), 3);
  int expected_values[] = {1, 2, 3};
  int i = 0;
  for (auto it = list1.cbegin(); it != list1.cend(); ++it, ++i) {
    EXPECT_EQ(*it, expected_values[i]);
  }
}

TEST(ListTest, ReverseEmptyList) {
  s21::list<int> lst;
  lst.reverse();
  EXPECT_TRUE(lst.empty());
}

TEST(ListTest, ReverseSingleElementList) {
  s21::list<int> lst{5};
  lst.reverse();
  EXPECT_EQ(lst.front(), 5);
}

TEST(ListTest, ReverseMultiElementList) {
  s21::list<int> lst{1, 2, 3, 4, 5};
  lst.reverse();
  int expected_values[] = {5, 4, 3, 2, 1};
  int i = 0;
  for (const auto& val : lst) {
    EXPECT_EQ(val, expected_values[i]);
    ++i;
  }
}

TEST(ListTest, ReverseStringList) {
  s21::list<std::string> lst{"apple", "banana", "cherry"};
  lst.reverse();
  std::vector<std::string> expected_values = {"cherry", "banana", "apple"};
  int i = 0;
  for (const auto& val : lst) {
    EXPECT_EQ(val, expected_values[i]);
    ++i;
  }
}

TEST(ListTest, UniqueDuplicates) {
  s21::list<int> noDuplicateList{1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
  noDuplicateList.unique();
  int expected_values[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
  int i = 0;
  for (const auto& val : noDuplicateList) {
    EXPECT_EQ(val, expected_values[i]);
    ++i;
  }
  EXPECT_EQ(noDuplicateList.size(), 9);
}

TEST(ListTest, UniqueWorksOnEmptyList) {
  s21::list<int> emptyList;
  emptyList.unique();
  EXPECT_TRUE(emptyList.empty());
}

TEST(ListTest, UniqueWorksOnSingleElementList) {
  s21::list<int> singleElementList = {42};
  singleElementList.unique();
  EXPECT_EQ(singleElementList.size(), 1);
  EXPECT_EQ(*(singleElementList.begin()), 42);
}

TEST(ListTest, UniqueNoDuplicates) {
  s21::list<int> noDuplicateList = {1, 2, 3, 4, 5};
  noDuplicateList.unique();
  int expected[] = {1, 2, 3, 4, 5};
  int i = 0;
  for (auto it = noDuplicateList.begin(); it != noDuplicateList.end();
       ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
  EXPECT_EQ(i, 5);
}

TEST(ListTest, SortsAscendingOrder) {
  s21::list<int> testList = {5, 3, 1, 4, 2};
  testList.sort();
  int expected[] = {1, 2, 3, 4, 5};
  int i = 0;
  for (auto it = testList.begin(); it != testList.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
  EXPECT_EQ(i, 5);
}

TEST(ListTest, SortWorksOnEmptyList) {
  s21::list<int> emptyList;
  emptyList.sort();
  EXPECT_TRUE(emptyList.empty());
}

TEST(ListTest, SortWorksOnSingleElementList) {
  s21::list<int> singleElementList = {42};
  singleElementList.sort();
  EXPECT_EQ(singleElementList.size(), 1);
  EXPECT_EQ(*(singleElementList.begin()), 42);
}