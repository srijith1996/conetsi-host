/*-------------------------------------------------------------------*/
#ifndef _REMOTE_CONN_H_
#define _REMOTE_CONN_H_
/*-------------------------------------------------------------------*/
#define REMOTE_HOST "api.urbansciences.in"
#define REMOTE_HOST_SIM "tsdb.urbansciences.in"
#define REMOTE_PORT "80"
/*-------------------------------------------------------------------*/
/* Now we will be waiting to send the packet unless it reaches 
 * the webserver. This is the number of retries for each duration 
 */
#define NUM_RETRIES     10
#define RETRY_COOL_TIME  1
#define MAX_SLEEP_TIME 100
#define ERROR            0
#define SUCCESS          1
#define RESPONSE_OK    200
/*-------------------------------------------------------------------*/
/* URL request strings */
#define REMOTE_URL_SIM  "/quartz/rawdata?imei=%s&sim1=%d&sim2=%d&timestr=%s&lat=28.6758&lon=77.2161"
#define REMOTE_URL_SO2  "/quartz/rawdata?imei=%s&so2op1=%d&so2op2=%d&timestr=%s&lat=28.6758&lon=77.2161"
#define REMOTE_URL_NO2_O3  "/quartz/rawdata?imei=%s&no2op1=%d&no2op2=%d&o3op1=%d&o3op2=%d&timestr=%s&lat=28.6758&lon=77.2161"
#define REMOTE_URL_DHT22  "/quartz/rawdata?imei=%s&temp=%.1f&humidity=%.1f&timestr=%s&lat=28.6758&lon=77.2161"
#define REMOTE_URL_PM25 "/quartz/rawdata?imei=%s&pm1conc=%d&pm25conc=%d&pm10conc=%d&timestr=%s&lat=28.6758&lon=77.2161"

/* IMEI field for Simulation */
#define SERVER_TIMESTAMP_FORMAT "%m%%2F%d%%2F%Y%%20%H%%3A%M%%3A%S"
/*-------------------------------------------------------------------*/
#endif /* _REMOTE_CONN_H_ */
/*-------------------------------------------------------------------*/
