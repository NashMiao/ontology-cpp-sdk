#!/bin/bash
path=$(
	cd $(dirname $0)
	pwd
)
cd $path
g++ TestAES.cpp $(pkg-config --cflags --libs openssl libcurl) -lgtest_main -lgtest -lpthread -std=c++11 -o ../bin/test
../bin/test
rm ../bin/test &&
cd $path/../