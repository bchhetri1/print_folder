# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS= -c -Wall
EFLAGS= -lboost_serialization
all: print_folder

print_folder: print_folder.o main.o 
	$(CC) $(CFLAGS) main.o print_folder.o -o print_folder -std=c++0x $(EFLAGS)

main.o: main.cpp
	$(CC) main.cpp

print_folder.o: print_folder.h
	$(CC) $(CFLAGS) print_folder.cpp -std=c++0x $(EFLAGS)

clean:
	rm *o print_folder
