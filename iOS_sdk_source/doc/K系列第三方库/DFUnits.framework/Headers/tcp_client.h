#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


struct tcp_client{
    int fd;
};

int tcp_connect(const char *ip, const int port, struct tcp_client **tc);

int tcp_read(struct tcp_client *tc, unsigned char *buf, int size);

int tcp_write(struct tcp_client *tc, unsigned char *buf, int size);

int tcp_close(struct tcp_client *tc);

#endif
