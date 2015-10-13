#include <pebble.h>
#include "w_communication.h"
#include "data.h"
#include "what.h"
#include "running_state.h"
#include "wakeup.h"
#include "debug.h"
#include "w_confirmation.h"

  // text buffers
static time_t time_now;
static char send_time_buf[10];
static char ack_time_buf[10];

// for some reason if I use maximum inbox/outbox I can get, after sending the system will just crash, so save some buffer
#define safety_buffer 40

static char onwatch_num_records[4];
static char sent_num_records[4];
static char ack_num_records[4];

static bool init_done = false;

static uint32_t inbox_size = 0;
static uint32_t outbox_size = 0;

// minutes to boost bluetooth response
#define bluetooth_high_durition 2

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_14;
static GBitmap *s_res_image_action_wireless;
static GBitmap *s_res_image_action_reset;
static TextLayer *s_textlayer_1;
static TextLayer *t_lastsend_time;
static TextLayer *t_lastsend_records;
static TextLayer *t_lastsend_status;
static TextLayer *s_textlayer_2;
static TextLayer *t_ack_time;
static TextLayer *s_textlayer_3;
static TextLayer *s_textlayer_4;
static TextLayer *t_num_records;
static TextLayer *s_textlayer_5;
static TextLayer *s_textlayer_6;
static TextLayer *s_textlayer_7;
static TextLayer *t_lastack_records;
static ActionBarLayer *s_actionbarlayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, false);
  #endif
  
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_image_action_wireless = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_WIRELESS);
  s_res_image_action_reset = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_RESET);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(1, 0, 56, 20));
  text_layer_set_text(s_textlayer_1, "Last Sent:");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // t_lastsend_time
  t_lastsend_time = text_layer_create(GRect(36, 20, 83, 20));
  text_layer_set_text(t_lastsend_time, " ");
  text_layer_set_font(t_lastsend_time, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_lastsend_time);
  
  // t_lastsend_records
  t_lastsend_records = text_layer_create(GRect(35, 40, 24, 20));
  text_layer_set_text(t_lastsend_records, " ");
  text_layer_set_font(t_lastsend_records, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_lastsend_records);
  
  // t_lastsend_status
  t_lastsend_status = text_layer_create(GRect(60, 40, 60, 20));
  text_layer_set_text(t_lastsend_status, " ");
  text_layer_set_font(t_lastsend_status, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_lastsend_status);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(1, 60, 56, 20));
  text_layer_set_text(s_textlayer_2, "Last Ack:");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
  
  // t_ack_time
  t_ack_time = text_layer_create(GRect(36, 80, 83, 20));
  text_layer_set_text(t_ack_time, " ");
  text_layer_set_font(t_ack_time, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_ack_time);
  
  // s_textlayer_3
  s_textlayer_3 = text_layer_create(GRect(1, 100, 35, 20));
  text_layer_set_text(s_textlayer_3, "# rec.");
  text_layer_set_font(s_textlayer_3, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_3);
  
  // s_textlayer_4
  s_textlayer_4 = text_layer_create(GRect(1, 125, 78, 20));
  text_layer_set_text(s_textlayer_4, "# saved rec. :");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_4);
  
  // t_num_records
  t_num_records = text_layer_create(GRect(80, 125, 36, 20));
  text_layer_set_text(t_num_records, " ");
  text_layer_set_font(t_num_records, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_num_records);
  
  // s_textlayer_5
  s_textlayer_5 = text_layer_create(GRect(1, 20, 35, 20));
  text_layer_set_text(s_textlayer_5, "Time");
  text_layer_set_font(s_textlayer_5, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_5);
  
  // s_textlayer_6
  s_textlayer_6 = text_layer_create(GRect(1, 40, 35, 20));
  text_layer_set_text(s_textlayer_6, "# rec. ");
  text_layer_set_font(s_textlayer_6, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_6);
  
  // s_textlayer_7
  s_textlayer_7 = text_layer_create(GRect(1, 80, 35, 20));
  text_layer_set_text(s_textlayer_7, "Time");
  text_layer_set_font(s_textlayer_7, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_7);
  
  // t_lastack_records
  t_lastack_records = text_layer_create(GRect(35, 100, 40, 20));
  text_layer_set_text(t_lastack_records, " ");
  text_layer_set_font(t_lastack_records, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_lastack_records);
  
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorBlack);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_image_action_wireless);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_image_action_reset);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(t_lastsend_time);
  text_layer_destroy(t_lastsend_records);
  text_layer_destroy(t_lastsend_status);
  text_layer_destroy(s_textlayer_2);
  text_layer_destroy(t_ack_time);
  text_layer_destroy(s_textlayer_3);
  text_layer_destroy(s_textlayer_4);
  text_layer_destroy(t_num_records);
  text_layer_destroy(s_textlayer_5);
  text_layer_destroy(s_textlayer_6);
  text_layer_destroy(s_textlayer_7);
  text_layer_destroy(t_lastack_records);
  action_bar_layer_destroy(s_actionbarlayer_1);
  gbitmap_destroy(s_res_image_action_wireless);
  gbitmap_destroy(s_res_image_action_reset);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static void my_init();

void show_w_communication(void) {
  APP_LOG(APP_LOG_LEVEL_INFO," #### showing window COMMUNICATION");
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  my_init();
}

void hide_w_communication(void) {
  window_stack_remove(s_window, true);
}

/***************************** communication functions *********************************/


void w_communication_update_record_num() {
	snprintf(onwatch_num_records, sizeof(onwatch_num_records), "%d", data_store_usage_count());
	text_layer_set_text(t_num_records, onwatch_num_records);
};


void messages_inbox_received(DictionaryIterator *iterator, void *context)  {
	APP_LOG(APP_LOG_LEVEL_INFO,"Message inbox received, size %lu", dict_size(iterator));
	// first record ack time
	time(&time_now);
	strftime(ack_time_buf, sizeof(ack_time_buf), "%H:%M:%S", localtime(&time_now));
	text_layer_set_text(t_ack_time, ack_time_buf);	
	
	Tuple *tuple = dict_read_first(iterator);
	char* ack_str;
	while (tuple) {
	  uint8_t tl = tuple->length;
	  APP_LOG(APP_LOG_LEVEL_INFO, "tuple: %li -> type %u length %u", tuple->key, tuple->type, tl);
	  switch (tuple->key) {
	    case 42:
			ack_str = tuple->value->cstring;
			if (tl > 1) {
				for (uint8_t i=0; i<(tl-1); i++) {
					// APP_LOG(APP_LOG_LEVEL_INFO, "[%d] idx: %d", i, (uint8_t)(ack_str[i])-1);
					data_free((uint8_t)(ack_str[i])-1);
				};
			};
		snprintf(ack_num_records, sizeof(ack_num_records), "%d", (tl-1));
		text_layer_set_text(t_lastack_records, ack_num_records);
	    break;
	  }
	  tuple = dict_read_next(iterator);
	}
	w_communication_update_record_num();
}

void messages_inbox_dropped(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_WARNING, "Message inbox dropped reason %d", reason);
}

void messages_outbox_sent(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Message sent / reply received");
  text_layer_set_text(t_lastsend_status, "Sent");
}
  
void messages_outbox_failed(DictionaryIterator *iterator, AppMessageResult reason, void *context){
  switch (reason) {
         case APP_MSG_SEND_TIMEOUT: text_layer_set_text(t_lastsend_status, "T-out"); break;
         case APP_MSG_SEND_REJECTED: text_layer_set_text(t_lastsend_status, "Rejected"); break;
         case APP_MSG_NOT_CONNECTED: text_layer_set_text(t_lastsend_status, "No conn"); break;
         case APP_MSG_APP_NOT_RUNNING: text_layer_set_text(t_lastsend_status, "App Close"); break;
         case APP_MSG_BUSY: text_layer_set_text(t_lastsend_status, "Busy"); break;
         case APP_MSG_OUT_OF_MEMORY: text_layer_set_text(t_lastsend_status, "Mem-out"); break;
         default: text_layer_set_text(t_lastsend_status, "No conn"); break;
	 };
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Message outbox failed, reason %d", reason);
}

void messages_init() {
  if (init_done) return;
 // first register callbacks
  app_message_register_inbox_received(messages_inbox_received);
  app_message_register_inbox_dropped(messages_inbox_dropped);
  app_message_register_outbox_sent(messages_outbox_sent);
  app_message_register_outbox_failed(messages_outbox_failed);
  // open message with maximum size
  inbox_size = app_message_inbox_size_maximum() - safety_buffer;
  outbox_size = app_message_outbox_size_maximum() - safety_buffer;
  if (app_message_open(inbox_size, outbox_size) != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Open Message Failed");
    return;
  }  
  APP_LOG(APP_LOG_LEVEL_INFO, "Open message OK, inbox size %lu outbox size %lu", inbox_size, outbox_size);
  init_done = true;
};	



// to send one batch of records to phone
// data protocol
// 0 -> number of records
// n*4+1 -> storage index (uint8)
// n*4+2 -> time (uint32)
// n*4+3 -> durition (uint16)
// n*4+4 -> what (string)

