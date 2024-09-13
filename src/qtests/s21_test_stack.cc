#include <gtest/gtest.h>

#include "../s21_containers/s21_stack/s21_stack.h"

using namespace s21;

TEST(StackTest, DefaultConstructor) {
  stack<int> mystack;
  EXPECT_TRUE(mystack.empty());
  EXPECT_EQ(mystack.size(), 0);
}

TEST(StackTest, Top) {
  stack<int> mystack;
  mystack.push(1);
  EXPECT_EQ(mystack.top(), 1);
}

TEST(StackTest, SizeAfterPush) {
  stack<int> mystack;
  mystack.push(1);
  mystack.push(2);
  mystack.push(3);
  EXPECT_EQ(mystack.size(), 3);
}

TEST(StackTest, SizeAfterPop) {
  stack<int> mystack;
  mystack.push(1);
  mystack.push(2);
  mystack.push(3);
  mystack.pop();
  EXPECT_EQ(mystack.size(), 2);
}

TEST(StackTest, EmptyAfterPush) {
  stack<int> mystack;
  mystack.push(1);
  EXPECT_FALSE(mystack.empty());
}

TEST(StackTest, EmptyAfterPop) {
  stack<int> mystack;
  mystack.push(1);
  mystack.pop();
  EXPECT_TRUE(mystack.empty());
}

TEST(StackTest, PushPopMultiple) {
  stack<int> mystack;
  mystack.push(1);
  mystack.push(2);
  mystack.push(3);
  mystack.pop();
  mystack.push(4);
  EXPECT_EQ(mystack.top(), 4);
}

TEST(StackTest, TopOnEmptyStack) {
  stack<int> mystack;
  EXPECT_THROW(mystack.top(), std::range_error);
}

TEST(StackTest, PushPop) {
  stack<int> mystack;
  mystack.push(1);
  EXPECT_EQ(mystack.top(), 1);
  mystack.pop();
  EXPECT_TRUE(mystack.empty());
}

TEST(StackTest, TopOnEmptyStackAfterPops) {
  stack<int> mystack;
  mystack.push(1);
  mystack.pop();
  EXPECT_THROW(mystack.top(), std::range_error);
}

TEST(StackTest, TopAfterPushPop) {
  stack<int> mystack;
  mystack.push(1);
  mystack.push(2);
  mystack.push(3);
  mystack.pop();
  mystack.pop();
  EXPECT_EQ(mystack.top(), 1);
}

TEST(StackTest, ContentAfterPushPop) {
  stack<int> mystack;
  mystack.push(1);
  mystack.push(2);
  mystack.push(3);
  mystack.pop();
  mystack.push(4);
  mystack.pop();
  EXPECT_EQ(mystack.top(), 2);
  EXPECT_EQ(mystack.size(), 2);
}

// int main(int argc, char* argv[]) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
