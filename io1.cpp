#include <cstdlib>
#include <iostream>

int main() {
  int lines = 0;
  std::cin >> lines;
  for (int i = 0; i < lines; ++i) {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
  }
  return EXIT_SUCCESS;
}

