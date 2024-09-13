#include <iostream>
// #include <list>
// #include "s21_list_jenisepl.h"
#include "s21_list.h"

// int main() {
//     // Создание списка целых чисел
//     std::list<int> myList;

//     // Добавление элементов в список
//     myList.push_back(10);  // Добавление в конец списка
//     myList.push_back(20);
//     myList.push_back(30);

//     myList.push_front(5);  // Добавление в начало списка

//     // Проход по списку и вывод элементов
//     std::cout << "Elements in the list: ";
//     for (auto it = myList.begin(); it != myList.end(); ++it) {
//         std::cout << *it << " ";
//     }
//     std::cout << std::endl;

//     // Удаление элемента из начала списка
//     myList.pop_front();

//     // Удаление элемента из конца списка
//     myList.pop_back();

//     std::cout << "Elements after popping front and back: ";
//     for (auto it = myList.begin(); it != myList.end(); ++it) {
//         std::cout << *it << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }

// int main() {
//     // Создание списка целых чисел
//     s21::list<int> myList;

//     // Добавление элементов в список
//     myList.push_back(10);  // Добавление в конец списка
//     myList.push_back(20);
//     myList.push_back(30);

//     myList.push_front(5);  // Добавление в начало списка

//     // Проход по списку и вывод элементов
//     std::cout << "Elements in the list: ";
//     for (auto it = myList.begin(); it != myList.end(); ++it) {
//         std::cout << *it << " ";
//     }
//     std::cout << std::endl;

//     // Удаление элемента из начала списка
//     myList.pop_front();

//     // Удаление элемента из конца списка
//     myList.pop_back();

//     std::cout << "Elements after popping front and back: ";
//     for (auto it = myList.begin(); it != myList.end(); ++it) {
//         std::cout << *it << " ";
//     }

//     // myList.printList();
//     std::cout << std::endl;

//     return 0;
// }

// int main() {
//     s21::list<int> list1;
//     s21::list<int> list2;

//     // Добавление элементов в первый список
//     list1.push_back(10);
//     list1.push_back(20);
//     list1.push_back(30);

//     // Добавление элементов во второй список
//     list2.push_back(100);
//     list2.push_back(200);
//     list2.push_back(300);

//     std::cout << "List1 before swap: ";
//     list1.printNode();  // Используем новый метод print() для вывода
//     содержимого

//     std::cout << "List2 before swap: ";
//     list2.printNode();  // Используем новый метод print() для вывода
//     содержимого

//     // Выполнение swap
//     list1.swap(list2);

//     std::cout << "List1 after swap: ";
//     list1.printNode();  // Проверяем после swap

//     std::cout << "List2 after swap: ";
//     list2.printNode();  // Проверяем после swap

//     // Проверка метода push_front
//     list1.push_front(5);
//     list1.push_front(1);

//     std::cout << "List1 after push_front: ";
//     list1.printNode();  // Проверяем после push_front

//     // Проверка метода pop_front
//     list1.pop_front();  // Удаляем из начала

//     std::cout << "List1 after pop_front: ";
//     list1.printNode();  // Проверяем после pop_front

//     // Проверка метода pop_back
//     list2.pop_back();  // Удаляем из конца

//     std::cout << "List2 after pop_back: ";
//     list2.printNode();  // Проверяем после pop_back

//     // Проверка метода insert
//     auto it = list1.begin();  // Итератор на начало
//     list1.insert(it, 50);  // Вставляем в начало

//     std::cout << "List1 after insert: ";
//     list1.printNode();  // Проверяем после insert

//     // Проверка метода erase
//     list1.erase(it);  // Удаляем элемент на позиции итератора

//     std::cout << "List1 after erase: ";
//     list1.printNode();  // Проверяем после erase

//     return 0;
// }

// int main() {
//     s21::list<int> lst1{1, 2, 3, 5};
//     lst1.merge(lst1);
//         for (const auto& val : lst1) {
//         std::cout << val << " ";  // Вывод объединенного списка
//     }
//     return 0;
// }

int main() {
  // Создаем два списка
  s21::list<int> lst1{1, 2, 3};  // Первый список
  s21::list<int> lst2{6, 7, 8};  // Второй список

  std::cout << "List 1 before splice: ";
  for (const auto& val : lst1) {
    std::cout << val << " ";  // Вывод содержимого первого списка
  }
  std::cout << std::endl;

  std::cout << "List 2 before splice: ";
  for (const auto& val : lst2) {
    std::cout << val << " ";  // Вывод содержимого второго списка
  }
  std::cout << std::endl;

  // Сплайсим второй список в начало первого
  lst1.splice(lst1.begin(), lst2);

  std::cout << "List 1 after splice: ";
  for (const auto& val : lst1) {
    std::cout << val
              << " ";  // Вывод содержимого первого списка после сплайсинга
  }
  std::cout << std::endl;

  // Проверяем, что второй список пустой
  if (lst2.empty()) {
    std::cout << "List 2 is empty after splice." << std::endl;
  }

  // Сплайсинг в середину
  s21::list<int> lst3{9, 10, 11};
  auto mid = lst1.begin();
  ++mid;  // Переходим ко второму элементу

  lst1.splice(mid, lst3);

  std::cout << "List 1 after splice in the middle: ";
  for (const auto& val : lst1) {
    std::cout
        << val
        << " ";  // Вывод содержимого первого списка после второго сплайсинга
  }
  std::cout << std::endl;

  // Сплайсинг в конец
  s21::list<int> lst4{12, 13, 14};
  lst1.splice(lst1.end(), lst4);

  std::cout << "List 1 after splice at the end: ";
  for (const auto& val : lst1) {
    std::cout
        << val
        << " ";  // Вывод содержимого первого списка после третьего сплайсинга
  }
  std::cout << std::endl;

  return 0;
}