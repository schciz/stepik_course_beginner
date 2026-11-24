#include <iostream>

struct String {
  String(size_t n, char c);
  char *str;
};

String spaces(size_t n) 
{
    const String s(n, ' ');
    return s;
}

int& wont_compile_ref(int n) {
  return n;
}

int* wont_compile_ptr(int n) {
  return &n;
}

const char return_const_char();

int main() {
  const int& i = 1;
  int& j = 1;
  char test = return_const_char();
  std::cout << spaces(10).str << "\n";
  return 0;
}
