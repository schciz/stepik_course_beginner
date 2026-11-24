#include <cstddef> // size_t

// реализуйте шаблонную функцию array_size,
// которая возвращает значение типа size_t.

// put your code here
template<class T, std::size_t Size>
std::size_t array_size(const T (&arr)[Size]) {
  return Size;
}

int main() {
  int ints[] = {1, 2, 3, 4};
  int *iptr = ints;
  double doubles[] = {3.14};
  array_size(ints); // вернет 4
  array_size(doubles); // вернет 1
  array_size(iptr); // тут должна произойти ошибка компиляции
}
