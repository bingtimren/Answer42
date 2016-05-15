#include <pebble.h>
#include "w_selection.h"
#include "what.h"
#include "running_state.h"
#include "wakeup.h"
#include "w_running.h"
#include "debug.h"

static GBitmap *s_res_image_action_yes;
static GBitmap *s_res_image_action_no;
static GBitmap *s_res_image_action_left;
static GBitmap *s_res_image_action_right;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_14;
static GFont s_res_gothic_18;
static GFont s_res_gothic_18_bold;
static GBitmap *s_res_image_action_up;
static GBitmap *s_res_image_action_mid;
static GBitmap *s_res_image_action_down;
static TextLayer *t_07;
static TextLayer *t_08;
static TextLayer *t_11;
static TextLayer *t_06;
static TextLayer *t_05;
static TextLayer *t_09;
static TextLayer *t_04;
static TextLayer *t_03;
static TextLayer *t_02;
static TextLayer *t_01;
static TextLayer *t_00;
static TextLayer *t_10;
static TextLayer *t_prompt_1;
static TextLayer *t_prompt_2;
static TextLayer *t_choice_confirmation;
static ActionBarLayer *s_actionbarlayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, 0);
  #endif
  
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_image_action_up = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_UP);
  s_res_image_action_mid = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_MID);
  s_res_image_action_down = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_DOWN);
  // t_07
  t_07 = text_layer_create(GRect(58, 76, 56, 16));
  text_layer_set_background_color(t_07, GColorBlack);
  text_layer_set_text_color(t_07, GColorWhite);
  text_layer_set_text(t_07, " 07");
  text_layer_set_font(t_07, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_07);
  
  // t_08
  t_08 = text_layer_create(GRect(0, 110, 56, 16));
  text_layer_set_text(t_08, " 08");
  text_layer_set_font(t_08, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_08);
  
  // t_11
  t_11 = text_layer_create(GRect(58, 126, 56, 16));
  text_layer_set_text(t_11, "11 ");
  text_layer_set_font(t_11, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_11);
  
  // t_06
  t_06 = text_layer_create(GRect(0, 76, 56, 16));
  text_layer_set_background_color(t_06, GColorBlack);
  text_layer_set_text_color(t_06, GColorWhite);
  text_layer_set_text(t_06, " 06");
  text_layer_set_font(t_06, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_06);
  
  // t_05
  t_05 = text_layer_create(GRect(58, 60, 56, 16));
  text_layer_set_background_color(t_05, GColorBlack);
  text_layer_set_text_color(t_05, GColorWhite);
  text_layer_set_text(t_05, " 05");
  text_layer_set_font(t_05, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_05);
  
  // t_09
  t_09 = text_layer_create(GRect(58, 110, 56, 16));
  text_layer_set_text(t_09, "09 ");
  text_layer_set_font(t_09, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_09);
  
  // t_04
  t_04 = text_layer_create(GRect(0, 60, 56, 16));
  text_layer_set_background_color(t_04, GColorBlack);
  text_layer_set_text_color(t_04, GColorWhite);
  text_layer_set_text(t_04, " 04");
  text_layer_set_font(t_04, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_04);
  
  // t_03
  t_03 = text_layer_create(GRect(58, 26, 56, 16));
  text_layer_set_text(t_03, "03 ");
  text_layer_set_font(t_03, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_03);
  
  // t_02
  t_02 = text_layer_create(GRect(0, 26, 56, 16));
  text_layer_set_text(t_02, " 02");
  text_layer_set_font(t_02, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_02);
  
  // t_01
  t_01 = text_layer_create(GRect(58, 10, 56, 16));
  text_layer_set_text(t_01, "01");
  text_layer_set_font(t_01, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_01);
  
  // t_00
  t_00 = text_layer_create(GRect(0, 10, 56, 16));
  text_layer_set_text(t_00, " 00");
  text_layer_set_font(t_00, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_00);
  
  // t_10
  t_10 = text_layer_create(GRect(0, 126, 56, 16));
  text_layer_set_text(t_10, " 10");
  text_layer_set_font(t_10, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_10);
  
  // t_prompt_1
  t_prompt_1 = text_layer_create(GRect(1, 17, 122, 19));
  text_layer_set_background_color(t_prompt_1, GColorClear);
  text_layer_set_text(t_prompt_1, " ");
  text_layer_set_font(t_prompt_1, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_prompt_1);
  
  // t_prompt_2
  t_prompt_2 = text_layer_create(GRect(1, 31, 122, 21));
  text_layer_set_background_color(t_prompt_2, GColorClear);
  text_layer_set_text(t_prompt_2, " ");
  text_layer_set_font(t_prompt_2, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_prompt_2);
  
  // t_choice_confirmation
  t_choice_confirmation = text_layer_create(GRect(0, 61, 124, 70));
  text_layer_set_background_color(t_choice_confirmation, GColorClear);
  text_layer_set_text(t_choice_confirmation, " ");
  text_layer_set_font(t_choice_confirmation, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_choice_confirmation);
  
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorBlack);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_image_action_up);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_image_action_mid);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_image_action_down);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(t_07);
  text_layer_destroy(t_08);
  text_layer_destroy(t_11);
  text_layer_destroy(t_06);
  text_layer_destroy(t_05);
  text_layer_destroy(t_09);
  text_layer_destroy(t_04);
  text_layer_destroy(t_03);
  text_layer_destroy(t_02);
  text_layer_destroy(t_01);
  text_layer_destroy(t_00);
  text_layer_destroy(t_10);
  text_layer_destroy(t_prompt_1);
  text_layer_destroy(t_prompt_2);
  text_layer_destroy(t_choice_confirmation);
  action_bar_layer_destroy(s_actionbarlayer_1);
  gbitmap_destroy(s_res_image_action_up);
  gbitmap_destroy(s_res_image_action_mid);
  gbitmap_destroy(s_res_image_action_down);
}
// END AUTO-GENERATED UI CODE

