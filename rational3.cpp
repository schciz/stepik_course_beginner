struct Rational {
  Rational(int numerator = 0, int denominator = 1);

  void add(Rational rational);
  void sub(Rational rational);
  void mul(Rational rational);
  void div(Rational rational);

  void neg();
  void inv();
  double to_double() const;

  Rational& operator+=(Rational rational);
  Rational& operator-=(Rational rational);
  Rational& operator*=(Rational rational);
  Rational& operator/=(Rational rational);

  Rational operator-() const;
  Rational operator+() const;

  int GetNumerator() const {
    return numerator_;
  }
  int GetDenominator() const {
    return denominator_;
  }

private:
  int numerator_;
  int denominator_;
};

Rational operator+(Rational lhs, Rational rhs);
Rational operator-(Rational lhs, Rational rhs);
Rational operator*(Rational lhs, Rational rhs);
Rational operator/(Rational lhs, Rational rhs);

bool operator<(const Rational& left, const Rational& other) {
  return left.GetNumerator() * other.GetDenominator() < left.GetDenominator() * other.GetNumerator();
}
bool operator==(const Rational& left, const Rational& other) {
  return left.GetNumerator() * other.GetDenominator() == left.GetDenominator() * other.GetNumerator();
}
bool operator>=(const Rational& left, const Rational& other) {
  return !(left < other);
}
bool operator<=(const Rational& left, const Rational& other) {
  return other >= left;
}
bool operator>(const Rational& left, const Rational& other) {
  return other < left;
}
bool operator!=(const Rational& left, const Rational& other) {
  return !(left == other);
}
