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
  (*result_buffer).seconds = secdiff % SEC_IN_MINUTE;
  (*result_buffer).minutes =  (secdiff % SEC_IN_HOUR) / SEC_IN_MINUTE;
  (*result_buffer).hours = (secdiff % SEC_IN_DAY) / SEC_IN_HOUR;
  (*result_buffer).days = secdiff / SEC_IN_DAY;
}

void fmt_minutes_to_hour_minutes(char* res_buffer, int buffer_length, uint16_t minutes) {
	uint16_t days = minutes / MINUTES_PER_DAY;
	uint8_t hours = (minutes % MINUTES_PER_DAY) / MINUTES_PER_HOUR;
	uint8_t min = (minutes % MINUTES_PER_DAY) % MINUTES_PER_HOUR;
	
	if (days > 0) {
		uint8_t d1 = snprintf(res_buffer, buffer_length, "%ud", days);
	};
	
}


// returns - earlier (true) or later
bool fmt_timediff_str(char* buffer, size_t size, time_t t1, time_t t2) {
  struct TimeDifference tdiff;
  fmt_to_timediff(&tdiff, t1, t2);
  if (tdiff.days != 0) {
    snprintf(buffer, size, "%ud %uh", tdiff.days, tdiff.hours);
  } else if (tdiff.hours != 0) {
    snprintf(buffer, size, "%uh %um", tdiff.hours, tdiff.minutes);
  } else {
    snprintf(buffer, size, "%um %us", tdiff.minutes, tdiff.seconds);
  };
  return tdiff.earlier;
}
