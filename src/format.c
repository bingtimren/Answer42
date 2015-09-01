#include <pebble.h>
#include "format.h"
#include "debug.h"

#define SEC_IN_HOUR 3600
#define SEC_IN_MINUTE 60  
#define SEC_IN_DAY 86400  
  
/* convert time to localtime and format to "HH:MM" */
void fmt_time_24h(char* buffer, const size_t size, const time_t *time_ptr) {
  strftime(buffer, size, FORMAT_24HTIME, localtime(time_ptr));
}

void fmt_to_timediff(struct TimeDifference* result_buffer, time_t t1, time_t t2) {
  (*result_buffer).earlier = (t1 < t2);
  uint32_t secdiff = abs(t1 - t2);
#ifdef DEBUG_TO_SECONDS
  (*result_buffer).seconds = secdiff % SEC_IN_MINUTE;
#else
  (*result_buffer).seconds = 0;
#endif
  (*result_buffer).minutes =  (secdiff % SEC_IN_HOUR) / SEC_IN_MINUTE;
  (*result_buffer).hours = (secdiff % SEC_IN_DAY) / SEC_IN_HOUR;
  (*result_buffer).days = secdiff / SEC_IN_DAY;
}

void fmt_timediff_str(char* buffer, size_t size, time_t t1, time_t t2, char* earlier_indicator, char* later_indicator) {
  struct TimeDifference tdiff;
  char* indicator = "";
  fmt_to_timediff(&tdiff, t1, t2);
  if (tdiff.earlier && (earlier_indicator != NULL))
    indicator = earlier_indicator;
  else if (later_indicator != NULL)
    indicator = later_indicator;
  if (tdiff.days != 0) {
    snprintf(buffer, size, "%ud %uh %um%s", tdiff.days, tdiff.hours, tdiff.minutes, indicator);
  } else {
    snprintf(buffer, size, "%uh %um %us%s", tdiff.hours, tdiff.minutes, tdiff.seconds, indicator);
  };
}