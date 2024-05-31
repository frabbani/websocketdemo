#!/bin/bash

echo "compiling..."
gcc --std=c99 -c ../base64.c
gcc --std=c99 -c ../handshake.c
gcc --std=c99 -c ../sha1.c
gcc --std=c99 -c ../utf8.c
gcc --std=c99 -c ../ws.c
g++ --std=c++17 -c ../main.cpp 
echo "linking..."
g++ -o server.exe base64.o handshake.o main.o sha1.o utf8.o ws.o -lwsock32 -lws2_32
echo "done!"