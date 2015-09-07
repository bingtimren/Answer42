#pragma once
#include <pebble.h>
#include "what.h"
  
/* current running status */
struct RunningState {
  uint8_t whats_running_idx;
  time_t start_time;
  time_t target_time;
  uint8_t stage_idx;
};

// global variable holding the current running state
struct RunningState running_state_current;

void running_state_save();
  
void running_state_kickoff(int whats_idx);

void running_state_load ();

const struct WhatType *running_state_what();

void running_state_clear();