#pragma once
#include <pebble.h>

#include "what.h"
  
/* current running status */
struct RunningState {
  uint8_t whats_running_idx;
  int plus_step;
  time_t start_time;
  time_t target_time;
  uint8_t stage_idx;
  uint8_t remaining_repeats;
};

// global variable holding the current running state
extern struct RunningState running_state_current;

void running_state_save();
  
void running_state_kickoff(int whats_idx);

void running_state_kickoff_stage(uint8_t stage_idx);

void running_state_load ();

void running_state_clear();

void running_reminder_handler();

// state holding pointers, to avoid repeated calculation but must be 
// consistently maintained;
extern const struct WhatType *running_state_what;
extern const struct WhatReminderStageType *running_state_reminder_stage;

void running_state_commit();
