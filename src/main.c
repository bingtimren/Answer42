#include <pebble.h>
#include "debug.h"
#include "w_running.h"
#include "running_state.h"
  
static void init(void) {
  APP_LOG(APP_LOG_LEVEL_INFO, "init....");
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