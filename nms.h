/*-------------------------------------------------------------------*/
#ifndef _NMS_H_
#define _NMS_H_
/*-------------------------------------------------------------------*/
#define NMS_PORT  3005

/* using IEEE 802.15.4g short or long addr */
#define CONF_LLADDR_SIZE  8
/*-------------------------------------------------------------------*/
#define NTOHS(x)  (x = ntohs(x))
/*-------------------------------------------------------------------*/
#if (CONF_LLADDR_SIZE == 2)

#define PRINTS_LLADDR(str, addr)                \
          sprintf(str, "%02x:%02x",             \
                  ((uint8_t *)addr)[0],         \
                  ((uint8_t *)addr)[1])
#define PRINT_LLADDR(addr)                      \
          printf("%02x:%02x",                   \
                  ((uint8_t *)addr)[0],         \
                  ((uint8_t *)addr)[1])

#elif (CONF_LLADDR_SIZE == 8)

#define PRINTS_LLADDR(str, addr)                \
          sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x", \
                  ((uint8_t *)addr)[0],         \
                  ((uint8_t *)addr)[1],         \
                  ((uint8_t *)addr)[2],         \
                  ((uint8_t *)addr)[3],         \
                  ((uint8_t *)addr)[4],         \
                  ((uint8_t *)addr)[5],         \
                  ((uint8_t *)addr)[6],         \
                  ((uint8_t *)addr)[7])
#define PRINT_LLADDR(addr)                      \
          printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x", \
                  ((uint8_t *)addr)[0],         \
                  ((uint8_t *)addr)[1],         \
                  ((uint8_t *)addr)[2],         \
                  ((uint8_t *)addr)[3],         \
                  ((uint8_t *)addr)[4],         \
                  ((uint8_t *)addr)[5],         \
                  ((uint8_t *)addr)[6],         \
                  ((uint8_t *)addr)[7])
#endif /* _NMS_H_ */
/*-------------------------------------------------------------------*/
#define TYPE_NSI    3
/*-------------------------------------------------------------------*/
struct oam_inst {
  unsigned char type;
  unsigned char len;
  unsigned char pad[2];
};

struct oam_node {
  unsigned char lladdr[CONF_LLADDR_SIZE];
  unsigned char len;
  unsigned char pad[3];
};
/*-------------------------------------------------------------------*/
#if 0
struct WriteThis {
  const char *readptr;
  size_t sizeleft;
};
/*-------------------------------------------------------------------*/
/* Configuration for pushing telemetry data to the Cloud */
#define TELEMETRY_POST_URL "http://104.211.114.72:9200/mote_stats/satvam"
#define POST_SUCCESS_CODE 201
#endif /* 0 */
/*-------------------------------------------------------------------*/
#endif /* _NMS_H_ */
/*-------------------------------------------------------------------*/
