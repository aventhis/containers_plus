// s21_container.h
#ifndef S21_CONTAINER_H_
#define S21_CONTAINER_H_

#include <stddef.h>  // for size_t

#include <algorithm>   // Для std::max
#include <cstddef>     // Для size_t
#include <functional>  // std::less
#include <iostream>
#include <limits>     // for max_size
#include <memory>     // for allocator
#include <stdexcept>  // for exceptions
#include <utility>    // Для std::pair

namespace s21 {
template <typename T>
class Container {
 public:
  using size_type = size_t;

  Container() : size_(0){};

  bool empty() { return size_ == 0; }
  size_type size() const { return size_; };
  // virtual size_type max_size() {
  //   return std::numeric_limits<std::size_t>::max() / sizeof(T);
  // };

 protected:
  size_t size_ = 0;
};  // class Container
}  // namespace s21

#endif