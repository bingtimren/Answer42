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

static char start_time[FORMAT_24HTIME_BUFFER_LENGTH];
static char target_time[FORMAT_24HTIME_BUFFER_LENGTH];  
static char elapsed_time[10];
static char remaining_time[10];  
static char warning[20];
static char current_time[20];

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_action_clear;
static GBitmap *s_res_image_action_wireless;
static GBitmap *s_res_image_action_stop;
static GFont s_res_gothic_18_bold;
static GFont s_res_gothic_18;
static GFont s_res_gothic_14;
static ActionBarLayer *s_actionbarlayer_1;
static TextLayer *t_what;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_2;
static TextLayer *s_textlayer_3;
static TextLayer *t_elapsed_time;
static TextLayer *t_start_time;
static TextLayer *t_target_time;
static TextLayer *t_remain_over;
static TextLayer *t_remaining_time;
static TextLayer *t_warning;
static TextLayer *t_time;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_image_action_clear = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_CLEAR);
  s_res_image_action_wireless = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_WIRELESS);
  s_res_image_action_stop = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_STOP);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorBlack);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_image_action_clear);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_image_action_wireless);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_image_action_stop);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
  
  // t_what
  t_what = text_layer_create(GRect(1, 25, 119, 26));
  text_layer_set_background_color(t_what, GColorBlack);
  text_layer_set_text_color(t_what, GColorWhite);
  text_layer_set_text(t_what, "Nothing ");
  text_layer_set_text_alignment(t_what, GTextAlignmentCenter);
  text_layer_set_font(t_what, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_what);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(1, 55, 58, 20));
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text(s_textlayer_1, "  Started:");
  text_layer_set_font(s_textlayer_1, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(1, 75, 58, 24));
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_text(s_textlayer_2, "  Target:");
  text_layer_set_font(s_textlayer_2, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
  
  // s_textlayer_3
  s_textlayer_3 = text_layer_create(GRect(1, 105, 119, 20));
  text_layer_set_background_color(s_textlayer_3, GColorBlack);
  text_layer_set_text_color(s_textlayer_3, GColorWhite);
  text_layer_set_text(s_textlayer_3, " Elapsed:");
  text_layer_set_font(s_textlayer_3, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_3);
  
  // t_elapsed_time
  t_elapsed_time = text_layer_create(GRect(61, 105, 60, 20));
  text_layer_set_background_color(t_elapsed_time, GColorClear);
  text_layer_set_text_color(t_elapsed_time, GColorWhite);
  text_layer_set_text(t_elapsed_time, " 12:33");
  text_layer_set_font(t_elapsed_time, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_elapsed_time);
  
  // t_start_time
  t_start_time = text_layer_create(GRect(60, 55, 60, 20));
  text_layer_set_background_color(t_start_time, GColorClear);
  text_layer_set_text_color(t_start_time, GColorWhite);
  text_layer_set_text(t_start_time, " ");
  text_layer_set_font(t_start_time, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_start_time);
  
  // t_target_time
  t_target_time = text_layer_create(GRect(60, 75, 60, 20));
  text_layer_set_background_color(t_target_time, GColorClear);
  text_layer_set_text_color(t_target_time, GColorWhite);
  text_layer_set_text(t_target_time, " ");
  text_layer_set_font(t_target_time, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_target_time);
  
  // t_remain_over
  t_remain_over = text_layer_create(GRect(1, 125, 119, 20));
  text_layer_set_background_color(t_remain_over, GColorBlack);
  text_layer_set_text_color(t_remain_over, GColorWhite);
  text_layer_set_text(t_remain_over, " Remain:");
  text_layer_set_font(t_remain_over, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_remain_over);
  
  // t_remaining_time
  t_remaining_time = text_layer_create(GRect(60, 125, 60, 20));
  text_layer_set_background_color(t_remaining_time, GColorClear);
  text_layer_set_text_color(t_remaining_time, GColorWhite);
  text_layer_set_text(t_remaining_time, " 12:33");
  text_layer_set_font(t_remaining_time, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_remaining_time);
  
  // t_warning
  t_warning = text_layer_create(GRect(1, 148, 122, 18));
  text_layer_set_background_color(t_warning, GColorClear);
  text_layer_set_text(t_warning, " ");
  text_layer_set_text_alignment(t_warning, GTextAlignmentCenter);
  text_layer_set_font(t_warning, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_warning);
  
  // t_time
  t_time = text_layer_create(GRect(1, 2, 119, 20));
  text_layer_set_text(t_time, " ");
  text_layer_set_text_alignment(t_time, GTextAlignmentCenter);
  text_layer_set_font(t_time, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_time);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  action_bar_layer_destroy(s_actionbarlayer_1);
  text_layer_destroy(t_what);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_2);
  text_layer_destroy(s_textlayer_3);
  text_layer_destroy(t_elapsed_time);
  text_layer_destroy(t_start_time);
  text_layer_destroy(t_target_time);
  text_layer_destroy(t_remain_over);
  text_layer_destroy(t_remaining_time);
  text_layer_destroy(t_warning);
  text_layer_destroy(t_time);
  gbitmap_destroy(s_res_image_action_clear);
  gbitmap_destroy(s_res_image_action_wireless);
  gbitmap_destroy(s_res_image_action_stop);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static void my_init(); // stub, definition at end

