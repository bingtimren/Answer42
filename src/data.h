#pragma once
#include "debug.h"
#include "pebble.h"
/* IDs for persistent storage */
#define KEY_CURRENT_RUNNING_STATE 1

/* everything related to storage of records and communication with phone */
/* pebble persisent storage capability: max value length 256 bytes, all cannot exceed 4K */  
  
#define DATA_STORE_SIZE 30  
  
typedef struct TimeRecord { // together = 8 bytes & aligned
  time_t time; // unsigned int = 4 bytes
  uint16_t durition; // 2 bytes
  uint16_t what_index; // 2 bytes
}  __attribute__((__packed__)) TimeRecord;



// the key to store all time records data
#define KEY_DATA_STORE 2
  
  
/* seconds in a minute - set to 1 for faster time lapsing for debugging */
#ifdef DEBUG_TO_SECONDS
  #define SECONDS_PER_MIN 1
#else
  #define SECONDS_PER_MIN 60
#endif


void data_store_load ();

void data_store_save ();