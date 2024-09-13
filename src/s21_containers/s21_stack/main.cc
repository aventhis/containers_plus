// #include <iostream>
// #include <stack>
// //#include "s21_list_jenisepl.h"
// #include "s21_stack.h"

#include <iostream>
#include <stack>
#include <vector>

#include "s21_stack.h"  // make sure this path is correct

int main() {
  // Create an s21::stack with an initializer list (assuming your custom stack
  // supports this)
  s21::stack<int> noDuplicateQueue{8, 5, 4, 1, 2, 3, 4, 5};

  // Initialize a standard std::stack using a std::vector and manual pushing
  std::vector<int> initVals{1, 2, 3, 4, 5};
  std::stack<int> noDuplicateQueueSTD;
  for (int val : initVals) {
    noDuplicateQueueSTD.push(val);
  }
  noDuplicateQueue.insert_many_front(8, 5, 4);
  // Printing elements from your custom stack
  std::cout << "Custom Stack Output:\n";
  while (!noDuplicateQueue.empty()) {
    std::cout << noDuplicateQueue.top() << " ";
    noDuplicateQueue.pop();
  }
  std::cout << std::endl;

  // Printing elements from the standard stack
  std::cout << "Standard Stack Output:\n";
  while (!noDuplicateQueueSTD.empty()) {
    std::cout << noDuplicateQueueSTD.top() << " ";
    noDuplicateQueueSTD.pop();
  }
  std::cout << std::endl;

  return 0;
}
