#pragma once
#include <pebble.h>

/* Definition of WHAT, the ultimate question :) */  
enum WhatTerminationActionType {
  LAST_FOREVER 1,  // last stage repeat forever, never finish
  COMMIT_AS_IS 2,  // commit as the type and length as recorded
  COMMIT_NOFIN 3   // commit "Not Finished"
}  
  
struct WhatType {
  char* name;
  char* short_name;
  // how many minutes to extend when user push "time extension" button, "0" indicates no extension allowed
  uint16_t manual_extension_length;
  // number of stages
  uint8_t number_of_stages;
  // length in minutes in each stage
  uint16_t stage_lengths[MAX_STAGES];
  // vibe reminder interval in minutes
  uint16_t reminder_intervals[MAX_STAGES];
  // what to do when last stage finishes & no user termination
  WhatTerminationActionType termination_action;
};

/* Definition of "WHAT"s - how I classify my time, how I want to be remindered */

const struct WhatType WHAT_NOTHING = WhatType{
  "Nothing",
  "Nil"
  0,
  3,
  {5,15,0},
  {1,3,60},
  LAST_FOREVER
}
  
/* WHAT database - a list of all the "WHAT"s, where position 0 should be the default - NOTHING  */

extern const struct WhatType* what_list[] = {
  &WHAT_NOTHING
};


