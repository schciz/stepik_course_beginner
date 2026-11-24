#include <iostream>
#include <algorithm>

int **AllocateMatrix(unsigned rows, unsigned cols) {
  uint8_t *matrix = new uint8_t[sizeof(int *) * rows + sizeof(int) * rows * cols];
  for (unsigned i = 0; i < rows; ++i) {
    reinterpret_cast<int **>(matrix)[i] = reinterpret_cast<int *>(matrix + rows * sizeof(int *) + cols * sizeof(int) * i);
  }
  return reinterpret_cast<int **>(matrix);
}

void ReleaseMatrix(int **matrix) {
  delete [] reinterpret_cast<uint8_t *>(matrix);
}

void OutMatrix(int **matrix, unsigned rows, unsigned cols) {
  for (unsigned i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j) {
      std::cout << matrix[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

void swap_min(int *m[], unsigned rows, unsigned cols) {
  if (0 == rows || 0 == cols) {
    return;
  }
  int min = *std::min_element(m[0], m[0] + cols);
  unsigned index = 0;
  for (unsigned i = 1; i < rows; ++i) {
    int min_i = *std::min_element(m[i], m[i] + cols);
    if (min_i < min) {
      min = min_i;
      index = i;
    }
  }
  std::swap(m[0], m[index]);
}

int **transpose(const int *const *m, unsigned rows, unsigned cols) {
  int **result = AllocateMatrix(cols, rows);
  for (unsigned i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j) {
      result[j][i] = m[i][j];
    }
  }
  return result;
}

int main() {
  constexpr unsigned rows = 3;
  constexpr unsigned cols = 4;
  int **matrix = AllocateMatrix(rows, cols);
  for (unsigned i = 0; i < cols; ++i) {
    matrix[0][i] = 3;
  }
  for (unsigned i = 0; i < cols; ++i) {
    matrix[1][i] = 2;
  }
  for (unsigned i = 0; i < cols; ++i) {
    matrix[2][i] = 1;
  }
  OutMatrix(matrix, rows, cols);
  swap_min(matrix, rows, cols);
  OutMatrix(matrix, rows, cols);
  ReleaseMatrix(matrix);
}

