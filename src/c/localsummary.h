#pragma once
#include <pebble.h>  

// local summary for each WhatType
struct LocalSummaryType {
  uint16_t one_100_hours_yesterday;
  uint16_t one_100_hours_today;
};


time_t starts_of_today();
void local_summary_load ();
void local_summary_accumulate(uint8_t what_index, int minutes);
void local_summary_clear();
struct LocalSummaryType* get_local_summary_by_what_index(uint8_t index);
void commit_local_summary_by_what_index(time_t time, uint16_t time_by_1_100th_hour, uint8_t index);
