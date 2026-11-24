#include <cstddef> // size_t
#include <cstring>

struct String {
  struct StringPart {
    const String& str;
    int begin;
    StringPart(const String& str, int begin) : str(str), begin(begin) {};
    String const operator[](int end) const {
      if (begin == end) {
        return "";
      }
      String sliced(static_cast<size_t>(end - begin), '\0');
      int sliced_idx = 0;
      for (int i = begin; i < end; ++i) {
        sliced.str[sliced_idx++] = str.str[i];
      }
      return sliced;
    }
  };

	String(const char *str = "");
	String(size_t n, char c);
	~String();

  String(const String &other);
  String &operator=(const String &other);

	void append(const String &other);

  StringPart const operator[](int begin) const {
    StringPart part(*this, begin);
    return part;
  }

	size_t size;
	char *str;
};

int main() {
  String const hello("hello");
  String const hell = hello[0][4]; // теперь в hell хранится подстрока "hell"
  String const ell  = hello[1][4]; // теперь в ell хранится подстрока "ell"
}