void show_w_running(void) {
	APP_LOG(APP_LOG_LEVEL_INFO," #### showing window Running");
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  my_init();
}

void hide_w_running(void) {
  window_stack_remove(s_window, true);
}

// display lapse and remain
void sync_time_lapse_remain(void) {
	// APP_LOG(APP_LOG_LEVEL_INFO,"Ticking...");
	time_t time_now;
	struct tm *time_now_local;	
	time(&time_now);
	time_now_local = localtime(&time_now);
  strftime(current_time, sizeof(current_time), FORMAT_CURRENT_TIME, time_now_local);
  text_layer_set_text(t_time, current_time);	
  if (fmt_timediff_str(elapsed_time, sizeof(elapsed_time), time_now, running_state_current.start_time)) {
		// now earlier than start time???!!
		text_layer_set_text(t_elapsed_time, "ERR!");
	} else
		text_layer_set_text(t_elapsed_time, elapsed_time);
  if (fmt_timediff_str(remaining_time, sizeof(remaining_time), time_now, running_state_current.target_time)) {
		// now earlier then target
		text_layer_set_text(t_remain_over, "Remain:");
	} else {
		text_layer_set_text(t_remain_over, "Over:");
	};
  text_layer_set_text(t_remaining_time, remaining_time);
}

// synchronize contents of the running window
void sync_w_running(void) {
  text_layer_set_text(t_what, (*running_state_what).name);
  // show state - start time / target time
  fmt_time_24h(start_time, sizeof(start_time), &(running_state_current.start_time));
  fmt_time_24h(target_time, sizeof(target_time), &(running_state_current.target_time));
  text_layer_set_text(t_start_time, start_time);
  text_layer_set_text(t_target_time, target_time);
  sync_time_lapse_remain();
};



// handle ticks - update running & remaining time
static void w_running_tick_handler(struct tm *tick_time, TimeUnits units_changed) {
	// if time-out, return to running window
	if ((window_stack_get_top_window() != s_window) && inactivity_timeout()) {
			APP_LOG(APP_LOG_LEVEL_INFO, "Inactive, return to window running...");
			while (window_stack_get_top_window() != s_window) 
				window_stack_pop(true);
			};
  sync_time_lapse_remain();
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

// down click handler - finish current what
static void what_finish_handler(ClickRecognizerRef recognizer, void *context) {
	reset_activity_timer();
	if (running_state_current.whats_running_idx == 0) { // nothing, no need to commit, just bring up selection window 
		show_w_selection();
	} else {
		// bring up confirmation window
		confirmation_ask("Log session?", &what_finish_handler_after_confirmation);
	};
}

// call communicator
static void call_communication_handler(ClickRecognizerRef recognizer, void *context) {
	reset_activity_timer();
  show_w_communication();
}

void what_discard_handler_after_confirmation(bool confirmed){
	if (confirmed) {
		running_state_kickoff(0);
	};
};

// down click handler - finish current what
static void what_discard_handler(ClickRecognizerRef recognizer, void *context) {
	reset_activity_timer();
	if (running_state_current.whats_running_idx != 0) { 
		confirmation_ask("Discard this?", &what_discard_handler_after_confirmation);
	};
}

// subscribe click events
void w_running_click_config_provider(void *context) {
  window_long_click_subscribe(BUTTON_ID_UP, 0, &what_discard_handler, NULL);	
  window_long_click_subscribe(BUTTON_ID_DOWN, 0, &what_finish_handler, NULL);
  window_single_click_subscribe(BUTTON_ID_SELECT, &call_communication_handler);
};

void running_vibe() {
	if (window_stack_get_top_window() == s_window) {
		vibes_long_pulse();
	};
} ;

// register handlers
static void my_init() {
	APP_LOG(APP_LOG_LEVEL_INFO,"w_running - my_init");
  // register tick handler
  tick_timer_service_subscribe(SECOND_UNIT, &w_running_tick_handler);
  // up click for time extension
  window_set_click_config_provider(s_window, &w_running_click_config_provider);
}
