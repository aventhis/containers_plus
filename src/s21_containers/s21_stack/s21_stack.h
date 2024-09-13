#ifndef S21_STACK_H_
#define S21_STACK_H_
#include "../s21_list/s21_list.h"
#include "../s21_vector/s21_vector.h"
/*
Stack - адаптер контейнера, который ограничивает функциональность базового
контейнера, позволяя выполнять только операции стека.

Доступ к элементам осуществляется только через вершину стека,
что соответствует последним поступил — первым обслужен
*/
namespace s21 {
template <class T>
class stack {
 public:
  using value_type = T;  // определяет тип
  using reference = value_type &;  // определяет тип ссылки на элемент
  using const_reference = const value_type &;  // тип ссылки на константу
  using size_type = size_t;  // определяет тип размера контейнера

  //Дефолтный конструктор
  stack() : list(){};
  //Конструктор Инициализации
  stack(std::initializer_list<value_type> const &items) : list(items){};
  // конструктор копирования
  stack(const stack &s) : list(s.list){};
  // конструктор перемещения
  stack(stack &&s) : list(std::move(s.list)){};
  // деструктор
  ~stack(){};  //автоматически вызовет деструктор листа

  stack &operator=(stack &&s) {
    if (this != &s) {
      list = std::move(s.list);
    }
    return *this;
  }

  const_reference top() { return list.back(); }
  bool empty() const { return list.empty(); }
  size_type size() { return list.size(); }

  void push(const_reference value) {
    list.push_back(value);
  }  // вставляет элемент вверху
  void pop() { list.pop_back(); }  // удаляет верхний элемент
  void swap(stack &other) { list.swap(other.list); }  // swaps the contents

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    s21::vector<value_type> temp{std::forward<Args>(args)...};
    size_t count = temp.size();
    for (int i = count - 1; i >= 0; --i) {
      list.push_front(std::move(temp[i]));
    }
  }

 private:
  s21::list<T> list;
};  // class stack
}  // namespace s21

#endif