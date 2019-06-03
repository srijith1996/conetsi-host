/*-------------------------------------------------------------------*/
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "data-buffer.h"
#include "request-buffer.h"
#include "utils.h"
#include "logging.h"
#include "sensors.h"
/*-------------------------------------------------------------------*/
#define DBG_PREFIX "log-util"
#define DEBUG 1
#if DEBUG
#define PRINTD(...) print_dbg(DBG_PREFIX, __VA_ARGS__)
#else /* DEBUG */
#define PRINTD(...)
#endif /* DEBUG */
/*-------------------------------------------------------------------*/
static char formatted_time[100];
struct timespec start_time;

static struct stat st = {0};
static char prefix[10];
/*-------------------------------------------------------------------*/
int
print_log_str(FILE *fh, char *str)
{
  struct timespec time;
  long diff_usec;

  /* print the log epoch */
  time_now(&time);

  diff_usec = (time.tv_nsec - start_time.tv_nsec) / 1000;
  if(diff_usec < 0) {
    time.tv_sec--;
    diff_usec = (1000000 + diff_usec);
  }

  if(fh == NULL) {
    return -1;
  }

  fprintf(fh, "[%ld.%06ld] ",
          ((time.tv_sec - start_time.tv_sec) % 1000000),
          (diff_usec % 1000000));

  /* print the log_str */
  PRINTD("printing to log");
  fprintf(fh, "%s\n", str);   /* flush here if needed */
  fflush(fh);

  return 0;
}
/*-------------------------------------------------------------------*/
/* TODO: log rotation */
FILE *
create_log(char* process_name, int inc, int sim)
{
  static int called = 0;
  char file_name[100];
  static char filename_ts[100];
  char tmp[70];
  FILE *log_file;

  if(!called) {
    time_now(&start_time);
    PRINTD("got time");
    get_ft_time(filename_ts, start_time.tv_sec,
                FILENAME_TIMESTAMP_FORMAT);

    if(sim) {
      if(stat(LOG_NAME_PREFIX_SIM, &st) == -1) {
        PRINTD("Creating directory %s", LOG_NAME_PREFIX_SIM);
        mkdir(LOG_NAME_PREFIX_SIM, 0700);
      }
    } else {
      if(stat(LOG_NAME_PREFIX, &st) == -1) {
        PRINTD("Creating directory %s", LOG_NAME_PREFIX);
        mkdir(LOG_NAME_PREFIX, 0700);
      }
    }
    called = 1;
  }

  /* choose the appropriate prefix */
  if(sim) {
    strcpy(prefix, LOG_NAME_PREFIX_SIM);
  } else {
    strcpy(prefix, LOG_NAME_PREFIX);
  }
 
  strcpy(file_name, prefix);
  sprintf(tmp, LOG_NAME_FORMAT, process_name, filename_ts, inc);
  strcat(file_name, tmp);

  log_file = fopen(file_name, "a");
  fprintf(log_file, "start epoch: %ld.%ld\n\n",
          start_time.tv_sec, start_time.tv_nsec);
  fflush(log_file);

  return log_file;
}
/*-------------------------------------------------------------------*/
#if 0
static void
get_log_time(char* time_str)
{
  char tmp_time_str[100];
  struct timespec tspec;
  long usec;

  tspec.tv_nsec = get_ft_time_now(tmp_time_str, 
                                   LOG_TIMESTAMP_FORMAT);
  usec = (long) round(tspec.tv_nsec/1000.0);
  sprintf(time_str, tmp_time_str, usec);

  PRINTD("Log Time: %s", time_str);
  return;
}
#endif /* 0 */
/*-------------------------------------------------------------------*/
int
log_request(FILE *http_log, struct request_buff *req) 
{
  char log_str[300];

  sprintf(log_str, "%10lu %8d %s",
          req->g_ctr, req->index,
          req->request_url);

  return print_log_str(http_log, log_str);
}
/*-------------------------------------------------------------------*/
int
log_response(FILE *log_file, struct request_buff *req,  
             long response_code, char *message) 
{
  char log_str[150];

  sprintf(log_str, "%10lu %8d %3lu %s",
          req->g_ctr, req->index,
          response_code, message);

  return print_log_str(log_file, log_str);
}
/*-------------------------------------------------------------------*/
int
log_data(FILE* log_file, struct data_buff* data, char* add_data) 
{
  char tmp_str[50];
  char log_str[150];
  long usec;

  get_ft_time(tmp_str, (data->rpi_timestamp).tv_sec,
              LOG_TIMESTAMP_FORMAT);

  usec = (long) round((data->rpi_timestamp).tv_nsec/1000.0);
  sprintf(formatted_time, tmp_str, usec);

  sprintf(log_str, "%10d %4d %-31s %10d %-25s %2d %4d ",
          data->g_ctr, data->index,
          formatted_time, data->ticks,
          data->trunc_ip, data->type,
          data->count);

  switch(data->type) {
  
   case SO2_SENSOR_TYPE:

    sprintf(tmp_str,"%3d %3d",
            SO2(data->sensor_data)->so2_1,
            SO2(data->sensor_data)->so2_2);
    strcat(log_str, tmp_str);
    break;

   case NO2_O3_SENSOR_TYPE:

    sprintf(tmp_str,"%3d %3d %3d %3d",
            NO2_O3(data->sensor_data)->no2_1,
            NO2_O3(data->sensor_data)->no2_2,
            NO2_O3(data->sensor_data)->o3_1,
            NO2_O3(data->sensor_data)->o3_2);
    strcat(log_str, tmp_str);
    break;

   case DHT22_SENSOR_TYPE:

    sprintf(tmp_str, "%.1f %.1f",
            ((double) DHT22(data->sensor_data)->temp)/10.0,
            ((double) DHT22(data->sensor_data)->hum)/10.0);
    strcat(log_str, tmp_str);
    break;

   case PM25_SENSOR_TYPE:

    sprintf(tmp_str, "%3d %3d %3d",
            PM25(data->sensor_data)->pm1_conc_atm,
            PM25(data->sensor_data)->pm25_conc_atm,
            PM25(data->sensor_data)->pm10_conc_atm);
    strcat(log_str, tmp_str);
    break;

   case ONBOARD_SENSOR_TYPE:

    sprintf(tmp_str,"%3d %3d",
            ONBOARD(data->sensor_data)->temp,
            ONBOARD(data->sensor_data)->bat_volt);
    strcat(log_str, tmp_str);
    break;

   case SIMULATION_TYPE:

    sprintf(tmp_str,"%5d %5d",
            SIM(data->sensor_data)->data_1,
            SIM(data->sensor_data)->data_2);
    strcat(log_str, tmp_str);
    break;

   default:
    PRINTD("Unknown data type encountered while logging");
    return -1;
  }

  strcat(log_str, add_data);
  return print_log_str(log_file, log_str);
}
/*-------------------------------------------------------------------*/
