#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include "../s21_container.h"

/*
Vector: вектор

Vector (вектор) - это последовательный контейнер,
инкапсулируюший в себе динамический массив для более интуитивной работы.
*/

namespace s21 {
template <typename T, typename Allocator = std::allocator<T>>
class vector : public Container<T> {
 public:
  // Vector Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  using iterator = T*;
  using const_iterator = const T*;
  using allocator_type = Allocator;

 private:
  T* data_;
  size_t capacity_;  //емкость вектора
  // объект, который управляеn выделением и освобождением памяти для элементов
  // вектора.
  Allocator allocator_;

 public:
  //Дефолтный конструктор
  vector() : data_(nullptr), capacity_(0) { this->size_ = 0; };
  //Параметеризированный констурктор
  vector(size_type n) {
    data_ = allocator_.allocate(n);
    this->size_ = n;
    capacity_ = n;
    //инициализируем каждый элемент
    for (size_type i = 0; i < n; ++i) {
      allocator_.construct(data_ + i, T());
    }
  };
  //Конструктор Инициализации
  vector(std::initializer_list<value_type> const& items)
      : data_(nullptr), capacity_(0) {
    size_type n = items.size();
    if (n > 0) {
      data_ = allocator_.allocate(n);
      this->size_ = n;
      capacity_ = n;
      auto it = items.begin();
      for (size_type i = 0; i < n; ++i, ++it) {
        allocator_.construct(data_ + i, *it);
      }
    }
  };
  // конструктор копирования
  vector(const vector& v) {
    this->size_ = v.size_;
    capacity_ = v.capacity_;
    data_ = allocator_.allocate(capacity_);

    for (size_type i = 0; i < this->size_; ++i) {
      allocator_.construct(data_ + i, v.data_[i]);
    }
  };
  // конструктор перемещения
  vector(vector&& v) noexcept {
    this->size_ = v.size_;
    capacity_ = v.capacity_;
    data_ = v.data_;
    v.size_ = 0;
    v.capacity_ = 0;
    v.data_ = nullptr;
  };
  // деструктор
  ~vector() {
    if (data_ != nullptr) {
      for (size_t i = 0; i < this->size_; i++) {
        allocator_.destroy(data_ + i);
      }
      allocator_.deallocate(data_, capacity_);
    }
    this->size_ = 0;
    capacity_ = 0;
  };

  //оператор перемещения
  vector& operator=(vector&& v) noexcept {
    if (this != &v) {
      if (data_ != nullptr) {
        for (size_t i = 0; i < this->size_; i++) {
          allocator_.destroy(data_ + i);
        }
        allocator_.deallocate(data_, capacity_);
      }

      this->size_ = v.size_;
      capacity_ = v.capacity_;
      data_ = v.data_;

      v.size_ = 0;
      v.capacity_ = 0;
      v.data_ = nullptr;
    }
    return *this;
  };

  // Методы доступа к элементам
  // безопасный доступ с проверкой границ
  reference at(size_type pos) {
    if (pos >= this->size_) {
      throw std::out_of_range("vector::at: position out of range");
    }
    return data_[pos];
  };

  // Без проверки границ
  reference operator[](size_type pos) { return data_[pos]; };
  const_reference front() {
    if (this->size_ == 0) {
      throw std::out_of_range("vector::front: empty vector");
    }
    return data_[0];
  };
  const_reference back() {
    if (this->size_ == 0) {
      throw std::out_of_range("vector::back: empty vector");
    }
    return data_[this->size_ - 1];
  };
  T* data() { return data_; };

  // Array Iterators
  iterator begin() { return data_; };
  iterator end() { return data_ + this->size_; };

  // Array Capacity
  size_type max_size() { return allocator_.max_size(); };

  void reserve(size_type size) {
    if (size > capacity_) {
      T* new_data = allocator_.allocate(size);
      for (size_type i = 0; i < this->size_; ++i) {
        allocator_.construct(new_data + i, std::move(data_[i]));
        allocator_.destroy(data_ + i);
      }
      allocator_.deallocate(data_, capacity_);
      data_ = new_data;
      capacity_ = size;
    }
  };

  size_type capacity() { return capacity_; };

  void shrink_to_fit() {
    if (capacity_ > this->size_) {
      T* new_data = allocator_.allocate(this->size_);
      for (size_type i = 0; i < this->size_; ++i) {
        allocator_.construct(new_data + i, std::move(data_[i]));
        allocator_.destroy(data_ + i);
      }
      allocator_.deallocate(data_, capacity_);
      data_ = new_data;
      capacity_ = this->size_;
    }
  };

  // Методы управления списком
  void clear() {
    for (size_t i = 0; i < this->size_; i++) {
      allocator_.destroy(data_ + i);
    }
    this->size_ = 0;
  };

  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end()) {
      throw std::out_of_range("Iterator out of bounds");
    }
    if (this->size_ == capacity_) {
      if (capacity_ > 0)
        reserve(capacity_ * 2);
      else
        reserve(1);
    }
    size_t index = pos - begin();

    if (this->size_ > 0) {
      allocator_.construct(data_ + this->size_,
                           std::move(data_[this->size_ - 1]));
      for (size_type i = this->size_ - 1; i > index; --i) {
        data_[i] = std::move(data_[i - 1]);  // Перемещаем без перестроения
      }
      allocator_.destroy(data_ + index);
    }

    allocator_.construct(data_ + index, value);
    ++this->size_;

    return iterator(data_ + index);
  };

  void erase(iterator pos) {
    if (pos < begin() || pos >= end()) {
      throw std::out_of_range("Iterator out of bounds");
    }
    size_t index = pos - begin();
    allocator_.destroy(data_ + index);
    for (size_t i = index; i < this->size_ - 1; i++) {
      allocator_.construct(data_ + i, std::move(data_[i + 1]));
      allocator_.destroy(data_ + i + 1);
    }
    --this->size_;
  };

  void push_back(const_reference value) {
    if (this->size_ == capacity_) {
      if (capacity_ > 0) {
        reserve(capacity_ * 2);
      } else {
        reserve(1);
      }
    }
    allocator_.construct(data_ + this->size_, value);
    ++this->size_;
  };

  void pop_back() {
    if (this->size_ == 0) {
      throw std::out_of_range("Cannot pop_back from an empty vector");
    }
    allocator_.destroy(data_ + this->size_ - 1);
    --this->size_;
  };

  void swap(vector& other) {
    std::swap(data_, other.data_);
    std::swap(this->size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(allocator_, other.allocator_);
  };

  // Дополнительные метода
  void print() const {
    for (size_t i = 0; i < this->size_; i++) {
      std::cout << data_[i] << " ";
    }
  };

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    if (pos < begin() || pos > end()) {
      throw std::out_of_range("Iterator out of bounds");
    }
    size_t index = pos - begin();
    size_t n = sizeof...(args);

    if (this->size_ + n > capacity_) {
      this->reserve(std::max(this->capacity_ * 2, this->size_ + n));
    }

    /// Сдвигаем элементы начиная с pos вправо
    for (size_type i = this->size_; i > index; --i) {
      allocator_.construct(data_ + i + n - 1, std::move(data_[i - 1]));
      allocator_.destroy(data_ + i - 1);
    }

    this->size_ += n;  // Обновляем размер

    // Вставляем новые элементы
    size_type count = 0;
    ((allocator_.construct(data_ + index + count++, std::forward<Args>(args))),
     ...);

    return iterator(data_ + index);
  };

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    insert_many(end(), args...);
  };

};  // class vector
}  // namespace s21

#endif