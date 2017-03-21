CC=gcc-6
CFLAGS=-Wall -g -O3
OMP=-fopenmp
CFLAGS+= $(OMP)
SDLFLAGS=`sdl2-config --cflags --libs`

all: dydama

dydama: dydama.o world.o ic.o sort.o graphics.o vector4.o
	$(CC) $(CFLAGS) $(SDLFLAGS) $^ -o $@

dydama.o: dydama.c dydama.h
	$(CC) $(CFLAGS) -c $< -o $@

world.o: world.c world.h
	$(CC) $(CFLAGS) -c $< -o $@

ic.o: ic.c ic.h
	$(CC) $(CFLAGS) -c $< -o $@

sort.o: sort.c sort.h
	$(CC) $(CFLAGS) -c $< -o $@

graphics.o: graphics.c graphics.h
	$(CC) $(CFLAGS) -c $< -o $@

vector4.o: vector4.c vector4.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -rf *.o dydama dydama.dSYM
