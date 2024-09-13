// #include <iostream>
// // #include <multiset> // Include for std::multiset
// #include "s21_multiset.h"

// using namespace s21;

#include <iostream>

#include "s21_multiset.h"

using namespace s21;

// Реализация оператора << для std::pair
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

int main() {
  // Создание объекта Multiset с использованием списка инициализации
  Multiset<int> myMultiset{1, 2, 3, 1, 2, 2};
  for (auto it = myMultiset.begin(); it != myMultiset.end(); ++it) {
    std::cout << *it << " ";
  }

  size_t it = myMultiset.count(2);
  std::cout << it << " ";
  s21::Multiset<int> my_multiset1{1, 2, 2, 3, 4, 4, 4, 5};

  auto range = my_multiset1.equal_range(4);
  std::cout << std::endl;
  for (auto it = range.first; it != range.second; ++it) {
    std::cout << *it << " ";
  }

  std::cout << std::endl;
  auto range1 = my_multiset1.upper_bound(4);
  std::cout << *range1 << " ";

  return 0;
}

TEST(MultisetTest, UpperBoundMethod) {
  Multiset<int> ms = {1, 2, 2, 3, 4, 4, 5};

  auto ub = ms.upper_bound(2);
  EXPECT_NE(ub, ms.end());  // Проверяем, что найден хотя бы один элемент
  EXPECT_EQ(*ub, 3);  // Проверяем, что элемент равен 3
}