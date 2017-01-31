#pragma once
#include "debug.h"
#include "pebble.h"
/* IDs for persistent storage */
#define KEY_CURRENT_RUNNING_STATE 1
#define KEY_DATA_STORE_START 10
#define KEY_WAKEUP_REGISTRY 3 
#define KEY_DATA_INDEX 2

#define DATA_SLOT_SIZE 10

extern uint8_t data_store_head;

extern struct TimeRecordDayStore data_today;
extern struct TimeRecordDayStore data_history;


/* everything related to storage of records and communication with phone */
/* pebble persisent storage capability: max value length 256 bytes, all cannot exceed 4K per app*/  
  
#ifdef DEBUG_SMALL_STORAGE
  #define DATA_STORE_SIZE_DAY 3
#else
  #define DATA_STORE_SIZE_DAY 45
#endif

typedef struct TimeRecord { // together = 5 bytes & aligned
  uint16_t time; // minutes since mid-night, 2 bytes
  uint16_t durition; // 2 bytes, in minutes
  uint8_t what_index; // 1 bytes
  char indicator; // adjustments, etc.
}  __attribute__((__packed__)) TimeRecord;

// The store - for one day
struct TimeRecordDayStore {
	uint8_t length;
	time_t day_start;
	struct TimeRecord day_records[DATA_STORE_SIZE_DAY];
};

/* seconds in a minute - set to 1 for faster time lapsing for debugging */
#ifdef DEBUG_TO_SECONDS
  #define SECONDS_PER_MIN 1
#else
  #define SECONDS_PER_MIN 60
#endif


void reset_data_today(time_t time);

void data_store_load ();

bool data_store_load_into_history (uint8_t slot);


// save index and today - history records are already saved
void data_store_save ();
// durition - in minutes
bool data_log_in(const time_t time, const uint16_t durition, const uint8_t what_index, char indicator);



// clear data store
void data_clear();
