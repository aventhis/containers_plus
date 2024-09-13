#include <array>  // Include for std::array
#include <iostream>

#include "s21_array.h"

int main() {
  // Создание объекта array с использованием списка инициализации
  std::array<int> myArray;
  // s21::array<int, 5> myArray1(myArray);
  // s21::array<int, 5> myMovedArray = std::move(myArray);

  // // Создание объекта std::array с использованием списка инициализации для
  // сравнения std::array<int, 5> myArray_std {1, 2, 3}; int& item2 =
  // myArray_std.at(10);
  //  std::cout << myArray_std[5] << std::endl;  // Выведет 20
  // Вывод содержимого пользовательского массива
  std::cout << "Custom array elements: ";
  // myArray.print();
  // int& item = myMovedArray.at(0);
  // item = 20;  // Изменяет элемент массива напрямую
  // std::cout << myMovedArray[0] << std::endl;  // Выведет 20
  // // Вывод содержимого стандартного массива
  std::cout << "Standard array elements: ";
  for (auto& element : myArray) {
    std::cout << element << " ";
  }
  std::cout << std::endl;

  return 0;
}
