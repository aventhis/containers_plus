#ifndef CPP2_S21_CONTAINERS_
#define CPP2_S21_CONTAINERS_

#include "../s21_container.h"

namespace s21 {

template <typename K, typename V>
class AVLTree {
 public:
  using key_type = K;
  using mapped_type = V;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  // Конструкторы, деструктор и операторы присваивания
  AVLTree() noexcept;
  AVLTree(const AVLTree& s);
  AVLTree(AVLTree&& s) noexcept;
  ~AVLTree();
  AVLTree& operator=(const AVLTree& s);
  AVLTree& operator=(AVLTree&& s) noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Дополнительные методы
  void merge(AVLTree& other);
  void swap(AVLTree& other);
  bool contains(const key_type& key) const noexcept;

 protected:
  // Структура Node объявлена здесь
  struct Node {
    Node* left;
    Node* right;
    Node* parent;
    value_type value_;
    int height_;

    Node(const_reference value = value_type(), Node* left = nullptr,
         Node* right = nullptr, Node* parent = nullptr)
        : left(left), right(right), parent(parent), value_(value), height_(1) {}
  };
  // key_type key = node->value_.first; Это дает вам доступ к ключу, хранящемуся
  // в узле.
  Node* root_;  // Указатель на корень AVL-дерева

  Node* insert_(Node* node, const value_type& value, Node* parent);
  Node* erase_(Node* node, const key_type& key);
  // доп методы для вставки и удаления
  void copyValue(value_type& dest, const value_type& src);
  void calcHeight(Node* node);
  int height(Node* node) const;
  int getBalance(Node* node) const;
  Node* rightRotate(Node* y);
  Node* leftRotate(Node* x);
  Node* balanceNode(Node* node);
  // внутренний contains find
  Node* findImpl(Node* node, const key_type& key) const noexcept;
  bool Contains_(const Node* node, const K& key) const noexcept;

  Node* CopyTree(Node* node, Node* parent);
  void ClearTree(Node* node);

 public:
  //  Методы вставки, удаления и поиска
  Node* insert(const_reference key) {
    root_ = insert_(root_, key, nullptr);
    return root_;
  };

  Node* erase(const key_type& key) {
    root_ = erase_(root_, key);
    return root_;
  };

  Node* find(const key_type& key) const noexcept {
    return findImpl(root_, key);
  };
  void clear() noexcept {
    ClearTree(root_);
    root_ = nullptr;
  };

  Node* getRoot() const { return root_; };

  class AvlTreeConstIterator {
   public:
    using Node = typename s21::AVLTree<K, V>::Node;
    using value_type = typename s21::AVLTree<K, V>::value_type;

   protected:
    const Node* current_node_;
    const AVLTree<K, V>* tree_;  // Добавляем указатель на объект AVLTree

   public:
    AvlTreeConstIterator() noexcept : current_node_(nullptr) {}
    AvlTreeConstIterator(const Node* node) noexcept : current_node_(node) {}
    const value_type& operator*() const { return current_node_->value_; }
    const value_type* operator->() const { return &(current_node_->value_); }
    bool operator==(const AvlTreeConstIterator& other) const {
      return current_node_ == other.current_node_;
    }
    bool operator!=(const AvlTreeConstIterator& other) const {
      return current_node_ != other.current_node_;
    }

    AvlTreeConstIterator& operator++() {
      if (current_node_) {
        if (current_node_->right) {
          current_node_ = tree_->findMin(current_node_->right);
        } else {
          const Node* parent = current_node_->parent;
          while (parent && current_node_ == parent->right) {
            current_node_ = parent;
            parent = parent->parent;
          }
          current_node_ = parent;
        }
      }
      return *this;
    };

    AvlTreeConstIterator operator++(int) {
      AvlTreeConstIterator tmp(*this);
      ++(*this);
      return tmp;
    };

