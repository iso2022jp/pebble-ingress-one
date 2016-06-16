/* This software is released under the MIT License, see LICENSE */

#pragma once
#include <pebble.h>

// max PERSIST_DATA_MAX_LENGTH bytes
typedef struct Config {

	GColor backgroundColor;
	GColor foregroundColor;
	uint8_t showSecondHand;
	GColor secondHandColor;
	
	int32_t detectedTimeZoneOffset; // special
	
	uint8_t showCyclePanel;
	GColor checkpointColor;
	uint8_t _reserved1;
	uint8_t _reserved2;

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

} __attribute__ ((packed)) Config;

typedef void (* ConfigChangedHandler)(const Config *config);

void config_init(ConfigChangedHandler handler);
void config_deinit(void);
bool config_update(DictionaryIterator *iter, void *context);

const Config* config_get(void);