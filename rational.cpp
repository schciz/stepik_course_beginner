// Вам нужно определить операторы +=, -=, *=, /= для класса Rational так, чтобы они могли принимать в качестве аргументов и объекты типа Rational и целые числа. Кроме того вам необходимо определить операторы унарного минуса и плюса для класса Rational.
struct Rational {
  Rational(int numerator = 0, int denominator = 1);

  void add(Rational rational);
  void sub(Rational rational);
  void mul(Rational rational);
  void div(Rational rational);

  void neg();
  void inv();
  double to_double() const;

  Rational &operator+=(const Rational &other) {
    add(other);
    return *this;
  }
  Rational &operator-=(const Rational &other) {
    sub(other);
    return *this;
  }
  Rational &operator*=(const Rational &other) {
    mul(other);
    return *this;
  }
  Rational &operator/=(const Rational &other) {
    div(other);
    return *this;
  }

  Rational &operator+=(int other) {
    add(Rational(other));
    return *this;
  }
  Rational &operator-=(int other) {
    sub(Rational(other));
    return *this;
  }
  Rational &operator*=(int other) {
    mul(Rational(other));
    return *this;
  }
  Rational &operator/=(int other) {
    div(Rational(other));
    return *this;
  }

  Rational operator+() const {
    return Rational(numerator_, denominator_);
  }
  Rational operator-() const {
    Rational copy(numerator_, denominator_);
    copy.neg();
    return copy;
  }

private:
  int numerator_;
  int denominator_;
};

int main() {
  Rational a;
  Rational b;
  a += b;
  a += 1;
}
