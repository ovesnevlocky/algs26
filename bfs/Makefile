CC = cc
CFLAGS = -g
RM = rm -f
BIN = bin/main
SRC = $(wildcard *.c) $(wildcard ./bfs/*.c) $(wildcard ./dfs/*.c)
OBJ = $(SRC:.c = .o)

%.o: %.c 
	$(CC) $(CFLAGS) -c $^ -o $@

$(BIN): $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@

vis: $(BIN)
	./$(BIN) $(ARGS) | dot -Tpdf > vis.pdf

run: $(BIN) 
	./$(BIN) $(ARGS)

gdb:
	gdb -iex "set debuginfod enabled off"  ./$(BIN)

clean: 
	$(RM) -r bin *.o vis.pdf

valg:
	valgrind ./$(BIN)
