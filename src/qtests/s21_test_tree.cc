#include <gtest/gtest.h>  // Подключение Google Test

#include <climits>

#include "../s21_containers/tree/s21_tree.h"
using namespace s21;

TEST(AVLTreeTest, ConstructorsDestructorsAssignmentOperators) {
  AVLTree<int, int> tree1;
  AVLTree<int, int> tree2 = tree1;
  AVLTree<int, int> tree3(std::move(tree1));

  EXPECT_NO_THROW(tree1 = tree2);
  EXPECT_NO_THROW(tree1 = std::move(tree3));
  EXPECT_EQ(tree1.size(), 0);
  EXPECT_EQ(tree2.size(), 0);
  EXPECT_EQ(tree3.size(), 0);
}

TEST(AVLTreeTest, EmptyTreeMethods) {
  AVLTree<int, int> tree;
  ASSERT_TRUE(tree.empty());
  ASSERT_EQ(tree.size(), 0);
}

TEST(AVLTreeTest, ContainsMethod) {
  AVLTree<int, int> tree;
  tree.insert({5, 50});
  tree.insert({3, 30});
  tree.insert({7, 70});

  ASSERT_TRUE(tree.contains(5));
  ASSERT_FALSE(tree.contains(8));
}

TEST(AVLTreeTest, MergeMethod) {
  AVLTree<int, int> tree1;
  tree1.insert({5, 50});
  tree1.insert({3, 30});
  tree1.insert({7, 70});

  AVLTree<int, int> tree2;
  tree2.insert({6, 60});
  tree2.insert({4, 40});
  tree2.insert({8, 80});

  tree1.merge(tree2);

  ASSERT_EQ(tree1.size(), 6);
  ASSERT_TRUE(tree1.contains(4));
  ASSERT_TRUE(tree1.contains(8));
}

TEST(AVLTreeTest, SwapMethod) {
  s21::AVLTree<int, int> tree1;
  tree1.insert({5, 50});
  tree1.insert({3, 30});
  tree1.insert({7, 70});

  s21::AVLTree<int, int> tree2;
  tree2.insert({6, 60});
  tree2.insert({4, 40});
  tree2.insert({8, 80});

  tree1.swap(tree2);

  // Проверяем размеры деревьев после swap
  ASSERT_EQ(tree1.size(), 3);
  ASSERT_EQ(tree2.size(), 3);

  // Проверяем содержимое tree1 после swap
  ASSERT_TRUE(tree1.contains(6));
  ASSERT_TRUE(tree1.contains(4));
  ASSERT_TRUE(tree1.contains(8));
  ASSERT_FALSE(tree1.contains(5));
  ASSERT_FALSE(tree1.contains(3));
  ASSERT_FALSE(tree1.contains(7));

  // Проверяем содержимое tree2 после swap
  ASSERT_TRUE(tree2.contains(5));
  ASSERT_TRUE(tree2.contains(3));
  ASSERT_TRUE(tree2.contains(7));
  ASSERT_FALSE(tree2.contains(6));
  ASSERT_FALSE(tree2.contains(4));
  ASSERT_FALSE(tree2.contains(8));
}

TEST(AVLTreeTest, EmptyTree) {
  s21::AVLTree<int, int> tree;
  ASSERT_TRUE(tree.empty());
  ASSERT_EQ(tree.size(), 0);
  ASSERT_EQ(tree.begin(), tree.end());
}

TEST(AVLTreeTest, InsertionAndSize) {
  s21::AVLTree<int, int> tree;
  tree.insert({5, 50});
  tree.insert({3, 30});
  tree.insert({7, 70});
  ASSERT_FALSE(tree.empty());
  ASSERT_EQ(tree.size(), 3);
}

TEST(AVLTreeTest, Erase) {
  s21::AVLTree<int, int> tree;
  tree.insert({5, 50});
  tree.insert({3, 30});
  tree.insert({7, 70});
  tree.erase(3);
  ASSERT_EQ(tree.size(), 2);
  ASSERT_EQ(tree.find(3), nullptr);  // Проверка, что элемент 3 удален
}

TEST(AVLTreeTest, Find) {
  s21::AVLTree<int, int> tree;
  tree.insert({5, 50});
  tree.insert({3, 30});
  tree.insert({7, 70});
  ASSERT_NE(tree.find(3), nullptr);
  ASSERT_EQ(tree.find(8), nullptr);
}

TEST(AVLTreeTest, Clear) {
  s21::AVLTree<int, int> tree;
  tree.insert({5, 50});
  tree.insert({3, 30});
  tree.insert({7, 70});
  tree.clear();
  ASSERT_TRUE(tree.empty());
  ASSERT_EQ(tree.size(), 0);
  ASSERT_EQ(tree.begin(), tree.end());
}

