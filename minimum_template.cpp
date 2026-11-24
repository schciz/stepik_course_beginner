#include <cstddef>

template <typename T>
class Array
{
public:
	explicit Array(size_t size = 0, const T& value = T());
	Array(const Array& other);
	~Array();
	Array& operator=(Array other);
	void swap(Array &other);
	size_t size() const;
	T& operator[](size_t idx);
	const T& operator[](size_t idx) const;

private:
	size_t size_;
	T *data_;
};

// put your code here
template<typename T, typename Comparator>
T minimum(const Array<T> array, Comparator compare) {
  T min = array[0];
  for (size_t i = 1; i < array.size(); ++i) {
    if (compare(array[i], min)) {
      min = array[i];
    }
  }
  return min;
}

