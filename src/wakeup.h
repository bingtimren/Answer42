#pragma once

enum WakeUpCookieType {
  REMINDER_DUE = 1
};

void wakeup_init();

void vibe_reminder();

// schedule next wakeup in minutes
void wakeup_schedule_next_in_minutes(uint16_t minutes_to_now);

// schedule next wakeup at target time
void wakeup_schedule_next_target_time(time_t target);

