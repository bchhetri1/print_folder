CC=g++
EFLAGS= -std=c++0x -lboost_serialization
all: print_folder

print_folder: print_folder.o
	$(CC) print_folder.o -o print_folder $(EFLAGS)

print_folder.o: print_folder.cpp print_folder.h main.cpp
	$(CC) print_folder.h print_folder.cpp main.cpp  $(EFLAGS)

clean:
	rm *o print_folder
