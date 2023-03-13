#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

struct tcp_server{
    int fd;
};

#include "tcp_client.h"

int tcp_new_server(const int port ,struct tcp_server **ts);

int tcp_new_client(int fd, struct tcp_client **tc);

int tcp_listen(struct tcp_server *ts, const int max);

int tcp_accept(struct tcp_server *ts, struct sockaddr *addr, socklen_t *len);

int tcp_server_close(struct tcp_server *ts);

#endif
