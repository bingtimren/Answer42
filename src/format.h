#pragma once
#include <pebble.h>  

#define FORMAT_24HTIME "%H:%M %S"
#define FORMAT_24HTIME_BUFFER_LENGTH 9
  
/* convert time to localtime and format to "HH:MM" */
void fmt_time_24h(char* buffer, const size_t size, const time_t *time_ptr);

struct TimeDifference {
  uint8_t days;
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
};