/*-------------------------------------------------------------------*/
#ifndef _REQUEST_BUFFER_H_
#define _REQUEST_BUFFER_H_
/*-------------------------------------------------------------------*/
#include "data-buffer.h"
#include "mutex.h"
/*-------------------------------------------------------------------*/
#define PACKET_BUFFER_SIZE 1000000
#define THREAD_POOL_SIZE   3
/*-------------------------------------------------------------------*/
struct http_response {
  char *ptr;
  size_t len;
};
/*-------------------------------------------------------------------*/
#define REQUEST_URL_SIZE   200

/*
 * struct for shared circular buffer entry
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                        Global Counter                         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                            Index                              |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * .                                                               .
 * .                        HTTP Request URL                       .
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 */
struct request_buff {
  unsigned long g_ctr;
  int index;
  char request_url[REQUEST_URL_SIZE];
};

#define REQUEST_BUFF(x)     (struct request_buff *)x
#define REQUEST_BUFFER_SIZE (4 + REQUEST_URL_SIZE)
/*-------------------------------------------------------------------*/
struct request_buff_info {
  int produce_pos;
  int consume_pos;
  sem_t mutex;
  int thread_num;
  int is_modifiable;
  struct request_buff *packets[PACKET_BUFFER_SIZE];
};
/*-------------------------------------------------------------------*/
void* http_handler_thread(void* arguments);
/*-------------------------------------------------------------------*/
#endif /* _REQUEST_BUFFER_H_ */
/*-------------------------------------------------------------------*/
