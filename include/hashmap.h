/*-------------------------------------------------------------------*/
#ifndef _HASHMAP_H_
#define _HASHMAP_H_
/*-------------------------------------------------------------------*/
#define AVG_TIME_SPAN_SEC 60
#define MAP_LENGTH 100
/*-------------------------------------------------------------------*/
#include "ll.h"
/*-------------------------------------------------------------------*/
/* utility for rolling averages */
#define ADD_AVG(x, y, ct)      \
          (x = ((((ct) * x) + y) / ((ct)+1)))
/*-------------------------------------------------------------------*/
struct map_key {
  char trunc_ip[40];
  uint16_t datatype;
  int count;
  time_t start_time_pkt;    /* Two time values: 1. active avg */
  time_t start_time_obs;    /* 2. reactive avg */
};
/*-------------------------------------------------------------------*/
/*
 * Append value to list
 */
int append_value(struct map_key *key, struct data_buff* add_val);

/*
 * Check if list is ready to send
 */
int proc_lists();

/*
 * Register to get back averaged data
 */
int reg_hashmap(int (* callback_func) (struct data_buff *));
/*-------------------------------------------------------------------*/
#endif /* _HASHMAP_H_ */
/*-------------------------------------------------------------------*/