static void send_communication_handler(ClickRecognizerRef recognizer, void *context) {
	// first record sending time
	time(&time_now);
	strftime(send_time_buf, sizeof(send_time_buf), "%H:%M:%S", localtime(&time_now));
	text_layer_set_text(t_lastsend_time, send_time_buf);
	
	// first check if there is a record
	uint8_t remaining_records = data_store_usage_count();
	if (remaining_records == 0) {
	  return;
	};
	// initialize dictionary
	DictionaryIterator* dic_iterator;
	if (app_message_outbox_begin(&dic_iterator) != APP_MSG_OK) {
	APP_LOG(APP_LOG_LEVEL_ERROR, "Begin Message Outbox Failed");
	return;
	}
	
	// start packing
	uint8_t records_packed = 0;
	uint8_t idx = data_seek_valid(0);
	uint16_t buffer_used = 9; // according to doc, buffer header 1 byte, and I also need to reserve the last triplet, key 0 length 1 byte (header 7 bytes)
	
	while (true) {
		// first calculate if there should be enough room
		buffer_used = buffer_used + dict_calc_buffer_size(
			4, // 4 tuplets
			1, // idx 1 byte
			4, // time 4 bytes
			2, // durition 2 bytes
			what_list_length_short_name[data_store[idx].what_index]); // what name, and then remove the buffer header as it's already calculated
		// APP_LOG(APP_LOG_LEVEL_INFO, "checking space, if pack record %d buffer size would be %d", (records_packed + 1), buffer_used);
		if (buffer_used  >= outbox_size) { // header size 7 + 1 byte record number = 8, for key 0
			break;
		};
		time_t time = data_store[idx].time;
		uint16_t durition = data_store[idx].durition;
		char* what = what_list[data_store[idx].what_index]->short_name;
		// #ifdef DEBUG_CHECK_MORE
		//	strftime(send_time_buf, sizeof(send_time_buf), "%d.%m.%y %H:%M", localtime(&(time)));
		//	APP_LOG(APP_LOG_LEVEL_INFO, "packing record %d [%d, time(%u, %s) %d, %s]", records_packed, idx, (unsigned int)time, send_time_buf, durition, what);	
		// #endif
	
		if (dict_write_uint8(dic_iterator,records_packed*4+1,idx) == DICT_OK) {
			if (dict_write_uint32(dic_iterator, records_packed*4+2, (unsigned int)time) == DICT_OK) {
				if (dict_write_uint16(dic_iterator, records_packed*4+3, durition) == DICT_OK) {
					if (dict_write_cstring(dic_iterator, records_packed*4+4, what) == DICT_OK) {
						records_packed += 1;
						APP_LOG(APP_LOG_LEVEL_INFO, "packing ALL OK for record %d",records_packed);
						if (records_packed < remaining_records) {
							// prepare next
							idx = data_seek_valid(idx + 1);
							continue;
						}; 
					};
				};
			};
		};
		// something wrong... mostly dictionary full, or maybe we just packed everything
		break;
	};

	// pack complete, write number of records, and prepare to send them off
	DictionaryResult res = dict_write_uint8(dic_iterator, 0, records_packed);
	uint32_t final_size = dict_write_end(dic_iterator);
	APP_LOG(APP_LOG_LEVEL_INFO, "Packed %d records, size (final_size %lu dict_size %lu)", records_packed, final_size, dict_size(dic_iterator));
	if (res != DICT_OK) {
		APP_LOG(APP_LOG_LEVEL_INFO, "Last write failed, reason %d, not sending", res);
		return;
	};
	// send
	APP_LOG(APP_LOG_LEVEL_INFO, "Last write checked OK, sending");
	snprintf(sent_num_records, sizeof(sent_num_records), "%d", records_packed);
	text_layer_set_text(t_lastsend_records, sent_num_records);
	if (app_message_outbox_send() == APP_MSG_OK) {
	  APP_LOG(APP_LOG_LEVEL_INFO, "Sending OK"); 
	  // boost bluetooth response and set timer to lower back
	  wakeup_schedule_next_in_minutes(bluetooth_high_durition, BluetoothHighTimeOut);
	  app_comm_set_sniff_interval(SNIFF_INTERVAL_REDUCED);
	} else {
		APP_LOG(APP_LOG_LEVEL_INFO, "Sending FAILED");
	};
}

void reset_handler_after_confirmation(bool confirmed){
	if (confirmed) {
		// completely reset everything
		data_clear();
		running_state_clear();
		wakeup_state_clear();
		// and exit everything
		window_stack_pop_all(false);
	};
};

static void reset_handler(ClickRecognizerRef recognizer, void *context) {
	// complete reset, first bring up confirmation
	confirmation_ask("RESET! Sure?", *reset_handler_after_confirmation);
};

// subscribe click events
void w_communication_click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, *send_communication_handler);
  window_long_click_subscribe(BUTTON_ID_DOWN, 0, *reset_handler, NULL);
};

static void my_init() {
	messages_init();
	w_communication_update_record_num();
	window_set_click_config_provider(s_window, *w_communication_click_config_provider);
};






