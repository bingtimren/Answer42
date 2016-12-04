/*#include <pebble.h>
#include "w_selection.h"
#include "what.h"
#include "running_state.h"
#include "wakeup.h"
#include "w_running.h"
#include "debug.h"
#include "format.h"
#include "localsummary.h"

static Window *s_window;
static SimpleMenuLayer *s_simple_menu;

static SimpleMenuSection s_menu_section;
static SimpleMenuItem s_menu_items[WHAT_LIST_LENGTH-1];
#define SUB_TITLE_LENGTH 20
static char subtitles[WHAT_LIST_LENGTH-1][SUB_TITLE_LENGTH];

static void menu_select_callback(int index, void *ctx) {
	running_state_kickoff(index+1);
	hide_w_selection(); 	
}

static void build_menu_section() {
	for (uint8_t i=1; i<WHAT_LIST_LENGTH; i++) { // note i starts from 1, mind array boundary!
	
		struct LocalSummaryType *lsum;
		lsum = get_local_summary_by_what_index(i);
		uint8_t tl = 0;
		if (lsum -> one_100_hours_today > 0) {
			tl = snprintf(&subtitles[i-1][0], SUB_TITLE_LENGTH, "Td %u.%02uh ", (lsum -> one_100_hours_today)/100, (lsum -> one_100_hours_today)%100);		
		};
		if ((lsum -> one_100_hours_yesterday > 0) && (tl < SUB_TITLE_LENGTH)) {
			snprintf(&subtitles[i-1][0]+tl, SUB_TITLE_LENGTH-tl, "Ystd %u.%02uh ", (lsum -> one_100_hours_yesterday)/100, (lsum -> one_100_hours_yesterday)%100);		
		};
		s_menu_items[i-1] = (SimpleMenuItem) {
			.title = what_list[i] -> name,
			.subtitle = &subtitles[i-1][0],
			.callback = menu_select_callback
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
    window_set_fullscreen(s_window, true);
	#endif
	
	Layer *window_layer = window_get_root_layer(s_window);
	GRect bounds = layer_get_frame(window_layer);  
  	s_simple_menu = simple_menu_layer_create(bounds, s_window, &s_menu_section, 1, NULL);
  	layer_add_child(window_layer, simple_menu_layer_get_layer(s_simple_menu));
}

static void handle_window_unload(Window* window) {
  window_destroy(s_window);
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

*/
#include <pebble.h>
#include "w_selection.h"
#include "running_state.h"

static int state = 0;

void show_w_selection(void) {
	if (state == 0) {
		running_state_kickoff(1);
		state = 1;
	} else {
		running_state_commit();
		state = 0;
	};
}

void hide_w_selection(void) {
  
}
