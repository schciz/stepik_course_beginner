#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <iostream>

struct String {
	String(const char *str = "") : size(strlen(str)), str(new char[size + 1]) {
    strcpy(this->str, str);
  }
  String(size_t n, char c) : size(n), str(new char[size + 1]) {
    for (size_t i = 0; i < size; ++i) {
      str[i] = c;
    }
    str[size] = '\0';
  }

  String(const String& other) : size(other.size), str(new char[size + 1]) {
    strcpy(str, other.str);
  };
  String& operator=(const String& other) {
    if (this != &other) {
      this->size = other.size;
      delete [] this->str;
      this->str = new char[this->size + 1];
      strcpy(this->str, other.str);
    }
    return *this;
  }

  void append(String &other) {
    String appended(this->size + other.size, '\0');
    memcpy(appended.str, this->str, this->size);
    memcpy(appended.str + this->size, other.str, other.size);
    delete []this->str;
    this->size = this->size + other.size;
    this->str = new char[this->size + 1];
    strcpy(this->str, appended.str);
  }

  ~String() {
    delete []str;
  }
	size_t size;
	char *str;
};

int main() {
  String s = "hello world!";
  String a = " wut";
  s.append(a);
  s.append(s);
  std::cout << s.str << '\n';
}

