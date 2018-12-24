CC=cc

BIN=bin

all:
	mkdir -p $(BIN)
	$(CC) pointers.c -o $(BIN)/pointers
	# socket
	$(CC) epoll_server.c -o $(BIN)/epoll_server
	$(CC) socket_server.c -o $(BIN)/server
	$(CC) socket_client.c -o $(BIN)/client
	# thread
	$(CC) pthread.c -o $(BIN)/pthread -pthread

clean:
	rm -rf $(BIN)/
