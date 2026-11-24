#include <iostream>

char *resize(const char *str, unsigned size, unsigned new_size) {
  char *new_str = new char[new_size];
  for (unsigned i = 0; i < std::min(size, new_size); ++i) {
    new_str[i] = str[i];
  }
  delete [] str;
  return new_str;
}

int main() {
  char *str = new char[10]{"hello"};
  str = resize(str, 10, 7);
  std::cout << str;
  delete [] str;
}

