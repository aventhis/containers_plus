#include <gtest/gtest.h>  // Подключение Google Test

// #include "../s21_containers.h"
// #include "../s21_containersplus.h"
// #include "s21_test_list.cc"
// #include "s21_test_vector.cpp"
// #include "s21_test_array.cpp"
// #include "s21_test_stack.cc"
// #include "s21_test_set.cc"
// #include "s21_test_multiset.cc"
// #include "s21_test_map.cc"
// #include "s21_test_queue.cc"

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}