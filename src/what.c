#include <pebble.h>
#include "what.h"
#include "debug.h"

#include "reminder_stages.h"

/*********************************************************************************************/
//                                 What definitions


const struct WhatType WHAT_NOTHING = {
  "Nothing",
  "Nil",
  3, // 3 stages
  r5x2_5x10_30,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_WORK = {
  "Work",
  "Work",
  2, // 2 stages
  r15x2_15,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_SLEEP = {
  "Sleep",
  "Sleep",
  2, // 3 stages
  r480_30x4,
  COMMIT_AS_IS
};

const struct WhatType WHAT_SPORTS = {
  "Sports",
  "Sports",
  2, // 2 stages
  r60_60x3,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_HYGIENE = {
  "Hygiene",
  "Hygiene",
  2, // 2 stages
  r30_10x5,
  COMMIT_AS_IS
};

const struct WhatType WHAT_DOMESTIC = {
  "Domestic",
  "Domestic Works",
  2, // 2 stages
  r30_10x5,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_SHOPPING = {
  "Shopping",
  "Shopping",
  2, // 2 stages
  r30_10x5,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_Purchasing = {
  "Purchasing",
  "Purchasing",
  2, // 2 stages
  r30_10x5,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_READING = {
  "Reading",
  "Reading",
  2, // 2 stages
  r30_30,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_STUDYING = {
  "Studying",
  "Studying",
  2, // 2 stages
  r30_30,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_LEISURE = {
  "Leisure",
  "Leisure",
  2, // 2 stages
  r180_60x5,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_MEDITATION = {
  "Meditation",
  "Meditation",
  2, // 2 stages
  r60_60x3,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_PET = {
  "Pet",
  "Pet",
  2, // 2 stages
  r60_60x3,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_TRAFFIC = {
  "Traffic",
  "Traffic",
  2, // 2 stages
  r60_60x3,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_HEALTH = {
  "Health Care",
  "Health",
  2, // 2 stages
  r60_60x3,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_SOCIAL = {
  "Social",
  "Social",
  2, // 2 stages
  r60_60x3,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_CULTURE = {
  "Culture",
  "Culture",
  2, // 2 stages
  r60_60x3,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_COOKDINE = {
  "Cook & Dine",
  "Cook Dine",
  2, // 2 stages
  r30x2_15x4,
  COMMIT_AS_IS
};

const struct WhatType WHAT_SMISC = {
  "Serious Misc.",
  "S. Misc.",
  2, // 2 stages
  r30_30,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_BREAKS = {
  "Breaks",
  "Breaks",
  2, // 2 stages
  r5_5x3,
  COMMIT_AS_IS
};

const struct WhatType WHAT_MISC = {
  "Misc.",
  "Misc.",
  2, // 2 stages
  r30_30,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_MEDIA = {
  "Media",
  "Media",
  2, // 2 stages
  r30_30,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_RELAX = {
  "Relaxing",
  "Relax",
  2, // 2 stages
  r180_60x5,
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


