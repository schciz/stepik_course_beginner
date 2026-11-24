#include <iostream>

unsigned strlen(const char *str) {
  unsigned size = 0;
  for (unsigned i = 0; str[i] != '\0'; ++i) {
    ++size;
  }
  return size;
}

void strcat(char *to, const char *from) {
  unsigned size_to = strlen(to);
  unsigned size_from = strlen(from);
  for (unsigned i = 0; i <= size_from; ++i) {
    to[size_to + i] = from[i];
  }
}

int strstr(const char *text, const char *pattern) {
  int size_text = static_cast<int>(strlen(text));
  int size_pattern = static_cast<int>(strlen(pattern));
  for (int i = 0; i < size_text - size_pattern + 1; ++i) {
    int expect = static_cast<int>(i);
    for (int j = 0; j < size_pattern; ++j) {
      if (text[i + j] != pattern[j]) {
        expect = -1;
        break;
      }
    }
    if (expect != -1) {
      return expect;
    }
  }
  return -1;
}

int main() {
  std::cout << strstr("12345", "34") << '\n';
  std::cout << strstr("12345", "3") << '\n';
  std::cout << strstr("12345", "5") << '\n';
  std::cout << strstr("12345", "1") << '\n';
  std::cout << strstr("12345", "12345") << '\n';
  std::cout << strstr("12345", "") << '\n';
  std::cout << strstr("123456", "5") << '\n';
  std::cout << strstr("123456", "1234567") << '\n';
  std::cout << strstr("123456", "1234567890") << '\n';
}

