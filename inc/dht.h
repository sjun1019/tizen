#ifndef _DHT_H_
#define _DHT_H_

#define DHT_LIB_VERSION "0.1.05 C"

#define DHTLIB_OK                0
#define DHTLIB_ERROR_CHECKSUM   -1
#define DHTLIB_ERROR_TIMEOUT    -2
#define DHTLIB_INVALID_VALUE    -999

#include <inttypes.h>
#include <stdlib.h>
#include "util.h"
#include "wiring.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t (*rpin_proc_t)(); 
typedef void (*wpin_proc_t)(uint8_t bit);
typedef void (*delay_proc_t)(uint16_t delay);

typedef enum {
	DHT_READ_PIN,
	DHT_WRITE_PIN,
	DHT_DELAY_MS,
	DHT_DELAY_US
} dht_request_t; 

typedef int16_t (*dht_service_proc_t)(dht_request_t req, uint16_t arg);

typedef struct dht_s
{
	double humidity;
	double temperature;
	
	dht_service_proc_t sproc; 
	/*
	rpin_proc_t read_pin;
	wpin_proc_t write_pin;
	delay_proc_t delay_ms;
	delay_proc_t delay_us;
	*/
	uint8_t _bits[5];
} dht_t;

// dht functions
int DHT_Init(dht_t *self, dht_service_proc_t sp); //rpin_proc_t read, wpin_proc_t write, delay_proc_t ms, delay_proc_t us); 
int DHT_Read11(dht_t *self);
int DHT_Read22(dht_t *self);

#ifdef __cplusplus
}
#endif

#endif
