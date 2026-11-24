#include <cstddef>
#include <memory>

template <typename T>
struct Deleter {
  void operator()(T* ptr) {
    operator delete[](static_cast<void *>(ptr));
  }
};

template <typename T>
class Array {
public:
  Array() : size_(0), ptr_(nullptr, Deleter<T>{}) {}
  explicit Array(size_t size, const T& value) : size_(size), ptr_(nullptr, Deleter<T>{}) {
    if (size_ > 0) {
      ptr_.reset(static_cast<T *>(operator new[](sizeof(T) * size_)));
      // ptr_.reset(new T[size_]);
      for (size_t i = 0; i < size_; ++i) {
        // ptr_[i] = value;
        new (ptr_.get() + i) T(value);
      }
    }
  }
  Array(const Array &other) : size_(other.size_), ptr_(nullptr) {
    if (other.size_ > 0) {
      ptr_.reset(static_cast<T *>(operator new[](sizeof(T) * other.size_)));
      for (size_t i = 0; i < other.size_; ++i) {
        // ptr_[i] = other.ptr_[i];
        new (ptr_.get() + i) T(*(other.ptr_.get() + i));
      }
    }
  }
  friend void swap(Array<T>& first, Array<T>& second) {
    std::swap(first.size_, second.size_);
    std::swap(first.ptr_, second.ptr_);
  }
  ~Array() {
    if (ptr_.get() != nullptr) {
      for (size_t i = 0; i < size_; ++i) {
        (ptr_.get() + i)->~T();
      }
    }
  }
  Array& operator=(Array other) {
    swap(*this, other);
    return *this;
  }
  size_t size() const {
    return size_;
  }
  T& operator[](size_t index) {
    return *(ptr_.get() + index);
  }
  const T& operator[](size_t index) const {
    return *(ptr_.get() + index);
  }
private:
  size_t size_;
  std::unique_ptr<T, Deleter<T>> ptr_;
};

int main() {
  Array<int> arr(10, 0);
}
