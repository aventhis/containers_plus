## English Version

# s21_containers_plus

### Introduction

`s21_containers_plus` is a custom C++ library designed to implement various container classes. This project demonstrates object-oriented design principles, templates, and iterator implementation to create an intuitive interface for handling data structures. The library allows you to work with containers like lists, maps, queues, and more, with full iterator support.

### Features

- Implementation of standard C++ containers (`list`, `map`, `queue`, `set`, `stack`, `vector`).
- Additional bonus containers like `array` and `multiset`.
- Support for special insertion methods (`insert_many`, `insert_many_back`, `insert_many_front`).
- Template-based implementation for handling different data types.
- Full iterator support for easy traversal.

### Containers Overview

| No. | Container  | Description |
| --- | ---------- | ----------- |
| 1   | `list`     | Doubly linked list implementation |
| 2   | `map`      | Associative container that stores key-value pairs |
| 3   | `queue`    | First-in, first-out (FIFO) container |
| 4   | `set`      | Stores unique elements |
| 5   | `stack`    | Last-in, first-out (LIFO) container |
| 6   | `vector`   | Dynamic array implementation |
| 7   | `array`    | Fixed-size array (Bonus) |
| 8   | `multiset` | Stores duplicate elements (Bonus) |

### Part 1. Implementation of s21_containers.h

The `s21_containers_plus` library implements container classes: `list`, `map`, `queue`, `set`, `stack`, and `vector`. Each container has its own header file and is structured similarly to its STL counterpart. Iterators are provided for all containers, following the STL-style for consistency.

### Part 2. Bonus: s21_containersplus.h

The bonus section includes additional containers: `array` for fixed-size arrays and `multiset` for storing duplicate values.

### Part 3. Bonus: Special Insertion Methods

This part covers the methods `insert_many`, `insert_many_back`, and `insert_many_front` to enable bulk element insertion in containers like `list`, `vector`, and `queue`.

### Build Instructions

To build and run the project:

1. Clone the repository:

    ```bash
    git clone <repository_url>
    cd <project_folder>
    ```

2. Compile using the Makefile:

    ```bash
    make all
    ```

### Makefile Targets

- **make all**: Compiles all source files and builds the container library.
- **make clean**: Removes all object files and executables.
- **make test**: Runs unit tests to verify container functionality.
- **make gcov_report**: Generates code coverage reports using `gcov`.

### Conclusion

The `s21_containers_plus` project provides an in-depth look at C++ containers, iterators, and template programming, offering an intuitive interface and robust testing framework.