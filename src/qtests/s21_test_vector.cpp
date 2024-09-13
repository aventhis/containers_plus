#include <gtest/gtest.h>  // Подключение Google Test

#include "../s21_containers/s21_vector/s21_vector.h"  // Подключение тестируемого класса

using namespace s21;

// Тесты на конструкторы
TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, InitializerListConstructor) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.front(), 1);
  EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2(v1);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[1], 2);
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2(std::move(v1));
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v1.size(), 0);  // v1 должен быть очищен
  EXPECT_EQ(v2.back(), 3);
}

// Тесты на методы доступа
TEST(VectorTest, AtMethod) {
  s21::vector<int> v{10, 20, 30};
  EXPECT_EQ(v.at(1), 20);
  EXPECT_THROW(v.at(5), std::out_of_range);
}

// Тесты на контроль емкости
TEST(VectorTest, ReserveAndCapacity) {
  s21::vector<int> v;
  v.reserve(10);
  EXPECT_GE(v.capacity(), 10);
  v.push_back(1);
  v.push_back(2);
  EXPECT_EQ(v.size(), 2);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 2);
}

// Тесты на операторы
TEST(VectorTest, AssignmentOperator) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v1.size(), 0);  // v1 должен быть очищен
}

TEST(VectorTest, MaxSizeInt) {
  s21::vector<int> v;
  // Using the allocator to determine expected max_size
  std::allocator<int> alloc;
  auto expected_max_size = alloc.max_size();
  EXPECT_EQ(v.max_size(), expected_max_size);
}

// int main(int argc, char* argv[]) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }