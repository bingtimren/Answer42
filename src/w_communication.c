#include <pebble.h>
#include "w_communication.h"
#include "data.h"
#include "what.h"
#include "running_state.h"
#include "wakeup.h"
#include "debug.h"

  // text buffers
#ifdef DEBUG_CHECK_MORE
static char send_time_buf[50];
#endif
// for some reason if I use maximum inbox/outbox I can get, after sending the system will just crash, so save some buffer
#define safety_buffer 70

static char num_records[4];

static bool init_done = false;

static uint32_t inbox_size = 0;
static uint32_t outbox_size = 0;
#define outbuffer_safety_gap 20
// seconds to boost bluetooth response
#define bluetooth_high_durition 5

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_14;
static TextLayer *s_textlayer_1;
static TextLayer *t_time;
static TextLayer *t_what;
static TextLayer *t_send_status;
static TextLayer *s_textlayer_2;
static TextLayer *t_ack_time;
static TextLayer *s_textlayer_3;
static TextLayer *t_ack_status;
static TextLayer *s_textlayer_4;
static TextLayer *t_num_records;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, false);
  #endif
  
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(1, 10, 56, 20));
  text_layer_set_text(s_textlayer_1, "Last Send:");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // t_time
  t_time = text_layer_create(GRect(60, 10, 83, 20));
  text_layer_set_text(t_time, "12.31 13:23");
  text_layer_set_font(t_time, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_time);
  
  // t_what
  t_what = text_layer_create(GRect(1, 30, 110, 20));
  text_layer_set_text(t_what, "what is done");
  text_layer_set_font(t_what, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_what);
  
  // t_send_status
  t_send_status = text_layer_create(GRect(115, 30, 30, 20));
  text_layer_set_text(t_send_status, "Fail");
  text_layer_set_font(t_send_status, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_send_status);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(1, 60, 56, 20));
  text_layer_set_text(s_textlayer_2, "Last Ack:");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
  
  // t_ack_time
  t_ack_time = text_layer_create(GRect(60, 60, 83, 20));
  text_layer_set_text(t_ack_time, "12:31 13:23");
  text_layer_set_font(t_ack_time, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_ack_time);
  
  // s_textlayer_3
  s_textlayer_3 = text_layer_create(GRect(1, 80, 110, 20));
  text_layer_set_text(s_textlayer_3, "what is done");
  text_layer_set_font(s_textlayer_3, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_3);
  
  // t_ack_status
  t_ack_status = text_layer_create(GRect(115, 80, 30, 20));
  text_layer_set_text(t_ack_status, "Fail");
  text_layer_set_font(t_ack_status, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_ack_status);
  
  // s_textlayer_4
  s_textlayer_4 = text_layer_create(GRect(1, 110, 107, 20));
  text_layer_set_text(s_textlayer_4, "#Records on Watch:");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_4);
  
  // t_num_records
  t_num_records = text_layer_create(GRect(110, 110, 30, 20));
  text_layer_set_text(t_num_records, "999");
  text_layer_set_font(t_num_records, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)t_num_records);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(t_time);
  text_layer_destroy(t_what);
  text_layer_destroy(t_send_status);
  text_layer_destroy(s_textlayer_2);
  text_layer_destroy(t_ack_time);
  text_layer_destroy(s_textlayer_3);
  text_layer_destroy(t_ack_status);
  text_layer_destroy(s_textlayer_4);
  text_layer_destroy(t_num_records);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static void my_init();

void show_w_communication(void) {
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

void messages_inbox_received(DictionaryIterator *iterator, void *context)  {
	APP_LOG(APP_LOG_LEVEL_INFO,"Message inbox received, size %lu", dict_size(iterator));
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
					APP_LOG(APP_LOG_LEVEL_INFO, "[%d] idx: %d", i, (uint8_t)(ack_str[i])-1);
					data_free((uint8_t)(ack_str[i])-1);
				};
			};
	      break;
	  }
	  tuple = dict_read_next(iterator);
	}
}

void messages_inbox_dropped(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_WARNING, "Message inbox dropped reason %d", reason);
}

void messages_outbox_sent(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Message sent / reply received");
  text_layer_set_text(t_send_status, "Sent");
}
  
void messages_outbox_failed(DictionaryIterator *iterator, AppMessageResult reason, void *context){
  text_layer_set_text(t_send_status, "Failed");
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

void w_communication_update_record_num() {
	snprintf(num_records, sizeof(num_records), "%d", data_store_usage_count());
	text_layer_set_text(t_num_records, num_records);
};



// to send one batch of records to phone
// data protocol
// 0 -> number of records
// n*4+1 -> storage index (uint8)
// n*4+2 -> time (uint32)
// n*4+3 -> durition (uint16)
// n*4+4 -> what (string)

static void send_communication_handler(ClickRecognizerRef recognizer, void *context) {
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
		APP_LOG(APP_LOG_LEVEL_INFO, "checking space, if pack record %d buffer size would be %d", (records_packed + 1), buffer_used);
		if (buffer_used  >= outbox_size) { // header size 7 + 1 byte record number = 8, for key 0
			break;
		};
		time_t time = data_store[idx].time;
		uint16_t durition = data_store[idx].durition;
		char* what = what_list[data_store[idx].what_index]->short_name;
		#ifdef DEBUG_CHECK_MORE
			strftime(send_time_buf, sizeof(send_time_buf), "%d.%m.%y %H:%M", localtime(&(time)));
			APP_LOG(APP_LOG_LEVEL_INFO, "packing record %d [%d, time(%u, %s) %d, %s]", records_packed, idx, (unsigned int)time, send_time_buf, durition, what);	
		#endif
	
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
	if (app_message_outbox_send() == APP_MSG_OK) {
	  APP_LOG(APP_LOG_LEVEL_INFO, "Sending OK"); 
	  // boost bluetooth response and set timer to lower back
	  wakeup_schedule_next_in_seconds(bluetooth_high_durition, BluetoothHighTimeOut);
	  app_comm_set_sniff_interval(SNIFF_INTERVAL_REDUCED);
	} else APP_LOG(APP_LOG_LEVEL_INFO, "Sending FAILED");
}

// subscribe click events
void w_communication_click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, *send_communication_handler);
};

static void my_init() {
	messages_init();
	w_communication_update_record_num();
	window_set_click_config_provider(s_window, *w_communication_click_config_provider);
};






