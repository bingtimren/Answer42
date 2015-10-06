#pragma once

enum WakeUpCookieType {
  RunningStateReminder = 1,
  SelectionTimeOut = 2,
  BluetoothHighTimeOut = 3
};

void wakeup_init();

void vibe_reminder();

// schedule next wakeup in period
void wakeup_schedule_next_in_minutes(uint16_t minutes_to_now, int32_t cookie );

void wakeup_schedule_next_in_seconds(uint16_t seconds_to_now, int32_t cookie );

// schedule next wakeup at target time
void wakeup_schedule_next_target_time(time_t target, int32_t cookie);

void wakeup_cancel_by_cookie(int32_t cookie);

