#include <iostream>

#include "s21_tree.h"

// int main() {
//     s21::AVLTree<int, int> tree;
//     tree.insert({10, 10});
//     tree.insert({20, 20});
//     tree.insert({30, 30});
//     tree.insert({40, 40});
//     tree.insert({50, 50});
//     tree.insert({25, 25});

//     std::cout << "Tree contents (key-value pairs):" << std::endl;
//     for (auto it = tree.begin(); it != tree.end(); ++it) {
//         std::cout << "2!!! Iterating: " << it->first << " - " << it->second
//         << std::endl;
//     }

//     return 0;
// }

int main() {
  s21::AVLTree<int, int> tree;
  tree.insert({10, 10});
  tree.insert({20, 20});
  tree.insert({30, 30});
  tree.insert({40, 40});
  tree.insert({50, 50});
  tree.insert({25, 25});
  s21::AVLTree<int, int> tree2(tree);

  std::cout << "Tree contents (key-value pairs):" << std::endl;
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    std::cout << "2!!! Iterating: " << it->first << " - " << it->second
              << std::endl;
  }
  std::cout << "Tree2 contents (key-value pairs):" << std::endl;
  for (auto it = tree2.begin(); it != tree2.end(); ++it) {
    std::cout << "2!!! Iterating: " << it->first << " - " << it->second
              << std::endl;
  }
  return 0;
}
// #include <iostream>
// #include <set>

// int main() {
//     // Создаем пустое множество целых чисел
//     std::set<int> mySet;

//     // Вставляем несколько элементов в множество
//     mySet.insert(1);
//     mySet.insert(2);
//     mySet.insert(3);

//     // Пытаемся вставить элемент, который уже существует
//     auto result = mySet.insert(2);

//     // // Проверяем результат вставки
//     // if (result.second) {
//     //     std::cout << "Element 2 was inserted successfully.\n";
//     // } else {
//     //     std::cout << "Element 2 already exists in the set.\n";
//     // }

//     // Выводим содержимое множества
//     std::cout << "Elements in the set: ";
//     for (const int& element : mySet) {
//         std::cout << element << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }