#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#include <functional>  // std::less
#include <utility>

#include "../s21_vector/s21_vector.h"
#include "../tree/s21_tree.h"

namespace s21 {
template <typename Key>
class multiset : public AVLTree<Key, Key> {
 private:
  using AVLTree<Key, Key>::Node;  // Используем Node из AVLTree

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  using iterator = typename AVLTree<Key, Key>::iterator;
  using const_iterator = typename AVLTree<Key, Key>::const_iterator;

  using AVLTree<Key, Key>::AVLTree;  // Наследование конструкторов

  // Дефолтный конструктор
  multiset() : AVLTree<Key, Key>(){};

  // Конструктор инициализации
  multiset(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  // Конструктор копирования
  multiset(const multiset& s) : AVLTree<Key, Key>(s){};

  // Конструктор перемещения
  multiset(multiset&& s) noexcept : AVLTree<Key, Key>(std::move(s)){};

  // Деструктор
  ~multiset() = default;

  // Оператор перемещения
  multiset& operator=(multiset&& s) noexcept;
  multiset& operator=(const multiset& s) noexcept;

  using AVLTree<Key, Key>::begin;
  using AVLTree<Key, Key>::end;
  using AVLTree<Key, Key>::empty;
  using AVLTree<Key, Key>::size;
  using AVLTree<Key, Key>::max_size;
  using AVLTree<Key, Key>::clear;
  using AVLTree<Key, Key>::swap;
  using AVLTree<Key, Key>::merge;

  bool contains(const Key& key) const noexcept {
    return containsImpl(this->root_, key);
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    auto node = insertAdapted(this->root_, value, nullptr);
    this->root_ = node;  // Обновление корня дерева, если это необходимо
    return {this->find(value), true};
  }

  void erase(iterator pos) {
    if (pos != this->end()) {
      AVLTree<Key, Key>::erase(pos->first);  // Извлекаем ключ из пары
    }
  }

  iterator find(const key_type& key) {
    auto node = AVLTree<Key, Key>::find(key);
    return node ? iterator(node) : this->end();
  }

  size_type count(const Key& key) {
    size_type count = 0;
    if (size() == 0) return 0;
    auto it = find(key);
    if (it == end()) {
      return 0;
    }
    for (; it != end(); ++it) {
      if (it->first == key) {
        count++;
      }
    }
    return count;
  };

  std::pair<iterator, iterator> equal_range(const Key& key) {
    // 1. Находит первый элемент, который >= key
    iterator first = this->lower_bound(key);

    // 2. Находит первый элемент, который > key
    iterator last = this->upper_bound(key);

    // 3. Возвращаем пару итераторов
    return std::make_pair(first, last);
  }

  iterator lower_bound(const Key& key) {
    auto it = this->begin();
    while (it != this->end() && it->first < key) {
      ++it;
    }
    return it;
  }

  iterator upper_bound(const Key& key) {
    auto it = this->begin();
    while (it != this->end() && it->first <= key) {
      ++it;
    }
    return it;
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    vector<std::pair<iterator, bool>> result;

    (result.push_back(insert(std::forward<value_type>(args))), ...);
    return result;
  }

 private:
  bool containsImpl(const typename AVLTree<Key, Key>::Node* node,
                    const Key& key) const noexcept {
    if (!node) return false;  // Если узел пустой, возвращаем false

    if (key == node->value_.first) {
      return true;  // Элемент найден
    } else if (key < node->value_.first) {
      return node->left
                 ? containsImpl(node->left, key)
                 : false;  // Поиск в левом поддереве, если оно существует
    } else {
      return node->right
                 ? containsImpl(node->right, key)
                 : false;  // Поиск в правом поддереве, если оно существует
    }
  }

  typename AVLTree<Key, Key>::Node* insertAdapted(
      typename AVLTree<Key, Key>::Node* node, const value_type& value,
      typename AVLTree<Key, Key>::Node* parent) {
    return AVLTree<Key, Key>::insert_(node, std::make_pair(value, value),
                                      parent);
  }
};  // class multiset

}  // namespace s21

// Оператор перемещения
template <typename Key>
s21::multiset<Key>& s21::multiset<Key>::operator=(multiset&& s) noexcept {
  AVLTree<Key, Key>::operator=(std::move(s));
  return *this;
}

template <typename Key>
s21::multiset<Key>& s21::multiset<Key>::operator=(const multiset& s) noexcept {
  if (this != &s) {
    AVLTree<Key, Key>::operator=(s);
  }
  return *this;
}

#endif  // S21_multiset_H_
