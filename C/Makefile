CC=cc

BIN=bin/
OBJ=obj/

all:
	mkdir -p $(BIN) $(OBJ)
	$(CC) -o $(OBJ)pointers.o -c pointers.c
	$(CC) -o $(BIN)pointers $(OBJ)pointers.o

clean:
	rm -f $(BIN)/* $(OBJ)/*
