#include <pebble.h>
#include "debug.h"
#include "w_running.h"
#include "data.h"
#include "running_state.h"
#include "what.h"
#include "format.h"
#include "wakeup.h"  
#include "w_selection.h"  
#include "w_communication.h"
#include "w_confirmation.h"
#include "localsummary.h"

enum MidSectionMode {
	start_lasted = 0,
	local_summary = 1,
};

static enum MidSectionMode mid_section_mode = start_lasted;

#define MID_SECTION_MODE_CHANGE_TIME 10

static char line1[15];
static char line2[15];
char warning[20];
static char current_date[15];
static char current_time[10];

char mode;
static GBitmap *s_res_image_action_plus;
static GBitmap *s_res_image_action_clear;
static GBitmap *s_res_image_action_minus;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_14;
static GFont s_res_gothic_28;
static GFont s_res_gothic_24_bold;
static GFont s_res_gothic_24;
static GBitmap *s_res_image_action_adjust;
static GBitmap *s_res_image_action_wireless;
static GBitmap *s_res_image_action_stop;
static GFont s_res_bitham_34_medium_numbers;
static TextLayer *t_warning;
static BitmapLayer *s_bitmaplayer_1;
static TextLayer *t_what;
static TextLayer *t_plus_minus;
static TextLayer *t_line2;
static TextLayer *t_line1;
static TextLayer *t_date;
static ActionBarLayer *s_actionbarlayer_1;
static TextLayer *t_time;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_gothic_28 = fonts_get_system_font(FONT_KEY_GOTHIC_28);
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  s_res_image_action_adjust = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_ADJUST);
  s_res_image_action_wireless = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_WIRELESS);
  s_res_image_action_stop = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_STOP);
  s_res_bitham_34_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS);
  // t_warning
  t_warning = text_layer_create(GRect(0, 150, 116, 20));
  text_layer_set_background_color(t_warning, GColorBlack);
  text_layer_set_text_color(t_warning, GColorWhite);
  text_layer_set_text(t_warning, " ");
  text_layer_set_text_alignment(t_warning, GTextAlignmentCenter);
  text_layer_set_font(t_warning, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_warning);
  
  // s_bitmaplayer_1
  s_bitmaplayer_1 = bitmap_layer_create(GRect(0, 103, 116, 47));
  bitmap_layer_set_background_color(s_bitmaplayer_1, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_1);
  
  // t_what
  t_what = text_layer_create(GRect(0, 72, 116, 31));
  text_layer_set_background_color(t_what, GColorBlack);
  text_layer_set_text_color(t_what, GColorWhite);
  text_layer_set_text(t_what, "Nothing ");
  text_layer_set_text_alignment(t_what, GTextAlignmentCenter);
  text_layer_set_font(t_what, s_res_gothic_28);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_what);
  
  // t_plus_minus
  t_plus_minus = text_layer_create(GRect(100, 124, 14, 26));
  text_layer_set_background_color(t_plus_minus, GColorClear);
  text_layer_set_text_color(t_plus_minus, GColorWhite);
  text_layer_set_text(t_plus_minus, "+");
  text_layer_set_font(t_plus_minus, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_plus_minus);
  
  // t_line2
  t_line2 = text_layer_create(GRect(2, 124, 105, 28));
  text_layer_set_background_color(t_line2, GColorClear);
  text_layer_set_text_color(t_line2, GColorWhite);
  text_layer_set_text(t_line2, "l2");
  text_layer_set_font(t_line2, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_line2);
  
  // t_line1
  t_line1 = text_layer_create(GRect(2, 102, 107, 30));
  text_layer_set_background_color(t_line1, GColorClear);
  text_layer_set_text_color(t_line1, GColorWhite);
  text_layer_set_text(t_line1, "l1");
  text_layer_set_font(t_line1, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_line1);
  
  // t_date
  t_date = text_layer_create(GRect(0, 0, 116, 28));
  text_layer_set_background_color(t_date, GColorBlack);
  text_layer_set_text_color(t_date, GColorWhite);
  text_layer_set_text(t_date, " Tue 23 Jun");
  text_layer_set_text_alignment(t_date, GTextAlignmentCenter);
  text_layer_set_font(t_date, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_date);
  
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorBlack);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_image_action_adjust);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_image_action_wireless);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_image_action_stop);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
  
  // t_time
  t_time = text_layer_create(GRect(0, 28, 116, 44));
  text_layer_set_background_color(t_time, GColorBlack);
  text_layer_set_text_color(t_time, GColorWhite);
  text_layer_set_text(t_time, "04:04");
  text_layer_set_text_alignment(t_time, GTextAlignmentCenter);
  text_layer_set_font(t_time, s_res_bitham_34_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_time);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(t_warning);
  bitmap_layer_destroy(s_bitmaplayer_1);
  text_layer_destroy(t_what);
  text_layer_destroy(t_plus_minus);
  text_layer_destroy(t_line2);
  text_layer_destroy(t_line1);
  text_layer_destroy(t_date);
  action_bar_layer_destroy(s_actionbarlayer_1);
  text_layer_destroy(t_time);
  gbitmap_destroy(s_res_image_action_adjust);
  gbitmap_destroy(s_res_image_action_wireless);
  gbitmap_destroy(s_res_image_action_stop);
}
// END AUTO-GENERATED UI CODE

