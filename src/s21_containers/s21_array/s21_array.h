#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include "../s21_container.h"

/*
Array: массив

Array (массив) - это последовательный контейнер, инкапсулирующий в себе
статический массив.

В array нельзя добавить новый элементы, можно только модифицировать значение
заданных изначально.

 Контейнер Array хранит размер массива и предоставляет итераторы.
 Так же как и vector, array занимает последовательную часть памяти
 и может быть передан в функцию как стандартный массив в Си.
 Вторым шаблонным аргументом класса array является его фактический размер.

*/

namespace s21 {
template <typename T, size_t N>
class array : public Container<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  using iterator = T *;
  using const_iterator = const T *;

 private:
  T data_[N];  // Статический массив для хранения элементов
  size_t initialized_size_ = 0;  // для метода back
 public:
  //Дефолтный конструктор
  array() : data_{} {
    this->size_ = N;
    // Инициализация массива data значениями по умолчанию.
  };
  //Конструктор Инициализации
  array(std::initializer_list<value_type> const &items) {
    size_t count = 0;
    for (auto &item : items) {
      if (count >= N) {
        break;
      }
      data_[count++] = item;
    }

    // оставшиеся элементы значением по умолчанию
    for (size_t i = count; i < N; i++) {
      data_[i] = T();
    }
    initialized_size_ = count;
    this->size_ = N;
  };
  // конструктор копирования
  array(const array &a) {
    for (size_t i = 0; i < N; ++i) {
      data_[i] = a.data_[i];
    }
    this->size_ = N;
  };
  // конструктор перемещения
  array(array &&a) noexcept {
    for (size_t i = 0; i < N; ++i) {
      data_[i] = std::move(a.data_[i]);
    }
    this->size_ = N;
  };

  // деструктор
  ~array(){};

  array &operator=(array &&a) noexcept {
    if (this != &a) {
      for (size_t i = 0; i < N; ++i) {
        data_[i] = std::move(a.data_[i]);
      }
    }
    this->size_ = N;
    return *this;
  };

  // Методы доступа к элементам
  // безопасный доступ с проверкой границ
  reference at(size_type pos) {
    if (pos >= this->size_) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  };
  // Без проверки границ
  reference operator[](size_type pos) { return data_[pos]; };
  const_reference front() {
    if (this->size_ == 0) throw std::out_of_range("array::front: empty array");
    return data_[0];
  };
  const_reference back() {
    if (initialized_size_ == 0)
      throw std::out_of_range("array::back: empty array");
    return data_[initialized_size_ - 1];
  };
  iterator data() { return data_; };

  // Array Iterators
  iterator begin() { return data_; };
  iterator end() { return data_ + this->size_; };

  const_iterator begin() const { return data_; };
  const_iterator end() const { return data_ + this->size_; };

  size_type max_size() { return this->size_; };

  // Методы управления списком

  void swap(array &other) {
    for (size_type i = 0; i < this->size_; ++i) {
      std::swap(data_[i], other.data_[i]);
    }
  };

  void fill(const_reference value) {
    for (size_t i = 0; i < this->size_; ++i) {
      data_[i] = value;
    }
  };

  // Дополнительные методы

  void print() const {
    for (size_t i = 0; i < this->size_; i++) {
      std::cout << data_[i] << " ";
    }
  };

};  // class array
}  // namespace s21

#endif