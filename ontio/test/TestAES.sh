#!/bin/bash
path=$(
	cd $(dirname $0)
	pwd
)
cd $path
g++ TestAES.cpp $(pkg-config --cflags gtest_main --libs openssl libcurl gtest_main) -std=c++11 -o ../bin/test
../bin/test
rm ../bin/test &&
cd $path/../