    AvlTreeConstIterator& operator--() {
      if (current_node_) {
        if (current_node_->left) {
          current_node_ = tree_->findMax(current_node_->left);
        } else {
          const Node* parent = current_node_->parent;
          while (parent && current_node_ == parent->left) {
            current_node_ = parent;
            parent = parent->parent;
          }
          current_node_ = parent;
        }
      }
      return *this;
    };

    AvlTreeConstIterator operator--(int) {
      AvlTreeConstIterator tmp(*this);
      --(*this);
      return tmp;
    };
  };

  class AvlTreeIterator : public AvlTreeConstIterator {
   public:
    using Node = typename s21::AVLTree<K, V>::Node;
    using value_type = typename s21::AVLTree<K, V>::value_type;

    using AvlTreeConstIterator::AvlTreeConstIterator;

    value_type& operator*() {
      return const_cast<value_type&>(AvlTreeConstIterator::operator*());
    };
    value_type* operator->() {
      return const_cast<value_type*>(AvlTreeConstIterator::operator->());
    };

    AvlTreeIterator& operator++() {
      AvlTreeConstIterator::operator++();
      return *this;
    };

    AvlTreeIterator operator++(int) {
      AvlTreeIterator tmp(*this);
      AvlTreeConstIterator::operator++(0);
      return tmp;
    };

    AvlTreeIterator& operator--() {
      AvlTreeConstIterator::operator--();
      return *this;
    };

    AvlTreeIterator operator--(int) {
      AvlTreeIterator tmp(*this);
      AvlTreeConstIterator::operator--(0);
      return tmp;
    };
  };

  using const_iterator = AvlTreeConstIterator;
  using iterator = AvlTreeIterator;

  iterator begin() {
    if (!root_) {
      return iterator(nullptr);
    }
    Node* tmp = root_;
    while (tmp->left) {
      tmp = tmp->left;
    }
    return iterator(tmp);
  };

  const_iterator begin() const {
    if (!root_) {
      return const_iterator(nullptr);
    }
    Node* tmp = root_;
    while (tmp->left) {
      tmp = tmp->left;
    }
    return const_iterator(tmp);
  };

  iterator end() { return iterator(nullptr); };

  const_iterator end() const { return const_iterator(nullptr); };

  Node* findMin(Node* node) const {
    while (node && node->left) {
      node = node->left;
    }
    return node;
  };

  Node* findMax(Node* node) const {
    while (node && node->right) {
      node = node->right;
    }
    return node;
  };
};

}  // namespace s21

/***********************************************************************
 ***********************************************************************
 ********************  КОНСТРУКТОРЫ И ДЕСТРУКТОР  **********************
 ***********************************************************************
 **********************************************************************/

template <typename K, typename V>
s21::AVLTree<K, V>::AVLTree() noexcept : root_(nullptr){};

template <typename K, typename V>
s21::AVLTree<K, V>::AVLTree(const AVLTree<K, V>& s) : root_(nullptr) {
  root_ = CopyTree(s.root_, nullptr);
};

template <typename K, typename V>
s21::AVLTree<K, V>::AVLTree(AVLTree&& s) noexcept {
  root_ = s.root_;
  s.root_ = nullptr;
};

template <typename K, typename V>
s21::AVLTree<K, V>::~AVLTree() {
  if (root_ != nullptr) {
    clear();
  }
};

template <typename K, typename V>
s21::AVLTree<K, V>& s21::AVLTree<K, V>::operator=(const AVLTree& s) {
  if (this != &s) {
    clear();
    root_ = CopyTree(s.root_, nullptr);
  }
  return *this;
};

template <typename K, typename V>
s21::AVLTree<K, V>& s21::AVLTree<K, V>::operator=(AVLTree&& s) noexcept {
  clear();
  root_ = s.root_;
  s.root_ = nullptr;
  return *this;
};

/***********************************************************************
 ***********************************************************************
 *******************   CopyTree и  ClearTree   *************************
 **************************** ***** ************************************
 **********************************************************************/

