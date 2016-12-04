#include <pebble.h>
#include "what.h"
#include "debug.h"

#include "reminder_stages.h"

/*********************************************************************************************/
//                                 What definitions


const struct WhatType WHAT_NOTHING = {
  "Nothing",
  "Nil",
  2, 
  r5x1_5x3,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_WORK = {
  "Work",
  "Work",
  2, // 2 stages
  r30_15,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_PERSONAL = {
  "Personal",
  "Personal",
  2, // 2 stages
  r30_30,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_DEVELOPMENT = {
  "Develop",
  "Development",
  2, // 2 stages
  r30_30,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_ENJOYMENT = {
  "Enjoy",
  "Enjoyment",
  2, // 2 stages
  r240_60,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_SLEEP = {
  "Sleep",
  "Sleep",
  2, // 3 stages
  r480_30x4,
  COMMIT_AS_IS
};

const struct WhatType WHAT_DOMESTIC = {
  "Domestic",
  "Domestic Works",
  2, // 2 stages
  r30_15,
  LAST_NO_REMINDER
};

const struct WhatType WHAT_PLAN = {
  "Plan",
  "Planning",
  2, // 2 stages
  r30_15,
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

const struct WhatType WHAT_LMATTER = {
  "LifeMat",
  "Life Matters",
  2, // 2 stages
  r30_30,
  LAST_NO_REMINDER
};



/*********************************************************************************************/
//                                 What - list

/* WHAT database - a list of all the "WHAT"s, where
 0 - NOTHING
 then free define
*/

// !!!!!! Update WHAT_LIST_LENGTH if change number of items in this list !!!!!!
const struct WhatType* what_list[] = {
  &WHAT_NOTHING,
  &WHAT_WORK,
  &WHAT_PERSONAL,
  &WHAT_DEVELOPMENT,
  &WHAT_ENJOYMENT,
  &WHAT_SLEEP,
  &WHAT_DOMESTIC,
  &WHAT_PLAN,
  &WHAT_READING,
  &WHAT_STUDYING,
  &WHAT_LMATTER
};

uint8_t what_list_length_short_name[WHAT_LIST_LENGTH];

// calculate lengths once for all
void what_initiate() {
	for (int i=0; i<WHAT_LIST_LENGTH; i++) {
		what_list_length_short_name[i] = strlen(what_list[i]->short_name);
	};
};


