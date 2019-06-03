/*-------------------------------------------------------------------*/
#ifndef _SICSLOWPAN_APP_H_
#define _SICSLOWPAN_APP_H_
/*-------------------------------------------------------------------*/
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
/*-------------------------------------------------------------------*/
#define PRINT_LLADDR(addr)                                        \\
                  PRINTF(" %02x%02x:%02x%02x:%02x%02x:%02x%02x ", \\
                         ((uint8_t *)addr)[0],                    \\
                         ((uint8_t *)addr)[1],                    \\
                         ((uint8_t *)addr)[2],                    \\
                         ((uint8_t *)addr)[3],                    \\
                         ((uint8_t *)addr)[4],                    \\
                         ((uint8_t *)addr)[5],                    \\
                         ((uint8_t *)addr)[6],                    \\
                         ((uint8_t *)addr)[7])

#define PRINTS_LLADDR(str, addr)                                  \\
            sprintf(str, " %02x%02x:%02x%02x:%02x%02x:%02x%02x ", \\
                        ((uint8_t *)addr)[0],                     \\
                        ((uint8_t *)addr)[1],                     \\
                        ((uint8_t *)addr)[2],                     \\
                        ((uint8_t *)addr)[3],                     \\
                        ((uint8_t *)addr)[4],                     \\
                        ((uint8_t *)addr)[5],                     \\
                        ((uint8_t *)addr)[6],                     \\
                        ((uint8_t *)addr)[7])

#define MY_IP_ADDR    "aaaa::1"
#define APP_PORT      5000
/*-------------------------------------------------------------------*/
/*
 * struct for application layer header
 * Since a 64-bit computer might pad a 
 * struct of size other than multiples 
 * of 64, its better to explicitly pad
 *
 * Tick_ref1 & 0x7f: most significant byte
 * Tick_ref3 & 0xff: least significant byte
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |     Type      |   Num_pts     |T|  Tick_ref1  |   Tick_ref2   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Tick_ref3   |    Count1     |    Count2     |     Count3    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * +                                                               +
 * |                      Sensor Data packets                      |
 * +                                                               +
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * T: tick offset resolution
 *    0 - seconds
 *    1 - minutes
 *
 */
struct app_hdr {
  uint8_t type;
  uint8_t num_pts;
  uint8_t tick_ref[3]; /* NOTE: MSB of tick_ref[0] is T */
  uint8_t count[3];
};

#define HEADER_SIZE 8

#define TICK_OFFSET_FINE    0
#define TICK_OFFSET_COARSE  1
/*-------------------------------------------------------------------*/
struct data_buff *prod_sim_pkt();

int proc_app_pkt(char *app_buff, char *remote_ip,
                 int (* callback_func) (struct data_buff *));

/*-------------------------------------------------------------------*/
#endif /* _SICSLOWPAN_APP_H_ */
/*-------------------------------------------------------------------*/
