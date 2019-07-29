#include <stdlib.h>
#include <sys/socket.h>
#include <uv.h>

uv_loop_t *loop;

void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
	if (nread < 0)
	{
		uv_close((uv_handle_t *)client, NULL);
		return;
	}
	uv_buf_t *rbuf = (uv_buf_t *)malloc(sizeof(uv_buf_t));

	rbuf->base = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\nfuck\n";
	rbuf->len = 49;

	uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
	uv_write(req, client, rbuf, 1, NULL);

	uv_close((uv_handle_t *)client, NULL);
}

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
	buf->base = (char *)malloc(suggested_size);
	buf->len = suggested_size;
}

void on_new_connect(uv_stream_t *server, int status)
{
	uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
	uv_tcp_init(loop, client);

	uv_accept(server, (uv_stream_t *)client);
	uv_read_start((uv_stream_t *)client, alloc_buffer, echo_read);
}

int main()
{
	uv_tcp_t server;
	loop = uv_default_loop();
	uv_tcp_init(loop, &server);

	struct sockaddr_in addr;
	uv_ip4_addr("0.0.0.0", 5000, &addr);
	uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);

	uv_listen((uv_stream_t *)&server, 128, on_new_connect);

	return uv_run(loop, UV_RUN_DEFAULT);
}
