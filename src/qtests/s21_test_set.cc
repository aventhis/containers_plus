#include <gtest/gtest.h>

#include "../s21_containers/s21_set/s21_set.h"

using namespace s21;

TEST(setTest, Contains) {
  set<int> set = {1, 2, 3, 4, 5};
  EXPECT_TRUE(set.contains(3));
  EXPECT_FALSE(set.contains(6));
}

TEST(setTest, DefaultConstructor) {
  set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(setTest, InitializerListConstructor) {
  set<int> s = {1, 2, 3, 4, 5};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 5);
  EXPECT_TRUE(s.contains(3));
  EXPECT_FALSE(s.contains(6));
}

TEST(setTest, CopyConstructor) {
  set<int> s1 = {1, 2, 3};
  set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(setTest, MoveConstructor) {
  set<int> s1 = {1, 2, 3};
  set<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s1.empty());
}

TEST(setTest, Insert) {
  set<int> s;
  auto [it, inserted] = s.insert(10);
  EXPECT_TRUE(inserted);
  EXPECT_TRUE(s.contains(10));
  EXPECT_EQ(s.size(), 1);
  auto [it2, inserted2] = s.insert(10);
  EXPECT_FALSE(inserted2);
  EXPECT_EQ(s.size(), 1);
}

TEST(setTest, InsertTest) {
  set<int> my_set;
  auto result = my_set.insert(1);
  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first->first, 1);
  result = my_set.insert(1);
  EXPECT_FALSE(result.second);
}

TEST(setTest, Erasetest) {
  set<int> s = {1, 2, 3, 4, 5};
  auto it = s.find(3);
  EXPECT_NE(it, s.end());
  s.erase(it);
  it = s.find(3);
  EXPECT_EQ(it, s.end());
  EXPECT_EQ(s.size(), 4);
  it = s.find(6);
  EXPECT_EQ(it, s.end());
  s.erase(it);
  EXPECT_EQ(s.size(), 4);
}

TEST(setTest, Clear) {
  set<int> s = {1, 2, 3};
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(setTest, Find) {
  set<int> s = {1, 2, 3, 4, 5};
  auto it = s.find(3);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(it->first, 3);
  auto it2 = s.find(6);
  EXPECT_EQ(it2, s.end());
}

TEST(setTest, ContainsTest) {
  set<int> my_set = {1, 2, 3};
  EXPECT_TRUE(my_set.contains(1));
  EXPECT_TRUE(my_set.contains(2));
  EXPECT_FALSE(my_set.contains(4));
}

TEST(setTest, Swap) {
  set<int> s1 = {1, 2, 3};
  set<int> s2 = {4, 5, 6};
  s1.swap(s2);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s2.contains(1));
  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);
}

TEST(setTest, Merge) {
  set<int> s1 = {1, 2, 3};
  set<int> s2 = {3, 4, 5};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 5);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
}

TEST(setTest, SizeTest) {
  set<int> s = {1, 2, 3, 4, 5};
  EXPECT_EQ(s.size(), 5);
  s.insert(6);
  EXPECT_EQ(s.size(), 6);
  s.erase(s.find(1));
  EXPECT_EQ(s.size(), 5);
}

TEST(setTest, DuplicatesTest) {
  set<int> s = {1, 2, 2, 3, 4, 5, 5, 5};
  EXPECT_EQ(s.size(), 5);
}

TEST(setTest, IterationTest) {
  set<int> s = {1, 2, 3, 4, 5};
  int count = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, 5);
}
