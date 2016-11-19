#include <pebble.h>
#include "w_selection.h"
#include "what.h"
#include "running_state.h"
#include "wakeup.h"
#include "w_running.h"
#include "debug.h"
#include "format.h"

static Window *s_window;
static SimpleMenuLayer *s_simple_menu;
static SimpleMenuSection s_menu_section;
static SimpleMenuItem s_menu_items[WHAT_LIST_LENGTH-1];
#define SUB_TITLE_LENGTH 20
static char subtitles[WHAT_LIST_LENGTH-1][SUB_TITLE_LENGTH];

static void menu_select_callback(int index, void *ctx) {
  s_menu_items[index].subtitle = "Hit here!";
  layer_mark_dirty(simple_menu_layer_get_layer(s_simple_menu));
}

static void build_menu_section() {
	for (uint8_t i=1; i<WHAT_LIST_LENGTH; i++) { // note i starts from 1, mind array boundary!
		fmt_minutes_to_hour_minutes(&subtitles[i-1][0], SUB_TITLE_LENGTH, 3*60*24);		
		s_menu_items[i-1] = (SimpleMenuItem) {
			.title = what_list[i] -> name,
			.subtitle = &subtitles[i-1][0],
			.callback = menu_select_callback,
		};
	};
	s_menu_section = (SimpleMenuSection) {
		.num_items = WHAT_LIST_LENGTH -1,
		.items = s_menu_items,
	};
};

static void initialise_ui(void) {
	build_menu_section();
	s_window = window_create();
	#ifndef PBL_SDK_3
    window_set_fullscreen(s_window, 0);
	#endif
	Layer *window_layer = window_get_root_layer(s_window);
	GRect bounds = layer_get_frame(window_layer);  
  	s_simple_menu = simple_menu_layer_create(bounds, s_window, &s_menu_section, 1, NULL);
  	layer_add_child(window_layer, simple_menu_layer_get_layer(s_simple_menu));
}

static void destroy_ui(void) {
  window_destroy(s_window);

}

static void handle_window_unload(Window* window) {
  destroy_ui();
}



void show_w_selection(void) {
  APP_LOG(APP_LOG_LEVEL_INFO,"show_w_selection");	
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });  
  window_stack_push(s_window, true);
}

void hide_w_selection(void) {
  window_stack_remove(s_window, true);
}


