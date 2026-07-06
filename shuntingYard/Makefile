
bin/main : main.c queue.c queue.h stack.c stack.h token.h token.c utils.h utils.c
	mkdir -p bin
	cc -g main.c queue.c stack.c token.c utils.c  -o bin/main

run:
	./bin/main


clean: 
	rm -f ./bin/main

valgrind:
	valgrind ./bin/main

gdb:
	gdb ./bin/main
