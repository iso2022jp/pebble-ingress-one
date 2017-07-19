/* This software is released under the MIT License, see LICENSE */

#pragma once
#include <pebble.h>

// Application settings
typedef struct {

	GColor backgroundColor;
	GColor foregroundColor;
	uint8_t showSecondHand;
	GColor secondHandColor;
	
	int32_t detectedTimeZoneOffset; // special
	
	uint8_t showCyclePanel;
	GColor checkpointColor;
	GColor locationMarkerColor;
	GColor locationMarkerBorderColor;

	uint8_t showStatusPanel;
	GColor powerReserveColor;
	uint8_t _reserved4;
	uint8_t _reserved5;

	uint8_t showSubclock;
	uint8_t _reserved6;
	uint8_t _reserved7;
	uint8_t _reserved8;

	int32_t subclockTimeZoneOffset;

// 	uint8_t showSecondOnTap;

} __attribute__ ((packed)) Config; // saving space (limit PERSIST_DATA_MAX_LENGTH in persistent API)

typedef void (* ConfigChangedHandler)(const Config *config);

void config_init(ConfigChangedHandler handler);
void config_deinit(void);
bool config_update(DictionaryIterator *iter, void *context);

const Config* config_get(void);
