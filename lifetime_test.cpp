#include <iostream>

int main() {
  int *p = nullptr;
  {
    int x = 50;
    p = &x;
  }
  std::cout << *p << '\n';
}

