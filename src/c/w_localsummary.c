#include <pebble.h>
#include "w_localsummary.h"
#include "format.h"
#include "what.h"
#include "data.h"
#include "wakeup.h"


static Window *s_window;
static MenuLayer *s_menu = NULL;
uint8_t history_head;
struct TimeRecordDayStore *dayStore;

/****************************************************************************************************
 *         Function section
 * **************************************************************************************************/


uint16_t localsummary_sum_whatid_total_durition(struct TimeRecordDayStore *dayStore, uint8_t what_index) {
	uint16_t total;
	total = 0;
	for (int i=0; i< dayStore -> length; i++) {
		struct TimeRecord *record = &(dayStore->day_records[i]);
		if (record -> what_index == what_index) {
			total = total + record -> durition;
		};
	};
	return total;
};

uint8_t localsummary_previous_slot(uint8_t current) {
	if (current == 0) 
		return DATA_SLOT_SIZE -1;
	return (current - 1);
};

bool localsummary_load_previous(uint8_t current) {
	// only load one - if it's empty then no more, because
	// normal usage will not create empty slot
	uint8_t prev = localsummary_previous_slot(current);
	if (prev == data_store_head) { // when there is no more
		return false;
	};
	return data_store_load_into_history(prev);
};
		
void get_brief_summary_from_whatid(uint8_t what_id, struct BriefSummary *result) {
	time_t today = starts_of_today();
	time_t yesterday = today - SECONDS_PER_DAY;
	struct TimeRecordDayStore *mightbe_yesterday;
	// check today
	if (today == data_today.day_start) { // there might be some records for today
		result -> today = localsummary_sum_whatid_total_durition(&data_today, what_id);
		localsummary_load_previous(data_store_head);
		mightbe_yesterday = &data_history;
	} else {
		result -> today = 0;
		mightbe_yesterday = &data_today;
	};
	// check yesterday
	if (yesterday == mightbe_yesterday -> day_start) {
		result -> yesterday = localsummary_sum_whatid_total_durition(mightbe_yesterday, what_id);
	} else {
		result -> yesterday = 0;
	};
};

/******************************************************************************************************************************
 *  Data prepare section
 ******************************************************************************************************************************/ 

// prepares data for summary section
static char todayStr[20];
static char todayRefStr[20];
static uint16_t total_100th_hours;
static uint8_t summary_what_idx[WHAT_LIST_LENGTH-1];
static uint16_t summary_what_durition[WHAT_LIST_LENGTH-1];
uint8_t summary_of_day_length;

// loads data for the list
static void loadsData(void) {
	if (history_head == data_store_head) {
		// current
		dayStore = &data_today;
		return;
	};
	// local history
	bool success = data_store_load_into_history(history_head);
	if (success) {
		dayStore = &data_history;
		return;
	};
	// return to current
	history_head = data_store_head;
	dayStore = &data_today;
};

static void prepareSummaryData(void) {
	// first, todayStr
	time_t today = dayStore -> day_start;
	time_t realToday = starts_of_today();
	int realToday_tm_wday = localtime(&realToday) -> tm_wday;
	struct tm *todayLocal = localtime(&today);	
	strftime(todayStr, sizeof(todayStr), FORMAT_CURRENT_DATE, todayLocal);

	// second todayRef
	if (today == realToday) {
		strcpy(todayRefStr,"Today");
	} else if ((today + SECONDS_PER_DAY) == realToday) {
		strcpy(todayRefStr,"Yesterday");
	} else {
			
		uint16_t daysBefore = (realToday - today)/SECONDS_PER_DAY;
		// "this Monday", "last Monday", or "45 DB"
		if ((daysBefore < 7) && (realToday_tm_wday > todayLocal -> tm_wday)) {
			// "this Monday"
			strftime(todayRefStr, sizeof(todayRefStr), "This %a", todayLocal);
		} else if ( (daysBefore - realToday_tm_wday) <= 7){
			strftime(todayRefStr, sizeof(todayRefStr), "Last %a", todayLocal);
		} else {
			snprintf(todayRefStr, sizeof(todayRefStr), "%d Days Before", daysBefore);
		}
	};
	
	// total & each
	total_100th_hours = 0;
	summary_of_day_length = 0;
	for (int i=1; i< WHAT_LIST_LENGTH; i++ ){
		uint16_t dur = localsummary_sum_whatid_total_durition(dayStore, i);
		if (dur > 0) {
			total_100th_hours = total_100th_hours + dur;
			summary_what_idx[summary_of_day_length] = i;
			summary_what_durition[summary_of_day_length] = dur;
			summary_of_day_length = summary_of_day_length + 1;
		};
	};
};