static TextLayer *tarray[12];

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
uint8_t line_starts;
uint8_t section_starts;
uint8_t choice;
uint8_t index_start;

static void handle_window_unload(Window* window) {
  destroy_ui();
  // additional destroy of resources
  gbitmap_destroy(s_res_image_action_left);
  gbitmap_destroy(s_res_image_action_right);
  gbitmap_destroy(s_res_image_action_yes);
  gbitmap_destroy(s_res_image_action_no);
}

static void show_all_choices();
static void my_init();
static void my_reset();

void show_w_selection(void) {
  APP_LOG(APP_LOG_LEVEL_INFO," #### showing window SELECTION");
  initialise_ui();
  // load addition action icons
  s_res_image_action_left = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_LEFT);
  s_res_image_action_right = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_RIGHT);
  s_res_image_action_yes = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_YES);
  s_res_image_action_no = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_NO);

  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  my_init();
}

void hide_w_selection(void) {
  window_stack_remove(s_window, true);
}


// the start point of what list that is visible for choosing
const uint8_t VISIBLE_START = 1; 
// initiate state & show all choices
// page start from 0; other parts of the code
// are responsible to keep page in valid range
static void show_all_choices() {
  index_start = 12 * page + VISIBLE_START;
  // iterate and set
  for (uint8_t i=0; i<12; i++) {
    if (index_start + i < WHAT_LIST_LENGTH) {
      text_layer_set_text(tarray[i], (*what_list[index_start + i]).short_name);
    } else {
      text_layer_set_text(tarray[i],"");
    };
    if (i < 4 || i>=8) {
			text_layer_set_background_color(tarray[i], GColorClear);
			text_layer_set_text_color(tarray[i], GColorBlack);
		} else {
			text_layer_set_background_color(tarray[i], GColorBlack);
			text_layer_set_text_color(tarray[i], GColorWhite);
		};    
  }
}


static void hide_prompt_choice() {
  text_layer_set_text(t_prompt_1,"");
  text_layer_set_text(t_prompt_2,"");
  text_layer_set_text(t_choice_confirmation,"");
}

static void show_prompt_choice() {
  text_layer_set_text(t_prompt_1,"Confirm your");
  text_layer_set_text(t_prompt_2,"Next Activity: ");
  text_layer_set_text(t_choice_confirmation, (*what_list[choice]).name);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_image_action_yes);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, NULL);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_image_action_no);    
}



