#pragma once
#include <pebble.h>

#include "what.h"
  
/* current running status */
struct RunningState {
  uint8_t whats_running_idx;
  time_t start_time;
  time_t target_time;
  uint8_t stage_idx;
  uint8_t remaining_repeats;
};

// global variable holding the current running state
struct RunningState running_state_current;

void running_state_save();
  
void running_state_kickoff(int whats_idx);

void running_state_change_stage(uint8_t stage_idx);

void running_state_load ();

void running_state_clear();

// state holding pointers, to avoid repeated calculation but must be 
// consistently maintained;
const struct WhatType *running_state_what;
const struct WhatReminderStageType *running_state_reminder_stage;
