/*-------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "sock.h"
#include "utils.h"
/*-------------------------------------------------------------------*/
#define LISTEN_TIMEOUT  60
/*-------------------------------------------------------------------*/
#define DBG_PREFIX  "socket-util"
#define DEBUG 1
#if DEBUG
#define PRINTD(...) print_dbg(DBG_PREFIX, __VA_ARGS__)
#else /* DEBUG */
#define PRINTD(...)
#endif /* DEBUG */
/*-------------------------------------------------------------------*/
static struct sockaddr_in6 host_addr;
/* static struct sockaddr_in6 remote_addr; */
/*-------------------------------------------------------------------*/
int
udp_socket_setup()
{
  int on = 1;
  int sock_handle;

  if((sock_handle = socket(PF_INET6, SOCK_DGRAM, 0)) < 0) {
    perror("Unable to create socket\n");
    return -1;
  }

  /* set the socket to IPv6 only */
  if(setsockopt(sock_handle, IPPROTO_IPV6, IPV6_V6ONLY, 
     &on, sizeof(on))) {

    perror("Unable to set socket options\n");
    return -1;
  }
 
  PRINTD("Created UDP socket successfully!");
  return sock_handle;
}
/*-------------------------------------------------------------------*/
int
bind_host_addr6(int sock_handle, struct in6_addr addr, in_port_t port)
{
  memset(&host_addr, 0, sizeof(host_addr));

  host_addr.sin6_family = AF_INET6;
  host_addr.sin6_addr = addr;
  host_addr.sin6_port = port;

  /* bind address to the socket */
  if(bind(sock_handle, (struct sockaddr *) &host_addr,
         sizeof(host_addr)) == -1) {
      perror("Unable to bind address!\n");
      return -1;
  }
  
  PRINTD("Address successfully bound");
  return 0;
}
/*-------------------------------------------------------------------*/
#if 0
int
setup_remote6(in_port_t port)
{
  memset(&remote_addr, 0, sizeof(remote_addr));

  remote_addr.sin6_family = AF_INET6;
  remote_addr.sin6_port = htons(PORT_NUMBER);

  /* Check validity of IPv6 Address */
  if(inet_pton(AF_INET6, MY_IP_ADDR, &remote_addr.sin6_addr) != 1) {
    PRINTD("[socket_util] inet_pton... failed");
    exit(0);
  }
  PRINTD("[socket_util] Remote setup done");
}
#endif /* 0 */
/*-------------------------------------------------------------------*/
fd_set
assign_read_handle(int sock_handle)
{
  fd_set read_handles;

  FD_ZERO(&read_handles);
  FD_SET(sock_handle, &read_handles);
  
  return read_handles;
}
/*-------------------------------------------------------------------*/
static int
select_sock(int sock_handle, fd_set read_handles)
{
  struct timeval timeout;

  timeout.tv_sec = LISTEN_TIMEOUT;
  timeout.tv_usec = 0;

  /* validate readiness of file handles pointed by read_handles*/
  return select(((int)sock_handle + 1), 
                &read_handles, NULL, 
                NULL, &timeout);
}
/*-------------------------------------------------------------------*/
int 
udp_listen(int sock_handle, fd_set read_handles,
           struct sockaddr *remote_addr, 
           int *remote_length,
           char *buf, int buf_size) 
{
  int recv_size;
  int select_ret;

  select_ret = select_sock(sock_handle, read_handles);

  if(select_ret < -1) {
    perror("Select error\n");
    return -1;

  } else if(select_ret == 0) {
    PRINTD("Timeout: No data received");
    return 0;

  } else {
    if(FD_ISSET(sock_handle, &read_handles)) {
      if((recv_size = recvfrom(sock_handle, buf, buf_size, 0,
                 remote_addr, (unsigned int *)remote_length)) < 0) {
        perror("Error in recvfrom.\n");
      }
    }
  }
  return recv_size;
}
/*-------------------------------------------------------------------*/
