#ifndef S21_LIST_H_
#define S21_LIST_H_

/*
list: двухсвязный список

Поддерживает только последовательный двухнаправленный доступ к элементам.

Обеспечивает удаление и добавление элементов в начале и в конце контейнера.

Контейнер list представляет двухсвязный список, то есть такой список,
где каждый элемент имеет указатели на предыдущий и последовательный элемент.

Благодаря чему мы можем перемещаться по списку как вперед, так и назад.
Для использования списка необходимо подключить заголовочный файл list.

*/

namespace s21 {
template <class T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  class ListIterator;
  class ListConstIterator;

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

 private:
  struct Node {
    value_type value_;
    Node* prev_;
    Node* next_;

    Node(const_reference value = value_type(), Node* prev = nullptr,
         Node* next = nullptr)
        : value_(value), prev_(prev), next_(next) {}
  };

  Node* head_;      // Головной узел
  Node* tail_;      // Хвостовой узел
  size_type size_;  // Размер списка

  // List Functions
 public:
  //Дефолтный конструктор

  list();
  // Параметоризированный конструктор
  list(size_type n);
  //Конструктор Инициализации
  list(std::initializer_list<value_type> const& items);
  // конструктор копирования
  list(const list& l);
  // конструктор перемещения
  list(list&& l);
  // деструктор
  ~list();

  list& operator=(const list& l);
  list& operator=(list&& l) noexcept;
  list& operator=(std::initializer_list<value_type> const& items);

  // Методы доступа к элементам
  const_reference front() const;
  const_reference back() const;

  iterator begin();
  iterator end();

  // Функции константных итераторов
  const_iterator cbegin() const { return const_iterator(head_); };

  const_iterator cend() const { return const_iterator(nullptr); };

  // Вспомогательные методы
  size_type size() const { return size_; };
  bool empty() const { return size_ == 0; };

  // Методы управления списком
  void clear();  // очистка списка

  iterator insert(iterator pos,
                  const_reference value);  // + вставка по итератору
  void erase(iterator pos);  // + удаление по итератору
  void push_back(const_reference value);   // + вставка в конец
  void pop_back();                         // + удаление из конца
  void push_front(const_reference value);  // + вставка в начало
  void pop_front();        // + удаление из начала
  void swap(list& other);  // + смена местами двух списков
  void merge(list& other);  //  + Объединяет два отсортированных списка
  void splice(const_iterator pos,
              list& other);  // Перемещает элементы из другого списка
  void reverse();  // +- Переворачивает порядок элементов
  void unique();  // Удаляет последовательные дубликаты
  void sort();  // Сортирует элементы

  // доп
  void printNode();
  list<T> splitForSort(T middle);
  list<T> merge_sort(list<T>& leftList, list<T>& rightList);

  iterator make_iterator(const_iterator pos) {
    return iterator(const_cast<Node*>(pos.getCurrent()));
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  void insert_many_front(Args&&... args);

};  // class list
}  // namespace s21

template <typename T>
void s21::list<T>::clear() {
  Node* current = this->head_;

  // Удаляем все узлы, пока не дойдем до конца списка
  while (current != nullptr) {
    Node* nextNode = current->next_;
    delete current;      // Освобождаем память
    current = nextNode;  // Переходим к следующему узлу
  }

  this->head_ = nullptr;  // Обнуляем указатели
  this->tail_ = nullptr;
  this->size_ = 0;  // Обнуляем размер
};

template <typename T>
typename s21::list<T>::iterator s21::list<T>::insert(iterator pos,
                                                     const_reference value) {
  if (pos == this->end()) {  // Если `pos` указывает на конец
    this->push_back(value);  // Используем `push_back`
    return iterator(this->tail_);  // Возвращаем итератор на конец
  } else if (pos == this->begin()) {  // Если вставка в начало
    this->push_front(value);          // Используем `push_front`
    return iterator(this->head_);  // Возвращаем итератор на начало
  } else {                         // Вставка между узлами
    Node* pos_node =
        pos.getCurrent();  // Узел, на который указывает итератор `pos`
    Node* new_node = new Node(value);  // Создаем новый узел
    new_node->next_ = pos_node;  // Связываем новый узел с `pos_node`
    new_node->prev_ = pos_node->prev_;  // Связываем с предыдущим узлом

    if (new_node->prev_ != nullptr) {  // Вставка между узлами
      new_node->prev_->next_ = new_node;  // Обновляем следующий узел
    }

    pos_node->prev_ = new_node;  // Обновляем предыдущий узел

    ++this->size_;  // Увеличиваем размер списка
    return iterator(new_node);  // Возвращаем итератор на новый узел
  }
};

