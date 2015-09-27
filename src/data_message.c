#include <pebble.h>
#include "data_message.h"
  
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
