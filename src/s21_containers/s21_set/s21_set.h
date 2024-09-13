#ifndef S21_SET_H_
#define S21_SET_H_

#include "../s21_vector/s21_vector.h"
#include "../tree/s21_tree.h"

/*
Key: тип ключа элементов, которые будут храниться в множестве.
Compare: тип функции сравнения, используемой для упорядочивания элементов в
множестве. Этот параметр имеет значение по умолчанию std::less<Key>, что
означает, что если тип Compare не указан явно при создании объекта set, будет
использована стандартная функция сравнения, которая реализует операцию меньше.*/

namespace s21 {
template <typename Key>
class set : public AVLTree<Key, Key> {
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

  set() : AVLTree<Key, Key>(){};
  //Конструктор Инициализации
  set(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  // Конструктор копирования
  set(const set& s) : AVLTree<Key, Key>(s){};

  // Конструктор перемещения
  set(set&& s) noexcept : AVLTree<Key, Key>(std::move(s)){};

  ~set() = default;

  // оператор перемещения
  set& operator=(set&& s) noexcept;
  set& operator=(const set& s) noexcept;

  using AVLTree<Key, Key>::begin;
  using AVLTree<Key, Key>::end;
  using AVLTree<Key, Key>::empty;
  using AVLTree<Key, Key>::size;
  using AVLTree<Key, Key>::max_size;
  using AVLTree<Key, Key>::clear;
  using AVLTree<Key, Key>::swap;
  using AVLTree<Key, Key>::merge;

  bool contains(const Key& key) const noexcept {
    bool result = containsImpl(this->root_, key);
    return result;
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    if (this->contains(value)) {
      return {this->find(value), false};
    }
    auto node = insertAdapted(this->root_, value, nullptr);
    this->root_ = node;  // Обновление корня дерева, если это необходимо
    return {this->find(value), true};
  }

  void erase(iterator pos) {
    if (pos != this->end()) {
      AVLTree<Key, Key>::erase(pos->first);  // Извлекаем ключ из пары
    }
  };

  iterator find(const key_type& key) {
    auto node = AVLTree<Key, Key>::find(key);
    return node ? iterator(node) : this->end();
  };

  void merge(set& other) {
    // Объединяем деревья, вставляя узлы из второго дерева в первое
    for (auto it = other.begin(); it != other.end(); ++it) {
      if (!contains(it->first)) {
        insert(it->first);
      }
    }
    // Очищаем второе дерево
    other.clear();
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
  };

};  // class set

}  // namespace s21

// оператор перемещения
template <typename Key>
s21::set<Key>& s21::set<Key>::operator=(set&& s) noexcept {
  AVLTree<Key, Key>::operator=(std::move(s));
  return *this;
};

template <typename Key>
s21::set<Key>& s21::set<Key>::operator=(const set& s) noexcept {
  if (this != &s) {
    AVLTree<Key, Key>::operator=(s);
  }
  return *this;
};

#endif