#include <pebble.h>
#include "debug.h"
#include "what.h"
#include "running_state.h"
#include "data.h"

const struct WhatType *running_state_what() {
  return &(what_list[current_running_state.whats_running_idx]);
}  

// obtain summary of running state for logging
#ifdef APP_LOG
char* running_state_summary() {
  static char running_state_summary_buffer[100];
  char t1buffer[6];
  char t2buffer[6];
  strftime(t1buffer, 6, "%H:%M", localtime(&(current_running_state.start_time)));
  strftime(t2buffer, 6, "%H:%M", localtime(&(current_running_state.target_time)));
  
  snprintf(running_state_summary_buffer,sizeof(running_state_summary_buffer),"[%s]ST[%s]TG[%s]", (*running_state_what()).name, t1buffer, t2buffer);
  return running_state_summary_buffer;
}
#endif

  
void running_state_save() {
  persist_write_data(KEY_CURRENT_RUNNING_STATE, &current_running_state, sizeof(current_running_state));
  APP_LOG(APP_LOG_LEVEL_INFO, "Running state [%s] saved ", running_state_summary());
}


void running_state_kickoff(int whats_idx) {
  current_running_state.whats_running_idx = whats_idx;
  time(&current_running_state.start_time);
  current_running_state.stage_idx = 0;
  current_running_state.target_time = current_running_state.start_time + 60 * what_list[whats_idx].stage_lengths[0];
  APP_LOG(APP_LOG_LEVEL_INFO, "Running state [%s] kicked-off ", running_state_summary());
};

void running_state_load () {
  if (persist_exists(KEY_CURRENT_RUNNING_STATE)) {
    persist_read_data(KEY_CURRENT_RUNNING_STATE, &current_running_state, sizeof(current_running_state));
    APP_LOG(APP_LOG_LEVEL_INFO, "Running state [%s] loaded ", running_state_summary());
    return;
  };
  APP_LOG(APP_LOG_LEVEL_INFO, "Running state not found in store, kicking off NIL");
  running_state_kickoff(0);
  running_state_save();
};