template <typename K, typename V>
typename s21::AVLTree<K, V>::Node* s21::AVLTree<K, V>::CopyTree(Node* node,
                                                                Node* parent) {
  if (!node) {
    return nullptr;
  }
  Node* new_node = new Node(node->value_, nullptr, nullptr, parent);
  new_node->left = CopyTree(node->left, new_node);
  new_node->right = CopyTree(node->right, new_node);
  return new_node;
};

template <typename K, typename V>
void s21::AVLTree<K, V>::ClearTree(Node* node) {
  if (node) {
    ClearTree(node->left);
    ClearTree(node->right);

    if (node->parent) {
      if (node->parent->left == node) {
        node->parent->left = nullptr;
      } else {
        node->parent->right = nullptr;
      }
    }
    delete node;
  }
  if (node && node == root_) {
    root_ = nullptr;
  }
};

/***********************************************************************
 ***********************************************************************
 **********************  empty  size max_size  *************************
 ***********************************************************************
 **********************************************************************/

template <typename K, typename V>
bool s21::AVLTree<K, V>::empty() const noexcept {
  return root_ == nullptr;
};

template <typename K, typename V>
typename s21::AVLTree<K, V>::size_type s21::AVLTree<K, V>::size()
    const noexcept {
  size_type counter = 0;
  if (root_) {
    for (auto it = begin(); it != end(); ++it) {
      ++counter;
    }
  }
  return counter;
}

template <typename K, typename V>
typename s21::AVLTree<K, V>::size_type s21::AVLTree<K, V>::max_size()
    const noexcept {
  return std::numeric_limits<size_type>::max();
}

/***********************************************************************
 ***********************************************************************
 ******************  calcHeight и getBalance   *************************
 *****************   rightRotate и leftRotate   ************************
 **********************************************************************/

template <typename K, typename V>
void s21::AVLTree<K, V>::calcHeight(Node* node) {
  if (node) {
    int leftHeight = node->left ? node->left->height_ : 0;
    int rightHeight = node->right ? node->right->height_ : 0;
    node->height_ = 1 + std::max(leftHeight, rightHeight);
  }
};

template <typename K, typename V>
int s21::AVLTree<K, V>::getBalance(Node* node) const {
  if (!node) return 0;
  int leftHeight = node->left ? node->left->height_ : 0;
  int rightHeight = node->right ? node->right->height_ : 0;
  return leftHeight - rightHeight;
};

template <typename K, typename V>
typename s21::AVLTree<K, V>::Node* s21::AVLTree<K, V>::rightRotate(Node* y) {
  Node* x = y->left;
  Node* temp = x->right;
  x->right = y;
  y->left = temp;
  if (temp) {
    temp->parent = y;
  }
  if (y->parent) {
    if (y->parent->left == y) {
      y->parent->left = x;
    } else {
      y->parent->right = x;
    }
  } else {
    root_ = x;
  }
  x->parent = y->parent;
  y->parent = x;
  calcHeight(y);
  calcHeight(x);
  return x;
}

template <typename K, typename V>
typename s21::AVLTree<K, V>::Node* s21::AVLTree<K, V>::leftRotate(Node* x) {
  Node* y = x->right;
  Node* temp = y->left;
  y->left = x;
  x->right = temp;
  if (temp) {
    temp->parent = x;
  }
  if (x->parent) {
    if (x->parent->left == x) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
  } else {
    root_ = y;
  }
  y->parent = x->parent;
  x->parent = y;
  calcHeight(x);
  calcHeight(y);
  return y;
}

/***********************************************************************
 ***********************************************************************
 ***********************   Insert и  Erase   ***************************
 ***********************************************************************
 **********************************************************************/

template <typename K, typename V>
typename s21::AVLTree<K, V>::Node* s21::AVLTree<K, V>::insert_(
    Node* node, const_reference value, Node* parent) {
  // Шаг 1: Найти место для вставки нового узла.
  if (!node) {
    // Шаг 2: Вставить новый узел.
    node = new Node(value, nullptr, nullptr, parent);
    node->height_ = 1;
    return node;
  }

  // Сама вставка узла влево или вправо через if else
  if (value.first < node->value_.first) {
    node->left = insert_(node->left, value, node);
  } else if (value.first >= node->value_.first) {
    node->right = insert_(node->right, value, node);
  } else {
    return node;
  }
  // Шаг 3: Обновить высоту текущего узла.
  calcHeight(node);
  // Шаг 4: Балансировка узла.
  node = balanceNode(node);

  return node;
}

