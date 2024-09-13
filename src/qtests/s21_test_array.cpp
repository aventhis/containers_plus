#include <gtest/gtest.h>  // Подключение Google Test

#include "../s21_containers/s21_array/s21_array.h"  // Подключение тестируемого класса

using namespace s21;  // Для удобства использования классов из пространства имен
                      // s21

// Тест для конструктора по умолчанию
TEST(ArrayTest, InitializesWithDefaultValues) {
  s21::array<int, 5> myArray;
  for (auto& element : myArray) {
    EXPECT_EQ(element, 0);
  }
}

// Тест для конструктора по умолчанию
TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  for (int element : arr) {
    EXPECT_EQ(element, 0);
  }
}

// Тест для конструктора инициализации
TEST(ArrayTest, InitializerListConstructor) {
  s21::array<int, 5> arr{1, 2, 3};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 0);
  EXPECT_EQ(arr[4], 0);
}

// Тест для конструктора копирования
TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 5> arr1{1, 2, 3};
  s21::array<int, 5> arr2(arr1);
  EXPECT_EQ(arr2[2], 3);
}

// Тест для конструктора перемещения
TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 5> arr1{1, 2, 3};
  s21::array<int, 5> arr2(std::move(arr1));
  EXPECT_EQ(arr2[2], 3);
}

// Тест для оператора присваивания перемещением
TEST(ArrayTest, MoveAssignment) {
  s21::array<int, 5> arr1{1, 2, 3};
  s21::array<int, 5> arr2 = std::move(arr1);
  EXPECT_EQ(arr2[2], 3);
}

// Тест для метода at с корректным доступом
TEST(ArrayTest, AtWithValidIndex) {
  s21::array<int, 5> arr{1, 2, 3};
  EXPECT_EQ(arr.at(2), 3);
}

// Тест для метода at с некорректным доступом
TEST(ArrayTest, AtWithInvalidIndex) {
  s21::array<int, 5> arr{1, 2, 3};
  EXPECT_THROW(arr.at(5), std::out_of_range);
}

// Тест для метода front и back
TEST(ArrayTest, FrontAndBack) {
  s21::array<int, 5> arr{1, 2, 3};
  EXPECT_EQ(arr.front(), 1);
  EXPECT_EQ(arr.back(), 3);
}

// Тест для итераторов begin и end
TEST(ArrayTest, Iterators) {
  s21::array<int, 5> arr{1, 2, 3};
  int sum = 0;
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 6);
}

// Тест для метода fill
TEST(ArrayTest, Fill) {
  s21::array<int, 5> arr;
  arr.fill(5);
  for (auto element : arr) {
    EXPECT_EQ(element, 5);
  }
}

// Тест для метода swap
TEST(ArrayTest, Swap) {
  s21::array<int, 5> arr1{1, 2, 3};
  s21::array<int, 5> arr2{4, 5, 6};
  arr1.swap(arr2);
  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr2[0], 1);
}

TEST(ArrayTest, Empty) {
  s21::array<int, 0> emptyArray;
  EXPECT_TRUE(emptyArray.empty());

  s21::array<int, 5> nonEmptyArray;
  EXPECT_FALSE(nonEmptyArray.empty());
}

TEST(ArrayTest, Size) {
  s21::array<int, 5> myArray;
  EXPECT_EQ(myArray.size(), 5);

  s21::array<int, 10> myArray10;
  EXPECT_EQ(myArray10.size(), 10);
}

TEST(ArrayTest, MaxSizeInt) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.max_size(), 5);
}

// int main(int argc, char* argv[]) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }