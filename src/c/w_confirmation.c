#include <pebble.h>
#include "w_confirmation.h"
#include "debug.h"
#include "wakeup.h"

ConfirmationReceived received_callback;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_action_yes;
static GBitmap *s_res_image_action_no;
static GFont s_res_gothic_18;
static ActionBarLayer *s_actionbarlayer_1;
static TextLayer *s_textlayer_1;
static TextLayer *t_version;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_image_action_yes = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_YES);
  s_res_image_action_no = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_NO);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorBlack);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_image_action_yes);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_image_action_no);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(0, 67, 112, 20));
  text_layer_set_text(s_textlayer_1, " ");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // t_version
  t_version = text_layer_create(GRect(0, 105, 112, 22));
  text_layer_set_font(t_version, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_version);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  action_bar_layer_destroy(s_actionbarlayer_1);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(t_version);
  gbitmap_destroy(s_res_image_action_yes);
  gbitmap_destroy(s_res_image_action_no);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void confirmation_ask(const char* prompt, ConfirmationReceived callback) {
	received_callback = callback;
	show_w_confirmation();
	text_layer_set_text(s_textlayer_1, prompt);
}

void hide_w_confirmation(void) {
  window_stack_remove(s_window, false);
}

static void debug_handler(ClickRecognizerRef recognizer, void *context) {
	text_layer_set_text(t_version, "Ver: "VERSION_INFO);
}

static void yes_handler(ClickRecognizerRef recognizer, void *context) {
	reset_activity_timer();
	hide_w_confirmation();
  received_callback(true);
}

static void no_handler(ClickRecognizerRef recognizer, void *context) {
	reset_activity_timer();
	hide_w_confirmation();
  received_callback(false);
}

// subscribe click events
void w_confirmation_click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, *yes_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT,0,*debug_handler,NULL);
  window_single_click_subscribe(BUTTON_ID_DOWN, *no_handler);
};

void show_w_confirmation(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  window_set_click_config_provider(s_window, *w_confirmation_click_config_provider);
}



