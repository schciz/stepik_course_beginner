#include <cstdlib>
#include <iostream>

uint64_t gcd(uint64_t a, uint64_t b) {
  if (0 == std::min(a, b)) {
    return std::max(a, b);
  }
  return gcd(std::max(a, b) % std::min(a, b), std::min(a, b));
}

int main() {
  std::cout << "GCD(12, 18):\n";
  std::cout << gcd(12, 18) << '\n';
  return EXIT_SUCCESS;
}

