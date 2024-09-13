#include <iostream>
#include <queue>
//#include "s21_list_jenisepl.h"
#include "s21_queue.h"

int main() {
  s21::queue<int> noDuplicateQueue{
      1, 2, 3, 4, 5, 5, 4, 3, 2, 1};  // Corrected the name if it was misspelled
  // std::queue<int> noDuplicateQueueSTD;  // Standard queue does not have a
  // constructor that accepts an initializer list

  // // Adding elements to the standard queue for demonstration, since it does
  // not support initializer list std::vector<int> initVals {1, 2, 3, 4, 5, 5,
  // 4, 3, 2, 1}; for (int val : initVals) {
  //     noDuplicateQueueSTD.push(val);
  // }

  // Example usage of your insert_many_back function if needed
  noDuplicateQueue.insert_many_back(6, 7, 8);

  // Printing elements from your custom queue
  while (!noDuplicateQueue.empty()) {
    std::cout << noDuplicateQueue.front() << " ";
    noDuplicateQueue.pop();
  }
  std::cout << std::endl;

  // // Printing elements from the standard queue
  // while (!noDuplicateQueueSTD.empty()) {
  //     std::cout << noDuplicateQueueSTD.front() << " ";
  //     noDuplicateQueueSTD.pop();
  // }
  // std::cout << std::endl;

  return 0;
}