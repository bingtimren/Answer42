#include <pebble.h>
#include "wakeup.h"
#include "running_state.h"
#include "w_running.h"
#include "w_selection.h"
#include "data.h"  
#include "format.h"  

WakeupId schedule_registry[10];

// schedule next wakeup in minutes
void wakeup_schedule_next_in_minutes(uint16_t minutes_to_now, int32_t cookie ) {
  return wakeup_schedule_next_target_time(time(NULL) + SECONDS_PER_MIN * minutes_to_now, cookie);
}

void wakeup_schedule_next_in_seconds(uint16_t seconds_to_now, int32_t cookie ) {
  return wakeup_schedule_next_target_time(time(NULL) + seconds_to_now, cookie);
}

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
}

// handling wakeup & stage changes
void running_reminder_handler() {
  running_vibe();
  APP_LOG(APP_LOG_LEVEL_INFO, "woke up, stage %d, repeats remaining %d", running_state_current.stage_idx, running_state_current.remaining_repeats);
  if ((*running_state_reminder_stage).repeats == 0) {
    // indicates repeating forever, only set next reminder
    APP_LOG(APP_LOG_LEVEL_INFO, "forever repeating...");
    wakeup_schedule_next_in_minutes((*running_state_reminder_stage).length, RunningStateReminder);
    return;
  };
  // check if there is still remaining repeat
  if (running_state_current.remaining_repeats > 0) {
    running_state_current.remaining_repeats -= 1;
    wakeup_schedule_next_in_minutes((*running_state_reminder_stage).length, RunningStateReminder);
    running_state_save();    
    return;
  };
  // exhausted repeats, now try to move to next reminding stage
  APP_LOG(APP_LOG_LEVEL_INFO, "Exhausted repeats, move to next stage");
  running_state_kickoff_stage(running_state_current.stage_idx + 1);
  // if out of stages, time to carry out end-of-stages action
  if (running_state_reminder_stage == NULL) {
    APP_LOG(APP_LOG_LEVEL_INFO, "run out of stages, time to commit end-of-stages action %d", 
            (*running_state_what).termination_action);
  }
  // only preserver running state in the end
  running_state_save();
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
  for (int i=0; i<10; i++) {
	  schedule_registry[i] = -1;
  };
  wakeup_service_subscribe(wakeup_handler);
  APP_LOG(APP_LOG_LEVEL_INFO, "wakeup initialized"); 
}
