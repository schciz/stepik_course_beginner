CC = g++
CFLAGS = -g -fno-omit-frame-pointer -fsanitize=address,undefined,leak -fno-permissive -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror -std=c++2c

BINS := $(patsubst %.cpp,%.out,$(wildcard *.cpp))
all: $(BINS)

%: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

