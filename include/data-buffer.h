/*-------------------------------------------------------------------*/
#ifndef _DATA_BUFFER_H_
#define _DATA_BUFFER_H_
/*-------------------------------------------------------------------*/
#include <sys/types.h>
#include <stdint.h>
#include <netinet/in.h>
#include <time.h>

#include "mutex.h"
/*-------------------------------------------------------------------*/
/*
 * struct defining the fields prepended to
 * the data in the log
 */
/*
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                         Global Counter                        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |           Index_H             |           Datatype            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                         Timestamp(secs)                       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                         Timestamp(nsecs)                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * .                                                               .
 * .              Truncated IP address [40 bytes]                  .
 * .                                                               .
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                        Mote ticks(secs)                       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                            Count                              |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * +                                                               +
 * |                                                               |
 * .                          Mote data                            .
 * .                                                               .
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define MAX_DATA_SIZE   8
#define MAX_IPADDR_LEN  INET6_ADDRSTRLEN

struct data_buff {
  uint32_t g_ctr;
  uint16_t index;
  uint16_t type;
  struct timespec rpi_timestamp;
  char trunc_ip[MAX_IPADDR_LEN];
  uint32_t ticks;
  int count;
  char sensor_data[MAX_DATA_SIZE];
};

#define IMEI_SIMULATION "IISC_SIMULATION%d"
#define SIM_CONF_SLEEP_TIME 1

#define DATA_BUFF_LEN   (sizeof(struct data_buff))
#define DATA_BUFF(x)    ((struct data_buff *) x)
/*-------------------------------------------------------------------*/
#define TASK_BUFFER_SIZE           1024

struct data_buff_info {
  int consume_pos;
  int produce_pos;
  sem_t mutex;
  struct data_buff *tasks[TASK_BUFFER_SIZE];
};

#define DATA_BUFF_INFO_SIZE  (sizeof(struct data_buff_info)) 
/*-------------------------------------------------------------------*/
void* consumer_thread(void *args);
/*-------------------------------------------------------------------*/
#endif /* _DATA_BUFFER_H_ */
/*-------------------------------------------------------------------*/
