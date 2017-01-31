#pragma once
#include <pebble.h>  

#define FORMAT_24HTIME "%I:%M %P"
#define FORMAT_CURRENT_DATE "%a %d %b"
#define FORMAT_CURRENT_TIME "%I:%M"
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


time_t starts_of_today();
time_t starts_of_the_day(time_t time_now);
uint16_t minutes_past_midnight(time_t t);
