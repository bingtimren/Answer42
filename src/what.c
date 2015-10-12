#include <pebble.h>
#include "what.h"
#include "debug.h"

/*********************************************************************************************/
//                                 Reminder stages  
  
const struct WhatReminderStageType reminder_then_give_up[3] = {
  {10,2},
  {5,3},
  {3,2}
};

const struct WhatReminderStageType reminder_then_forever[2] = {
  {10,2},
  {5,0}
};

/*********************************************************************************************/
//                                 What definitions


const struct WhatType WHAT_NOTHING = {
  "Nothing",
  "Nil",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_WORK = {
  "Work",
  "Work",
  2, // 2 stages
  reminder_then_forever,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_SLEEP = {
  "Sleep",
  "Sleep",
  3, // 3 stages
  reminder_then_give_up,
  COMMIT_AS_IS
};

const struct WhatType WHAT_SPORTS = {
  "Sports",
  "Sports",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_HYGIENE = {
  "Hygiene",
  "Hygiene",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_DOMESTIC = {
  "Domestic",
  "Domestic Works",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_SHOPPING = {
  "Shopping",
  "Shopping",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_Purchasing = {
  "Purchasing",
  "Purchasing",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_READING = {
  "Reading",
  "Reading",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_STUDYING = {
  "Studying",
  "Studying",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_LEISURE = {
  "Leisure",
  "Leisure",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_MEDITATION = {
  "Meditation",
  "Meditation",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_PET = {
  "Pet",
  "Pet",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_TRAFFIC = {
  "Traffic",
  "Traffic",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_HEALTH = {
  "Health Care",
  "Health",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_SOCIAL = {
  "Social",
  "Social",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_CULTURE = {
  "Culture",
  "Culture",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_COOKDINE = {
  "Cook & Dine",
  "Cook Dine",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_SMISC = {
  "Serious Misc.",
  "S. Misc.",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_BREAKS = {
  "Breaks",
  "Breaks",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_MISC = {
  "Misc.",
  "Misc.",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_MEDIA = {
  "Media",
  "Media",
  3, // 3 stages
  reminder_then_give_up,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_RELAX = {
  "Relaxing",
  "Relax",
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
  &WHAT_MEDIA,
  &WHAT_RELAX
};

uint8_t what_list_length_short_name[WHAT_LIST_LENGTH];

// calculate lengths once for all
void what_initiate() {
	for (int i=0; i<WHAT_LIST_LENGTH; i++) {
		what_list_length_short_name[i] = strlen(what_list[i]->short_name);
	};
};


