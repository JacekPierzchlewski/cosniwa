# Makefile:  Makefile for Python Cosniwa
#
# platforms:  Linux, Mac
# (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
# license: BSD-2-Clause.

# Install cCosniwa Python module on the computer
.PHONY: install
install:
	rm -fR cCosniwa
	mkdir cCosniwa
	python3 setup.py install
	rm -fR cCosniwa
	rm -fR build/

# Compile Cosniwa for Python
.PHONY: module
module:
	python3 setup.py build_ext --inplace

# Clean up
.PHONY: clean
clean:
	@rm -f MANIFEST
	@rm -f *.so
	@rm -fR build
	@rm -fR cCosniwa
	@rm -fR dist