template <typename T>
void s21::list<T>::erase(iterator pos) {
  Node* node_to_delete = pos.getCurrent();
  if (node_to_delete == nullptr) return;  // Если итератор недействителен

  if (node_to_delete->prev_) {
    node_to_delete->prev_->next_ = node_to_delete->next_;
  } else {
    this->head_ =
        node_to_delete->next_;  // Обновляем head, если удаляем первый элемент
  }

  if (node_to_delete->next_) {
    node_to_delete->next_->prev_ = node_to_delete->prev_;
  } else {
    this->tail_ =
        node_to_delete
            ->prev_;  // Обновляем tail, если удаляем последний элемент
  }

  delete node_to_delete;  // Освобождаем память
  --this->size_;          // Обновляем размер списка
}

template <typename T>
void s21::list<T>::push_back(const_reference value) {
  Node* new_node = new Node(value);
  if (this->tail_ == nullptr) {
    this->head_ = new_node;
    this->tail_ = new_node;
  } else {
    tail_->next_ = new_node;
    new_node->prev_ = this->tail_;
    this->tail_ = new_node;
  }
  this->size_++;  // this-> Для избежание ошибок компиляции
};

template <typename T>
void s21::list<T>::pop_back() {
  if (this->tail_ == nullptr) {  // Если список пуст, выбрасываем исключение
    throw std::out_of_range("List is empty");
  }
  Node* current = this->tail_;  // Сохраняем узел, который будет удален
  this->tail_ = this->tail_->prev_;  // Обновляем `tail_`
  if (this->tail_ !=
      nullptr) {  // Если новый `tail_` не является `nullptr`, обнуляем `next_`
    this->tail_->next_ = nullptr;
  } else {
    this->head_ = nullptr;  // Если список стал пустым, обнуляем `head_`
  }
  delete current;  // Удаляем узел и освобождаем память
  if (this->size_ > 0) {  // Уменьшаем размер списка, только если он больше 0
    --this->size_;
  }
};

template <typename T>
void s21::list<T>::push_front(const_reference value) {
  Node* new_node = new Node(value);
  if (this->head_ == nullptr) {
    this->head_ = new_node;
    this->tail_ = new_node;
  } else {
    new_node->next_ = this->head_;
    this->head_->prev_ = new_node;
    this->head_ = new_node;
  }
  this->size_++;  // this-> Для избежание ошибок компиляции
};

template <typename T>
void s21::list<T>::pop_front() {
  if (this->head_ == nullptr) {  // Если список пуст, выбрасываем исключение
    throw std::out_of_range("List is empty");
  }
  Node* current = this->head_;  // Сохраняем узел, который будет удален
  this->head_ = this->head_->next_;  // Обновляем `tail_`
  if (this->head_ !=
      nullptr) {  // Если новый `tail_` не является `nullptr`, обнуляем `next_`
    this->head_->prev_ = nullptr;
  } else {
    this->head_ = nullptr;  // Если список стал пустым, обнуляем `head_`
  }
  delete current;  // Удаляем узел и освобождаем память
  if (this->size_ > 0) {  // Уменьшаем размер списка, только если он больше 0
    this->size_--;
  }
};

template <typename T>
void s21::list<T>::swap(list& other) {
  if (this != &other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(this->size_, other.size_);
  }
};

template <typename T>
void s21::list<T>::merge(list& other) {
  if (this == &other) {
    return;
  }
  iterator it1 = begin();
  iterator it2 = other.begin();

  while (it1 != end() && it2 != end()) {
    if (*it2 < *it1) {
      insert(it1, *it2);  // Вставляем перед `it1`
      ++it2;  // Переходим к следующему элементу во втором списке
    } else {
      ++it1;  // Переходим к следующему элементу в первом списке
    }
  }
  // Добавляем оставшиеся элементы из `other`
  while (it2 != other.end()) {
    push_back(*it2);  // Вставляем в конец первого списка
    ++it2;  // Переходим к следующему элементу во втором списке
  }
  // После слияния очищаем `other`
  other.clear();
};

template <class T>
void s21::list<T>::splice(const_iterator pos, s21::list<T>& other) {
  if (other.empty() || this == &other) {
    return;  // Если исходный список пуст, нечего перемещать
  }

  Node* current = const_cast<Node*>(pos.getCurrent());

  if (current != nullptr) {
    if (current->prev_ != nullptr) {
      current->prev_->next_ = other.head_;
    } else {
      head_ = other.head_;  // Если pos указывает на начало
    }

    if (other.tail_ != nullptr) {
      other.tail_->next_ = current;
    }
    other.head_->prev_ = current->prev_;
    current->prev_ = other.tail_;
  } else {
    // Если pos указывает на конец, соедините с хвостом
    tail_->next_ = other.head_;
    other.head_->prev_ = tail_;
    tail_ = other.tail_;
  }
  size_ += other.size_;

  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;  // Исходный список теперь пуст
};

