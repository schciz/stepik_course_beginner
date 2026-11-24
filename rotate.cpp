#include <iostream>

void Swap(int &a, int &b) {
  int c = a;
  a = b;
  b = c;
}

void RotateRight(int a[], unsigned size) {
  for (unsigned i = 0; i < size - 1; ++i) {
    Swap(a[i + 1], a[i]);
  }
}

void RotateLeft(int a[], unsigned size) {
  for (unsigned i = size - 1; i >= 1; --i) {
    Swap(a[i - 1], a[i]);
  }
}

void rotate(int a[], unsigned size, int shift) {
  if (size <= 1) {
    return;
  }
  shift = shift % static_cast<int>(size);
  if (0 == shift) {
    return;
  }
  if (shift > 0) {
    RotateRight(a, size);
    rotate(a, size, --shift);
  } else {
    RotateLeft(a, size);
    rotate(a, size, ++shift);
  }
}

int main() {
  int a[] = {1, 2, 3, 4, 5};
  rotate(a, sizeof(a) / sizeof(int), -2);
  rotate(a, sizeof(a) / sizeof(int), 3);
  for (unsigned i = 0; i < 5; ++i) {
    std::cout << a[i] << ' ';
  }
  std::cout << '\n';
}

