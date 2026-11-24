#include <iostream>

struct Cls {
  Cls(char c, double d, int i) : c(c), d(d), i(i) {
    std::cout << this->c << ' ' << this->d << ' ' << this->i << '\n';
  }
private:
  char c;
  double d;
  int i;
};

struct ClsPublic {
  char c;
  double d;
  int i;
};

char &get_c(Cls &cls) {
  return reinterpret_cast<ClsPublic*>(&cls)->c;
}

double &get_d(Cls &cls) {
  return reinterpret_cast<ClsPublic*>(&cls)->d;
}

int &get_i(Cls &cls) {
  return reinterpret_cast<ClsPublic*>(&cls)->i;
}

int main() {
  Cls cls('v', 13.25, 10);
  std::cout << get_c(cls) << '\n'
            << get_d(cls) << '\n'
            << get_i(cls) << '\n';
}


