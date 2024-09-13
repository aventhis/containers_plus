#ifndef S21_MAP_H_
#define S21_MAP_H_

#include "../s21_vector/s21_vector.h"
#include "../tree/s21_tree.h"

namespace s21 {
template <typename Key, typename T>
class map : public AVLTree<Key, T> {
 private:
  using AVLTree<Key, T>::Node;  // Используем Node из AVLTree

 public:
  // map Member type
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using const_iterator = typename AVLTree<Key, T>::const_iterator;
  using iterator = typename AVLTree<Key, T>::iterator;

  using AVLTree<Key, T>::AVLTree;  // Наследование конструкторов

  // //Дефолтный конструктор
  map() : AVLTree<Key, T>(){};

  //Конструктор Инициализации
  map(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  // Копирующий конструктор
  map(const map& m) : AVLTree<Key, T>(m) {}

  // Конструктор перемещения
  map(map&& m) : AVLTree<Key, T>(std::move(m)) {}

  // Деструктор
  ~map() = default;

  // оператор перемещения
  map& operator=(map&& s) noexcept;
  map& operator=(const map& s) noexcept;

  using AVLTree<Key, T>::begin;
  using AVLTree<Key, T>::end;
  using AVLTree<Key, T>::empty;
  using AVLTree<Key, T>::size;
  using AVLTree<Key, T>::max_size;
  using AVLTree<Key, T>::clear;
  using AVLTree<Key, T>::swap;
  using AVLTree<Key, T>::merge;

  iterator find(const Key& key);
  T& at(const Key& key);
  T& operator[](const Key& key);

  // Адаптированная вставка для карты
  typename AVLTree<Key, T>::Node* insertAdapted(
      typename AVLTree<Key, T>::Node* node, const value_type& value,
      typename AVLTree<Key, T>::Node* parent) {
    return AVLTree<Key, T>::insert_(node, value, parent);
  };

  std::pair<iterator, bool> insert(const value_type& value) {
    if (contains(value.first)) {
      return {find(value.first), false};
    }
    auto node = insertAdapted(this->root_, value, nullptr);
    this->root_ = node;  // Обновление корня дерева, если это необходимо
    return {find(value.first), true};
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    auto node = AVLTree<Key, T>::find(key);
    if (node) {
      node.value_.second = obj;
      iterator it(node);
      return std::pair<iterator, bool>(it, false);  // Элемент уже существует
    } else
      return insert({key, obj});
  }

  void erase(iterator pos) { AVLTree<Key, T>::erase(pos->first); }

  bool contains(const Key& key) { return AVLTree<Key, T>::contains(key); }

  // Печать содержимого map
  void print() const {
    for (const auto& pair : *this) {
      std::cout << pair.first << ": " << pair.second << std::endl;
    }
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    vector<std::pair<iterator, bool>> result;

    (result.push_back(insert(std::forward<value_type>(args))), ...);
    return result;
  }
};
};  // namespace s21

// оператор перемещения
template <typename Key, typename T>
s21::map<Key, T>& s21::map<Key, T>::operator=(map&& m) noexcept {
  if (this != &m) {
    AVLTree<Key, T>::operator=(std::move(m));
  }
  return *this;
};

template <typename Key, typename T>
s21::map<Key, T>& s21::map<Key, T>::operator=(const map& m) noexcept {
  if (this != &m) {
    AVLTree<Key, T>::operator=(m);
  }
  return *this;
};

template <typename Key, typename T>
typename s21::map<Key, T>::iterator s21::map<Key, T>::find(const Key& key) {
  auto node = AVLTree<Key, T>::find(key);
  return node ? iterator(node) : this->end();
};

template <typename Key, typename T>
T& s21::map<Key, T>::at(const Key& key) {
  auto node = AVLTree<Key, T>::find(key);
  if (!node) {
    throw std::out_of_range("Key not found");
  }
  return node->value_.second;
}

// Доступ по ключу с оператором []
template <typename Key, typename T>
T& s21::map<Key, T>::operator[](const Key& key) {
  auto node = AVLTree<Key, T>::find(key);
  if (node) {
    // Если ключ найден, возвращаем его значение.
    return node->value_.second;
  } else {
    auto result = insert({key, T()});
    auto it = result.first;
    return it->second;
  }
}

#endif