#include <pebble.h>
#include "w_communication.h"

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

void show_w_communication(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_w_communication(void) {
  window_stack_remove(s_window, true);
}

/***************************** communication functions *********************************/




void messages_inbox_received(DictionaryIterator *iterator, void *context)  {
  APP_LOG(APP_LOG_LEVEL_INFO,"Message inbox received");
}

void messages_inbox_dropped(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_WARNING, "Message inbox dropped reason %d", reason);
}

void messages_outbox_sent(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Message sent / reply received");
}
  
void messages_outbox_failed(DictionaryIterator *iterator, AppMessageResult reason, void *context){
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

// send one record
bool messsages_open_send(int store_index, char* time, char* durition, char* what) {
  DictionaryIterator* dic_iterator;
  if (app_message_outbox_begin(&dic_iterator) != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Begin Message Outbox Failed");
    return false;
  }
  // pack data into dict
  dict_write_int(dict_iterator,0,store_index);
  dict_write_cstring(dic_iterator, 1, time);
  dict_write_cstring(dic_iterator, 2, durition);
  dict_write_cstring(dic_iterator, 3, what);
  dict_write_end(dic_iterator);
  // send
  app_message_outbox_send();
  return true;
}

void messages_pack

