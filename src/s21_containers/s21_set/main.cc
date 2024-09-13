#include <iostream>

#include "s21_set.h"

using namespace s21;

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<const K, V>& p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

int main() {
  // Создание множества и добавление элементов
  Set<int> my_set;
  my_set.insert(10);
  my_set.insert(20);
  my_set.insert(30);

  std::cout << "After inserting 10, 20, 30:" << std::endl;
  for (const auto& pair : my_set) {
    std::cout << pair.second << " ";
  }
  std::cout << std::endl;

  // Удаление элемента
  auto it = my_set.find(20);
  if (it != my_set.end()) {
    my_set.erase(it);
  }

  std::cout << "After erasing 20:" << std::endl;
  for (const auto& pair : my_set) {
    std::cout << pair.second << " ";
  }
  std::cout << std::endl;

  // Проверка наличия элемента
  if (my_set.contains(10)) {
    std::cout << "Set contains 10" << std::endl;
  } else {
    std::cout << "Set does not contain 10" << std::endl;
  }

  // Проверка размера множества
  std::cout << "Set size: " << my_set.size() << std::endl;

  // Очистка множества
  my_set.clear();
  std::cout << "After clearing, set size: " << my_set.size() << std::endl;

  // Пополнение множества и проверка обмена
  Set<int> another_set = {40, 50, 60};
  my_set.insert(70);
  my_set.insert(80);

  std::cout << "Before swap:" << std::endl;
  std::cout << "my_set: ";
  for (const auto& pair : my_set) {
    std::cout << pair.second << " ";
  }
  std::cout << std::endl;
  std::cout << "another_set: ";
  for (const auto& pair : another_set) {
    std::cout << pair.second << " ";
  }
  std::cout << std::endl;

  my_set.swap(another_set);

  std::cout << "After swap:" << std::endl;
  std::cout << "my_set: ";
  for (const auto& pair : my_set) {
    std::cout << pair.second << " ";
  }
  std::cout << std::endl;
  std::cout << "another_set: ";
  for (const auto& pair : another_set) {
    std::cout << pair.second << " ";
  }
  std::cout << std::endl;

  return 0;
}
