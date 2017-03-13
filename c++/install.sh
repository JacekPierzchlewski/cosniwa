#!/bin/bash
#
# install.sh:  install C++ Cosniwa library on a local computer
#
# platforms:  Linux, Mac
# (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
# license: BSD-2-Clause.

VERSION="1.0"
INC_DIR="/usr/local/include"   # Directory for "cosniwa.h" header
LIB_DIR="/usr/local/lib"       # Directory for libcosniwa.a

# You must be root to run this script
if [ "$EUID" -ne 0 ]
  then echo "Please run 'install.sh' as superuser!"
  exit
fi

# If libcosniwa.a does not exist, instruct user to generate it
if [ ! -f ./libcosniwa.a ]
  then echo "Please compile Cosniwa as library! ($ make cosniwa)"
  exit
fi

# if include directory (default: /usr/local/include)
# does not exists, create it
if [ ! -d "$INC_DIR" ]; then
    mkdir $INC_DIR
    echo "$INC_DIR created"
fi

# if library directory (default /usr/local/lib)
# does not exists, create it
if [ ! -d "$LIB_DIR" ]; then
    mkdir $LIB_DIR
    echo "$LIB_DIR created"
fi

# Copy the include and library file
cp -v ./cosniwa.h "$INC_DIR"
cp -v ./libcosniwa.a "$LIB_DIR/libcosniwa-$VERSION.a"
rm -f "$LIB_DIR/libcosniwa.a"
ln -vs "$LIB_DIR/libcosniwa-$VERSION.a" "$LIB_DIR/libcosniwa.a"
