#include <pebble.h>
#include "format.h"

/* convert time to localtime and format to "HH:MM" */
void fmt_time_24h(char* buffer, const size_t size, const time_t *time_ptr) {
  strftime(buffer, size, FORMAT_24HTIME, localtime(time_ptr));
}