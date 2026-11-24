#include <cstddef>
#include <memory>

template <typename T>
class Array {
  // Список операций:
  //
public:
  explicit Array(size_t size = 0, const T& value = T()) : size_(size), ptr_(nullptr) {
    if (size_ > 0) {
      ptr_.reset(new T[size_]);
      for (size_t i = 0; i < size_; ++i) {
        ptr_[i] = value;
      }
    }
  }
  //   конструктор класса, который создает
  //   Array размера size, заполненный значениями
  //   value типа T. Считайте что у типа T есть
  //   конструктор, который можно вызвать без
  //   без параметров, либо он ему не нужен.
  //
  Array(const Array &other) : size_(other.size_), ptr_(nullptr) {
    if (other.size_ > 0) {
      ptr_.reset(new T[other.size_]);
      for (size_t i = 0; i < other.size_; ++i) {
        ptr_[i] = other.ptr_[i];
      }
    }
  }
  //   конструктор копирования, который создает
  //   копию параметра. Считайте, что для типа
  //   T определен оператор присваивания.
  friend void swap(Array<T>& first, Array<T>& second) {
    std::swap(first.size_, second.size_);
    std::swap(first.ptr_, second.ptr_);
  }
  //
  // ~Array() {}
  //   деструктор, если он вам необходим.
  //
  Array& operator=(Array other) {
    swap(*this, other);
    return *this;
  }
  //   оператор присваивания.
  //
  size_t size() const {
    return size_;
  }
  //   возвращает размер массива (количество
  //                              элементов).
  //
  T& operator[](size_t index) {
    return ptr_[index];
  }
  const T& operator[](size_t index) const {
    return ptr_[index];
  }
  //   две версии оператора доступа по индексу.
private:
  size_t size_;
  std::unique_ptr<T[]> ptr_;
};

int main() {}

