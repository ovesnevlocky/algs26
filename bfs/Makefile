C = cc
CFLAGS = -g
RM = rm -f
BIN = main
SRC = $(wildcard *.c)
OBJ = $(SRC:.c = .o)

%.o: %.c 
	$(CC) $(CFLAGS) -c $^ -o $@

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

vis: $(BIN)
	./$(BIN) | dot -Tpdf > vis.pdf

run: 
	./main
