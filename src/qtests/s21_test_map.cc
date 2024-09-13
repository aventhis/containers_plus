#include <gtest/gtest.h>  // Подключение Google Test

#include "../s21_containers/s21_map/s21_map.h"  // Подключение тестируемого класса

TEST(mapTest, DefaultConstructor) {
  s21::map<int, std::string> map;
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0);
}

TEST(mapTest, InitializerListConstructor) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");
}

TEST(mapTest, CopyConstructor) {
  s21::map<int, std::string> map1{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> map2(map1);
  EXPECT_EQ(map2.size(), 3);
  EXPECT_EQ(map2[1], "one");
  EXPECT_EQ(map2[2], "two");
  EXPECT_EQ(map2[3], "three");
}

TEST(mapTest, MoveConstructor) {
  s21::map<int, std::string> map1{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> map2(std::move(map1));
  EXPECT_EQ(map2.size(), 3);
  EXPECT_EQ(map2[1], "one");
  EXPECT_EQ(map2[2], "two");
  EXPECT_EQ(map2[3], "three");
  EXPECT_TRUE(map1.empty());
}

TEST(mapTest, CopyAssignmentOperator) {
  s21::map<int, std::string> map1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> map2;
  map2 = map1;
  EXPECT_EQ(map2.size(), 3);
  EXPECT_EQ(map2[1], "one");
  EXPECT_EQ(map2[2], "two");
  EXPECT_EQ(map2[3], "three");
}

TEST(mapTest, MoveAssignmentOperator) {
  s21::map<int, std::string> map1{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> map2;
  map2 = std::move(map1);
  EXPECT_EQ(map2.size(), 3);
  EXPECT_EQ(map2[1], "one");
  EXPECT_EQ(map2[2], "two");
  EXPECT_EQ(map2[3], "three");
  EXPECT_TRUE(map1.empty());
}

TEST(mapTest, Insert) {
  s21::map<int, std::string> map;
  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");
}

TEST(mapTest, Erase) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  map.erase(map.find(2));
  EXPECT_EQ(map.size(), 2);

  EXPECT_EQ(map.find(1), map.find(1));
  EXPECT_EQ(map.find(2), map.end());
  EXPECT_EQ(map.find(3), map.find(3));
}

TEST(mapTest, Clear) {
  s21::map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};
  map.clear();
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0);
}

TEST(mapTest, Contains) {
  s21::map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_TRUE(map.contains(1));
  EXPECT_FALSE(map.contains(4));
}

TEST(mapTest, At) {
  s21::map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map.at(2), "two");
  EXPECT_EQ(map.at(3), "three");
  EXPECT_THROW(map.at(4), std::out_of_range);
}

TEST(mapTest, SquareBracketOperator) {
  s21::map<int, std::string> map;
  map[1] = "one";
  map[2] = "two";
  map[3] = "three";
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");
}

TEST(mapTest, Swap) {
  s21::map<int, std::string> map1 = {{1, "one"}, {2, "two"}};
  s21::map<int, std::string> map2 = {{3, "three"}, {4, "four"}};
  map1.swap(map2);
  EXPECT_EQ(map1.size(), 2);
  EXPECT_EQ(map2.size(), 2);
  EXPECT_EQ(map1[3], "three");
  EXPECT_EQ(map1[4], "four");
  EXPECT_EQ(map2[1], "one");
  EXPECT_EQ(map2[2], "two");
}

TEST(mapTest, Merge) {
  s21::map<int, std::string> map1 = {{1, "one"}, {2, "two"}};
  s21::map<int, std::string> map2 = {{3, "three"}, {4, "four"}};
  map1.merge(map2);
  EXPECT_EQ(map1.size(), 4);
  EXPECT_TRUE(map2.empty());
  EXPECT_EQ(map1[1], "one");
  EXPECT_EQ(map1[2], "two");
  EXPECT_EQ(map1[3], "three");
  EXPECT_EQ(map1[4], "four");
}

TEST(mapTest, BeginEnd) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  auto it = map.begin();
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "one");
  ++it;
  EXPECT_EQ(it->first, 2);
  EXPECT_EQ(it->second, "two");
  ++it;
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(it->second, "three");
  ++it;
  EXPECT_EQ(it, map.end());
}
