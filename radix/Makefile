
bin/radix : radix.c 
	mkdir -p bin
		cc -g radix.c -o bin/radix

clean : 
	rm -f bin/radix

run : 
	./bin/radix > res.txt

valgrind : 
	valgrind ./bin/radix

gdb : 
	gdb ./bin/radix
