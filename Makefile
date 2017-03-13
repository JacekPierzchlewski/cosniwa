# Makefile:  Main Makefile for Cosniwa
#
# platforms:  Linux, Mac
# (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
# license: BSD-2-Clause.

# Install full Cosniwa in the system
.PHONY: install
install:
	make -C c++/ install
	make -C python/ install

