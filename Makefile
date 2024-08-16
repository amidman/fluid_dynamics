CC=g++
CFLAGS=
LDFLAGS=-lgtest -pthread

all:
	$(CC) ./tests/tests.cpp -o ./build/tests.out $(CFLAGS) $(LDFLAGS)