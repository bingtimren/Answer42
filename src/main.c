#include <pebble.h>
#include "debug.h"
#include "w_running.h"
#include "running_state.h"
#include "wakeup.h"
#include "data.h"  
#include "what.h"
  
static void init(void) {
  APP_LOG(APP_LOG_LEVEL_INFO, "****************************************** [%s] starting.... *******************************", VERSION_INFO);
  setlocale(LC_ALL, "en_AU");
  // initialize what - calculate the lengths of each short names
  what_initiate();
  // initialize wakeup service - subscribe
  wakeup_init();
  // show running window
  show_w_running();  
  // load running states
  running_state_load();

  //is the launch due to wake_up?
  if (launch_reason() == APP_LAUNCH_WAKEUP) {
	  WakeupId wakeup_id;
	  int32_t cookie;
	  if (wakeup_get_launch_event(&wakeup_id, &cookie)) {
		  APP_LOG(APP_LOG_LEVEL_INFO,"Relaunching due to wake-up, calling handler...");
		  wakeup_handler(wakeup_id, cookie);
	  };
  };
}

static void deinit(void) {
	APP_LOG(APP_LOG_LEVEL_INFO,"********************************* DE-INIT ******************************");	
}

// main
int main(void) {
  init();
  app_event_loop();
  deinit();
}
