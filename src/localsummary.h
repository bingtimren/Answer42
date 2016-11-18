#pragma once
#include <pebble.h>  

// local summary for each WhatType
struct LocalSummaryType {
  uint16_t minutes_yesterday;
  uint16_t minutes_today;
};


time_t starts_of_today();
void local_summary_load ();
void local_summary_accumulate(uint8_t what_index, int minutes);
struct LocalSummaryType get_local_summary_by_what_index(uint8_t index);

