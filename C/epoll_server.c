#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main()
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = INADDR_ANY;

	int s = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

	bind(s, (struct sockaddr*) &addr, sizeof(addr));
    listen(s, 5);

	int epfd = epoll_create1(0);
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = s;

	epoll_ctl(epfd, EPOLL_CTL_ADD, s, &ev);

	while (1)
	{
		struct epoll_event events[10];
		int nfds = epoll_wait(epfd, events, 10, -1);

		for (int n = 0; n < nfds; n++)
		{
			int evfd = events[n].data.fd;
			if (evfd == s)
			{
				struct sockaddr_in client;
				int addrlen = sizeof(client);
				int conn = accept(s, (struct sockaddr*) &client, &addrlen);

				// set non blocking conn
				int flags = fcntl(conn, F_GETFL, 0);
				fcntl(conn, F_SETFL, flags | O_NONBLOCK);

				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = conn;

				epoll_ctl(epfd, EPOLL_CTL_ADD, conn, &ev);
			}
			else
			{
				char buf[1024];
				bzero(buf, 1024);

				read(evfd, buf, 1024);
				puts(buf);

				write(evfd, buf, strlen(buf));

				close(evfd);
			}
		}
	}
}

