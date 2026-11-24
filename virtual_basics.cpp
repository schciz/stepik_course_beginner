#include <iostream>

class A {
public:
  virtual ~A() {}
  virtual void f() {
    std::cout << "Virtual Base\n";
    g();
  }
  void g() {
    std::cout << "Non virtual Base\n";
  }
  void e() {
    f();
  }
};

class B : public A {
  void f() {
    std::cout << "Derived\n";
    g();
  };
};

int main() {
  B derived;
  A base;

  A &virt = derived;
  virt.f();
}

