#pragma once
#include <pebble.h>

/* What type */
#define MAX_STAGES 3

struct WhatType {
  char* name;
  uint16_t manual_extension_length;
  uint16_t stage_lengths[MAX_STAGES];
  uint16_t reminder_intervals[MAX_STAGES];
};

/* Whats DB */

#define MAX_WHATS 1
  
extern const struct WhatType what_list[MAX_WHATS];



/* What constants */
#define WHAT_NOTHING_IDX 0
extern const struct WhatType *WHAT_NOTHING_PTR;