
bin/main : main.c queue.c queue.h stack.c stack.h token.h token.c
	mkdir -p bin
	cc -g main.c queue.c stack.c token.c  -o bin/main

run:
	./bin/main


clean: 
	rm -f ./bin/main

valgrind:
	valgrind ./bin/main

gdb:
	gdb ./bin/main
