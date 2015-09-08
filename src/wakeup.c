#include <pebble.h>
#include "wakeup.h"
#include "running_state.h"
#include "data.h"  
  
void vibe_reminder() {
  vibes_long_pulse();
}  


// schedule next wakeup in minutes
void wakeup_schedule_next(uint16_t minutes_to_now) {
  time_t next_wakeup_time = time(NULL) + SECONDS_PER_MIN * minutes_to_now;
  wakeup_schedule(next_wakeup_time, REMINDER_DUE, false);
}


// handling wakeup & stage changes
void wakeup_handler(WakeupId wakeup_id, int32_t cookie) {
  // now no check of cookie, since only one type of event is handled: stage reminder / possible next stage
  vibe_reminder();
  APP_LOG(APP_LOG_LEVEL_INFO, "woke up, stage %d, repeats remaining %d", running_state_current.stage_idx, running_state_current.remaining_repeats);
  if ((*running_state_reminder_stage).repeats == 0) {
    // indicates repeating forever, only set next reminder
    wakeup_schedule_next((*running_state_reminder_stage).length);
  };
  // check if there is still remaining repeat
  if (running_state_current.remaining_repeats > 0) {
    running_state_current.remaining_repeats -= 1;
    running_state_save();
    wakeup_schedule_next((*running_state_reminder_stage).length);
  };
  // try to move to next reminding stage
  running_state_change_stage(running_state_current.stage_idx + 1);
  // if out of stages, time to carry out end-of-stages action
  if (running_state_reminder_stage == NULL) {
    APP_LOG(APP_LOG_LEVEL_INFO, "run out of stages, time to commit end-of-stages action %d", 
            (*running_state_what).termination_action);
  }
}