TEST(AVLTreeTest, IteratorOperators) {
  AVLTree<int, int> tree;
  tree.insert(std::make_pair(10, 10));
  tree.insert(std::make_pair(5, 5));
  tree.insert(std::make_pair(15, 15));
  tree.insert(std::make_pair(3, 3));
  tree.insert(std::make_pair(7, 7));
  tree.insert(std::make_pair(12, 12));
  tree.insert(std::make_pair(18, 18));

  auto it = tree.begin();
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ((*it).first, 3);

  ++it;
  EXPECT_EQ(it->first, 5);
  it++;
  EXPECT_EQ(it->first, 7);

  --it;
  EXPECT_EQ(it->first, 5);
  it--;
  EXPECT_EQ(it->first, 3);

  auto it2 = tree.begin();
  EXPECT_TRUE(it == it2);
  ++it2;
  EXPECT_TRUE(it != it2);
}

TEST(AVLTreeTest, ConstIteratorOperators) {
  AVLTree<int, int> tree;
  tree.insert(std::make_pair(10, 10));
  tree.insert(std::make_pair(5, 5));
  tree.insert(std::make_pair(15, 15));
  tree.insert(std::make_pair(3, 3));
  tree.insert(std::make_pair(7, 7));
  tree.insert(std::make_pair(12, 12));
  tree.insert(std::make_pair(18, 18));

  const AVLTree<int, int>& const_tree = tree;

  auto it = const_tree.begin();
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ((*it).first, 3);

  ++it;
  EXPECT_EQ(it->first, 5);
  it++;
  EXPECT_EQ(it->first, 7);

  --it;
  EXPECT_EQ(it->first, 5);
  it--;
  EXPECT_EQ(it->first, 3);

  auto it2 = const_tree.begin();
  EXPECT_TRUE(it == it2);
  ++it2;
  EXPECT_TRUE(it != it2);
}

TEST(AVLTreeTest, IteratorTraversal) {
  s21::AVLTree<int, int> tree;
  tree.insert(std::make_pair(10, 10));
  tree.insert(std::make_pair(5, 5));
  tree.insert(std::make_pair(15, 15));
  tree.insert(std::make_pair(3, 3));
  tree.insert(std::make_pair(7, 7));
  tree.insert(std::make_pair(12, 12));
  tree.insert(std::make_pair(18, 18));

  std::vector<int> expected_order = {3, 5, 7, 10, 12, 15, 18};
  std::vector<int> actual_order;

  for (auto it = tree.begin(); it != tree.end(); ++it) {
    actual_order.push_back(it->first);
  }

  EXPECT_EQ(expected_order, actual_order);
}

TEST(AVLTreeTest, ConstIteratorTraversal) {
  s21::AVLTree<int, int> tree;
  tree.insert(std::make_pair(10, 10));
  tree.insert(std::make_pair(5, 5));
  tree.insert(std::make_pair(15, 15));
  tree.insert(std::make_pair(3, 3));
  tree.insert(std::make_pair(7, 7));
  tree.insert(std::make_pair(12, 12));
  tree.insert(std::make_pair(18, 18));

  const AVLTree<int, int>& const_tree = tree;

  std::vector<int> expected_order = {3, 5, 7, 10, 12, 15, 18};
  std::vector<int> actual_order;

  for (auto it = const_tree.begin(); it != const_tree.end(); ++it) {
    actual_order.push_back(it->first);
  }

  EXPECT_EQ(expected_order, actual_order);
}

TEST(AVLTreeTest, CorrectHeightAndStructure) {
  s21::AVLTree<int, int> tree;
  tree.insert(std::make_pair(10, 10));
  tree.insert(std::make_pair(20, 20));
  tree.insert(std::make_pair(30, 30));
  tree.insert(std::make_pair(40, 40));
  tree.insert(std::make_pair(50, 50));
  tree.insert(std::make_pair(25, 25));

  auto root = tree.getRoot();
  EXPECT_EQ(root->value_.first, 30);
  EXPECT_EQ(root->height_, 3);

  EXPECT_EQ(root->left->value_.first, 20);
  EXPECT_EQ(root->left->height_, 2);

  EXPECT_EQ(root->right->value_.first, 40);
  EXPECT_EQ(root->right->height_, 2);

  EXPECT_EQ(root->left->left->value_.first, 10);
  EXPECT_EQ(root->left->left->height_, 1);

  EXPECT_EQ(root->left->right->value_.first, 25);
  EXPECT_EQ(root->left->right->height_, 1);

  EXPECT_EQ(root->right->right->value_.first, 50);
  EXPECT_EQ(root->right->right->height_, 1);
}

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
