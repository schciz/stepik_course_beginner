#include <cstdlib>
#include <iostream>

int main()
{
  char character = '\0';
  while (std::cin.get(character) && !std::cin.eof()) {
    if (' ' == character) {
      std::cout << ' ';
    }
    while (' ' == character) {
      std::cin.get(character);
    }
    std::cout << character;
  }
  return EXIT_SUCCESS;
}

