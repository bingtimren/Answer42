#include <pebble.h>
#include "w_selection.h"
#include "what.h"
#include "running_state.h"
#include "wakeup.h"
#include "w_running.h"
#include "debug.h"
#include "format.h"
#include "w_localsummary.h"

static Window *s_window;
static MenuLayer *s_menu;

static void menuLayerSelectCallback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
	hide_w_selection();
	running_state_kickoff(cell_index -> row + 1);
};

static uint16_t menuLayerGetNumberOfSectionsCallback(struct MenuLayer *menu_layer, void *callback_context) {
	return 1;
};

static uint16_t menuLayerGetNumberOfRowsInSectionsCallback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
	return WHAT_LIST_LENGTH - 1;
};

static void menuLayerDrawRowCallback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
	menu_cell_title_draw(ctx, cell_layer, what_list[cell_index->row+1]-> name);
};

static int16_t menuLayerGetCellHeightCallback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
	return 30;
};

static void menuLayerSelectionWillChangeCallback(struct MenuLayer *menu_layer, MenuIndex *new_index, MenuIndex old_index, void *callback_context) {
	reset_activity_timer();
};


static void initialise_ui(void) {
	s_window = window_create();
	#ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
	#endif
	
	Layer *window_layer = window_get_root_layer(s_window);
	GRect bounds = layer_get_frame(window_layer);
  	s_menu = menu_layer_create(bounds);
  	MenuLayerCallbacks callbacks;
  	callbacks.get_num_sections = menuLayerGetNumberOfSectionsCallback; // default 1 if NULL
  	callbacks.get_num_rows = menuLayerGetNumberOfRowsInSectionsCallback; // must have
  	callbacks.get_cell_height = menuLayerGetCellHeightCallback; // default 44
  	callbacks.get_header_height = NULL; // default 0 and disable headers
  	callbacks.draw_row = menuLayerDrawRowCallback; // must have
  	callbacks.draw_header = NULL; // must have if header height not 0
  	callbacks.select_click = menuLayerSelectCallback; // ignored event by default
  	callbacks.select_long_click = NULL; // ignored
  	callbacks.selection_changed = NULL;
  	callbacks.get_separator_height = NULL; // 0 by default
  	callbacks.draw_separator = NULL; // must have if separator height is not 0
  	callbacks.selection_will_change = menuLayerSelectionWillChangeCallback; // before change, and can override change
  	callbacks.draw_background = NULL; // called before any cell, can be leave empty

  	menu_layer_set_callbacks(s_menu, NULL, callbacks); 
  	menu_layer_set_click_config_onto_window(s_menu, s_window);
  	layer_add_child(window_layer, menu_layer_get_layer(s_menu));
}

static void handle_window_unload(Window* window) {
  menu_layer_destroy(s_menu);
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