template <typename T>
void s21::list<T>::reverse() {
  Node* current = this->head_;
  Node* prev = nullptr;
  Node* next = nullptr;

  while (current != nullptr) {
    next = current->next_;

    current->next_ = prev;
    current->prev_ = next;

    prev = current;
    current = next;
  }

  this->tail_ = this->head_;
  this->head_ = prev;
}

template <typename T>
void s21::list<T>::unique() {
  iterator begin_iter = begin();
  iterator end_iter = end();
  iterator previous = begin_iter;

  if (begin_iter != end_iter) {
    ++begin_iter;
    while (begin_iter != end_iter) {
      if (*previous == *begin_iter) {
        iterator to_erase = begin_iter;
        ++begin_iter;
        erase(to_erase);
      } else {
        ++previous;
        ++begin_iter;
      }
    }
  }
}

template <typename T>
s21::list<T> s21::list<T>::splitForSort(T middle) {
  list result;

  iterator begin_iter = begin();
  // копируем первую половину из списка
  for (auto i = 0; i < middle; i++) {
    result.push_back(*begin_iter);
    ++begin_iter;
  }
  // удаляем половину из списка
  begin_iter = begin();
  for (auto i = 0; i < middle; i++) {
    iterator to_erase = begin_iter;
    ++begin_iter;  // получаем следующий итератор до удаления
    erase(to_erase);  // удаляем элемент
  }
  return result;
}

template <typename T>
void s21::list<T>::sort() {
  if (this->size_ < 2) return;

  auto middle = size_ / 2;
  list leftSide = splitForSort(middle);
  list rigthSide(*this);

  leftSide.sort();
  rigthSide.sort();

  list result = merge_sort(leftSide, rigthSide);
  this->swap(result);
}

template <typename T>
s21::list<T> s21::list<T>::merge_sort(s21::list<T>& leftList,
                                      s21::list<T>& rightList) {
  list result;
  iterator begin_iter_left = leftList.begin();
  iterator end_iter_left = leftList.end();
  iterator begin_iter_right = rightList.begin();
  iterator end_iter_right = rightList.end();

  while (begin_iter_left != end_iter_left &&
         begin_iter_right != end_iter_right) {
    if (*begin_iter_left <= *begin_iter_right) {
      result.push_back(*begin_iter_left);
      ++begin_iter_left;
    } else {
      result.push_back(*begin_iter_right);
      ++begin_iter_right;
    }
  }

  // Добавление оставшихся элементов
  while (begin_iter_left != end_iter_left) {
    result.push_back(*begin_iter_left);
    ++begin_iter_left;
  }

  while (begin_iter_right != end_iter_right) {
    result.push_back(*begin_iter_right);
    ++begin_iter_right;
  }

  return result;
}

/*****************************
 * консутрукторы и деструктор *
 */

template <typename T>
s21::list<T>::list() : head_(nullptr), tail_(nullptr), size_(0){};

template <typename T>
s21::list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
};

template <typename T>
s21::list<T>::list(std::initializer_list<T> const& items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (const auto& item : items) {
    push_back(item);  // Добавляем элементы из initializer_list
  }
};

template <typename T>
s21::list<T>::list(const list& l) {
  this->head_ = nullptr;  // Инициализация головы
  this->tail_ = nullptr;  // Инициализация хвоста
  this->size_ = 0;  // Инициализация размера списка

  Node* current = l.head_;  // Начинаем с головы списка
  while (current != nullptr) {
    push_back(current->value_);  // Копируем значение в конец списка
    current = current->next_;  // Переходим к следующему узлу
  }
};

template <typename T>
s21::list<T>::list(list&& l) : head_(l.head_), tail_(l.tail_), size_(l.size_) {
  l.head_ = nullptr;  // Очищаем оригинальный список
  l.tail_ = nullptr;
  l.size_ = 0;
};

template <typename T>
s21::list<T>::~list() {
  clear();  // Очищаем список и освобождаем память
};

template <typename T>
s21::list<T>& s21::list<T>::operator=(const list& l) {
  if (this == &l) {
    return *this;
  }

  clear();
  for (auto iter = l.cbegin(); iter != l.cend(); ++iter) {
    push_back(*iter);
  }
  return *this;
};

