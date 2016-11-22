#include <pebble.h>
#include "w_credit.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_42;
static GFont s_res_gothic_18;
static BitmapLayer *s_bitmaplayer_1;
static TextLayer *s_textlayer_motto;
static TextLayer *s_textlayer_2;
static TextLayer *s_textlayer_3;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_4;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_image_42 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_42);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  // s_bitmaplayer_1
  s_bitmaplayer_1 = bitmap_layer_create(GRect(109, 7, 31, 28));
  bitmap_layer_set_bitmap(s_bitmaplayer_1, s_res_image_42);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_1);
  
  // s_textlayer_motto
  s_textlayer_motto = text_layer_create(GRect(8, 31, 129, 44));
  text_layer_set_text(s_textlayer_motto, "Life, the Universe and Everything");
  text_layer_set_font(s_textlayer_motto, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_motto);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(8, 93, 100, 20));
  text_layer_set_text(s_textlayer_2, "Developer: Bing Ren");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
  
  // s_textlayer_3
  s_textlayer_3 = text_layer_create(GRect(8, 107, 100, 20));
  text_layer_set_text(s_textlayer_3, "Version:");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_3);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(8, 123, 100, 20));
  text_layer_set_text(s_textlayer_1, "Built: ");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_4
  s_textlayer_4 = text_layer_create(GRect(68, 15, 40, 20));
  text_layer_set_text(s_textlayer_4, "Answer");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_4);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_1);
  text_layer_destroy(s_textlayer_motto);
  text_layer_destroy(s_textlayer_2);
  text_layer_destroy(s_textlayer_3);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_4);
  gbitmap_destroy(s_res_image_42);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_w_credit(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_w_credit(void) {
  window_stack_remove(s_window, true);
}
