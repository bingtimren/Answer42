#pragma once

#define WAKEUP_COOKIE_NUMOF 2


#define INACTIVITY_TIME_OUT 30

enum WakeUpCookieType {
  RunningStateReminder = 0,
  BluetoothHighTimeOut = 1
};

void reset_activity_timer();

bool inactivity_timeout();


void wakeup_init();

void vibe_reminder();

// schedule next wakeup in period
void wakeup_schedule_next_in_minutes(uint16_t minutes_to_now, int32_t cookie );

// schedule next wakeup at target time
void wakeup_schedule_next_target_time(time_t target, int32_t cookie);

void wakeup_cancel_by_cookie(int32_t cookie);

void wakeup_state_clear();

extern WakeupId schedule_registry[];

void wakeup_handler(WakeupId wakeup_id, int32_t cookie);