template <typename T>
s21::list<T>& s21::list<T>::operator=(list&& l) noexcept {
  if (this != &l) {
    this->~list();
    this->size_ = l.size_;
    head_ = l.head_;
    tail_ = l.tail_;
    l.size_ = 0;
    l.head_ = nullptr;
    l.tail_ = nullptr;
  }
  return *this;
};

template <typename T>
s21::list<T>& s21::list<T>::operator=(std::initializer_list<T> const& items) {
  clear();
  for (auto item : items) {
    push_back(item);
  }
  return *this;
}

// Реализация методов s21::list<T>
template <typename T>
typename s21::list<T>::const_reference s21::list<T>::front() const {
  if (this->head_ == nullptr) {
    throw std::range_error("List is empty");
  }
  return this->head_->value_;
};

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::back() const {
  if (this->tail_ == nullptr) {
    throw std::range_error("List is empty");
  }
  return this->tail_->value_;
};

template <typename T>
class s21::list<T>::ListIterator {
  Node* current_;  // Объявление поля current_
  friend class list<T>;

 public:
  // Конструктор по умолчанию
  ListIterator() noexcept : current_(nullptr) {}
  // Конструктор с указателем
  ListIterator(Node* start) noexcept : current_(start) {}
  // Конструктор копирования
  ListIterator(const ListIterator& other) noexcept : current_(other.current_) {}

  bool operator==(const ListIterator& other) const {
    return current_ == other.current_;
  }

  bool operator!=(const ListIterator& other) const {
    return current_ != other.current_;
  }

  // Публичный метод доступа к `current_`
  Node* getCurrent() const { return current_; }

  T& operator*() {
    if (current_ == nullptr) {  // Защита от разыменования nullptr
      throw std::runtime_error("Dereferencing a nullptr");
    }
    return current_->value_;
  }

  ListIterator& operator++() {
    if (current_ != nullptr) {
      current_ = current_->next_;
    }
    return *this;
  }

  ListIterator& operator--() {
    if (current_ != nullptr) {
      current_ = current_->prev_;
    }
    return *this;
  }

  ListIterator& operator=(const ListIterator& other) noexcept {
    if (this != &other) {
      current_ = other.current_;
    }
    return *this;
  }
};

template <typename T>
class s21::list<T>::ListConstIterator {
  const Node* current_;  // Объявление поля current_
 public:
  ListConstIterator() noexcept : current_(nullptr) {}
  ListConstIterator(Node* start) : current_(start) {}
  ListConstIterator(const ListIterator& other) noexcept
      : current_(other.getCurrent()) {}

  const Node* getCurrent() const { return current_; }

  bool operator==(const ListConstIterator& other) const {
    return current_ == other.current_;
  }

  bool operator!=(const ListConstIterator& other) const {
    return !(*this == other);
  }

  const T& operator*() const {
    if (current_ == nullptr) {
      throw std::runtime_error("Dereferencing a nullptr");
    }
    return current_->value_;
  }

  ListConstIterator& operator++() {
    if (current_ != nullptr) {
      current_ = current_->next_;
    }
    return *this;
  }
};

// Реализация методов для итераторов
template <typename T>
typename s21::list<T>::iterator s21::list<T>::begin() {
  return ListIterator(this->head_);
};

template <typename T>
typename s21::list<T>::iterator s21::list<T>::end() {
  return ListIterator(nullptr);
};

template <typename T>
void s21::list<T>::printNode() {
  for (auto it = this->begin(); it != this->end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
};

/***********************************************************************
 ***********************************************************************
 *************************   insert_many   *****************************
 ***********************************************************************
 **********************************************************************/

template <typename T>
template <typename... Args>
typename s21::list<T>::iterator s21::list<T>::insert_many(const_iterator pos,
                                                          Args&&... args) {
  // Создаем временный итератор, чтобы сохранить позицию вставки
  iterator iter = make_iterator(pos);  // Преобразуем const_iterator в iterator
  if constexpr (sizeof...(args) > 0) {
    iterator first_inserted =
        nullptr;  // Для хранения итератора на первый вставленный элемент
    for (const auto& arg : {std::forward<Args>(args)...}) {
      iter = insert(iter, arg);
      if (first_inserted == nullptr) {
        first_inserted =
            iter;  // Запоминаем итератор на первый вставленный элемент
      }
      ++iter;  // Продвигаем итератор после вставки
    }
    // Возвращаем итератор на первый вставленный элемент
    return first_inserted;
  }
  return iter;
};

template <typename T>
template <typename... Args>
void s21::list<T>::insert_many_back(Args&&... args) {
  (push_back(value_type(std::forward<Args>(args))), ...);
};

template <typename T>
template <typename... Args>
void s21::list<T>::insert_many_front(Args&&... args) {
  insert_many(begin(), args...);
};

#endif