#include <sys/socket.h>

int main()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);

	connect(sock, addr, sizeof(addr));

	send(sock, "abc", 3, 0);

	return 0;
}
