# Makefile:  Main Makefile for Cosniwa
#
# platforms:  Linux, Mac
# (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
# license: BSD-2-Clause.

# Install full Cosniwa in the system


# #####################################
# INSTALL COSNIWA FOR C++, PYTHON
# #####################################
.PHONY: install
install: install_py install_cpp


# #####################################
# INSTALL COSIWA FOR C++
# #####################################
.PHONY: install_cpp
install_cpp:
	make -C c++/ install


# #####################################
# INSTALL COSNIWA FOR PYTHON
# #####################################
.PHONY: install_py
install_py:
	make -C python/ install


# #####################################
# BUILD CPP MODULE FOR OCTAVE
# #####################################
.PHONY: octave_cpp
octave_cpp:
	make -C octave/cpp compile


# #####################################
# CLEAN UP
# #####################################
clean:
	make -C c++/ clean
	make -C python/ clean
	make -C octave/ clean

