#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>


int main()
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = INADDR_ANY;

	int s = socket(AF_INET, SOCK_STREAM, 0);

	if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		puts(strerror(errno));
		return -1;
	}
	listen(s, 10);

	struct sockaddr_in client;
	int len = sizeof(client);
	
	char buf[1024];

	while (1)
	{
		int conn = accept(s, (struct sockaddr*)&client, &len);

		bzero(buf, 1024);
		read(conn, buf, 1024);

		puts(buf);

		write(conn, buf, strlen(buf));
		
		close(conn);
	}	
	// close(s);

	return 0;
}
