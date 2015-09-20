#include <pebble.h>
#include "debug.h"
#include "w_running.h"
#include "running_state.h"
#include "wakeup.h"
  
static void init(void) {
  APP_LOG(APP_LOG_LEVEL_INFO, "[%s] starting....", VERSION_INFO);
  // initialize wakeup service - subscribe
  wakeup_init();
  // load running states
  running_state_load();
  show_w_running();
  sync_w_running();
}

static void deinit(void) {
}

// main
int main(void) {
  init();
  app_event_loop();
  deinit();
}