CC=cc

BIN=bin

all:
	mkdir -p $(BIN)
	$(CC) pointers.c -o $(BIN)/pointers
	# thread
	$(CC) pthread.c -o $(BIN)/pthread -pthread

clean:
	rm -rf $(BIN)/
