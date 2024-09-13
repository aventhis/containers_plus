#include <iostream>
#include <vector>

#include "s21_vector.h"

// int main() {

//     std::vector<int> stdVector {1, 2, 3};
//     // s21::vector<int> s21Vector {1, 2, 3};

//     // std::vector<int> stdVector1(5);
//     // s21::vector<int> s21Vector1(5);

//     // stdVector.insert(stdVector.begin() + 2, 3);
//     // s21Vector.insert(s21Vector.begin() + 2, 3);
//     auto it = stdVector.insert_many(stdVector.begin() + 3, 4, 5, 6);

//     for (auto& element : stdVector) {
//         std::cout << element << " ";
//     }
//     // std::cout << stdVector.size() << stdVector.capacity() << std::endl;
//     // s21Vector.print();
//     //     std::cout << s21Vector.size() << s21Vector.capacity() <<
//     std::endl;

//     return 0;
// }

int main() {
  s21::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.insert_many_back(1, 4, 5, 6);

  vec.print();  // Должен вывести: 1 4 5 6 2 3

  return 0;
}