// prepares data for the list
static void prepareData(void) {
	loadsData();
	prepareSummaryData();
};


	
/**************************************************************************************************************
 * Call back section
 * ************************************************************************************************************/

char buffer[20];

static void menuLayerSelectCallback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
	// rotate to previous day and reload
	history_head = localsummary_previous_slot(history_head);
	prepareData(); // if load not successful will auto rotate
	menu_layer_reload_data(s_menu);
	menu_layer_set_selected_index(s_menu, (struct MenuIndex){0,0}, MenuRowAlignBottom, true);
};

static uint16_t menuLayerGetNumberOfSectionsCallback(struct MenuLayer *menu_layer, void *callback_context) {
	return 4; 
	/* two sections but some fake ones to render header
	 *  0: ****************
	 * 	   Date / Today
	 * 	   Total / xxx
	 * 	   Each item / xxx
	 *  1: ****************
	 *  2:  Section records title
	 *  3: ****************
	 * 		Records
	 * */
	
};

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  // Determine which section we're working with
  switch (section_index) {
    case 0:
    case 1:
    case 3:
      // Draw title text in the section header
      menu_cell_basic_header_draw(ctx, cell_layer, "=================");
      return;
    case 2:
      menu_cell_basic_header_draw(ctx, cell_layer, "     * Time Records *");
      return;
  }
}

static uint16_t menuLayerGetNumberOfRowsInSectionsCallback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
  switch (section_index) {
    case 0: // summary
      return 2 + summary_of_day_length;
    case 3: // records
      return dayStore -> length;
    default:
      return 0;
	}
};

static void menuLayerDrawRowCallback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
  // Determine which section we're going to draw in
  if (cell_index->section == 0) {
      // summary
      if (cell_index -> row == 0) {// today ref
		  menu_cell_basic_draw(ctx, cell_layer, todayStr, todayRefStr, NULL);
		  return;
	  };
	  if (cell_index -> row == 1) {// total
		  snprintf(buffer, sizeof(buffer), "TTL %u.%02u h", total_100th_hours/100, total_100th_hours%100);
		  menu_cell_basic_draw(ctx, cell_layer, "[Everything]", buffer, NULL);
		  return;
	  };
	  // summary of each what
	  uint8_t idx = summary_what_idx[cell_index -> row - 2];
	  uint16_t dur = summary_what_durition[cell_index -> row - 2];
	  snprintf(buffer, sizeof(buffer), "TTL %u.%02u h", dur/100, dur%100);
	  menu_cell_basic_draw(ctx, cell_layer, what_list[idx]-> name,buffer,NULL);
	  return;
  };
  if (cell_index->section == 3) {
  	  TimeRecord *rec;
	  rec = &(dayStore -> day_records[cell_index -> row]);
	  snprintf(buffer, sizeof(buffer), "%02u:%02u %u.%02uh", rec->time/60,rec->time%60, rec->durition/100, rec->durition%100); 
	  menu_cell_basic_draw(ctx, cell_layer, what_list[rec->what_index]->name,buffer,NULL);
  };
};

static int16_t menuLayerGetCellHeightCallback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
	return 44; // default
};

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return MENU_CELL_BASIC_HEADER_HEIGHT; // header height
}

static void menuLayerSelectionWillChangeCallback(struct MenuLayer *menu_layer, MenuIndex *new_index, MenuIndex old_index, void *callback_context) {
	reset_activity_timer();
};

/**************************************************************************************************************
 * UI Section
 * ************************************************************************************************************/


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
  	callbacks.get_header_height = menu_get_header_height_callback; // default 0 and disable headers
  	callbacks.draw_row = menuLayerDrawRowCallback; // must have
  	callbacks.draw_header = menu_draw_header_callback; // must have if header height not 0
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

void show_w_localsummary(void) {
  APP_LOG(APP_LOG_LEVEL_INFO,"show w_localsummary");	
  history_head = data_store_head;
  prepareData();
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });  
  window_stack_push(s_window, true);
}

void hide_w_localsummary(void) {
  window_stack_remove(s_window, true);
}



