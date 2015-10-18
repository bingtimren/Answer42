#pragma once
#include <pebble.h>  

#define FORMAT_24HTIME "%H:%M %S"
#define FORMAT_CURRENT_TIME "%a %d %b %I:%M"
#define FORMAT_24HTIME_BUFFER_LENGTH 9
  
/* convert time to localtime and format to "HH:MM" */
void fmt_time_24h(char* buffer, const size_t size, const time_t *time_ptr);

struct TimeDifference {
  bool earlier;
  uint8_t days;
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
};
void fmt_to_timediff(struct TimeDifference* result_buffer, time_t t1, time_t t2);
bool fmt_timediff_str(char* buffer, size_t size, time_t t1, time_t t2);
