#include <gtest/gtest.h>  // Подключение Google Test

#include "../s21_containers/s21_multiset/s21_multiset.h"  // Подключение тестируемого класса

using namespace s21;
TEST(multisetTest, Contains) {
  multiset<int> multiset = {1, 2, 3, 4, 5};
  EXPECT_TRUE(multiset.contains(3));
  EXPECT_FALSE(multiset.contains(6));
}

TEST(multisetTest, DefaultConstructor) {
  multiset<int> ms;
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);
}

TEST(multisetTest, InitializerListConstructor) {
  multiset<int> ms = {1, 2, 3, 4, 5};
  EXPECT_FALSE(ms.empty());
  EXPECT_EQ(ms.size(), 5);
  EXPECT_TRUE(ms.contains(3));
  EXPECT_FALSE(ms.contains(6));
}

TEST(multisetTest, CopyConstructor) {
  multiset<int> ms1 = {1, 2, 3};
  multiset<int> ms2(ms1);
  EXPECT_EQ(ms1.size(), ms2.size());
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
}

TEST(multisetTest, MoveConstructor) {
  multiset<int> ms1 = {1, 2, 3};
  multiset<int> ms2(std::move(ms1));
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms1.empty());
}

TEST(multisetTest, Insert) {
  multiset<int> ms;
  auto [it, inserted] = ms.insert(10);
  EXPECT_TRUE(inserted);
  EXPECT_TRUE(ms.contains(10));
  EXPECT_EQ(ms.size(), 1);

  auto [it2, inserted2] = ms.insert(10);
  EXPECT_TRUE(inserted2);
  EXPECT_EQ(ms.size(), 2);
}

TEST(multisetTest, EraseTest) {
  multiset<int> ms = {1, 2, 3, 4, 5};

  // Удаляем элемент, который существует
  auto it = ms.find(3);
  EXPECT_NE(it, ms.end());
  ms.erase(it);
  // Проверяем, что элемент был удален
  it = ms.find(3);
  EXPECT_EQ(it, ms.end());
  // Проверяем, что размер множества уменьшился
  EXPECT_EQ(ms.size(), 4);
  // Пытаемся удалить элемент, который не существует
  it = ms.find(6);
  if (it != ms.end()) {  // Проверяем, что элемент найден
    ms.erase(it);        // Удаляем элемент
  }
  // Проверяем, что размер множества не изменился
  EXPECT_EQ(ms.size(), 4);
}

TEST(multisetTest, Clear) {
  multiset<int> ms = {1, 2, 3};
  ms.clear();
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);
}

TEST(multisetTest, Find) {
  multiset<int> ms = {1, 2, 3, 4, 5};

  // Проверяем существующий элемент
  auto it = ms.find(3);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(it->first, 3);

  // Проверяем несуществующий элемент
  auto it2 = ms.find(6);
  EXPECT_EQ(it2, ms.end());
}

TEST(multisetTest, ContainsTest) {
  multiset<int> ms = {1, 2, 3};
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_FALSE(ms.contains(4));
}

TEST(multisetTest, Swap) {
  multiset<int> ms1 = {1, 2, 3};
  multiset<int> ms2 = {4, 5, 6};
  ms1.swap(ms2);
  EXPECT_TRUE(ms1.contains(4));
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_EQ(ms1.size(), 3);
  EXPECT_EQ(ms2.size(), 3);
}

TEST(multisetTest, Merge) {
  multiset<int> ms1 = {1, 2, 3};
  multiset<int> ms2 = {3, 4, 5};
  ms1.merge(ms2);
  EXPECT_EQ(ms1.size(), 6);
  EXPECT_TRUE(ms1.contains(4));
  EXPECT_TRUE(ms1.contains(5));
}

TEST(multisetTest, SizeTest) {
  multiset<int> ms = {1, 2, 3, 4, 5};
  EXPECT_EQ(ms.size(), 5);

  // Добавление и проверка размера
  ms.insert(6);
  EXPECT_EQ(ms.size(), 6);
  ms.erase(ms.find(1));
  EXPECT_EQ(ms.size(), 5);
}

// Проверка множества с дубликатами
TEST(multisetTest, DuplicatesTest) {
  multiset<int> ms = {1, 2, 2, 3, 4, 5, 5, 5};
  EXPECT_EQ(ms.size(), 8);  // Дубликаты должны учитываться
}

// Проверка итерирования
TEST(multisetTest, IterationTest) {
  multiset<int> ms = {1, 2, 3, 4, 5};
  int count = 0;
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, 5);  // Убедимся, что пройдено 5 элементов
}

TEST(multisetTest, CountMethod) {
  multiset<int> ms = {1, 2, 2, 3};

  EXPECT_EQ(ms.count(1), 1);  // Проверяем, что ключ 1 присутствует один раз
  EXPECT_EQ(ms.count(2), 2);  // Проверяем, что ключ 2 присутствует дважды
  EXPECT_EQ(ms.count(4), 0);  // Проверяем, что ключ 4 отсутствует
}

TEST(multisetTest, EqualRangeMethod) {
  multiset<int> ms = {1, 2, 3};

  auto range = ms.equal_range(2);
  EXPECT_NE(range.first,
            ms.end());  // Проверяем, что найден хотя бы один элемент
  EXPECT_EQ(range.first->first, 2);  // Проверяем, что первый элемент равен 2
  EXPECT_EQ(range.second->first, 3);  // Проверяем, что второй элемент равен 3
}

TEST(multisetTest, LowerBoundMethod) {
  multiset<int> ms = {1, 2, 2, 3, 4, 4, 5};

  auto lb = ms.lower_bound(2);
  EXPECT_NE(lb, ms.end());  // Проверяем, что найден хотя бы один элемент
  EXPECT_EQ(lb->first, 2);  // Проверяем, что элемент равен 2
}

TEST(multisetTest, UpperBoundMethod) {
  multiset<int> ms = {1, 2, 2, 3, 4, 4, 5};

  auto ub = ms.upper_bound(2);
  EXPECT_NE(ub, ms.end());  // Проверяем, что найден хотя бы один элемент
  EXPECT_EQ(ub->first, 3);  // Проверяем, что элемент равен 3
}