name = erg1
src = $(wildcard *.cpp)
obj = $(src:/c=.o)

CC = g++
CFLAGS = -std=c++0x -O3
LIBFLAGS = -lleda -lm

LedaLibs = '/home/raven/Documents/algo/LEDA/incl'
Leda = '/home/raven/Documents/algo/LEDA'

all: $(name)
$(name): $(obj)
	$(CC) $(CFLAGS) -o $@ $^ -I$(LedaLibs) -L$(Leda) $(LIBFLAGS)

run:
	./$(name)

clean:
	rm -f $(name)
