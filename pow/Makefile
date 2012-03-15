all: test1 test2 controltest1 controltest2

check: check1 check2

check1: test1 controltest1
	 ../checker ./test1 ./controltest1 tests1

check2: test2 controltest2
	 ../checker ./test2 ./controltest2 tests2

test1:
	g++ -Wall -g $@.cpp matrix/exceptions.cpp -o $@

test2:
	g++ -Wall -g $@.cpp matrix/exceptions.cpp -o $@

controltest1:
	g++ -Wall -g $@.cpp matrix/exceptions.cpp -o $@

controltest2:
	g++ -Wall -g $@.cpp matrix/exceptions.cpp -o $@

clean:
	rm -f test1 test2 controltest1 controltest2
