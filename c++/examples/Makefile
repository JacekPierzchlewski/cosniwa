# Makefile:  Makefile for C++ Cosniwa examples
#
# platforms:  Linux, Mac
# (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
# license: BSD-2-Clause.

# Compile all the examples
.PHOHY: all
all:
	make example1
	make example2
	make example3A
	make example3B
	make example4
	make example5A
	make example5B
	make case1

# Make cosniwa.o in the examples directory
cosniwa:
	g++ -c cosniwa.cpp

# Compile examples and cases:
example1:  cosniwa  example1.cpp
	g++ -c example1.cpp
	g++  example1.o cosniwa.o -o example1

example2:  cosniwa  example2.cpp
	g++ -c example2.cpp
	g++  example2.o cosniwa.o -o example2

example3A:  cosniwa  example3A.cpp
	g++ -c example3A.cpp
	g++  example3A.o cosniwa.o -o example3A

example3B:  cosniwa  example3B.cpp
	g++ -c example3B.cpp
	g++  example3B.o cosniwa.o -o example3B

example4:  cosniwa  example4.cpp
	g++ -c example4.cpp
	g++  example4.o cosniwa.o -o example4

example5A:  cosniwa  example5A.cpp
	g++ -c example5A.cpp
	g++  example5A.o cosniwa.o -o example5A

example5B:  cosniwa  example5B.cpp
	g++ -c example5B.cpp
	g++  example5B.o cosniwa.o -o example5B

case1:  cosniwa  case1.cpp
	g++ -c case1.cpp
	g++  case1.o cosniwa.o -o case1

# Clean up
.PHOHY: clean
clean:
	@rm -f *.o
	@rm -f example1
	@rm -f example2
	@rm -f example3A
	@rm -f example3B
	@rm -f example4
	@rm -f example5A
	@rm -f example5B
	@rm -f case1
