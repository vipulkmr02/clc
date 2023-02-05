default:
	g++ main.cpp -o main

install:
	sudo g++ main.cpp -o /usr/bin/clc
