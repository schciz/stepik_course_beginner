#include <cstdlib>
#include <iostream>

void Auxiliary() {
  uint64_t num;
  std::cin >> num;
  if (0 == num) {
    return;
  }
  Auxiliary();
  std::cout << num << ' ';
}

int main() {
  Auxiliary();
  return EXIT_SUCCESS;
}

