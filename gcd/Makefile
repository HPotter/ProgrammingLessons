CC = g++
CFLAGS = -Wall -g
O = test1.o test2.o fraction.o polynom.o

all: test1 test2
	rm -f $(O)

test1: test1.o polynom.o fraction.o
	$(CC) $(CFLAGS) test1.o polynom.o fraction.o -o test1
	rm -f $(O)

test2: test2.o polynom.o fraction.o
	$(CC) $(CFLAGS) test2.o polynom.o fraction.o -o test2
	rm -f $(O)

polynom.o: polynom.cpp
	$(CC) $(CFLAGS) -c polynom.cpp -o polynom.o

fraction.o: fraction.cpp
	$(CC) $(CFLAGS) -c fraction.cpp -o fraction.o

test1.o: test1.cpp
	$(CC) $(CFLAGS) -c test1.cpp -o test1.o

test2.o: test2.cpp
	$(CC) $(CFLAGS) -c test2.cpp -o test2.o

clean:
	rm -f test1 test2 $(O)
