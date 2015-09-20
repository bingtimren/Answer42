#include <pebble.h>
#include "what.h"

/*********************************************************************************************/
//                                 Reminder stages  
  
const struct WhatReminderStageType reminder_then_give_up[3] = {
  {10,2},
  {5,3},
  {3,2}
};

/*********************************************************************************************/
//                                 What definitions


const struct WhatType WHAT_NOTHING = {
  "Nothing",
  "Nil",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_WORK = {
  "Work",
  "Work",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_SLEEP = {
  "Sleep",
  "Sleep",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_SPORTS = {
  "Sports",
  "Sports",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_HYGIENE = {
  "Hygiene",
  "Hygiene",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_DOMESTIC = {
  "Domestic",
  "Domestic Works",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_SHOPPING = {
  "Shopping",
  "Shopping",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_Purchasing = {
  "Purchasing",
  "Purchasing",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_READING = {
  "Reading",
  "Reading",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_STUDYING = {
  "Studying",
  "Studying",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_LEISURE = {
  "Leisure",
  "Leisure",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_MEDITATION = {
  "Meditation",
  "Meditation",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_PET = {
  "Pet",
  "Pet",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_TRAFFIC = {
  "Traffic",
  "Traffic",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_HEALTH = {
  "Health Care",
  "Health",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_SOCIAL = {
  "Social",
  "Social",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_CULTURE = {
  "Culture",
  "Culture",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_COOKDINE = {
  "Cook & Dine",
  "Cook Dine",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_SMISC = {
  "Serious Misc.",
  "S. Misc.",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_BREAKS = {
  "Breaks",
  "Breaks",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_MISC = {
  "Misc.",
  "Misc.",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_MEDIA = {
  "Media",
  "Media",
  5, // no manual extension
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};


/*********************************************************************************************/
//                                 What - list

/* WHAT database - a list of all the "WHAT"s, where
 0 - NOTHING
 then free define
*/

const struct WhatType* what_list[] = {
  &WHAT_NOTHING,
  &WHAT_WORK,
  &WHAT_SLEEP,
  &WHAT_SPORTS,
  &WHAT_HYGIENE,
  &WHAT_DOMESTIC,
  &WHAT_SHOPPING,
  &WHAT_Purchasing,
  &WHAT_READING,
  &WHAT_STUDYING,
  &WHAT_LEISURE,
  &WHAT_MEDITATION,
  &WHAT_PET,
  &WHAT_TRAFFIC,
  &WHAT_HEALTH,
  &WHAT_SOCIAL,
  &WHAT_CULTURE,
  &WHAT_COOKDINE,
  &WHAT_SMISC,
  &WHAT_BREAKS,
  &WHAT_MISC,
  &WHAT_MEDIA
};

const uint8_t WHAT_LIST_LENGTH = 22;
