#include <pebble.h>
#include "debug.h"
#include "what.h"
#include "running_state.h"
#include "data.h"
#include "format.h"
#include "wakeup.h"
#include "w_running.h"

const struct WhatType *running_state_what;
struct RunningState running_state_current;
const struct WhatReminderStageType *running_state_reminder_stage;

// obtain summary of running state for logging
#ifdef APP_LOG
char* running_state_summary() {
  static char running_state_summary_buffer[100];
  char t1buffer[FORMAT_24HTIME_BUFFER_LENGTH];
  char t2buffer[FORMAT_24HTIME_BUFFER_LENGTH];
  fmt_time_24h(t1buffer, sizeof(t1buffer), &(running_state_current.start_time));
  fmt_time_24h(t2buffer, sizeof(t2buffer), &(running_state_current.target_time));
  snprintf(running_state_summary_buffer,sizeof(running_state_summary_buffer),"[%s]ST[%s]TG[%s]", (*running_state_what).name, t1buffer, t2buffer);
  return running_state_summary_buffer;
}
#endif

void running_state_kickoff_repeat();  // stub definition
  
// clear running state - this should be called only for debugging purpose
void running_state_clear() {
  if (persist_exists(KEY_CURRENT_RUNNING_STATE)) {
    persist_delete(KEY_CURRENT_RUNNING_STATE);
    APP_LOG(APP_LOG_LEVEL_INFO, "Running state cleared.");
  };
}

// save running state into the persistent storage of the watch
void running_state_save() {
  persist_write_data(KEY_CURRENT_RUNNING_STATE, &running_state_current, sizeof(running_state_current));
  APP_LOG(APP_LOG_LEVEL_INFO, "Running state [%s] saved ", running_state_summary());
}

// calculate next reminder from time; 0 if no more reminder (where index out of range)
time_t running_next_reminder_time(time_t start) {
  if (running_state_reminder_stage != NULL){
    return start + SECONDS_PER_MIN * ((*running_state_reminder_stage).length);
  }
  APP_LOG(APP_LOG_LEVEL_ERROR, "when running_state_reminder_stage is NULL, should not calculate next reminder");
  return (time_t)0;
}

// change reminder stage to given index, set running state stage, set reminder stage pointer (so easier to get parameters)
// then kick start the first repeat
void running_state_kickoff_stage(uint8_t stage_idx) {
  APP_LOG(APP_LOG_LEVEL_INFO, "stage index setting to %d", stage_idx);
  running_state_current.stage_idx = stage_idx;
  if (stage_idx >= (*running_state_what).number_of_stages) {
    running_state_reminder_stage = NULL;
    APP_LOG(APP_LOG_LEVEL_INFO, "out of stages");
    return;
  }

  // when index updated, convenience pointer must also be updated
  running_state_reminder_stage = (*running_state_what).stages + stage_idx;
  APP_LOG(APP_LOG_LEVEL_INFO, "stage parameters to %d,%d", (*running_state_reminder_stage).length,(*running_state_reminder_stage).repeats);

  // set remaining repeats
  running_state_current.remaining_repeats = (*running_state_reminder_stage).repeats;
  // if this is stage 0, also update target time
  if (stage_idx == 0) {
    running_state_current.target_time = running_state_current.start_time + 
    (*running_state_reminder_stage).length * (*running_state_reminder_stage).repeats * SECONDS_PER_MIN;
    APP_LOG(APP_LOG_LEVEL_INFO, "running target time updated, %s", running_state_summary());
  };
  // kick off the first repeat
  running_state_kickoff_repeat();
}

// kick starting a WHAT as current running state (not saved; saving to be done by caller always)
// 1. update running_state_current
// 2. pointing running_state_what
// 3. update start / target time
// 4. kick off stage 0
void running_state_kickoff(int whats_idx) {
  running_state_current.whats_running_idx = whats_idx;
  running_state_what = what_list[whats_idx];
  // set start time 
  time(&running_state_current.start_time);
  // kick off stage 0, in which will also update target time
  running_state_kickoff_stage(0);
  APP_LOG(APP_LOG_LEVEL_INFO, "Running state [%s] kicked-off ", running_state_summary());
};

// load the running state from persistent storage of the phone. if not found, kick off the first one (index 0), which should
// be NOTHING
void running_state_load () {
  if (persist_exists(KEY_CURRENT_RUNNING_STATE)) {
    persist_read_data(KEY_CURRENT_RUNNING_STATE, &running_state_current, sizeof(running_state_current));
    // state maintain
    running_state_what = what_list[running_state_current.whats_running_idx];
    running_state_reminder_stage = (*running_state_what).stages + running_state_current.stage_idx;
    APP_LOG(APP_LOG_LEVEL_INFO, "Running state [%s] loaded ", running_state_summary());
    return;
  };
  APP_LOG(APP_LOG_LEVEL_INFO, "Running state not found in store, kicking off NIL");
  running_state_kickoff(0);
  running_state_save();
};

// kick off start a repeat
void running_state_kickoff_repeat() {
  APP_LOG(APP_LOG_LEVEL_INFO, "stage %d, repeats remaining %d, kick off repeat", running_state_current.stage_idx, running_state_current.remaining_repeats);
  if ((*running_state_reminder_stage).repeats == 0) {
    // indicates repeating forever, only set next reminder
    wakeup_schedule_next_in_minutes((*running_state_reminder_stage).length, RunningStateReminder);
    return;
  };
  // check if there is still remaining repeat
  if (running_state_current.remaining_repeats > 0) {
    running_state_current.remaining_repeats -= 1;
    wakeup_schedule_next_in_minutes((*running_state_reminder_stage).length, RunningStateReminder);
    return;
  };
  // try to move to next reminding stage
  running_state_kickoff_stage(running_state_current.stage_idx + 1);
  // if out of stages, time to carry out end-of-stages action
  if (running_state_reminder_stage == NULL) {
    APP_LOG(APP_LOG_LEVEL_INFO, "run out of stages, time to commit end-of-stages action %d", 
            (*running_state_what).termination_action);
  }
};

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

