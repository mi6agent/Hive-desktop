#include "UvTcpServer.h"

uv_loop_t* UvTcpServer::loop;
struct sockaddr_in UvTcpServer::addr;

UvTcpServer::UvTcpServer(QObject *parent) : QThread(parent)
{

}

void UvTcpServer::run()
{
  loop = uv_default_loop();

  uv_tcp_t server;
  uv_tcp_init(loop, &server);

  uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);

  uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
  int r = uv_listen((uv_stream_t*) &server, DEFAULT_BACKLOG, onNewConnection);
  if(r)
    {
      fprintf(stderr, "Listen error %s\n", uv_strerror(r));
    }
  uv_run(loop, UV_RUN_DEFAULT);

}

void UvTcpServer::onNewConnection(uv_stream_t *server, int status)
{
  if(status < 0)
    {
          fprintf(stderr, "New connection error %s\n", uv_strerror(status));
          // error!
          return;
    }

      uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
      uv_tcp_init(loop, client);
      if (uv_accept(server, (uv_stream_t*) client) == 0) {
          uv_read_start((uv_stream_t*) client, allocBuffer, echoRead);
      }
      else {
          uv_close((uv_handle_t*) client, NULL);
        }
}

void UvTcpServer::echoRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
  if (nread > 0) {
      write_req_t *req = (write_req_t*) malloc(sizeof(write_req_t));
      req->buf = uv_buf_init(buf->base, nread);
      uv_write((uv_write_t*) req, client, &req->buf, 1, echoWrite);
      return;
  }
  if (nread < 0) {
      if (nread != UV_EOF)
          fprintf(stderr, "Read error %s\n", uv_err_name(nread));
      uv_close((uv_handle_t*) client, NULL);
  }

  free(buf->base);
}

void UvTcpServer::echoWrite(uv_write_t *req, int status)
{
  if (status)
    {
      fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }
  freeWriteReq(req);
}

void UvTcpServer::allocBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
  buf->base = (char*) malloc(suggested_size);
  buf->len = suggested_size;
}

void UvTcpServer::freeWriteReq(uv_write_t *req)
{
  write_req_t *wr = (write_req_t*) req;
  free(wr->buf.base);
  free(wr);
}
