#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
	int s = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	inet_aton("127.0.0.1", &addr.sin_addr);

	connect(s, (struct sockaddr *)&addr, sizeof(addr));

	write(s, "abcdefg", 3);

	close(s);

	return 0;
}
