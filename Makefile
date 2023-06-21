build:
	g++ main.cpp -o bin/main -lraylib

run: build
	bin/main

