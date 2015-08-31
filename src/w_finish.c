#include <pebble.h>
#include "debug.h"
#include "w_finish.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_action_focus;
static GBitmap *s_res_image_action_switch;
static GBitmap *s_res_image_action_feel;
static TextLayer *t_whatfinished;
static TextLayer *t_running_time;
static TextLayer *s_concentration_splitmuch;
static TextLayer *s_feel_splitwhat;
static ActionBarLayer *s_actionbarlayer_1;
static TextLayer *s_mode;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, false);
  #endif
  
  s_res_image_action_focus = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_FOCUS);
  s_res_image_action_switch = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_SWITCH);
  s_res_image_action_feel = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_FEEL);
  // t_whatfinished
  t_whatfinished = text_layer_create(GRect(9, 4, 100, 20));
  text_layer_set_text(t_whatfinished, "What's Finished");
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_whatfinished);
  
  // t_running_time
  t_running_time = text_layer_create(GRect(12, 25, 100, 20));
  text_layer_set_text(t_running_time, "Running Time");
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_running_time);
  
  // s_concentration_splitmuch
  s_concentration_splitmuch = text_layer_create(GRect(5, 108, 122, 20));
  text_layer_set_text(s_concentration_splitmuch, "Concentration Split");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_concentration_splitmuch);
  
  // s_feel_splitwhat
  s_feel_splitwhat = text_layer_create(GRect(5, 125, 100, 20));
  text_layer_set_text(s_feel_splitwhat, "Feel Split What");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_feel_splitwhat);
  
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorBlack);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_image_action_focus);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_image_action_switch);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_image_action_feel);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
  
  // s_mode
  s_mode = text_layer_create(GRect(6, 86, 100, 20));
  text_layer_set_text(s_mode, "Concentr. & Feel");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_mode);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(t_whatfinished);
  text_layer_destroy(t_running_time);
  text_layer_destroy(s_concentration_splitmuch);
  text_layer_destroy(s_feel_splitwhat);
  action_bar_layer_destroy(s_actionbarlayer_1);
  text_layer_destroy(s_mode);
  gbitmap_destroy(s_res_image_action_focus);
  gbitmap_destroy(s_res_image_action_switch);
  gbitmap_destroy(s_res_image_action_feel);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_w_finish(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_w_finish(void) {
  window_stack_remove(s_window, true);
}
