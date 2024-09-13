#include <iostream>
#include <list>
//#include "s21_list_jenisepl.h"
#include "s21_list.h"

int main() {
  s21::list<int> noDuplicateList{1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
  std::list<int> noDuplicateListSTD{1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
  // s21::list<int> list1{0, 6, 1, 3, 5, 21};
  // s21::list<int> list1;
  // s21::list<int> list1 = {1, 2, 3, 4, 5};
  // s21::list<int> list1 = {21, 2, 10, 7, 4, 5};
  // auto it = list1.begin();
  //++it; // Перемещаем итератор на второй элемент списка

  // Вы можете использовать const_iterator здесь, если ваш список поддерживает
  // это s21::list<int>::const_iterator cit = list1.begin(); int middle =
  // list1.size()/2; std::cout << "middle: "<< middle << std::endl;
  noDuplicateList.unique();  // Перемещаем все элементы из list2 в list1,
                             // начиная с позиции it
  noDuplicateListSTD.unique();  // Перемещаем все элементы из list2 в list1,
                                // начиная с позиции it
  for (auto it = noDuplicateList.begin(); it != noDuplicateList.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  for (auto it = noDuplicateListSTD.begin(); it != noDuplicateListSTD.end();
       ++it) {
    std::cout << *it << " ";
  }

  return 0;
}