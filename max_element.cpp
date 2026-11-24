#include <cstdlib>
#include <iostream>

int main() {
  int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::cout << *std::min_element(arr, arr + (sizeof(arr) / sizeof(int))) << ' ' << *std::max_element(arr, arr + (sizeof(arr) / sizeof(int)));
  return EXIT_SUCCESS;
}

