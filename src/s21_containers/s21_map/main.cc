#include <iostream>
#include <map>

#include "s21_map.h"  // Замените на правильный путь к вашему заголовочному файлу
// void test_assignment_operator_move() {
//     s21::Map<std::string, int> ms21_init{{"CPU", 10}, {"GPU", 15}, {"RAM",
//     20}}; s21::Map<std::string, int> ms21_move_assigned; ms21_move_assigned =
//     std::move(ms21_init); std::cout << "Assignment operator move:" <<
//     std::endl; ms21_move_assigned.print();
// }

// void test_assignment_operator_copy() {
//     s21::Map<std::string, int> ms21_init{{"CPU", 10}, {"GPU", 15}, {"RAM",
//     20}}; s21::Map<std::string, int> ms21_copy_assigned; ms21_copy_assigned =
//     ms21_init; std::cout << "Assignment operator copy:" << std::endl;
//     ms21_copy_assigned.print();
// }

// void test_iterators() {
//     s21::Map<std::string, int> ms21{{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};
//     std::cout << "Iterator test:" << std::endl;
//     for (auto it = ms21.begin(); it != ms21.end(); ++it) {
//         std::cout << it->first << ": " << it->second << std::endl;
//     }
// }

// void test_capacity() {
//     s21::Map<std::string, int> ms21{{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};
//     std::cout << "Capacity test:" << std::endl;
//     std::cout << "Empty: " << ms21.empty() << std::endl;
//     std::cout << "Size: " << ms21.size() << std::endl;
//     std::cout << "Max size: " << ms21.max_size() << std::endl;
// }

// int main() {
//     std::map<std::string, int> m{{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};
//     s21::Map<std::string, int> ms21;

//     ms21.insert({"CPU", 10});
//     ms21.insert({"GPU", 15});
//     ms21.insert({"RAM", 20});

//     std::cout << "std::map contents:" << std::endl;
//     for (const auto& pair : m) {
//         std::cout << pair.first << ": " << pair.second << std::endl;
//     }

//     std::cout << "s21::map contents:" << std::endl;
//     ms21.print();

//     // Тестирование дефолтного конструктора
//     s21::Map<std::string, int> ms21_default;
//     std::cout << "Default constructor:" << std::endl;
//     ms21_default.print();

//     // Тестирование конструктора с инициализатором
//     s21::Map<std::string, int> ms21_init{{"CPU", 10}, {"GPU", 15}, {"RAM",
//     20}}; std::cout << "Initializer list constructor:" << std::endl;
//     ms21_init.print();

//     // Тестирование копирующего конструктора
//     s21::Map<std::string, int> ms21_copy(ms21_init);
//     std::cout << "Copy constructor:" << std::endl;
//     ms21_copy.print();

//     // Тестирование конструктора перемещения
//     s21::Map<std::string, int> ms21_move(std::move(ms21_init));
//     std::cout << "Move constructor:" << std::endl;
//     ms21_move.print();

//     std::cout << "Testing assignment operator move:" << std::endl;
//     test_assignment_operator_move();
//     std::cout << std::endl;

//     std::cout << "Testing assignment operator copy:" << std::endl;
//     test_assignment_operator_copy();
//     std::cout << std::endl;

//     std::cout << "Testing iterators:" << std::endl;
//     test_iterators();
//     std::cout << std::endl;

//     std::cout << "Testing capacity:" << std::endl;
//     test_capacity();
//     std::cout << std::endl;

//     s21::Map<std::string, int> ms211;
//     std::cout << "Modifiers test:" << std::endl;

//     ms211.insert({"CPU", 10});
//     ms211.insert({"GPU", 15});
//     ms211.insert({"RAM", 20});

//     std::cout << "After clear:" << std::endl;
//     ms21.clear();
//     ms21.print();

//     s21::Map<std::string, int> ms21_2{{"SSD", 30}, {"HDD", 45}};
//     std::cout << "After swap:" << std::endl;
//     ms211.swap(ms21_2);
//     ms211.print();
//     ms21_2.print();

//     s21::Map<std::string, int> ms21_3{{"USB", 50}, {"HDMI", 55}};
//     std::cout << "After merge:" << std::endl;
//     ms211.merge(ms21_3);
//     ms211.print();
//     ms21_3.print();

//     std::cout << "Before erase:" << std::endl;
//     ms211.print();
//     std::cout << "After erase:" << std::endl;
//     ms211.erase(ms211.begin());
//     ms211.print();

//     std::cout << "at" << std::endl;
//     auto t = ms211.at("USB");
//     std::cout << t << std::endl;

//     s21::Map<std::string, int> ms211111;

//     // Вставка элементов
//     ms211111["CPU"] = 10;
//     ms211111["GPU"] = 15;

//     // Доступ к элементам
//     std::cout << "CPU: " << ms211111["CPU"] << std::endl;  // Вывод: 10
//     std::cout << "GPU: " << ms211111["GPU"] << std::endl;  // Вывод: 15

//     // Вставка нового элемента по умолчанию
//     std::cout << "RAM: " << ms211111["RAM"] << std::endl;  // Вывод: 0
//     (значение по умолчанию)

//     // Изменение значения элемента
//     ms211111["RAM"] = 20;
//     std::cout << "RAM: " << ms211111["RAM"] << std::endl << std::endl;  //
//     Вывод: 20

//     ms211111.insert({"RAM", 2000 });
//     ms211111.print();

//     s21::Map<std::string, int> m11111{{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};
//     m11111.insert({"RAM", 20}); // Пара ключ-значение
//     m11111.print();

//     bool res = m11111.contains("CPU");
//     std::cout << res << std::endl;

//     s21::Map<int, std::string> map;
//     map[1] = "one";
//     map[2] = "two";
//     map[3] = "three";

//     std::cout << std::endl;
//     map.print();

//     return 0;
// }

// int main() {
//     // Создание карты и заполнение её значениями
//     s21::Map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

//     // Вывод элементов до удаления
//     std::cout << "Elements before erasing:\n";
//     for (const auto& pair : map) {
//         std::cout << "Key: " << pair.first << ", Value: " << pair.second <<
//         std::endl;
//     }

//     // Удаление элемента с ключом 2
//     auto it = map.find(2);
//     if (it != map.end()) {
//         std::cout << "Value of element with key 2 before erasing: " <<
//         it->second << std::endl; map.erase(it);
//     } else {
//         std::cout << "Element with key 2 not found\n";
//     }

//     // Вывод значения map.find(2) и map.end()
//     std::cout << "\nValue of map.find(2) after erasing: ";
//     auto find_result = map.find(2);
//     if (find_result != map.end()) {
//         std::cout << "Key: " << find_result->first << ", Value: " <<
//         find_result->second << std::endl;
//     } else {
//         std::cout << "Not found\n";
//     }
//     std::cout << "Value of map.end(): " << (map.end() == typename
//     s21::Map<int, std::string>::iterator()) << std::endl;

//     // Вывод элементов после удаления
//     std::cout << "\nElements after erasing:\n";
//     for (const auto& pair : map) {
//         std::cout << "Key: " << pair.first << ", Value: " << pair.second <<
//         std::endl;
//     }

//     return 0;
// }

int main() {
  // Пример использования insert_many с контейнером Map
  s21::Map<int, std::string> my_map;
  auto results_map =
      my_map.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"),
                         std::make_pair(3, "three"));

  // Вывод результатов
  std::cout << "Results of insert_many:\n";
  for (const auto& result : results_map) {
    std::cout << "Key: " << (*result.first).first
              << ", Value: " << (*result.first).second
              << ", Inserted: " << result.second << std::endl;
  }

  return 0;
}