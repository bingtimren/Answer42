#include <pebble.h>
#include "w_selection.h"
#include "what.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_14;
static TextLayer *t_07;
static TextLayer *t_08;
static TextLayer *t_12;
static TextLayer *t_11;
static ActionBarLayer *s_actionbarlayer_1;
static TextLayer *t_06;
static TextLayer *t_05;
static TextLayer *t_09;
static TextLayer *t_04;
static TextLayer *t_03;
static TextLayer *t_02;
static TextLayer *t_01;
static TextLayer *t_00;
static TextLayer *t_13;
static TextLayer *t_14;
static TextLayer *t_15;
static TextLayer *t_16;
static TextLayer *t_17;
static TextLayer *t_10;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, false);
  #endif
  
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  // t_07
  t_07 = text_layer_create(GRect(0, 120, 60, 16));
  text_layer_set_text(t_07, "08");
  text_layer_set_font(t_07, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_07);
  
  // t_08
  t_08 = text_layer_create(GRect(0, 136, 60, 16));
  text_layer_set_text(t_08, "09");
  text_layer_set_font(t_08, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_08);
  
  // t_12
  t_12 = text_layer_create(GRect(62, 52, 60, 16));
  text_layer_set_text(t_12, "13");
  text_layer_set_font(t_12, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_12);
  
  // t_11
  t_11 = text_layer_create(GRect(62, 32, 60, 16));
  text_layer_set_text(t_11, "12");
  text_layer_set_font(t_11, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_11);
  
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
  
  // t_06
  t_06 = text_layer_create(GRect(0, 104, 60, 16));
  text_layer_set_text(t_06, "07");
  text_layer_set_font(t_06, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_06);
  
  // t_05
  t_05 = text_layer_create(GRect(0, 84, 60, 16));
  text_layer_set_text(t_05, "06");
  text_layer_set_font(t_05, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_05);
  
  // t_09
  t_09 = text_layer_create(GRect(62, 0, 60, 16));
  text_layer_set_text(t_09, "10");
  text_layer_set_font(t_09, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_09);
  
  // t_04
  t_04 = text_layer_create(GRect(0, 68, 60, 16));
  text_layer_set_text(t_04, "05");
  text_layer_set_font(t_04, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_04);
  
  // t_03
  t_03 = text_layer_create(GRect(0, 52, 60, 16));
  text_layer_set_text(t_03, "04");
  text_layer_set_font(t_03, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_03);
  
  // t_02
  t_02 = text_layer_create(GRect(0, 32, 60, 16));
  text_layer_set_text(t_02, "03");
  text_layer_set_font(t_02, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_02);
  
  // t_01
  t_01 = text_layer_create(GRect(0, 16, 60, 16));
  text_layer_set_text(t_01, "01");
  text_layer_set_font(t_01, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_01);
  
  // t_00
  t_00 = text_layer_create(GRect(0, 0, 60, 16));
  text_layer_set_text(t_00, "00");
  text_layer_set_font(t_00, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_00);
  
  // t_13
  t_13 = text_layer_create(GRect(62, 68, 60, 16));
  text_layer_set_text(t_13, "14");
  text_layer_set_font(t_13, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_13);
  
  // t_14
  t_14 = text_layer_create(GRect(62, 84, 60, 16));
  text_layer_set_text(t_14, "15");
  text_layer_set_font(t_14, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_14);
  
  // t_15
  t_15 = text_layer_create(GRect(62, 104, 60, 16));
  text_layer_set_text(t_15, "16");
  text_layer_set_font(t_15, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_15);
  
  // t_16
  t_16 = text_layer_create(GRect(62, 120, 60, 16));
  text_layer_set_text(t_16, "17");
  text_layer_set_font(t_16, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_16);
  
  // t_17
  t_17 = text_layer_create(GRect(62, 136, 60, 16));
  text_layer_set_text(t_17, "18");
  text_layer_set_font(t_17, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_17);
  
  // t_10
  t_10 = text_layer_create(GRect(62, 16, 60, 16));
  text_layer_set_text(t_10, "11");
  text_layer_set_font(t_10, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_10);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(t_07);
  text_layer_destroy(t_08);
  text_layer_destroy(t_12);
  text_layer_destroy(t_11);
  action_bar_layer_destroy(s_actionbarlayer_1);
  text_layer_destroy(t_06);
  text_layer_destroy(t_05);
  text_layer_destroy(t_09);
  text_layer_destroy(t_04);
  text_layer_destroy(t_03);
  text_layer_destroy(t_02);
  text_layer_destroy(t_01);
  text_layer_destroy(t_00);
  text_layer_destroy(t_13);
  text_layer_destroy(t_14);
  text_layer_destroy(t_15);
  text_layer_destroy(t_16);
  text_layer_destroy(t_17);
  text_layer_destroy(t_10);
}
// END AUTO-GENERATED UI CODE

static TextLayer *tarray[18];

// record the current choice
typedef enum {
  INIT = 0,
  HALF_SET = 1,
  SECTION_SET = 2,
  LINE_SET = 3
} SelectionState;

// current selection state
SelectionState state;
uint8_t page;
uint8_t half;
uint8_t section;
uint8_t line;
uint8_t index_start;

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void s01_show_all_choices();

void show_w_selection(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  // initialize tarray
  tarray[0] = t_00;
  tarray[1] = t_01;
  tarray[2] = t_02;
  tarray[3] = t_03;
  tarray[4] = t_04;
  tarray[5] = t_05;
  tarray[6] = t_06;
  tarray[7] = t_07;
  tarray[8] = t_08;
  tarray[9] = t_09;
  tarray[10] = t_10;
  tarray[11] = t_11;
  tarray[12] = t_12;
  tarray[13] = t_13;
  tarray[14] = t_14;
  tarray[15] = t_15;
  tarray[16] = t_16;
  tarray[17] = t_17;
  // init
  page = 0;
  s01_show_all_choices(); 
}

void hide_w_selection(void) {
  window_stack_remove(s_window, true);
}


// the start point of what list that is visible for choosing
const uint8_t VISIBLE_START = 1; 
// initiate state & show all choices
// page start from 0; other parts of the code
// are responsible to keep page in valid range
void s01_show_all_choices() {
  // set status 
  state = INIT;
  index_start = 18 * page + VISIBLE_START;
  // iterate and set
  for (uint8_t i=0; i<18; i++) {
    if (index_start + i < WHAT_LIST_LENGTH) {
      text_layer_set_text(tarray[i], (*what_list[index_start + i]).short_name);
    } else {
      text_layer_set_text(tarray[i],"------");
    };
  }
}