void mode_normal() {
  mode = 'N'; // mode normal
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_image_action_adjust);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_image_action_wireless);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_image_action_stop);
}

void mode_adjust() {
  mode = 'A'; // mode adjust
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_image_action_plus);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_image_action_clear);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_image_action_minus);
}


static void handle_window_unload(Window* window) {
  destroy_ui();
  gbitmap_destroy(s_res_image_action_plus);
  gbitmap_destroy(s_res_image_action_clear);
  gbitmap_destroy(s_res_image_action_minus);  
}

static void my_init(); // stub, definition at end

void show_w_running(void) {
	APP_LOG(APP_LOG_LEVEL_INFO," #### showing window Running");
  initialise_ui();
  mode = 'N';
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  my_init();
}


void hide_w_running(void) {
  window_stack_remove(s_window, true);
}

// returns - earlier (true) or later
bool fmt_timediff_str(char* buffer, size_t size, time_t t1, time_t t2) {
  struct TimeDifference tdiff;
  fmt_to_timediff(&tdiff, t1, t2);
  if (tdiff.days != 0) {
    snprintf(buffer, size, "Lst: %ud %u h", tdiff.days, tdiff.hours);
  } else if (tdiff.hours != 0) {
    snprintf(buffer, size, "Lst: %uh %u m", tdiff.hours, tdiff.minutes);
  } else {
    snprintf(buffer, size, "Lst: %um %u s", tdiff.minutes, tdiff.seconds);
  };
  return tdiff.earlier;
}

static time_t mid_section_mode_lastchange_time;

void display_mid_section_switch_state(time_t now) {
	if ((mid_section_mode != start_lasted) && (now - mid_section_mode_lastchange_time) >= MID_SECTION_MODE_CHANGE_TIME) {
		mid_section_mode = start_lasted;
	};
};

void display_mid_section_start_lasted (time_t tnow) {
	// start / lasted time
	strftime(line1, sizeof(line1), "Str: %I:%M %P", localtime(&(running_state_current.start_time)));
	text_layer_set_text(t_line1, line1);  
	if (fmt_timediff_str(line2, sizeof(line2), tnow, running_state_current.start_time)) {
		// now earlier than start time???!!
		text_layer_set_text(t_line2, "Lst: ERR!");
	} else {
		text_layer_set_text(t_line2, line2);	
	};
};	

void display_mid_section_tdy_yest(time_t tnow) {
	// today / yesterday
	struct LocalSummaryType *lsum = get_local_summary_by_what_index(running_state_current.whats_running_idx);
	uint16_t today = lsum -> one_100_hours_today + (tnow - running_state_current.start_time + 18) / 36;
	snprintf(line1, sizeof(line1), "Tody: %u.%02u h ", (today)/100, (today)%100);	
	text_layer_set_text(t_line1, line1);  
	snprintf(line2, sizeof(line2), "Ystdy: %u.%02u h ", (lsum -> one_100_hours_yesterday)/100, (lsum -> one_100_hours_yesterday)%100);	
	text_layer_set_text(t_line2, line2);	
};	


void display_mid_section(void) {
	time_t time_now;
	struct tm *time_now_local;	
	time(&time_now);
	time_now_local = localtime(&time_now);
	
	display_mid_section_switch_state(time_now);
	
	strftime(current_date, sizeof(current_date), FORMAT_CURRENT_DATE, time_now_local);
	strftime(current_time, sizeof(current_time), FORMAT_CURRENT_TIME, time_now_local);
  
	text_layer_set_text(t_date, current_date);	
	text_layer_set_text(t_time, current_time);	
  
	switch (mid_section_mode) {
		case 0: 
			display_mid_section_start_lasted(time_now);
			break;
		case 1 : 
			display_mid_section_tdy_yest(time_now);
			break;
	};
};

// synchronize contents of the running window
void sync_w_running(void) {
  text_layer_set_text(t_what, (*running_state_what).name);
  if (running_state_current.plus_step == 0) {
    text_layer_set_text(t_plus_minus, "");
  } else if (running_state_current.plus_step > 0) {
    text_layer_set_text(t_plus_minus, "+");
  } else {
    text_layer_set_text(t_plus_minus, "-");
  };

  display_mid_section();
};



// handle ticks - update running & remaining time
static void w_running_tick_handler(struct tm *tick_time, TimeUnits units_changed) {
	// if time-out, return to running window
  if (inactivity_timeout()) {
  	if (window_stack_get_top_window() != s_window) {
  			APP_LOG(APP_LOG_LEVEL_INFO, "Inactive, return to window running...");
  			while (window_stack_get_top_window() != s_window) 
  				window_stack_pop(true);
  			}; 
    if (mode != 'N')
      mode_normal();
    }
  display_mid_section();
};

