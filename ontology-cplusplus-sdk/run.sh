g++ main.cpp crypto/Sign.cpp crypto/AES.cpp `pkg-config --cflags --libs openssl` -Wall -g -O2 -lcurl -std=c++11 -o main && ./main