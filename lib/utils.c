/*-------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>

#include "utils.h"
/*-------------------------------------------------------------------*/
#define DBG_PREFIX "utils"
#define DEBUG 1
#if DEBUG
#define PRINTD(...) print_dbg(DBG_PREFIX, __VA_ARGS__)
#else /* DEBUG */
#define PRINTD(...) 
#endif /* DEBUG */
/*-------------------------------------------------------------------*/
void
time_now(struct timespec *spec)
{
  clock_gettime(CLOCK_REALTIME, spec);
  return;
}
/*-------------------------------------------------------------------*/
void 
get_ft_time(char* time_str, time_t t, char *format)
{
  struct tm *tmp;
  size_t ts_size;
  size_t len = strlen(format) + DIFF_TIMESTR_FORMAT;
  
  tmp = localtime(&t);
  if(tmp == NULL){
    perror("ERROR: localtime");
    exit(EXIT_FAILURE);
  }

  if((ts_size = strftime(time_str, len, 
          format, tmp)) == 0) {
    PRINTD("strftime returned 0");
    exit(EXIT_FAILURE);
  }
  
  time_str[ts_size] = '\0';
}
/*-------------------------------------------------------------------*/
/* Wrapper function to get formatted time now */
unsigned long
get_ft_time_now(char* time_str, char *format)
{
  unsigned long nsec = 0;
  struct timespec *now = (struct timespec *) 
          malloc(sizeof(struct timespec));
  time_now(now);

  get_ft_time(time_str, now->tv_sec, format);
  nsec = now->tv_nsec;

  free(now);
  return nsec;
}
/*-------------------------------------------------------------------*/
void 
append_buffer(char *dest, char *text, int *start) 
{
  memcpy(dest+(*start),text,strlen(text));
  /* PRINTD("%d",start+sizeof(text)); */
  *start += strlen(text);
}
/*-------------------------------------------------------------------*/
/*
 * This method currently removes only colon character but can 
 * be modified to remove other special char as well
 * 
 * 17/09/18 Updated to do the removal operation in place
 */
void 
rm_special_char(char *string) {

  unsigned int i, ctr;
  int flag = 0;
  if(string == NULL) {
    return;
  }

  ctr = 0;
  for(i = 0; (i + ctr) < strlen(string); i++) {
    
    /* change this condition for other special chars */
    while(string[i + ctr] == ':') {
      ctr++;
      if((i + ctr) >= strlen(string)) {
        flag = 1;
        break;
      }
    }
    if(flag) {
      break;
    }
    string[i] = string[i + ctr];
  }

  string[i] = '\0';
  return;
}
/*-------------------------------------------------------------------*/
void
print_dbg(char *prefix, char *str, ...)
{
  va_list args;
  char print_str[PRINT_LIM];
  va_start(args, str);
  
  vsnprintf(print_str, PRINT_LIM, str, args);
  printf("[%s] %s\n", prefix, print_str);

  return;
}
/*-------------------------------------------------------------------*/
