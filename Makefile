CC=g++
EFLAGS= -std=c++0x -lboost_serialization

all: print_folder

print_folder: print_folder.o main.o 
	$(CC) main.o print_folder.o -o print_folder $(EFLAGS)

main.o: main.cpp print_folder.cpp print_folder.h 
	$(CC) -c main.cpp print_folder.cpp print_folder.h $(EFLAGS)

print_folder.o: print_folder.cpp print_folder.h
	$(CC) -c print_folder.h print_folder.cpp $(EFLAGS)

clean:
	rm *o print_folder