/*
// turn pages
static void turnpage() {
  if (12*page+VISIBLE_START+12 >= WHAT_LIST_LENGTH) {
    page = 0;
  } else {
    page += 1;
  }
  show_all_choices();
};
*/

// hide from start to end but keep from keep_start to keep_end
static void hide_other_whats(uint8_t start, uint8_t end, uint8_t keep_start, uint8_t keep_end, uint8_t inverse_start, int8_t inverse_end) {
  for (uint8_t i=start; i<end; i++ ) {
    if (i<keep_start || i>= keep_end) {
      text_layer_set_text(tarray[i],"");
    }
    if (i < inverse_start || i >= inverse_end) {
			text_layer_set_background_color(tarray[i], GColorClear);
			text_layer_set_text_color(tarray[i], GColorBlack);
		} else {
			text_layer_set_background_color(tarray[i], GColorBlack);
			text_layer_set_text_color(tarray[i], GColorWhite);
		};			
  }
}

// select half 0 or 1, bold display selection and ask for confirmation
static void select_half(uint8_t h) {
  choice = h + index_start + line_starts;
  if (choice >= WHAT_LIST_LENGTH) {
    // invalid choice, empty section, state not set
    return;
  }
  state = HALF_SET;
  // hide all items
  for (uint8_t i = line_starts; i < line_starts+2; i++) {
    text_layer_set_text(tarray[i],"");
  };
	text_layer_set_background_color(tarray[line_starts+1], GColorClear);
  
  // display prompt & choice
  show_prompt_choice();
}

// select section 0,1,2
static void select_section(uint8_t s) {
  section_starts = 4*s;
  if (index_start + section_starts >= WHAT_LIST_LENGTH) {
    // invalid choice, empty half, state not set
    return;
  }
  state = SECTION_SET;
  hide_other_whats(0,12,section_starts,section_starts+4,section_starts+2,section_starts+4);
  // set action icon to up/mid/down
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_image_action_up);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, NULL);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_image_action_down);    
}

// select line 0,1; 
static void select_line(uint8_t l) {
  line_starts = section_starts + 2*l;
  if (index_start + line_starts >= WHAT_LIST_LENGTH) {
    // invalid choice, empty half, state not set
    return;
  }
  state = LINE_SET;
  hide_other_whats(0,12,line_starts,line_starts+2,line_starts+1,line_starts+2);
  // set action icon to up/mid/down
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_image_action_left);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, NULL);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_image_action_right);  
}


// up button
static void up_button_handler(ClickRecognizerRef recognizer, void *context) {
  reset_activity_timer();
  // set selection time out - remove previous one if needed
  switch (state) {
    case INIT: select_section(0); break;
    case SECTION_SET: select_line(0); break;
    case LINE_SET: select_half(0); break;
    case HALF_SET: 
		running_state_kickoff(choice);
		hide_w_selection(); 
		break;
  }
};


// middle button
static void middle_button_handler(ClickRecognizerRef recognizer, void *context) {
  reset_activity_timer();
  switch (state) {
    case INIT: select_section(1); break;
    case SECTION_SET: break;
    case LINE_SET: break;
    case HALF_SET: break;
  }
};

// down button
static void down_button_handler(ClickRecognizerRef recognizer, void *context) {
  reset_activity_timer();
  switch (state) {
    case INIT: select_section(2); break;
    case SECTION_SET: select_line(1); break;
    case LINE_SET: select_half(1); break;
    case HALF_SET: my_reset(); break;
  }
};

static void back_button_handler(ClickRecognizerRef recognizer, void *context) {
  reset_activity_timer();
  if (state == INIT && page == 0) 
		hide_w_selection();
	else
		my_reset(); // reset
};

// subscribe click events
void w_selection_click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, *up_button_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, *middle_button_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, *down_button_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, *back_button_handler);  
};

// register handlers
static void register_tarray();

static void my_reset() {
  page = 0;
  hide_prompt_choice();
    // set status 
  state = INIT;
  // reset action bar
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_image_action_up);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_image_action_mid);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_image_action_down);  
  show_all_choices(); 
}

static void my_init() {
  register_tarray();
  // click handlers
  window_set_click_config_provider(s_window, *w_selection_click_config_provider);
  my_reset();
}

static void register_tarray() {
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
}
