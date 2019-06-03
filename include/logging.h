/*-------------------------------------------------------------------*/
#ifndef _LOGGING_H_
#define _LOGGING_H_
/*-------------------------------------------------------------------*/
#include "request-buffer.h"
#include <stdio.h>
/*-------------------------------------------------------------------*/
/* Includes for log4c */
/* #include "log4c.h" */
/* #include "log4c/appender_type_rollingfile.h" */
/* #include "log4c/rollingpolicy_type_sizewin.h" */
/*-------------------------------------------------------------------*/
#define FILENAME_TIMESTAMP_FORMAT "%Y-%m-%dT%H-%M-%S"
#define LOG_NAME_PREFIX      "logs/"
#define LOG_NAME_PREFIX_SIM  "logs-sim/"
#define LOG_NAME_FORMAT  "%s-%s-%d.log" 
/*-------------------------------------------------------------------*/
/* Define log timestamp format */
/* the %%ld is for %ld which will be used for printing msec */
#define LOG_TIMESTAMP_FORMAT "%Y-%m-%dT%H:%M:%S.%%ld%z" 
/*-------------------------------------------------------------------*/
/* Functions for logging data to files
 * [the code could be made a little more generic]
 */

/* Create log file with process_name */
FILE* create_log(char* process_name, int inc, int sim);

/* Log an HTTP request */
int log_request(FILE* http_log_file, struct request_buff* req);

/* Log an HTTP response */
int log_response(FILE* logfile, struct request_buff* req,
                 long response_code, char* message);

/* Log complete packet data to a log
 * with a timestamp
 */
int log_data(FILE* log_file, struct data_buff* data, char* add_data);

/* print a string to a custom log */
int print_log_str(FILE* fh, char *str);
/*-------------------------------------------------------------------*/
#endif /* _LOGGING_H_ */
/*-------------------------------------------------------------------*/
