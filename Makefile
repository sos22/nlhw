hello: entry.o c_hello.o
	ld entry.o c_hello.o -o hello

entry.o: entry.S
	as entry.S -o entry.o

c_hello.o: c_hello.c
	gcc -Wall -nostdlib -nostdinc -c c_hello.c -o c_hello.o
