#pragma once
#include "debug.h"
#include "pebble.h"
/* IDs for persistent storage */
#define KEY_CURRENT_RUNNING_STATE 1
#define KEY_DATA_STORE 2
#define KEY_WAKEUP_REGISTRY 3 


/* everything related to storage of records and communication with phone */
/* pebble persisent storage capability: max value length 256 bytes, all cannot exceed 4K */  
  
#define DATA_STORE_SIZE 30  
  
typedef struct TimeRecord { // together = 8 bytes & aligned
  time_t time; // unsigned int = 4 bytes
  uint16_t durition; // 2 bytes
  uint16_t what_index; // 2 bytes
}  __attribute__((__packed__)) TimeRecord;

// the store
extern struct TimeRecord data_store[DATA_STORE_SIZE];


void data_clear();  
  
/* seconds in a minute - set to 1 for faster time lapsing for debugging */
#ifdef DEBUG_TO_SECONDS
  #define SECONDS_PER_MIN 1
#else
  #define SECONDS_PER_MIN 60
#endif


void data_store_load ();

void data_store_save ();

bool data_log_in(time_t time, uint16_t durition, uint16_t what_index);

uint8_t data_seek_valid(uint8_t start);

uint8_t data_store_usage_count();

void data_free(const uint8_t i);
