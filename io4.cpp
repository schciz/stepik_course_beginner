#include <cstdlib>
#include <iostream>

int DecimalLog(int64_t number) {
  int p = 0;
  int64_t decimal = 2;
  while (decimal <= number) {
    decimal *= 2;
    ++p;
  }
  return p;
}

int main() {
  int64_t t = 0;
  std::cin >> t;
  for (int64_t i = 0; i < t; ++i) {
    int64_t a = 0;
    std::cin >> a;
    std::cout << DecimalLog(a) << '\n';
  }
  return EXIT_SUCCESS;
}

