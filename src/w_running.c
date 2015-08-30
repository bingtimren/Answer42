#include <pebble.h>
#include "w_running.h"
#include "data.h"
#include "running_state.h"
#include "what.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_action_plus;
static GBitmap *s_res_image_action_stop;
static GFont s_res_gothic_18_bold;
static GFont s_res_gothic_14;
static ActionBarLayer *s_actionbarlayer_1;
static TextLayer *t_what;
static BitmapLayer *b_progress;
static TextLayer *t_rtime;
static TextLayer *t_target;

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
  
  // t_rtime
  t_rtime = text_layer_create(GRect(12, 41, 100, 20));
  text_layer_set_background_color(t_rtime, GColorBlack);
  text_layer_set_text_color(t_rtime, GColorWhite);
  text_layer_set_text(t_rtime, "Run 00h : 00m");
  text_layer_set_text_alignment(t_rtime, GTextAlignmentCenter);
  text_layer_set_font(t_rtime, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_rtime);
  
  // t_target
  t_target = text_layer_create(GRect(12, 65, 100, 20));
  text_layer_set_text(t_target, "Target 00h : 00m");
  text_layer_set_text_alignment(t_target, GTextAlignmentCenter);
  text_layer_set_font(t_target, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_target);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  action_bar_layer_destroy(s_actionbarlayer_1);
  text_layer_destroy(t_what);
  bitmap_layer_destroy(b_progress);
  text_layer_destroy(t_rtime);
  text_layer_destroy(t_target);
  gbitmap_destroy(s_res_image_action_plus);
  gbitmap_destroy(s_res_image_action_stop);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_w_running(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_w_running(void) {
  window_stack_remove(s_window, true);
}

// synchronize contents of the running window
void sync_w_running(void) {
  const struct WhatType* current_running_what_ptr = running_state_what();
  // show state - name
  text_layer_set_text(t_what, (*current_running_what_ptr).name);
  // show state - start time
  
}
