/*-------------------------------------------------------------------*/
#ifndef _SENSOR_H_
#define _SENSOR_H_
/*-------------------------------------------------------------------*/
/*
 * types of data that may flow from UDP stream
 * This should be in strict agreement with the corresponding
 * variables in the contiki source code for these sensors
 *
 * $CONTIKI_SRC/examples/zolertia/zoul/cc1200-demo/event_data.h
 */
#define UNKNOWN_SENSOR_TYPE   (-1)
#define SIMULATION_TYPE       0

#define ONBOARD_SENSOR_TYPE   1
#define SO2_SENSOR_TYPE       2
#define NO2_O3_SENSOR_TYPE    3
#define DHT22_SENSOR_TYPE     4
#define PM25_SENSOR_TYPE      5
/*-------------------------------------------------------------------*/
#define REAL_DATA_FORMAT "%s %s Type: %d Temperature: %d Battery Voltage: %d Sample Count: %d"
#define COMMON_SENSOR_DATA "%s %s Type: %d "
#define ONBOARD_SENSOR_DATA_FORMAT COMMON_SENSOR_DATA "%d %d %d"
#define SO2_SENSOR_DATA_FORMAT COMMON_SENSOR_DATA "%d %d %d"
#define NO2_SENSOR_DATA_FORMAT COMMON_SENSOR_DATA "%d %d %d"
#define O3_SENSOR_DATA_FORMAT COMMON_SENSOR_DATA "%d %d %d"
/*-------------------------------------------------------------------*/
#define NTOHS(x)  (x = ntohs(x))
/*-------------------------------------------------------------------*/
/*
 * definition of the sensor data structures below
 * is the same as the definitions in the contiki source
 * code. All changes made should be done there too
 */
struct onboard_sensor_data {
  uint16_t temp;
  uint16_t bat_volt;
};

#define ONBOARD(x)    ((struct onboard_sensor_data *) x)
#define SIZE_ONBOARD  sizeof(struct onboard_sensor_data)
/*-------------------------------------------------------------------*/
struct so2_sensor_data {
  uint16_t so2_1;
  uint16_t so2_2;
};

#define SO2(x)    ((struct so2_sensor_data *) x)
#define SIZE_SO2  sizeof(struct so2_sensor_data)
/*-------------------------------------------------------------------*/
struct no2_o3_sensor_data {
  uint16_t no2_1;
  uint16_t no2_2;
  uint16_t o3_1;
  uint16_t o3_2;
};

#define NO2_O3(x)   ((struct no2_o3_sensor_data *) x)
#define SIZE_NO2_O3 sizeof(struct no2_o3_sensor_data)
/*-------------------------------------------------------------------*/
struct dht22_sensor_data {
  uint16_t temp;
  uint16_t hum;
};

#define DHT22(x)    ((struct dht22_sensor_data *) x)
#define SIZE_DHT22  sizeof(struct dht22_sensor_data)
/*-------------------------------------------------------------------*/
struct pm25_sensor_data {
  uint16_t pm1_conc_atm;
  uint16_t pm25_conc_atm;
  uint16_t pm10_conc_atm;
};

#define PM25(x)   ((struct pm25_sensor_data *) x)
#define SIZE_PM25 sizeof(struct pm25_sensor_data)
/*-------------------------------------------------------------------*/
struct simulate_data {
  uint16_t data_1;
  uint16_t data_2;
};
#define SIM(x)  ((struct simulate_data *) x)
#define SIZE_SIM sizeof(struct simulate_data)
#define SIM_CONF_NUM_KEYS   20
/*-------------------------------------------------------------------*/
#endif /* _SENSOR_H_ */
/*-------------------------------------------------------------------*/
