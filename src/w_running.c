#include <pebble.h>
#include "debug.h"
#include "w_running.h"
#include "data.h"
#include "running_state.h"
#include "what.h"
#include "format.h"
#include "wakeup.h"  

static char start_time[FORMAT_24HTIME_BUFFER_LENGTH];
static char target_time[FORMAT_24HTIME_BUFFER_LENGTH];  
static char elapsed_time[50];
static char remaining_time[50];  

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_action_plus;
static GBitmap *s_res_image_action_stop;
static GFont s_res_gothic_18_bold;
static GFont s_res_gothic_14;
static ActionBarLayer *s_actionbarlayer_1;
static TextLayer *t_what;
static BitmapLayer *b_progress;
static TextLayer *t_start_time;
static TextLayer *t_target_time;
static TextLayer *t_elapsed_time;
static TextLayer *t_remaining_time;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, false);
  #endif
  
  s_res_image_action_plus = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_PLUS);
  s_res_image_action_stop = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_STOP);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorBlack);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_image_action_plus);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_image_action_stop);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
  
  // t_what
  t_what = text_layer_create(GRect(1, 0, 117, 21));
  text_layer_set_text(t_what, "What going on");
  text_layer_set_text_alignment(t_what, GTextAlignmentCenter);
  text_layer_set_font(t_what, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_what);
  
  // b_progress
  b_progress = bitmap_layer_create(GRect(3, 20, 117, 7));
  layer_add_child(window_get_root_layer(s_window), (Layer *)b_progress);
  
  // t_start_time
  t_start_time = text_layer_create(GRect(12, 41, 100, 20));
  text_layer_set_background_color(t_start_time, GColorBlack);
  text_layer_set_text_color(t_start_time, GColorWhite);
  text_layer_set_text(t_start_time, "Run 00h : 00m");
  text_layer_set_text_alignment(t_start_time, GTextAlignmentCenter);
  text_layer_set_font(t_start_time, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_start_time);
  
  // t_target_time
  t_target_time = text_layer_create(GRect(12, 65, 100, 20));
  text_layer_set_text(t_target_time, "Target 00h : 00m");
  text_layer_set_text_alignment(t_target_time, GTextAlignmentCenter);
  text_layer_set_font(t_target_time, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_target_time);
  
  // t_elapsed_time
  t_elapsed_time = text_layer_create(GRect(14, 83, 100, 20));
  text_layer_set_text(t_elapsed_time, "Text layer");
  text_layer_set_font(t_elapsed_time, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_elapsed_time);
  
  // t_remaining_time
  t_remaining_time = text_layer_create(GRect(13, 102, 100, 20));
  text_layer_set_text(t_remaining_time, "Text layer");
  text_layer_set_font(t_remaining_time, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_remaining_time);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  action_bar_layer_destroy(s_actionbarlayer_1);
  text_layer_destroy(t_what);
  bitmap_layer_destroy(b_progress);
  text_layer_destroy(t_start_time);
  text_layer_destroy(t_target_time);
  text_layer_destroy(t_elapsed_time);
  text_layer_destroy(t_remaining_time);
  gbitmap_destroy(s_res_image_action_plus);
  gbitmap_destroy(s_res_image_action_stop);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static void register_handlers(); // stub, definition at end

void show_w_running(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  register_handlers();
}



void hide_w_running(void) {
  window_stack_remove(s_window, true);
}

// display lapse and remain
void sync_lapse_remain(void) {
  time_t now = time(NULL);
  fmt_timediff_str(elapsed_time, sizeof(elapsed_time), now, running_state_current.start_time, " ERR!", NULL);
  fmt_timediff_str(remaining_time, sizeof(remaining_time), now, running_state_current.target_time, " [R]", " [OverR]");
  text_layer_set_text(t_elapsed_time, elapsed_time);
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
  sync_lapse_remain();
};

// handle ticks - update running & remaining time
static void w_running_tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  sync_lapse_remain();
};

// up click handler - increase time
static void time_extension_handler(ClickRecognizerRef recognizer, void *context) {
  running_state_current.target_time = time(NULL) + ((*running_state_what).manual_extension_length);
  running_state_current.stage_idx = 0;
  running_state_save();
  sync_w_running();
}

#ifdef DEBUG_CLEAR_RUNNING_STATE
// long click up button to quit and clear running state, for debug purpose
static void clear_running_state_handler(ClickRecognizerRef recognizer, void *context) {
  running_state_clear();
  window_stack_pop(true);
};
#endif


// subscribe click events
void w_running_click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, *time_extension_handler);
  #ifdef DEBUG_CLEAR_RUNNING_STATE
    window_long_click_subscribe(BUTTON_ID_UP, 3000, NULL, clear_running_state_handler);
  #endif
};

static void register_handlers() {
  // register tick handler
  tick_timer_service_subscribe(SECOND_UNIT, &w_running_tick_handler);
  // up click for time extension
  window_set_click_config_provider(s_window, *w_running_click_config_provider);
  // wakeup handler
  wakeup_init();
}