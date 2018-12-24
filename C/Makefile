CC=cc

BIN=bin

all:
	mkdir -p $(BIN)
	$(CC) pointers.c -o $(BIN)/pointers
	$(CC) epoll_server.c -o $(BIN)/epoll_server
	$(CC) socket_server.c -o $(BIN)/server
	$(CC) socket_client.c -o $(BIN)/client

clean:
	rm -rf $(BIN)/
