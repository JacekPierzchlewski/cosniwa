# Makefile:  Makefile for C++ Cosniwa
#
# platforms:  Linux, Mac
# (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
# license: BSD-2-Clause.

# Install Cosniwa static library for C++
install: cosniwa
	sudo ./install.sh

# Make cosniwa.o and static Cosniwa library
.PHONY: cosniwa
cosniwa: cosniwa.o libcosniwa.a

cosniwa.o: cosniwa.cpp cosniwa.h
	g++ -Wall -c cosniwa.cpp

# Generate C++ static library
libcosniwa.a: cosniwa.o
	ar rcs libcosniwa.a cosniwa.o

# Clean up
.PHONY: clean
clean:
	@rm -f libcosniwa.a
	@rm -f cosniwa.o
