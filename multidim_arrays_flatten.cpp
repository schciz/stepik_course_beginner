// Весь вывод должен осуществляться в поток out,
// переданный в качестве параметра.
//
// Можно заводить любые вспомогательные функции,
// структуры или даже изменять сигнатуру flatten,
// но при этом все примеры вызова из задания должны
// компилироваться и работать.
#include <vector>
template <typename T>
using Array = std::vector<T>;

#include <iostream>

template <typename T>
void flatten(const Array<T>& array, std::ostream& out) {
  for (size_t i = 0; i < array.size(); ++i) {
    out << ' ' << array[i];
  }
}

template <typename T>
void flatten(const Array<Array<T>>& array, std::ostream& out) {
  for (size_t i = 0; i < array.size(); ++i) {
    flatten(array[i], out);
  }
}

int main() {
  Array<int> ints(2, 0);
  ints[0] = 10;
  ints[1] = 20;
  flatten(ints, std::cout); // выводит на экран строку "10 20"
  std::cout << '\n';
  Array< Array<int> > array_of_ints(2, ints);
  flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20"
  std::cout << '\n';
  Array<double> doubles(10, 0.0);
  flatten(doubles, std::cout); // работать должно не только для типа int
  std::cout << '\n';
}

