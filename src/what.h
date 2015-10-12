#pragma once
#include <pebble.h>

/* Definition of WHAT, the ultimate question */  

enum WhatTerminationActionType {
  LAST_NO_REMINDER = 1,  // no more reminder, never finish
  COMMIT_AS_IS = 2  // commit as the type and length as recorded
};  

struct WhatReminderStageType {
  uint16_t length;
  uint8_t repeats; // 0 indicating repeat forever
};

struct WhatType {
  char* name;
  char* short_name;
  // number of stages
  uint8_t number_of_stages;
  // length in minutes in each stage
  const struct WhatReminderStageType* stages;
  // what to do when last stage finishes & no user termination
  uint8_t termination_action;
};

/* Definition of reminder patterns */
extern const struct WhatReminderStageType reminder_then_give_up[3];

/* Definition of "WHAT"s - how I classify my time, how I want to be remindered */

extern const struct WhatType WHAT_NOTHING;
  
/* WHAT database - a list of all the "WHAT"s, where position 0 should be the default - NOTHING  */

#define WHAT_LIST_LENGTH 23
extern const struct WhatType* what_list[];
extern uint8_t what_list_length_short_name[];

void what_initiate();
