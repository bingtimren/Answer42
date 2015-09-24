#include <pebble.h>
#include "debug.h"
#include "data.h"

// load the time records. if not found, initiate the store
// the in-memory store
static struct TimeRecord data_store[DATA_STORE_SIZE];

void data_store_load () {
  if (persist_exists(KEY_DATA_STORE)) {
    persist_read_data(KEY_DATA_STORE, &data_store, sizeof(data_store));
    APP_LOG(APP_LOG_LEVEL_INFO, "Data store (l=%ud) loaded ", sizeof(data_store));
    return;
  };
  for (unsigned int i=0; i< DATA_STORE_SIZE; i++) {
    data_store[i].time = 0;
    data_store[i].durition = 0;
  }
  APP_LOG(APP_LOG_LEVEL_INFO, "Data store not found, in-memory store initialized, size %ud", sizeof(data_store));
};

void data_store_save () {
  persist_write_data(KEY_DATA_STORE, &data_store, sizeof(data_store));
  APP_LOG(APP_LOG_LEVEL_INFO, "Data store (l=%ud) saved ", sizeof(data_store));
};