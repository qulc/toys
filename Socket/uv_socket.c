#include <stdlib.h>
#include <sys/socket.h>
#include <uv.h>

uv_loop_t *loop;

typedef struct
{
	uv_write_t req;
	uv_buf_t buf;
} write_req_t;

void echo_write(uv_write_t *req, int status)
{
	write_req_t *wr = (write_req_t *)req;
	free(wr->buf.base);
	free(wr);
}

void on_close(uv_handle_t *handle)
{
	free(handle);
}

void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
	if (nread < 0)
	{
		uv_close((uv_handle_t *)client, on_close);
		return;
	}

	write_req_t *req = (write_req_t *)malloc(sizeof(write_req_t));
	req->buf = uv_buf_init(buf->base, nread);
	uv_write((uv_write_t *)req, client, buf, 1, echo_write);
}

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
	buf->base = (char *)malloc(suggested_size);
	buf->len = suggested_size;
}

void on_new_conn(uv_stream_t *server, int status)
{
	uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
	uv_tcp_init(loop, client);

	if (uv_accept(server, (uv_stream_t *)client) == 0)
		uv_read_start((uv_stream_t *)client, alloc_buffer, echo_read);
	else
		uv_close((uv_handle_t *)client, on_close);
}

int main()
{
	uv_tcp_t server;
	loop = uv_default_loop();
	uv_tcp_init(loop, &server);

	struct sockaddr_in addr;
	uv_ip4_addr("0.0.0.0", 5000, &addr);
	uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);

	uv_listen((uv_stream_t *)&server, 128, on_new_conn);

	return uv_run(loop, UV_RUN_DEFAULT);
}
