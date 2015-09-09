#include <pebble.h>
#include "what.h"

const struct WhatReminderStageType reminder_then_give_up[3] = {
  {10,2},
  {5,3},
  {3,2}
};
  
  
const struct WhatType WHAT_NOTHING = {
  "Nothing",
  "Nil",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};
  
/* WHAT database - a list of all the "WHAT"s, where position 0 should be the default - NOTHING  */

const struct WhatType* what_list[] = {
  &WHAT_NOTHING
};


