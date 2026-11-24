#include <iostream>

struct Expression {
  virtual ~Expression() = default;
  virtual double evaluate() const = 0;
};

struct Number : Expression {
  Number(double value)
    : value(value)
  {}
  double evaluate() const override {
    return value;
  }
private:
  double value;
};

struct BinaryOperation : Expression {
  /*
    Здесь op это один из 4 символов: '+', '-', '*' или '/', соответствующих операциям,
    которые вам нужно реализовать.
  */
  BinaryOperation(Expression const * left, char op, Expression const * right)
    : left(left), right(right), op(op)
  { }
  ~BinaryOperation() override {
    delete left;
    delete right;
  }
  BinaryOperation(const BinaryOperation&) = delete;
  BinaryOperation& operator=(const BinaryOperation&) = delete;
  double evaluate() const override {
    const double l = left->evaluate();
    const double r = right->evaluate();
    double result = 0;
    switch (op) {
      case '+':
        result = l + r;
        break;
      case '-':
        result = l - r;
        break;
      case '*':
        result = l * r;
        break;
      case '/':
        result = l / r;
        break;
    }
    return result;
  }
private:
  Expression const * left;
  Expression const * right;
  char op;
};

struct Vptr {
  void *vptr;
};

bool check_equals(Expression const *left, Expression const *right) {
  return *reinterpret_cast<void * const *>(left) == *reinterpret_cast<void * const *>(right);
  // return reinterpret_cast<const Vptr *>(left)->vptr == reinterpret_cast<const Vptr *>(right)->vptr;
}

int main() {
  // сначала создаём объекты для подвыражения 4.5 * 5
  Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
  // потом используем его в выражении для +
  Expression * expr = new BinaryOperation(new Number(3), '+', sube);
  // вычисляем и выводим результат: 25.5
  std::cout << expr->evaluate() << std::endl;
  // тут освобождаются *все* выделенные объекты
  // (например, sube будет правым операндом expr, поэтому его удалять не нужно)
  delete expr;
}
