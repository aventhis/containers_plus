#include <gtest/gtest.h>

#include "../s21_containers.h"
#include "../s21_containersplus.h"

using namespace s21;

TEST(ListTest, InsertManyIntoEmptyList) {
  s21::list<int> myList;
  auto it = myList.end();
  myList.insert_many(it, 1, 2, 3);
  std::vector<int> expected = {1, 2, 3};
  auto list_it = myList.begin();
  for (auto exp_it = expected.begin(); exp_it != expected.end();
       ++exp_it, ++list_it) {
    EXPECT_EQ(*list_it, *exp_it);
  }
}

TEST(ListTest, InsertManyOnce) {
  s21::list<int> l({1, 2, 3});
  auto pos = l.begin();
  ++pos;
  pos = l.insert_many(pos, 4);
  EXPECT_EQ(4, *pos);
  EXPECT_EQ(4, l.size());
  int arr[] = {1, 4, 2, 3};
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(arr[i], *iter);
  }
}

TEST(ListTest, InsertManyMultiple) {
  s21::list<char> l({'a', 'b', 'c'});
  auto pos = l.begin();
  ++pos;
  ++pos;
  pos = l.insert_many(pos, 'd', 'e', 'f');
  EXPECT_EQ(*pos, 'd');
  EXPECT_EQ(6, l.size());
  char arr[] = {'a', 'b', 'd', 'e', 'f', 'c'};
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(arr[i], *iter);
  }
  pos = l.insert_many(l.begin(), 'a', 'b', std::move('o'), 'b', 'a');
  EXPECT_EQ(*pos, 'a');
  char extended_arr[] = {'a', 'b', 'o', 'b', 'a', 'a', 'b', 'd', 'e', 'f', 'c'};
  i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(extended_arr[i], *iter);
  }
}

TEST(ListTest, InsertManyNothing) {
  s21::list<double> l({1.1, 2.2, 3.3});
  auto pos = l.insert_many(l.begin());
  EXPECT_DOUBLE_EQ(*pos, 1.1);
  EXPECT_EQ(3, l.size());
  int i = 1;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_DOUBLE_EQ(i * 1.1, *iter);
  }
}

