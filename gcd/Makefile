CC = g++
CFLAGS = -Wall -g
O = test1.o test2.o test3.o test4.o test5.o fraction.o polynom.o

all: test1 test2
	rm -f $(O)

test1: test1.o polynom.o fraction.o
	$(CC) $(CFLAGS) test1.o polynom.o fraction.o -o test1
	rm -f $(O)

test2: test2.o polynom.o fraction.o
	$(CC) $(CFLAGS) test2.o polynom.o fraction.o -o test2
	rm -f $(O)

test3: test3.o polynom.o fraction.o
	$(CC) $(CFLAGS) test3.o polynom.o fraction.o -o test3
	rm -f $(O)

test4: test4.o polynom.o fraction.o
	$(CC) $(CFLAGS) test4.o polynom.o fraction.o -o test4
	rm -f $(O)

test5: test5.o polynom.o fraction.o
	$(CC) $(CFLAGS) test5.o polynom.o fraction.o -o test5
	rm -f $(O)

polynom.o: polynom.cpp
	$(CC) $(CFLAGS) -c polynom.cpp -o polynom.o

fraction.o: fraction.cpp
	$(CC) $(CFLAGS) -c fraction.cpp -o fraction.o

test1.o: test1.cpp
	$(CC) $(CFLAGS) -c test1.cpp -o test1.o

test2.o: test2.cpp
	$(CC) $(CFLAGS) -c test2.cpp -o test2.o

test4.o: test4.cpp
	$(CC) $(CFLAGS) -c test4.cpp -o test4.o

test3.o: test3.cpp
	$(CC) $(CFLAGS) -c test3.cpp -o test3.o

test5.o: test5.cpp
	$(CC) $(CFLAGS) -c test5.cpp -o test5.o

clean:
	rm -f test1 test2 test3 test4 test5 $(O)
