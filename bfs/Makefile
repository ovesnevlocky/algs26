C = cc
CFLAGS = -g
RM = rm -f
BIN = bin/main
SRC = $(wildcard *.c)
OBJ = $(SRC:.c = .o)

%.o: %.c 
	$(CC) $(CFLAGS) -c $^ -o $@

$(BIN): $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@

vis: $(BIN)
	./$(BIN) | dot -Tpdf > vis.pdf

run: 
	./$(BIN)

gdb:
	gdb ./$(BIN)

clean: 
	$(RM) -r bin *.o vis.pdf

