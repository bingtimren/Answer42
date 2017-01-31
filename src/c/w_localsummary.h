#pragma once
#include <pebble.h>  
#include "data.h"

struct BriefSummary {
	uint16_t today;
	uint16_t yesterday;
};


uint16_t localsummary_sum_whatid_total_durition(struct TimeRecordDayStore *dayStore, uint8_t what_index);

uint8_t localsummary_previous_slot(uint8_t current);

bool localsummary_load_previous(uint8_t current);
		
void get_brief_summary_from_whatid(uint8_t what_id, struct BriefSummary *result);
	
void show_w_localsummary(void);

void hide_w_localsummary(void);
