#include <pebble.h>
#include "w_communication.h"
#include "data.h"
#include "what.h"
#include "running_state.h"
#include "wakeup.h"

  // text buffers
static char send_time_buf[50];
static char num_records[4];

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
	APP_LOG(APP_LOG_LEVEL_INFO,"Message inbox received");
	Tuple *tuple = dict_read_first(iterator);
	while (tuple) {
	  APP_LOG(APP_LOG_LEVEL_INFO, "tuple: %li -> type %u length %u", tuple->key, tuple->type, tuple->length);
	  int slot_num;
	  switch (tuple->key) {
	    case 0:
			slot_num = (int)tuple->value->int32;
			APP_LOG(APP_LOG_LEVEL_INFO, "key 0, slot = %d", slot_num);
			// should remove slot
	      break;
	    case 4:
			APP_LOG(APP_LOG_LEVEL_INFO, "key 4, status = %s", tuple->value->cstring);
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
 // first register callbacks
  app_message_register_inbox_received(messages_inbox_received);
  app_message_register_inbox_dropped(messages_inbox_dropped);
  app_message_register_outbox_sent(messages_outbox_sent);
  app_message_register_outbox_failed(messages_outbox_failed);
  // open message with minimum size
  if (app_message_open(APP_MESSAGE_INBOX_SIZE_MINIMUM, APP_MESSAGE_OUTBOX_SIZE_MINIMUM) != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Open Message Failed");
    return;
  }  
};	

void w_communication_update_record_num() {
	snprintf(num_records, sizeof(num_records), "%d", data_store_usage_count());
	text_layer_set_text(t_num_records, num_records);
};

// send one record
bool message_open_send(uint8_t store_index, time_t time, uint16_t durition, char* what) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Sending record [%d, %u, %d, %s] to watch", store_index, (unsigned int)time, durition, what);	
  DictionaryIterator* dic_iterator;
  if (app_message_outbox_begin(&dic_iterator) != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Begin Message Outbox Failed");
    return false;
  }
  // pack data into dict
  dict_write_uint8(dic_iterator,0,store_index);
  dict_write_uint32(dic_iterator, 1, (unsigned int)time);
  dict_write_uint16(dic_iterator, 2, durition);
  dict_write_cstring(dic_iterator, 3, what);
  dict_write_end(dic_iterator);
  // send
  if (app_message_outbox_send() == APP_MSG_OK) {
	  return true;
  };
  return false;
}

// to send one record to phone
static void send_communication_handler(ClickRecognizerRef recognizer, void *context) {
  // first check out a record
  if (data_store_usage_count() == 0) {
	  return;
  };
  uint8_t idx = data_seek_valid();
  strftime(send_time_buf, sizeof(send_time_buf), "%d.%m.%y %H:%M", localtime(&(data_store[idx].time)));
  text_layer_set_text(t_time, send_time_buf);
  text_layer_set_text(t_what, (*what_list[data_store[idx].what_index]).short_name);
  if (message_open_send(idx, data_store[idx].time, data_store[idx].durition, (*what_list[data_store[idx].what_index]).short_name)) {
	  text_layer_set_text(t_send_status, "Sending");
	  // boost bluetooth response and set timer to lower back
	  wakeup_schedule_next_in_seconds(bluetooth_high_durition, BluetoothHighTimeOut);
	  app_comm_set_sniff_interval(SNIFF_INTERVAL_REDUCED);
	  APP_LOG(APP_LOG_LEVEL_INFO, "send communication - idx %u time %s", idx, send_time_buf);
  } else {
	  text_layer_set_text(t_send_status, "Failed");
  };
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






