#include <pebble.h>
#include "debug.h"
#include "data.h"


static uint8_t data_store_usage;

struct TimeRecord data_store[DATA_STORE_SIZE];

static bool data_store_loaded = false;

void data_store_load () {
  data_store_loaded = true;
  data_store_usage = 0;
  if (persist_exists(KEY_DATA_STORE)) {
    persist_read_data(KEY_DATA_STORE, &data_store, sizeof(data_store));
    // now count the empty slots
    for (uint8_t i=0; i<DATA_STORE_SIZE; i++) {
			if (data_store[i].time != 0) { data_store_usage += 1; };
		};
		APP_LOG(APP_LOG_LEVEL_INFO, "Data store (size %u load %u) loaded ", sizeof(data_store), data_store_usage);
    return;
  };
  // not found persisted data store
  for (unsigned int i=0; i< DATA_STORE_SIZE; i++) {
    data_store[i].time = 0;
    data_store[i].durition = 0;
  }
  APP_LOG(APP_LOG_LEVEL_INFO, "Data store not found, in-memory store initialized, size %u", sizeof(data_store));
};

uint8_t data_store_usage_count() {
	if (! data_store_loaded) {
		data_store_load();
		};	
	return data_store_usage;
};



void data_store_save () {
  persist_write_data(KEY_DATA_STORE, &data_store, sizeof(data_store));
  APP_LOG(APP_LOG_LEVEL_INFO, "Data store (l=%u) saved ", sizeof(data_store));
};

bool data_log_in(const time_t time, const uint16_t durition, const uint16_t what_index) {
	#ifdef DEBUG_CHECK_MORE
	char time_buf[30];
	strftime(time_buf, sizeof(time_buf), "%d.%m.%y %H:%M", localtime(&time));
	APP_LOG(APP_LOG_LEVEL_INFO, "data logging: time %s durition %u index %u", time_buf, durition, what_index);
	#endif
	if (! data_store_loaded) {
		data_store_load();
	};	
	// if there is no empty slot, just exit
	if (data_store_usage == DATA_STORE_SIZE) {
		APP_LOG(APP_LOG_LEVEL_INFO, "should not run here... storage full");
		return false;
	};
	// find an empty slot and put data into
    for (uint8_t i=0; i<DATA_STORE_SIZE; i++) {
		if (data_store[i].time == 0) {
			// empty slot
			data_store[i].time = time;
			data_store[i].durition = durition;
			data_store[i].what_index = what_index;
			data_store_usage += 1;
			APP_LOG(APP_LOG_LEVEL_INFO, "data logged in what index %u slot position %u storage usage %u", what_index, i, data_store_usage);
			data_store_save();
			return true;
		};
	};
	APP_LOG(APP_LOG_LEVEL_INFO, "should not run here... storage full");
	data_store_usage = DATA_STORE_SIZE;
	return false;
};

void data_free(const uint8_t i) {
	if (data_store[i].time != 0) {
		data_store[i].time = 0;
		data_store_usage -= 1;
		data_store_save();
		APP_LOG(APP_LOG_LEVEL_INFO, "Freed slot %u usage=%d", i, data_store_usage);		
	} else APP_LOG(APP_LOG_LEVEL_ERROR, "Slot %u already freed", i);
};


uint8_t data_seek_valid(uint8_t start) {
	if (! data_store_loaded) {
		data_store_load();
	};
	// find an occupied slot
    for (uint8_t i=start; i<DATA_STORE_SIZE; i++) {
		if (data_store[i].time != 0) {
			APP_LOG(APP_LOG_LEVEL_INFO, "data_seek_valid return %u time %ld", i, (data_store[i].time - 0));
			return i;
		};
	};
	APP_LOG(APP_LOG_LEVEL_ERROR, "should not be here, store empty");
	return DATA_STORE_SIZE;
};