template <typename K, typename V>
typename s21::AVLTree<K, V>::Node* s21::AVLTree<K, V>::erase_(
    Node* node, const key_type& key) {
  if (!node) {
    return nullptr;
  }
  if (key < node->value_.first) {
    node->left = erase_(node->left, key);
  } else if (key > node->value_.first) {
    node->right = erase_(node->right, key);
  } else {
    if (!node->left || !node->right) {
      Node* temp = node->left ? node->left : node->right;
      if (!temp) {
        temp = node;
        delete node;  // Освобождаем память для удаляемого узла
        node = nullptr;
      } else {
        node->left = temp->left;
        node->right = temp->right;
        node->parent = temp->parent;
        copyValue(node->value_, temp->value_);
        node->height_ = temp->height_;
        delete temp;
      }
    } else {
      Node* temp = findMin(node->right);
      copyValue(node->value_, temp->value_);
      node->right = erase_(node->right, key);
    }
  }
  if (!node) {
    return node;
  }
  calcHeight(node);
  node = balanceNode(node);
  return node;
};

template <typename K, typename V>
void s21::AVLTree<K, V>::copyValue(value_type& dest, const value_type& src) {
  // Копируем значение из src в dest
  // Для ключа ничего не делаем, так как он const и не может быть изменен
  const_cast<K&>(dest.first) =
      src.first;  // Используем const_cast для изменения ключа
  dest.second = src.second;  // Копируем значение
}

template <typename K, typename V>
typename s21::AVLTree<K, V>::Node* s21::AVLTree<K, V>::balanceNode(Node* node) {
  int balance = getBalance(node);
  if (balance > 1) {
    if (getBalance(node->left) < 0) {
      node->left = leftRotate(node->left);
    }
    node = rightRotate(node);
  } else if (balance < -1) {
    if (getBalance(node->right) > 0) {
      node->right = rightRotate(node->right);
    }
    node = leftRotate(node);
  }
  return node;
}

/***********************************************************************
 ***********************************************************************
 ***************************   contains   ******************************
 ***********************************************************************
 **********************************************************************/

template <typename K, typename V>
bool s21::AVLTree<K, V>::contains(const K& key) const noexcept {
  return Contains_(root_, key);  // Начинаем поиск с корня
};

template <typename K, typename V>
bool s21::AVLTree<K, V>::Contains_(const Node* node,
                                   const K& key) const noexcept {
  if (!node) return false;

  if (key == node->value_.first) {
    return true;
  } else if (key < node->value_.first) {
    return Contains_(node->left, key);
  } else {
    return Contains_(node->right, key);
  }
  return false;  // Добавленный оператор return для избежания предупреждения
                 // компилятора
};

/***********************************************************************
 ***********************************************************************
 ***********************   merge и swap  *******************************
 ***********************************************************************
 **********************************************************************/

template <typename K, typename V>
void s21::AVLTree<K, V>::merge(AVLTree& other) {
  // Объединяем деревья, вставляя узлы из второго дерева в первое
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
  // Очищаем второе дерево
  other.clear();
};

template <typename K, typename V>
void s21::AVLTree<K, V>::swap(AVLTree& other) {
  // Обмениваем содержимое двух деревьев
  std::swap(root_, other.root_);
};

/***********************************************************************
 ***********************************************************************
 **************************** ********** *******************************
 ***************************   findImpl   ******************************
 **********************************************************************/

template <typename K, typename V>
typename s21::AVLTree<K, V>::Node* s21::AVLTree<K, V>::findImpl(
    Node* node, const key_type& key) const noexcept {
  if (!node) return nullptr;
  if (key == node->value_.first) return node;
  if (key < node->value_.first) return findImpl(node->left, key);
  return findImpl(node->right, key);
};

#endif