#!/bin/bash

mkdir libs
cd libs
mkdir tmp
cd tmp
wget https://github.com/gansm/finalcut/archive/0.5.0.tar.gz
tar -xvzf 0.5.0.tar.gz
cd finalcut-0.5.0
case `uname` in
  Darwin*) sed -i '.bak' 's/libtoolize --copy/glibtoolize --copy/' autogen.sh;;
  *) ;;
esac
bash ./autogen.sh
./configure --prefix=`pwd`
make
make install
mv lib ../../lib
mv include ../../include
cd ../..
rm -rf tmp
cd ..
