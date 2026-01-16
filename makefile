CC = gcc
C++ = g++
C_FOLDER = C
CPP_FOLDER = C++
RUST_FOLDER = Rust
BIN = bin
SRC = src
OBJECTS = objects
DATA_STRUCTURES = data_structure
FLAGS = -std=c++20 -O0 -g \
-fsanitize=address,vptr \
-fno-omit-frame-pointer \
-Wall -Wextra -Wpedantic \

run: main
	 $(CPP_FOLDER)/$(BIN)/main 

	 
main: main.o
	$(C++) $(CPP_FOLDER)/$(OBJECTS)/main.o $(CPP_FOLDER)/$(OBJECTS)/Node.o $(CPP_FOLDER)/$(OBJECTS)/LinkedList.o -o $(CPP_FOLDER)/$(BIN)/main

main.o: Node.o LinkedList.o
	$(C++) -c $(CPP_FOLDER)/$(SRC)/$(DATA_STRUCTURES)/main.cpp -o $(CPP_FOLDER)/$(OBJECTS)/main.o

LinkedList.o: $(CPP_FOLDER)/$(SRC)/$(DATA_STRUCTURES)/LinkedList.h $(CPP_FOLDER)/$(SRC)/$(DATA_STRUCTURES)/LinkedList.cpp
	$(C++) -c $(CPP_FOLDER)/$(SRC)/$(DATA_STRUCTURES)/LinkedList.cpp -o $(CPP_FOLDER)/$(OBJECTS)/LinkedList.o

Node.o: $(CPP_FOLDER)/$(SRC)/$(DATA_STRUCTURES)/Node.h $(CPP_FOLDER)/$(SRC)/$(DATA_STRUCTURES)/Node.cpp
	$(C++) -c $(CPP_FOLDER)/$(SRC)/$(DATA_STRUCTURES)/Node.cpp -o $(CPP_FOLDER)/$(OBJECTS)/Node.o


