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

uint8_t fmt_minutes_to_hour_minutes(char* res_buffer, int buffer_length, uint16_t minutes) {
	uint16_t days = minutes / MINUTES_PER_DAY;
	uint8_t hours = (minutes % MINUTES_PER_DAY) / MINUTES_PER_HOUR;
	uint8_t min = (minutes % MINUTES_PER_DAY) % MINUTES_PER_HOUR;
	uint8_t d1 = 0;
	uint8_t d2 = 0;
	uint8_t d3 = 0;
	if (days > 0) {
		d1 = snprintf(res_buffer, buffer_length, "%ud ", days);
	};
	if ((hours > 0) && (d1<buffer_length)) {
		d2 = snprintf(res_buffer+d1, buffer_length-d1, "%uh", hours);
	};
	if ((minutes > 0) && ((d1+d2)<buffer_length)) {
		d3 = snprintf(res_buffer+d1+d2, buffer_length-d1-d2, "%um", min);
	};
	return d1+d2+d3;
}


