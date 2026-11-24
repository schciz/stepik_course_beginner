#include <cmath>
#include <cstdlib>
#include <iostream>

int main() {
  double a = 0;
  double b = 0;
  double c = 0;

  std::cin >> a >> b >> c;

  double x1 = (-b - std::sqrt(std::pow(b, 2.0) - 4 * a * c)) / (2 * a);
  double x2 = (-b + std::sqrt(std::pow(b, 2.0) - 4 * a * c)) / (2 * a);

  if (std::isnan(x1) && std::isnan(x2)) {
    std::cout << "No real roots\n";
  } else {
    if (std::abs(x1) == 0) {
      x1 = 0;
    }
    if (std::abs(x2) == 0) {
      x2 = 0;
    }
    std::cout << x1 << ' ' << x2 << '\n';
  }
  return EXIT_SUCCESS;
}

