#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

struct ThreadConn
{
	pthread_t id;
	int conn;
};

void *conn_handle(void *ptr)
{
	struct ThreadConn *info = (struct ThreadConn *)ptr;
	int conn = info->conn;

	char buf[1024];
	bzero(buf, 1024);
	read(conn, buf, 1024);

	// puts(buf);

	char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nfuck\n";
	write(conn, response, strlen(response));

	close(conn);

	free(info);
}

int main()
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = INADDR_ANY;

	int s = socket(AF_INET, SOCK_STREAM, 0);
	int optval = 1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	int b = bind(s, (struct sockaddr *)&addr, sizeof(addr));
	if (b == -1)
	{
		perror("bind error");
		return -1;
	}
	listen(s, 10);

	struct sockaddr_in client;
	int len = sizeof(client);

	while (true)
	{
		struct ThreadConn *info = malloc(sizeof(struct ThreadConn));

		info->conn = accept(s, (struct sockaddr *)&client, &len);

		pthread_create(&(info->id), NULL, conn_handle, info);
	}
}
