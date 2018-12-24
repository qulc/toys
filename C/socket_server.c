#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


int main()
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = INADDR_ANY;

	int s = socket(AF_INET, SOCK_STREAM, 0);
	int optval = 1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	int b = bind(s, (struct sockaddr*)&addr, sizeof(addr));
	if (b == -1)
	{
		perror("bind error");
		return -1;
	}
	listen(s, 10);

	struct sockaddr_in client;
	int len = sizeof(client);
	
	char buf[1024];

	while (true)
	{
		int conn = accept(s, (struct sockaddr*)&client, &len);

		bzero(buf, 1024);
		read(conn, buf, 1024);

		puts(buf);

		write(conn, buf, strlen(buf));
		
		close(conn);
	}	
}