TEST(ListTest, InsertManyToEmpty) {
  s21::list<int> l;
  auto pos = l.insert_many(l.begin(), 1, 2, 3);
  EXPECT_EQ(*pos, 1);
  EXPECT_EQ(3, l.size());
  int i = 1;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(ListTest, InsertManyToEnd) {
  s21::list<char> l({'a', 'b', 'o'});
  auto pos = l.insert_many(l.end(), 'b', 'u', 's');
  EXPECT_EQ(*pos, 'b');
  EXPECT_EQ(6, l.size());
  std::string text = "abobus";
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(ListTest, InsertManyBackOnce) {
  s21::list<int> l({0, 2, 4, 6});
  l.insert_many_back(8);
  EXPECT_EQ(5, l.size());
  auto iter = l.begin();
  for (size_t i = 0; i < l.size(); ++i, ++iter) {
    EXPECT_EQ(2 * i, *iter);
  }
}

TEST(ListTest, InsertManyBackMultiple) {
  s21::list<int> l({0, 1, 4, 9});
  l.insert_many_back(std::move(16), std::move(25), 36);
  EXPECT_EQ(7, l.size());
  auto iter = l.begin();
  for (size_t i = 0; i < l.size(); ++i, ++iter) {
    EXPECT_EQ(i * i, *iter);
  }
}

TEST(ListTest, InsertManyBackNothing) {
  s21::list<char> l({'c', 'o', 'o', 'l'});
  l.insert_many_back();
  EXPECT_EQ(4, l.size());
  std::string text = "cool";
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(ListTest, InsertManyBackEmpty) {
  s21::list<char> l;
  l.insert_many_back('c', 'o', 'o', 'l');
  EXPECT_EQ(4, l.size());
  std::string text = "cool";
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(ListTest, InsertManyFrontOnce) {
  s21::list<int> l({2, 4, 6, 8});
  l.insert_many_front(0);
  EXPECT_EQ(5, l.size());
  auto iter = l.begin();
  for (size_t i = 0; i < l.size(); ++i, ++iter) {
    EXPECT_EQ(2 * i, *iter);
  }
}

TEST(ListTest, InsertManyFrontMultiple) {
  s21::list<int> l({9, 16, 25, 36});
  l.insert_many_front(std::move(0), std::move(1), 4);
  EXPECT_EQ(7, l.size());
  auto iter = l.begin();
  for (size_t i = 0; i < l.size(); ++i, ++iter) {
    EXPECT_EQ(i * i, *iter);
  }
}

TEST(ListTest, InsertManyFrontNothing) {
  s21::list<char> l({'c', 'o', 'o', 'l'});
  l.insert_many_front();
  EXPECT_EQ(4, l.size());
  std::string text = "cool";
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(ListTest, InsertManyFrontEmpty) {
  s21::list<char> l;
  l.insert_many_front('c', 'o', 'o', 'l');
  EXPECT_EQ(4, l.size());
  std::string text = "cool";
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(StackTest, InsertManyFront_EmptyStack) {
  s21::stack<int> stack;
  stack.insert_many_front(1, 2, 3);
  std::vector<int> result;
  while (!stack.empty()) {
    result.push_back(stack.top());
    stack.pop();
  }
  std::vector<int> expected = {3, 2, 1};
  EXPECT_EQ(result, expected);
}

TEST(StackTest, InsertManyFront_NonEmptyStack) {
  s21::stack<int> stack;
  stack.push(4);
  stack.push(5);
  stack.push(6);
  stack.insert_many_front(1, 2, 3);
  std::vector<int> result;
  while (!stack.empty()) {
    result.push_back(stack.top());
    stack.pop();
  }
  std::vector<int> expected = {6, 5, 4, 3, 2, 1};
  EXPECT_EQ(result, expected);
}

TEST(StackTest, InsertManyFront_SingleElement) {
  s21::stack<int> stack;
  stack.push(4);
  stack.push(5);
  stack.push(6);
  stack.insert_many_front(7);
  std::vector<int> result;
  while (!stack.empty()) {
    result.push_back(stack.top());
    stack.pop();
  }
  std::vector<int> expected = {6, 5, 4, 7};
  EXPECT_EQ(result, expected);
}

TEST(StackTest, InsertManyFront_NoElements) {
  s21::stack<int> stack;
  stack.push(4);
  stack.push(5);
  stack.push(6);
  stack.insert_many_front();
  std::vector<int> result;
  while (!stack.empty()) {
    result.push_back(stack.top());
    stack.pop();
  }
  std::vector<int> expected = {6, 5, 4};
  EXPECT_EQ(result, expected);
}

TEST(QueueTest, InsertManyBack) {
  s21::queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);
  queue.push(4);
  queue.push(5);
  queue.insert_many_back(6, 7, 8);
  std::vector<int> result;
  while (!queue.empty()) {
    result.push_back(queue.front());
    queue.pop();
  }
  std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(result, expected);
}

TEST(VectorTest, InsertMany) {
  s21::vector<int> vector;
  vector.push_back(1);
  vector.push_back(2);
  vector.push_back(3);
  auto pos = vector.begin();
  ++pos;
  pos = vector.insert_many(pos, 4, 5);
  std::vector<int> result(vector.begin(), vector.end());
  std::vector<int> expected = {1, 4, 5, 2, 3};
  EXPECT_EQ(result, expected);
}

TEST(VectorTest, InsertManyBack) {
  s21::vector<int> vector;
  vector.push_back(1);
  vector.push_back(2);
  vector.push_back(3);
  vector.insert_many_back(4, 5, 6);
  std::vector<int> result(vector.begin(), vector.end());
  std::vector<int> expected = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(result, expected);
}

TEST(mapTest, InsertMany) {
  s21::map<int, std::string> my_map;
  auto results_map =
      my_map.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"),
                         std::make_pair(3, "three"));
  ASSERT_EQ(results_map.size(), 3);
  EXPECT_EQ(results_map[0].second, true);
  EXPECT_EQ(results_map[1].second, true);
  EXPECT_EQ(results_map[2].second, true);
  EXPECT_EQ(my_map.size(), 3);
  EXPECT_EQ(my_map[1], "one");
  EXPECT_EQ(my_map[2], "two");
  EXPECT_EQ(my_map[3], "three");
}

TEST(setTest, InsertMany) {
  s21::set<int> my_set;
  auto results_set = my_set.insert_many(1, 2, 3, 4, 5);
  ASSERT_EQ(results_set.size(), 5);
  EXPECT_EQ(results_set[0].second, true);
  EXPECT_EQ(results_set[1].second, true);
  EXPECT_EQ(results_set[2].second, true);
  EXPECT_EQ(results_set[3].second, true);
  EXPECT_EQ(results_set[4].second, true);
  EXPECT_EQ(my_set.size(), 5);
}

TEST(multisetTest, InsertMany) {
  s21::multiset<int> my_multiset;
  auto results_multiset = my_multiset.insert_many(1, 2, 3, 4, 4, 5);
  ASSERT_EQ(results_multiset.size(), 6);
  EXPECT_EQ(results_multiset[0].second, true);
  EXPECT_EQ(results_multiset[1].second, true);
  EXPECT_EQ(results_multiset[2].second, true);
  EXPECT_EQ(results_multiset[3].second, true);
  EXPECT_EQ(results_multiset[4].second, true);
  EXPECT_EQ(results_multiset[5].second, true);
  EXPECT_EQ(my_multiset.size(), 6);
}
