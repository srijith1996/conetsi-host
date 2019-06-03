/*-------------------------------------------------------------------*/
#ifndef _SOCK_H_
#define _SOCK_H_
/*-------------------------------------------------------------------*/
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
/*-------------------------------------------------------------------*/
/* Functions to aid socket setup and reading */
int udp_socket_setup();
int bind_host_addr6(int sock_handle, struct in6_addr, in_port_t);
fd_set assign_read_handle(int sock_handle);
int udp_listen(int sock_handle, fd_set read_handles,
               struct sockaddr *remote_addr,
               int *remote_length,
               char *buf, int buf_size);
/*-------------------------------------------------------------------*/
#endif /* _SOCK_H_ */
/*-------------------------------------------------------------------*/
