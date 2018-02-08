# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
OFLAGS= -c -g -ggdb -Wall -std=c++11
CFLAGS = -g -ggdb -Wall -std=c++11
#For threads: 
# needed: -pthread
# might be needed  -lpthread -Wl,--no-as-needed
#Segun algunos, hay que separarlo:
#CTHREADS = -pthread
#OTHREADS = -pthread

all: tests

tests: AdjMatrix.h AdjTest.cpp
	$(CC) $(CFLAGS) AdjMatrix.h AdjTest.cpp -o tests

clean:
	#rm *.gch
	#rm *.o
	rm tests
