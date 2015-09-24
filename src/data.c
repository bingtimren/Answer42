#include <pebble.h>
#include "debug.h"
#include "data.h"

// load the time records. if not found, initiate the store
// the in-memory store
static struct TimeRecord data_store[DATA_STORE_SIZE];

void data_store_load () {
  data_store_usage = 0;
  if (persist_exists(KEY_DATA_STORE)) {
    persist_read_data(KEY_DATA_STORE, &data_store, sizeof(data_store));
    // now count the empty slots
    for (uint8_t i=0; i<DATA_STORE_SIZE; i++) {
		if (data_store[i].time != 0) {
			data_store_usage += 1;
		};
	};
	APP_LOG(APP_LOG_LEVEL_INFO, "Data store (size %u load %u) loaded ", sizeof(data_store), data_store_usage);
    return;
  };
  for (unsigned int i=0; i< DATA_STORE_SIZE; i++) {
    data_store[i].time = 0;
    data_store[i].durition = 0;
  }
  APP_LOG(APP_LOG_LEVEL_INFO, "Data store not found, in-memory store initialized, size %u", sizeof(data_store));
};

void data_store_save () {
  persist_write_data(KEY_DATA_STORE, &data_store, sizeof(data_store));
  APP_LOG(APP_LOG_LEVEL_INFO, "Data store (l=%u) saved ", sizeof(data_store));
};

void data_log_in(time_t time, uint16_t durition, uint16_t what_index) {
	// if there is no empty slot, just exit
	if (data_store_usage == DATA_STORE_SIZE) {
		APP_LOG(APP_LOG_LEVEL_INFO, "should not run here... storage full");
		return;
	};
	// find an empty slot and put data into
    for (uint8_t i=0; i<DATA_STORE_SIZE; i++) {
		if (data_store[i].time == 0) {
			data_store[i].time = time;
			data_store[i].durition = durition;
			data_store[i].what_index = what_index;
			break;
		};
		APP_LOG(APP_LOG_LEVEL_INFO, "should not run here... storage full");
	};
};

void data_send_out() {
	// send data to phone
};
