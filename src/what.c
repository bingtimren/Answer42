#include <pebble.h>
#include "debug.h"
#include "what.h"

const struct WhatType what_list[MAX_WHATS] = {
  {
    "Nothing",
    5,
    {5,15,0},
    {1,3,60}
  }
};

const struct WhatType *WHAT_NOTHING_PTR = &(what_list[0]);