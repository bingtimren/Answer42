#include <pebble.h>
#include "debug.h"
#include "what.h"
#include "running_state.h"
#include "data.h"
#include "format.h"

const struct WhatType *running_state_what() {
  return &(what_list[current_running_state.whats_running_idx]);
}  

// obtain summary of running state for logging
#ifdef APP_LOG
char* running_state_summary() {
  static char running_state_summary_buffer[100];
  char t1buffer[FORMAT_24HTIME_BUFFER_LENGTH];
  char t2buffer[FORMAT_24HTIME_BUFFER_LENGTH];
  fmt_time_24h(t1buffer, sizeof(t1buffer), &(current_running_state.start_time));
  fmt_time_24h(t2buffer, sizeof(t2buffer), &(current_running_state.target_time));
  snprintf(running_state_summary_buffer,sizeof(running_state_summary_buffer),"[%s]ST[%s]TG[%s]", (*running_state_what()).name, t1buffer, t2buffer);
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
  persist_write_data(KEY_CURRENT_RUNNING_STATE, &current_running_state, sizeof(current_running_state));
  APP_LOG(APP_LOG_LEVEL_INFO, "Running state [%s] saved ", running_state_summary());
}

// kick starting a WHAT as current running state and save the running state
void running_state_kickoff(int whats_idx) {
  current_running_state.whats_running_idx = whats_idx;
  time(&current_running_state.start_time);
  current_running_state.stage_idx = 0;
  current_running_state.target_time = current_running_state.start_time + SECONDS_PER_MIN * what_list[whats_idx].stage_lengths[0];
  running_state_save();
  APP_LOG(APP_LOG_LEVEL_INFO, "Running state [%s] kicked-off ", running_state_summary());
};

// load the running state from persistent storage of the phone. if not found, kick off the first one (index 0), which should
// be NOTHING
void running_state_load () {
  if (persist_exists(KEY_CURRENT_RUNNING_STATE)) {
    persist_read_data(KEY_CURRENT_RUNNING_STATE, &current_running_state, sizeof(current_running_state));
    APP_LOG(APP_LOG_LEVEL_INFO, "Running state [%s] loaded ", running_state_summary());
    return;
  };
  APP_LOG(APP_LOG_LEVEL_INFO, "Running state not found in store, kicking off NIL");
  running_state_kickoff(0);
};
