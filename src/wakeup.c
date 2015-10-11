#include <pebble.h>
#include "wakeup.h"
#include "running_state.h"
#include "w_running.h"
#include "w_selection.h"
#include "data.h"  
#include "format.h"  

// schedule registry remembers the schedule id
// so that if a wakeup for a cookie has already been registered,
// cancel that event first before registering the new wakeup
// so basically - one wakeup one cookie
WakeupId schedule_registry[10];

// load wakeup registry from persistent storage
void wakeup_state_load () {
  if (persist_exists(KEY_WAKEUP_REGISTRY)) {
    persist_read_data(KEY_WAKEUP_REGISTRY, &schedule_registry, sizeof(schedule_registry));
    APP_LOG(APP_LOG_LEVEL_INFO, "Wakeup registry loaded ");
    return;
  };
  APP_LOG(APP_LOG_LEVEL_INFO, "No wakeup registry found, initiate");
  for (int i=0; i<10; i++) {
	  schedule_registry[i] = -1;
  };
};


// clear running state - this should be called only for debugging purpose
void wakeup_state_clear() {
  if (persist_exists(KEY_WAKEUP_REGISTRY)) {
    persist_delete(KEY_WAKEUP_REGISTRY);
    APP_LOG(APP_LOG_LEVEL_INFO, "Wakeup registry state cleared.");
  };
  // cancel all wakeups
  wakeup_cancel_all();
}

// save running state into the persistent storage of the watch
void wakeup_state_save() {
  persist_write_data(KEY_WAKEUP_REGISTRY, &schedule_registry, sizeof(schedule_registry));
  APP_LOG(APP_LOG_LEVEL_INFO, "Wakeup registry saved ");
}



// schedule next wakeup in minutes
void wakeup_schedule_next_in_minutes(uint16_t minutes_to_now, int32_t cookie ) {
  return wakeup_schedule_next_target_time(time(NULL) + SECONDS_PER_MIN * minutes_to_now, cookie);
}

void wakeup_schedule_next_in_seconds(uint16_t seconds_to_now, int32_t cookie ) {
  return wakeup_schedule_next_target_time(time(NULL) + seconds_to_now, cookie);
}

// if previously registered then cancel
void wakeup_cancel_by_cookie(int32_t cookie) {
  if (schedule_registry[cookie] > 0) {
	  APP_LOG(APP_LOG_LEVEL_INFO, "cancel previous scheduled wakeup %ld", cookie);
	  wakeup_cancel(schedule_registry[cookie]);
  };	
};

// schedule next wakeup at target time
void wakeup_schedule_next_target_time(time_t target, int32_t cookie) {
  // only one wakeup for a cookie type is allowed
  wakeup_cancel_by_cookie(cookie);
  #ifdef APP_LOG
	  char buffer[20];
	  fmt_time_24h(buffer, sizeof(buffer), &(target));
	  APP_LOG(APP_LOG_LEVEL_INFO, "wake up scheduled target %s cookie %ld", buffer, cookie);
  #endif
  schedule_registry[cookie] = wakeup_schedule(target, cookie, false);  
  wakeup_state_save();
}

// handling wakeup & stage changes
void wakeup_handler(WakeupId wakeup_id, int32_t cookie) {
  switch (cookie) {
	  case RunningStateReminder: running_reminder_handler(); break;
	  case SelectionTimeOut: hide_w_selection(); break;
	  case BluetoothHighTimeOut : APP_LOG(APP_LOG_LEVEL_INFO, "turnning down bluetooth level"); app_comm_set_sniff_interval(SNIFF_INTERVAL_NORMAL); break;
  };
};

// initialize wakeup & subscribe  
void wakeup_init() {
  wakeup_state_load();
  wakeup_service_subscribe(wakeup_handler);
  APP_LOG(APP_LOG_LEVEL_INFO, "wakeup initialized"); 
}