void update_warning(const char* warning) {
	text_layer_set_text(t_warning, warning);
};

void space_shortage_warning_check() {
	uint8_t spaceleft = DATA_STORE_SIZE - data_store_usage_count();
	if (spaceleft > 20) update_warning(" ");
	else if (spaceleft > 1) {
			snprintf(warning, sizeof(warning), "%d Spaces Left",spaceleft);
			update_warning(warning);
	}	else if (spaceleft == 1) update_warning("Last Space Left");
		else update_warning("Storage Full");
};

void what_finish_handler_after_confirmation(bool confirmed){
	if (confirmed) {
		running_state_commit();
		// then pop-up selection window
		#ifdef DEBUG_SAVE_DEBUG_RECORDS
			// write random records to test batch sending function
			while (data_store_usage_count() < DATA_STORE_SIZE) {
				running_state_current.start_time -= 3 * 3600 * data_store_usage_count(); // previous 3 hours
				running_state_current.whats_running_idx = data_store_usage_count()%WHAT_LIST_LENGTH;
				running_state_commit();
			};	  
		#endif
		show_w_selection();		
	};
};

/* adjust step: 10 minutes */
#define adjust_step 600

void adjust_plus() {
  running_state_current.start_time -= adjust_step;
  running_state_current.plus_step += 1; 
  sync_w_running();
  running_state_save();
};

void adjust_minus() {
	time_t time_now;
	time(&time_now);  
  if (running_state_current.start_time + adjust_step <= time_now) { // otherwise start in future, not allowed
    running_state_current.start_time += adjust_step;
    running_state_current.plus_step -= 1;   
    sync_w_running();
    running_state_save();
  }
};

// up_handler
static void up_short_handler(ClickRecognizerRef recognizer, void *context) {
  reset_activity_timer();
  if (mode == 'A')
    adjust_plus();
}

// down_handler
static void down_short_handler(ClickRecognizerRef recognizer, void *context) {
  reset_activity_timer();
  if (mode == 'A')
    adjust_minus();
  else {
  	if (mid_section_mode == start_lasted && running_state_current.whats_running_idx!=0) { // if running nothing, no local summary mode
		mid_section_mode = local_summary;
		mid_section_mode_lastchange_time = time(NULL);
	} else {
		mid_section_mode = start_lasted;
	};
	display_mid_section();
  };
}

void what_discard_handler_after_confirmation(bool confirmed){
	if (confirmed) {
		running_state_kickoff(0);
	};
};


// mid_handler
static void mid_short_handler(ClickRecognizerRef recognizer, void *context) {
  reset_activity_timer();
  if (mode == 'N') { // call communicator
    show_w_communication();
  } else {
	  if (running_state_current.whats_running_idx != 0) { 
		  confirmation_ask("Discard this?", &what_discard_handler_after_confirmation);
	  };
  }
}  

// back_handler
static void back_short_handler(ClickRecognizerRef recognizer, void *context) {
  if (mode == 'N') { // exit
    reset_activity_timer();
    window_stack_pop_all(false);
  } else {
  	mode_normal();
  }
} 

// up_long_handler
static void up_long_handler(ClickRecognizerRef recognizer, void *context) {
  reset_activity_timer();
  mode_adjust();
}


// down click handler - finish current what
static void what_finish_handler_long(ClickRecognizerRef recognizer, void *context) {
	reset_activity_timer();
	if (mode == 'A') return;
	if (running_state_current.whats_running_idx == 0) { // nothing, no need to commit, just bring up selection window 
		show_w_selection();
	} else {
    // bring up confirmation window
		confirmation_ask("Log session?", &what_finish_handler_after_confirmation);
	};
}


// subscribe click events
void w_running_click_config_provider(void *context) {
  window_long_click_subscribe(BUTTON_ID_UP, 0, &up_long_handler, NULL);	
  window_long_click_subscribe(BUTTON_ID_DOWN, 0, &what_finish_handler_long, NULL);
  window_single_click_subscribe(BUTTON_ID_UP, &up_short_handler);  
  window_single_click_subscribe(BUTTON_ID_DOWN, &down_short_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, &mid_short_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, &back_short_handler);
};

void running_vibe() {
	if (window_stack_get_top_window() == s_window) {
		vibes_long_pulse();
	};
} ;

// register handlers
static void my_init() {
	APP_LOG(APP_LOG_LEVEL_INFO,"w_running - my_init");
  // load additional icons
  s_res_image_action_plus = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_PLUS);
  s_res_image_action_clear = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_CLEAR);
  s_res_image_action_minus = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_MINUS);  
  // register tick handler
  tick_timer_service_subscribe(SECOND_UNIT, &w_running_tick_handler);
  // up click for time extension
  window_set_click_config_provider(s_window, &w_running_click_config_provider);
}
