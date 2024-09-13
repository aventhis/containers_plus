#include <gtest/gtest.h>

#include "../s21_containers/s21_queue/s21_queue.h"

using namespace s21;

TEST(QueueTest, DefaultConstructor) {
  queue<int> myqueue;
  EXPECT_TRUE(myqueue.empty());
  EXPECT_EQ(myqueue.size(), 0);
}

TEST(QueueTest, InitializerListConstructor) {
  queue<int> myqueue({1, 2, 3});
  EXPECT_EQ(myqueue.size(), 3);
  EXPECT_EQ(myqueue.front(), 1);
  EXPECT_EQ(myqueue.back(), 3);
}

TEST(QueueTest, PushPop) {
  queue<int> myqueue;
  myqueue.push(1);
  EXPECT_EQ(myqueue.front(), 1);
  EXPECT_EQ(myqueue.back(), 1);
  myqueue.pop();
  EXPECT_TRUE(myqueue.empty());
}

TEST(QueueTest, FrontBackAfterPush) {
  queue<int> myqueue;
  myqueue.push(1);
  myqueue.push(2);
  myqueue.push(3);
  EXPECT_EQ(myqueue.front(), 1);
  EXPECT_EQ(myqueue.back(), 3);
}

TEST(QueueTest, SizeAfterPushPop) {
  queue<int> myqueue;
  myqueue.push(1);
  myqueue.push(2);
  myqueue.push(3);
  myqueue.pop();
  EXPECT_EQ(myqueue.size(), 2);
}

TEST(QueueTest, EmptyAfterPushPop) {
  queue<int> myqueue;
  myqueue.push(1);
  EXPECT_FALSE(myqueue.empty());
  myqueue.pop();
  EXPECT_TRUE(myqueue.empty());
}

TEST(QueueTest, Swap) {
  queue<int> myqueue1({1, 2, 3});
  queue<int> myqueue2({4, 5, 6});
  myqueue1.swap(myqueue2);
  EXPECT_EQ(myqueue1.size(), 3);
  EXPECT_EQ(myqueue1.front(), 4);
  EXPECT_EQ(myqueue1.back(), 6);
  EXPECT_EQ(myqueue2.size(), 3);
  EXPECT_EQ(myqueue2.front(), 1);
  EXPECT_EQ(myqueue2.back(), 3);
}
