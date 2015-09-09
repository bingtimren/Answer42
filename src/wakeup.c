#include <pebble.h>
#include "wakeup.h"
#include "running_state.h"
#include "data.h"  
  
void vibe_reminder() {
  vibes_long_pulse();
}  

// schedule next wakeup in minutes
void wakeup_schedule_next_in_minutes(uint16_t minutes_to_now) {
  wakeup_schedule_next_target_time(time(NULL) + SECONDS_PER_MIN * minutes_to_now);
}
// schedule next wakeup at target time
void wakeup_schedule_next_target_time(time_t target) {
  wakeup_schedule(target, REMINDER_DUE, false);
  #ifdef APP_LOG
  char buffer[20];
  fmt_time_24h(buffer, sizeof(buffer), &(target));
  APP_LOG(APP_LOG_LEVEL_INFO, "wake up scheduled target %s", buffer);
  #endif
}


// handling wakeup & stage changes
void wakeup_handler(WakeupId wakeup_id, int32_t cookie) {
  // now no check of cookie, since only one type of event is handled: stage reminder / possible next stage
  vibe_reminder();
  APP_LOG(APP_LOG_LEVEL_INFO, "woke up, stage %d, repeats remaining %d", running_state_current.stage_idx, running_state_current.remaining_repeats);
  if ((*running_state_reminder_stage).repeats == 0) {
    // indicates repeating forever, only set next reminder
    APP_LOG(APP_LOG_LEVEL_INFO, "forever repeating...");
    wakeup_schedule_next_in_minutes((*running_state_reminder_stage).length);
    return;
  };
  // check if there is still remaining repeat
  if (running_state_current.remaining_repeats > 0) {
    running_state_current.remaining_repeats -= 1;
    wakeup_schedule_next_in_minutes((*running_state_reminder_stage).length);
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

// initialize wakeup & subscribe  
void wakeup_init() {
  wakeup_service_subscribe(wakeup_handler);
  APP_LOG(APP_LOG_LEVEL_INFO, "wakeup initialized"); 
}
