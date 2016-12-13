CC = g++

matrix.out: main.o function.o
	$(CC) -g -Wall -pedantic $^ -o $@

function.o: function.cpp matrix.h
	$(CC) -g -Wall -pedantic -c $< -o $@

main.o: test_matrix.cpp matrix.h
	$(CC) -g -Wall -pedantic -c $< -o $@

.PHONY: clean

clean:
	-rm function.o main.o matrix.out
