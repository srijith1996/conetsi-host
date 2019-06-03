/*-------------------------------------------------------------------*/
#ifndef _UTILS_H_
#define _UTILS_H_
/*-------------------------------------------------------------------*/
#include <time.h>
/*-------------------------------------------------------------------*/
#define DIFF_TIMESTR_FORMAT 15
#define PRINT_LIM           200
/*-------------------------------------------------------------------*/
/*
 * Utility functions for host side code
 */
/* Get current time on system clock */
void time_now();

/* Get time t formatted as per format */
void get_ft_time(char* time_str, time_t t, char* format);

/* Get current time as per format */
unsigned long get_ft_time_now(char* time_str, char* format);

/* Append a string to a buffer */
void append_buffer(char* dest, char* text, int* start);

/* Remove special characters in a string */
void rm_special_char(char* string);

/* Print utility for debugging */
void print_dbg(char* prefix, char* str, ...);
/*-------------------------------------------------------------------*/
#endif /* _UTILS_H_ */
/*-------------------------------------------------------------------*/
