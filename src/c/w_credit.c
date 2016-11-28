#include <pebble.h>
#include "w_credit.h"
#include "debug.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_18;
static GFont s_res_gothic_14;
static TextLayer *s_textlayer_motto;
static TextLayer *s_textlayer_dtitle;
static TextLayer *s_textlayer_vtitle;
static TextLayer *s_textlayer_answer;
static TextLayer *s_textlayer_developer;
static TextLayer *s_textlayer_version;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, 0);
  #endif
  
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  // s_textlayer_motto
  s_textlayer_motto = text_layer_create(GRect(2, 34, 138, 44));
  text_layer_set_text(s_textlayer_motto, "Life, the Universe and Everything");
  text_layer_set_font(s_textlayer_motto, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_motto);
  
  // s_textlayer_dtitle
  s_textlayer_dtitle = text_layer_create(GRect(2, 83, 100, 20));
  text_layer_set_text(s_textlayer_dtitle, "Developer:");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_dtitle);
  
  // s_textlayer_vtitle
  s_textlayer_vtitle = text_layer_create(GRect(2, 125, 100, 20));
  text_layer_set_text(s_textlayer_vtitle, "Version:");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_vtitle);
  
  // s_textlayer_answer
  s_textlayer_answer = text_layer_create(GRect(2, 16, 79, 20));
  text_layer_set_text(s_textlayer_answer, "Answer 42");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_answer);
  
  // s_textlayer_developer
  s_textlayer_developer = text_layer_create(GRect(2, 103, 138, 20));
  text_layer_set_text(s_textlayer_developer, "Bing Ren");
  text_layer_set_text_alignment(s_textlayer_developer, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_developer, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_developer);
  
  // s_textlayer_version
  s_textlayer_version = text_layer_create(GRect(2, 145, 138, 20));
  text_layer_set_text(s_textlayer_version, "Text layer");
  text_layer_set_text_alignment(s_textlayer_version, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_version, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_version);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_motto);
  text_layer_destroy(s_textlayer_dtitle);
  text_layer_destroy(s_textlayer_vtitle);
  text_layer_destroy(s_textlayer_answer);
  text_layer_destroy(s_textlayer_developer);
  text_layer_destroy(s_textlayer_version);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void my_init(void) {
	text_layer_set_text(s_textlayer_version, VERSION_INFO);
};

void show_w_credit(void) {
  initialise_ui();
  my_init();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_w_credit(void) {
  window_stack_remove(s_window, true);
}


