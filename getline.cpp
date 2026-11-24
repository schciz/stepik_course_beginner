#include <iostream>

char *resize(const char *str, unsigned size, unsigned new_size) {
  char *new_str = new char[new_size];
  for (unsigned i = 0; i < std::min(size, new_size); ++i) {
    new_str[i] = str[i];
  }
  delete [] str;
  return new_str;
}

char *getline() {
  std::size_t index = 0;
  std::size_t capacity = 1;
  char *str = new char[capacity]{'\0'};
  char character = '\0';
  while (std::cin.get(character) && !std::cin.eof() && character != '\n') {
    str[index++] = character;
    str = resize(str, static_cast<unsigned>(capacity), static_cast<unsigned>(capacity + 1));
    ++capacity;
  }
  str[index] = '\0';
  return str;
}

int main() {
  char *str = getline();
  std::cout << str;
  delete []str;
}
