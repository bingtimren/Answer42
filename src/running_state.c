#include <pebble.h>
#include "debug.h"
#include "what.h"
#include "running_state.h"
#include "data.h"
#include "format.h"

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
    return start + SECONDS_PER_MIN * (*running_state_reminder_stage).length;
  }
  return (time_t)0;
}

// change reminder stage to given index
void running_state_change_stage(uint8_t stage_idx) {
  APP_LOG(APP_LOG_LEVEL_INFO, "stage index setting to %d", stage_idx);
  running_state_current.stage_idx = stage_idx;
  // when index updated, convenience pointer must also be updated
  if (stage_idx < (*running_state_what).number_of_stages) {
    running_state_reminder_stage = (*running_state_what).stages + stage_idx;
    APP_LOG(APP_LOG_LEVEL_INFO, "stage parameters to %d,%d", (*running_state_reminder_stage).length,(*running_state_reminder_stage).repeats);
  } else {
    running_state_reminder_stage = NULL;
    APP_LOG(APP_LOG_LEVEL_INFO, "out of stages");
  }
}

// kick starting a WHAT as current running state and save the running state
void running_state_kickoff(int whats_idx) {
  running_state_current.whats_running_idx = whats_idx;
  running_state_what = what_list[whats_idx];
  // set start time
  time(&running_state_current.start_time);
  // change stage index
  running_state_change_stage(0);
  // update target time
  running_state_current.target_time = running_state_current.start_time + running_next_reminder_time(running_state_current.start_time);
  running_state_save();
  APP_LOG(APP_LOG_LEVEL_INFO, "Running state [%s] kicked-off ", running_state_summary());
};

// load the running state from persistent storage of the phone. if not found, kick off the first one (index 0), which should
// be NOTHING
void running_state_load () {
  if (persist_exists(KEY_CURRENT_RUNNING_STATE)) {
    persist_read_data(KEY_CURRENT_RUNNING_STATE, &running_state_current, sizeof(running_state_current));
    APP_LOG(APP_LOG_LEVEL_INFO, "Running state [%s] loaded ", running_state_summary());
    return;
  };
  APP_LOG(APP_LOG_LEVEL_INFO, "Running state not found in store, kicking off NIL");
  running_state_kickoff(0);
};
