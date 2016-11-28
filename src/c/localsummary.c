#include <pebble.h>
#include "localsummary.h"
#include "what.h"
#include "data.h"

struct LocalSummaryDataStorage {
	time_t local_summary_today;
	struct LocalSummaryType local_summarys[WHAT_LIST_LENGTH];
};

struct LocalSummaryDataStorage local_summary_store;
static bool local_summary_data_loaded = false;

time_t starts_of_today() {
	time_t time_now;
	time(&time_now);
	struct tm *time_now_local = localtime(&time_now);	
	return time_now - 3600*(time_now_local->tm_hour) - 60*(time_now_local->tm_min) - (time_now_local->tm_sec);
};

// save local summary status
void local_summary_save () {
  persist_write_data(KEY_LOCAL_SUMMARY, &local_summary_store, sizeof(local_summary_store));
  local_summary_data_loaded = true;
  APP_LOG(APP_LOG_LEVEL_INFO, "Local summary store (l=%u) saved ", sizeof(local_summary_store));
};

// reset local_summary_today and all minutes to zero
void local_summary_reset() {
	local_summary_store.local_summary_today = starts_of_today();
	for (uint8_t i=0; i < WHAT_LIST_LENGTH; i++) {
		local_summary_store.local_summarys[i].one_100_hours_yesterday = 0;
		local_summary_store.local_summarys[i].one_100_hours_today = 0;					
	};
	local_summary_save();
};

// swap out yesterday and today to yesterday
void local_summary_swap() {
	local_summary_store.local_summary_today = starts_of_today();
	for (uint8_t i=0; i < WHAT_LIST_LENGTH; i++) {
		local_summary_store.local_summarys[i].one_100_hours_yesterday = local_summary_store.local_summarys[i].one_100_hours_today;
		local_summary_store.local_summarys[i].one_100_hours_today = 0;					
	};
	local_summary_save();
};

// check a summary, if 
// 	  now - today <= 24 hour, still today & no change
//    now - today > 24 hour but <= 48 hour (no more today, yesterday) -> swap out 
//    now - today > 48 hour, reset
void check_local_summary() {
	if (!local_summary_data_loaded)
		local_summary_load();
	time_t time_now;
	time(&time_now);
	time_t tdiff = time_now - local_summary_store.local_summary_today;
	APP_LOG(APP_LOG_LEVEL_INFO, "Local Summary check local status, Time now: %ld, time diff %ld", time_now, tdiff);
	if (tdiff < SECONDS_PER_DAY)
		return; // nothing to do
	if (tdiff < 2 * SECONDS_PER_DAY) { // swap out		
		local_summary_swap();
	} else {
		local_summary_reset();
	};
};

// clear 
void local_summary_clear() {
  if (persist_exists(KEY_LOCAL_SUMMARY)) {
    persist_delete(KEY_LOCAL_SUMMARY);
    APP_LOG(APP_LOG_LEVEL_INFO, "Local Summary cleared.");
  };
}

// load local summary, or kick off if not found
void local_summary_load () {
	local_summary_data_loaded = true;
	APP_LOG(APP_LOG_LEVEL_INFO,"Loadding local summary store...");
	if (persist_exists(KEY_LOCAL_SUMMARY)) {
		persist_read_data(KEY_LOCAL_SUMMARY, &local_summary_store, sizeof(local_summary_store));
		// and check
		check_local_summary();
		return;
	}; 
	// otherwise kick off
	local_summary_reset();				
};

struct LocalSummaryType* get_local_summary_by_what_index(uint8_t index) {
	check_local_summary();
	if (index < WHAT_LIST_LENGTH) {
		return &local_summary_store.local_summarys[index];
	};
	// SHOULD NOT BE HERE!!
	APP_LOG(APP_LOG_LEVEL_ERROR,"get_local_summary_by_what_index exceeds boundary"); 
	return 0;
};

void commit_local_summary_by_what_index(uint16_t time_by_1_100th_hour, uint8_t index) {
	check_local_summary();
	if (index < WHAT_LIST_LENGTH) {	
		local_summary_store.local_summarys[index].one_100_hours_today += time_by_1_100th_hour;
		local_summary_save();
		return;
	};
	APP_LOG(APP_LOG_LEVEL_ERROR,"commit_local_summary_by_what_index exceeds boundary (index=%u)", index); 
};
