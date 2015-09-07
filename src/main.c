#include <pebble.h>
#include "debug.h"
#include "w_running.h"
#include "running_state.h"
  
static void init(void) {
  APP_LOG(APP_LOG_LEVEL_INFO, "init....");
  #ifdef DEBUG_CLEAR_RUNNING_STATE
    APP_LOG(APP_LOG_LEVEL_INFO, "running state cleaning....");
    running_state_clear();
  #endif
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