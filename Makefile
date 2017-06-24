# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-c -Wall
EFLAGS=-std=c++0x -lboost_serialization
all: print_folder

print_folder: print_folder.o main.o 
	$(CC) main.o print_folder.o -o print_folder

main.o: main.cpp
	$(CC) main.cpp

print_folder.o: print_folder.cpp print_folder.h
	$(CC) print_folder.cpp print_folder.h $(EFLAGS)

clean:
	rm *o print_folder
