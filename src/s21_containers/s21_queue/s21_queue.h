#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include "../s21_list/s21_list.h"
/*
элементы, добавленные первыми, будут удалены первыми.
Элементы вставляются в конец (заднюю часть) очереди и удаляются из начала.
*/
namespace s21 {
template <class T>
class queue {
 public:
  using value_type = T;  // определяет тип
  using reference = value_type &;  // определяет тип ссылки на элемент
  using const_reference = const value_type &;  // тип ссылки на константу
  using size_type = size_t;  // определяет тип размера контейнера

  //Дефолтный конструктор
  queue() : list(){};
  //Конструктор Инициализации
  queue(std::initializer_list<value_type> const &items) : list(items){};
  // конструктор копирования
  queue(const queue &q) : list(q.list){};
  // конструктор перемещения
  queue(queue &&q) : list(std::move(q.list)){};
  // деструктор
  ~queue(){};  //автоматически вызовет деструктор листа

  queue &operator=(queue &&q) {
    if (this != &q) {
      list = std::move(q.list);
    }
    return *this;
  }

  const_reference front() { return list.front(); }
  const_reference back() { return list.back(); }

  bool empty() const { return list.empty(); }
  size_type size() { return list.size(); }

  void push(const_reference value) {
    list.push_back(value);
  }  // вставляет элемент в конец
  void pop() { list.pop_front(); }  // удаляет 1й элемент
  void swap(queue &other) { list.swap(other.list); }  // swaps the contents

  // Реализация insert_many_back
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (list.push_back(std::forward<Args>(args)), ...);
  }

 private:
  s21::list<T> list;
};  // class queue
}  // namespace s21

#endif