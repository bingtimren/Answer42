#include <pebble.h>
#include "debug.h"
#include "data.h"
#include "w_running.h"
#include "w_localsummary.h"
#include "format.h"

/*
 * manage TimeRecord data storage 
 * 
 * 
 * 
 */

uint8_t data_store_head;
struct TimeRecordDayStore data_today;
struct TimeRecordDayStore data_history;
static bool data_store_loaded = false;

void reset_data_today(time_t time) {
	data_today.day_start = starts_of_the_day(time);
	data_today.length = 0;
	data_store_save();
};

void data_store_load () {
  data_store_loaded = true;
  if (persist_exists(KEY_DATA_INDEX)) {
    persist_read_data(KEY_DATA_INDEX, &data_store_head, sizeof(data_store_head));
	APP_LOG(APP_LOG_LEVEL_INFO, "Data data_store_head loaded, size %u ", sizeof(data_store_head));
	persist_read_data(KEY_DATA_STORE_START+data_store_head, &data_today, sizeof(data_today));
	APP_LOG(APP_LOG_LEVEL_INFO, "Data today loaded, size %u, length %u", sizeof(data_today), data_today.length);
    return;
  };
  // not found persisted data store, initialize
  data_store_head = 0;
  reset_data_today(time(NULL));
  APP_LOG(APP_LOG_LEVEL_INFO, "Data store not found, in-memory store initialized.");
};

bool data_store_load_into_history (uint8_t slot) {
  if (persist_exists(KEY_DATA_STORE_START+slot)) {
	persist_read_data(KEY_DATA_STORE_START+slot, &data_history, sizeof(data_history));
	APP_LOG(APP_LOG_LEVEL_INFO, "Data history loaded, slot %u, length %u", slot, data_history.length);
	return true;
  };  
  // not found persisted history
  data_history.day_start = 0;
  data_history.length = 0;
  APP_LOG(APP_LOG_LEVEL_INFO, "Data history slot %u not found.", slot);
  return false;
};


// save index and today - history records are already saved
void data_store_save () {
  persist_write_data(KEY_DATA_INDEX, &data_store_head, sizeof(data_store_head));
  APP_LOG(APP_LOG_LEVEL_INFO, "Data data_store_head (l=%u) saved ", sizeof(data_store_head));
  persist_write_data(KEY_DATA_STORE_START+data_store_head, &data_today, sizeof(data_today));
  APP_LOG(APP_LOG_LEVEL_INFO, "Data index (l=%u) saved, as index %u", sizeof(data_today), KEY_DATA_STORE_START+data_store_head);
};

// durition - in minutes
bool data_log_in(const time_t time, const uint16_t durition, const uint8_t what_index, char indicator) {
	#ifdef DEBUG_CHECK_MORE
	char time_buf[50];
	strftime(time_buf, sizeof(time_buf), "%d.%m.%y %H:%M", localtime(&time));
	APP_LOG(APP_LOG_LEVEL_INFO, "data logging: time %s durition %u index %u", time_buf, durition, what_index);
	#endif
	
	// handles data store
	if (! data_store_loaded) {
		data_store_load();
	};	
	
	// check if need to change slot
	if ((time - data_today.day_start) > SECONDS_PER_DAY) {// not today, need to go next
		data_store_head = data_store_head + 1;
		if (data_store_head == DATA_SLOT_SIZE) 
			data_store_head = 0;
		reset_data_today(time);
	};
	
	// if there is no empty slot, just exit
	if (data_today.length == DATA_STORE_SIZE_DAY) {
		APP_LOG(APP_LOG_LEVEL_INFO, "today's storage full");
		return false;
	};
	
	// put data into, first calculate time as minutes past mid-night
	data_today.day_records[data_today.length].time = minutes_past_midnight(time);
	data_today.day_records[data_today.length].durition = durition;
	data_today.day_records[data_today.length].what_index = what_index;
	data_today.day_records[data_today.length].indicator = indicator;
	data_today.length = data_today.length + 1;
	APP_LOG(APP_LOG_LEVEL_INFO, "data logged in what index %u length %u data_store_head %u", what_index, data_today.length, data_store_head);
	data_store_save();
	return true;
};



// clear data store
void data_clear() {
	for (int i=0; i<DATA_SLOT_SIZE; i++) {
		if (persist_exists(KEY_DATA_STORE_START+i)) {
			persist_delete(KEY_DATA_STORE_START+i);
		};
	};
	data_store_head = 0;
	reset_data_today(time(NULL));
	APP_LOG(APP_LOG_LEVEL_INFO, "Data store cleared.");
};

