#pragma once
#include "debug.h"
  /* IDs for persistent storage */
#define KEY_CURRENT_RUNNING_STATE 1

/* seconds in a minute - set to 1 for faster time lapsing for debugging */
#ifdef DEBUG_TO_SECONDS
  #define SECONDS_PER_MIN 1
#else
  #define SECONDS_PER_MIN 60
#endif
